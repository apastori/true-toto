# true-toto

A C11 replica of the GNU coreutils `true` command. `true-toto` exits
immediately with status `0`, silently ignores every argument, and produces no
output in normal operation. Useful in shell loops (`while true-toto`), as a
no-op branch placeholder, and with `|| true-toto` to suppress `set -e` exits.

## Build

```sh
make              # release binary: true-toto
make debug        # true-toto-debug (ASan/UBSan)
make test         # build and run tests/test_core
make clean        # remove build artefacts
make install      # install to /usr/local/bin (Linux/macOS; needs sudo)
```

**Linux:**

```sh
make clean && make
```

**Windows (MSYS2 UCRT64):**

Open the **MSYS2 UCRT64** terminal from the Start menu, then:

```sh
pacman -S make mingw-w64-ucrt-x86_64-gcc   # once
make clean && make && make test
```

Produces a native Windows executable (`true-toto` or `true-toto.exe`) that
runs in UCRT64, Git Bash, cmd, and PowerShell.

**Git Bash caveat:** ensure `/c/msys64/ucrt64/bin` is early on `PATH`
(before Anaconda). Otherwise `gcc --version` may work while `cc1` fails
silently. Prefer the UCRT64 shell, or:

```sh
PATH="/c/msys64/ucrt64/bin:$PATH" make
```

## Usage

| Invocation | Behaviour |
|---|---|
| `true-toto` | exits `0`; no output |
| `true-toto any args` | exits `0`; all args ignored; no output |
| `true-toto --help` / `true-toto --h` | prints usage on stdout; exits `0` |
| `true-toto --version` / `true-toto --v` | prints `true-toto <version>`; exits `0` |
| `true-toto --help --version` | `--help` wins; prints usage; exits `0` |

Single-dash `-h` and `-v` are **not** special — they are silently ignored
like any other argument.

## Exit codes

| Code | Meaning |
|---|---|
| `0` | Normal exit, `--help`, `--version`, or any arguments |
| `1` | Write failure when printing `--help` or `--version`; stderr format: `true-toto: <context>: <reason>` |

## Layout

```
true-toto/
├── LICENSE.txt
├── c_version.txt
├── Makefile
├── README.md
├── include/
│   ├── true_toto.h
│   ├── true_toto_emit.h
│   └── true_toto_cli.h
├── src/
│   ├── main.c
│   ├── true_toto_emit.c
│   └── true_toto_cli.c
└── tests/
    ├── test_runner.c
    └── test_scan_*.c / .h  →  tests/test_core
```
