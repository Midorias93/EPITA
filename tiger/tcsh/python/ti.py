#! /usr/bin/env python3

# Tiger interpreter.

# Execute a Tiger program, using the Tiger Compiler through
# TCSH/Python and a supporting back-end environment (HAVM, Nolimips,
# or an IA-32 environment).
#
# This script needs a complete, dynamically-compiled Tiger compiler
# (with all its modules) to work.  The Tree back-end needs a `havm'
# binary to be available in the PATH; the MIPS back-end, a `nolimips'
# binary; and the IA-32 back-end, an IA-32 execution environment.

from __future__ import annotations
from collections.abc import Callable
from typing import List, Optional, Tuple, TypeVar, Union

import optparse
import tempfile
import subprocess

import os
import sys
import re

import tc


# Subclass to redefine error method (for exit code to be 1).
class TiOptionParser(optparse.OptionParser):
    def error(self, msg: str) -> None:
        self.print_usage(sys.stderr)
        self.exit(1, "%s: error: %s\n" % (self.get_prog_name(), msg))


T = TypeVar("T")


def wrap_step(
    modules: List[str] = [],
    require: Optional[str] = None,
    backend: Optional[tc.BackendType] = None,
) -> Callable[[Callable[[TiExecutor], T]], Callable[[TiExecutor], Optional[T]]]:
    """
    Decorator for steps of TiExecutor, execute the require step if needed
    """

    def check_wrap_step(
        f: Callable[[TiExecutor], T]
    ) -> Callable[[TiExecutor], Optional[T]]:
        def new_f(self: TiExecutor) -> Optional[T]:
            if self.debug:
                print(f"CALL  {f.__name__} [{self.backend}]")
            if backend and self.backend != backend:
                self.backend = backend
                if hasattr(self, "__step"):
                    delattr(self, "__step")
                    self._rm_asm()
                    self._rm_llvm()
                    self.data = TiExecutor.TiExecution()
            if require and not hasattr(self, require):
                raise RuntimeError(require + " step must exist")
            if self.data.error:
                return None
            hasstep = hasattr(self, "__step")
            if require and (not hasstep or hasstep and not self.__step == require):
                getattr(self, require)()
                if self.data.error:
                    return None
            for mod in modules:
                if not tc.has(mod):
                    msg = f"Module {mod} is not available to execute {f.__name__} step\nCheck your install of tc"
                    self.data.error = (-1, msg)
                    print(msg, file=sys.stderr)
                    if self.exit_on_error:
                        sys.exit(1)
                    return None
            if self.debug:
                print(f"ENTER {f.__name__} [{self.backend}]")
            res = f(self)
            if self.debug:
                print(f"EXIT  {f.__name__} [{self.backend}]")
            self.__step = f.__name__
            return res

        new_f.__doc__ = f"Ast {f.__name__} step"
        if require:
            new_f.__doc__ += f"\nRequire {require} step, execute it otherwise"
        if modules and len(modules):
            new_f.__doc__ += "\nRequire {} tc modules".format(", ".join(modules))
        new_f.__name__ = f.__name__
        return new_f

    return check_wrap_step


class TiExecutor:
    class TiExecution:
        ast: Optional[tc.ast.ChunkList] = None
        error: Optional[Tuple[int, str]] = None
        fragments: Optional[tc.tree.Fragments] = None
        lir_fragments: Optional[tc.assem.Fragments] = None
        target: Optional[Union[tc.target.Ia32Target, tc.target.MipsTarget]] = None
        tempmap: Optional[tc.temp.TempMap] = None
        result: Optional[str] = None
        llvm: Optional[str] = None

        def __str__(self) -> str:
            res = ""

            def truncate(msg: str) -> str:
                return msg if not msg or len(msg) < 100 else msg[:100] + "..."

            for e in dir(self):
                if not e.startswith("_"):
                    res += e + ": " + truncate(repr(getattr(self, e))) + "\n"
            return res

    def __init__(
        self,
        filename: str,
        backend: tc.BackendType = tc.BackendType.mips,
        exit_on_error: bool = True,
        get_result: bool = False,
        rename: bool = True,
        desugar: bool = True,
        object_enabled: bool = True,
        debug: bool = False,
    ):
        self.filename = filename
        self.backend = tc.BackendType(backend)
        self.exit_on_error = exit_on_error
        self.get = get_result
        self.rename_enabled = rename
        self.desugar_enabled = desugar
        self.object_enabled = object_enabled
        self.debug = debug
        self.data = TiExecutor.TiExecution()

    def error_message(self) -> str:
        if not self.data.error:
            return ""
        status, message = self.data.error
        statusMessage = tc.misc.error.error_type_message()[status]
        if re.match(r"(.*/)?tmp\w{8}\.tig$", self.filename):
            if message.startswith(self.filename + ":"):
                message = message.replace(self.filename + ":", "")
            message = " " + message
        else:
            message = "\n" + message
        return str(status) + " " + statusMessage + ":" + message

    def throw_error(self, e: Exception) -> None:
        self.__step = "error"
        self.data.error = e.args
        status, message = e.args
        if self.exit_on_error:
            print(message, file=sys.stderr)
            sys.exit(status)
        else:
            print(self.error_message(), end="", file=sys.stderr)

    def _rm_attribute_file(self, arg: str) -> None:
        if hasattr(self, arg):
            os.unlink(getattr(self, arg))
            delattr(self, arg)

    def _rm_attribute_dir(self, arg: str) -> None:
        if hasattr(self, arg):
            os.rmdir(getattr(self, arg))
            delattr(self, arg)

    def _rm_attribute_temp(self, arg: str) -> None:
        if hasattr(self, arg):
            os.unlink(getattr(self, arg).name)
            delattr(self, arg)

    def _run_cmd(self, *cmd: str) -> Optional[str]:
        if self.get:
            proc = subprocess.run(cmd, capture_output=True)
            self.data.result = proc.stdout.decode("utf-8")
        else:
            os.system(" ".join(cmd))
            self.data.result = None
        return self.data.result

    @wrap_step(["misc", "parse"])
    def parse(self) -> Optional[tc.ast.ChunkList]:
        lib = tc.misc.file_library()
        try:
            self.data.ast = tc.parse.parse("builtin", self.filename, lib)
        except Exception as e:
            return self.throw_error(e)
        return self.data.ast

    @wrap_step(["bind"], "parse")
    def bind(self) -> Optional[tc.ast.ChunkList]:
        try:
            if self.object_enabled and tc.has("object"):
                tc.object.bind(self.data.ast).exit_on_error()
            else:
                tc.bind.bind(self.data.ast).exit_on_error()
        except Exception as e:
            return self.throw_error(e)
        return self.data.ast

    @wrap_step([], "bind")
    def rename(self) -> Optional[tc.ast.ChunkList]:
        if (
            self.rename_enabled
            and tc.has("bind")
            and not self.object_enabled
            and not tc.has("object")
        ):
            tc.bind.rename(self.data.ast)
        return self.data.ast

    @wrap_step(["type"], "rename")
    def type(self) -> Optional[tc.ast.ChunkList]:
        try:
            if self.object_enabled and tc.has("object"):
                tc.object.types_check(self.data.ast).exit_on_error()
            else:
                tc.type.types_check(self.data.ast).exit_on_error()
        except Exception as e:
            return self.throw_error(e)
        return self.data.ast

    @wrap_step([], "type")
    def object_desugar(self) -> Optional[tc.ast.ChunkList]:
        if self.object_enabled and tc.has("object"):
            class_names = tc.object.rename(self.data.ast)
            self.data.ast = tc.object.desugar(self.data.ast, class_names)
        return self.data.ast

    @wrap_step([], "object_desugar")
    def desugar(self) -> Optional[tc.ast.ChunkList]:
        if self.desugar_enabled and tc.has("desugar"):
            self.data.ast = tc.desugar.desugar(self.data.ast, True, True)
        return self.data.ast

    def frontend_run(self) -> None:
        """Run parse, bind and type depending of TC step"""
        self.parse()

        self.bind()
        self.rename()
        self.type()
        self.object_desugar()
        self.desugar()
        return None

    def backend_exec(self) -> Optional[str]:
        """execute backends: llvm, hir, lir, mips and ia32"""
        self.frontend_run()
        return None

    def backend_run(self) -> None:
        self.get = False
        self.backend_exec()

    def backend_get(self) -> Optional[str]:
        self.get = True
        return self.backend_exec()


def process_file(
    filename: str, backend: tc.BackendType = tc.BackendType.mips, **kwargs
) -> None:
    executor = TiExecutor(filename, backend=backend, **kwargs)
    executor.backend_run()


if __name__ == "__main__":
    # Parser creation.
    parser = TiOptionParser(
        """%prog [options] file.tig
    Execute a Tiger program, using a given back-end."""
    )
    parser.add_option(
        "-b",
        "--back-end",
        metavar="BACKEND",
        dest="backend",
        default=tc.BackendType.mips,
        help="use BACKEND as back-end.  Can be either "
        f"`{tc.BackendType.mips.value}' (MIPS assembly language) "
        "[default: %default]",
    )
    parser.add_option(
        "-d",
        "--debug",
        action="store_true",
        dest="debug",
        default=False,
        help="print debug call trace",
    )

    # Options parsing.
    (options, args) = parser.parse_args()

    # Invalid argument.
    me = os.path.basename(sys.argv[0])
    error = False
    if len(args) != 1:
        print(f"{me}: not enough arguments")
        error = True

    if options.backend not in [e.value for e in tc.BackendType]:
        print(f"{me}: select a valid backend")
        error = True

    if error:
        parser.print_help()
        sys.exit(1)

    # Get filename from arguments.
    filename = args[-1]
    process_file(filename, **vars(options))

# Local Variables:
# mode: python
# End:
