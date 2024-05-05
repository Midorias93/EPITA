# Tiger Compiler module loader.

import importlib

from enum import Enum
from typing import List, Literal


class BackendType(Enum):
    mips: Literal["mips"] = "mips"


def try_import(prefix: str, modules: List[str]):
    for mod in modules:
        mod_name = prefix + mod
        try:
            globals()[mod] = importlib.import_module(mod_name)
        except:
            pass


# Query tc for a module.
def has(module_name: str) -> bool:
    return module_name in globals()


try_import(
    "tiger_",
    [
        "misc",
        "common",
        "parse",
        "object",
        "ast",
        "bind",
        "escapes",
        "type",
        "combine",
        "astclone",
        "desugar",
    ],
)

# Shortcuts
Cout = common.cvar.Cout
Cerr = common.cvar.Cerr
Ofstream = common.Ofstream

# Load IPython specific support if we can.
try:
    # Load only if we are running IPython.
    from IPython import get_ipython
    from IPython.core.magic import Magics, magics_class, cell_magic
    import os
    import sys
    import tempfile

    import ti

    @magics_class
    class TigerMagics(Magics):
        @cell_magic
        def tiger(self, line, cell):
            if not line:
                print(self.__doc__, file=sys.stderr)
                return
            backend = BackendType("mips")
            line = line.split()
            if len(line) == 2 and line[1] in [e.value for e in BackendType]:
                backend = BackendType(line[1])
            elif len(line) > 1:
                print(self.__doc__, file=sys.stderr)
                return
            with tempfile.NamedTemporaryFile(dir=".", suffix=".tig") as t:
                t.write(cell.encode("utf-8"))
                t.flush()
                executor = ti.TiExecutor(t.name, exit_on_error=False, backend=backend)
                executor.backend_get()
                self.shell.user_ns[line[0]] = executor.data

    TigerMagics.__doc__ = (
        "%%tiger variable_name [backend]\n"
        "variable_name is the name of the finale variable\n"
        "backend is optional and must be in [{}]".format(
            ", ".join((e.value for e in BackendType))
        )
    )

    ip = get_ipython()
    if ip:
        ip.register_magics(TigerMagics)

except (ImportError, NameError) as e:
    pass
