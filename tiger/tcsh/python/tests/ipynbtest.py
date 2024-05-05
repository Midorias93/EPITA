#!/usr/bin/env python3
"""
simple example script for running and testing notebooks.

Usage: `ipnbdoctest.py foo.ipynb [bar.ipynb [...]]`

Each cell is submitted to the kernel, and the outputs are compared
with those stored in the notebook.
"""

# Derived from https://gist.github.com/minrk/2620735
# Derived from https://gitlab.lrde.epita.fr/spot/spot/-/raw/next/tests/python/ipnbdoctest.py

from __future__ import print_function

import os
import sys
import time
import base64
import re
import pprint
import random
from difflib import unified_diff as diff

from collections import defaultdict
try:
    from queue import Empty
except ImportError:
    print('Python 3.x is needed to run this script.')
    sys.exit(77)

import importlib.util
try:
    importlib.util.find_spec('IPython')
except:
    print('IPython is needed to run this script.')
    sys.exit(77)

try:
    from jupyter_client import KernelManager
except ImportError:
    try:
        from IPython.kernel import KernelManager
    except ImportError:
        try:
            from IPython.zmq.blockingkernelmanager \
                import BlockingKernelManager as KernelManager
        except:
            print('IPython is needed to run this script.')
            sys.exit(77)

# Until Debian Stable ships IPython >3.0, we stick to the v3 format.
try:
    from nbformat import v4 as nbformat
except ImportError:
    from IPython.nbformat import v4 as nbformat


def canonicalize(s):
    """sanitize a string for comparison.

    fix universal newlines, strip trailing newlines, and normalize likely
    random values (memory addresses and UUIDs)
    """
    if not isinstance(s, str):
        return s

    # normalize newline:
    s = s.replace('\r\n', '\n')

    # ignore trailing newlines (but not space)
    s = s.rstrip('\n')

    # remove hex addresses:
    s = re.sub(r'at 0x[a-f0-9]+', 'at 0xadd7e5500000', s)

    # remove backend lists in documentations/errors:
    s = re.sub(r'\[((lir|hir|llvm|mips|ia32), ?)*(lir|hir|llvm|mips|ia32)\]',
               '[]', s)

    return s


def canonical_dict(data):
    """Neutralize gratuitous differences in a Jupyter dictionary."""

    if 'text' in data:
        data['text'] = canonicalize(data['text'])

    if 'data' in data:
        d = data['data']
        if "text/html" in d and "text/plain" in d:
            del d["text/plain"]
        for k in d:
            d[k] = canonicalize(d[k])

    if ('ename' in data and
            data['ename'] == 'SystemExit' and data['evalue'] == '77'):
        # sys.exit(77) is used to Skip the test.
        sys.exit(77)

    if 'ename' in data and data['ename'] == 'CalledProcessError':
        # CalledProcessError message has a final dot in Python 3.6
        data['evalue'] = re.sub(r"(' returned non-zero exit status \d+)\.",
                                r'\1', data['evalue'])

    for e in ('transient', 'execution_count', 'traceback'):
        if e in data:
            del data[e]
    return data


def compare_outputs(ref, test):
    """Check that two lists of outputs are equivalent and report the result."""

    cref = list(map(canonical_dict, ref))
    ctest = list(map(canonical_dict, test))

    ok = True

    if len(cref) != len(ctest):
        print("output length mismatch (expected {}, got {})"
                .format(len(cref), len(ctest)))
        ok = False
    # There can be several outputs.  For instance wnen the cell both
    # prints a result (goes to "stdout") and displays an automaton
    # (goes to "data").
    exp = pprint.pformat(cref, width=132)
    eff = pprint.pformat(ctest, width=132)
    if exp[:-1] != '\n':
        exp += '\n'
    if eff[:-1] != '\n':
        eff += '\n'
    if exp == eff:
        return ok
    else:
        print(''.join(diff(exp.splitlines(1), eff.splitlines(1),
                           fromfile='expected', tofile='effective')))
        return False


def _wait_for_ready_backport(kc):
    """Backport BlockingKernelClient.wait_for_ready from IPython 3"""
    # Wait for kernel info reply on shell channel
    kc.kernel_info()
    while True:
        msg = kc.get_shell_msg(block=True, timeout=30)
        if msg['msg_type'] == 'kernel_info_reply':
            break
    # Flush IOPub channel
    while True:
        try:
            msg = kc.get_iopub_msg(block=True, timeout=1)
        except Empty:
            break


def run_cell(kc, cell):
    kc.execute(cell.source)
    outs = []

    while True:
        try:
            msg = kc.get_iopub_msg(timeout=1)
        except Empty:
            if not kc.is_alive():
                raise RuntimeError("Kernel died")
            continue

        msg_type = msg['msg_type']
        content = msg['content']

        if msg_type == 'status' and content['execution_state'] == 'idle':
            break
        if msg_type in ('status', 'pyin', 'execute_input',
                        'comm_open', 'comm_msg'):
            continue
        if msg_type == 'stream':
            if 'Widget' in content['text']:
                continue
            # If the last stream had the same name, then outputs are
            # appended.
            if outs:
                last = outs[-1]
                if last['output_type'] == 'stream' and \
                        last['name'] == content['name']:
                    last['text'] += content['text']
                    continue
        elif msg_type == 'clear_output':
            outs = []
            continue

        content['output_type'] = msg_type
        outs.append(content)
    # Flush shell channel
    while True:
        try:
            kc.get_shell_msg(timeout=0.1)
        except Empty:
            if not kc.is_alive():
                raise RuntimeError("Kernel died")
            break
    return outs


def test_notebook(ipynb):
    with open(ipynb, encoding='utf-8') as f:
        nb = nbformat.reads_json(f.read())
    km = KernelManager()
    # Do not save the history to disk, as it can yield spurious lock errors.
    # See https://github.com/ipython/ipython/issues/2845
    km.start_kernel(extra_arguments=['--HistoryManager.hist_file=:memory:',
                                     '--quiet'])

    kc = km.client()
    kc.start_channels()

    try:
        kc.wait_for_ready(timeout=30)
    except AttributeError:
        _wait_for_ready_backport(kc)

    successes = 0
    failures = 0
    errors = 0
    for i, cell in enumerate(nb.cells):
        if cell.cell_type == 'markdown' and cell.source.startswith("#"):
            title = re.sub(r'^#+ ?', '', cell.source.splitlines()[0])
        if cell.cell_type != 'code' or cell.source.startswith('#DONTCHECK'):
            continue
        try:
            outs = run_cell(kc, cell)
        except Exception as e:
            print("failed to run cell:", repr(e))
            print(cell.input)
            errors += 1
            continue

        failed = not compare_outputs(cell.outputs, outs)
        print("{: <30} {: >2}: ".format(title, i), end="")
        if failed:
            print("FAIL")
            failures += 1
        else:
            print("OK")
            successes += 1

    print("tested notebook %s" % ipynb)
    print("    %3i cells successfully replicated" % successes)
    if failures:
        print("    %3i cells mismatched output" % failures)
    if errors:
        print("    %3i cells failed to complete" % errors)
    kc.stop_channels()
    km.shutdown_kernel()
    del km
    if failures or errors:
        sys.exit(1)


if __name__ == '__main__':
    for ipynb in sys.argv[1:]:
        tries=3
        while tries:
            print("testing %s" % ipynb)
            try:
                test_notebook(ipynb)
                break
            except RuntimeError as e:
                # If the Kernel dies, try again.  It seems we have spurious
                # failures when multiple instances of jupyter start in parallel.
                if 'Kernel died' in str(e):
                    tries -= 1
                    if tries:
                        s = random.randint(1, 5)
                        print("trying again in", s, "seconds...")
                        time.sleep(s)
                else:
                    raise e
