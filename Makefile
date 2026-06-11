# true-toto — GNU Make build (C11, libc only)

CC := $(shell command -v gcc >/dev/null 2>&1 && echo gcc || echo clang)

CFLAGS := -std=c11 -Wall -Wextra -Wpedantic -Werror \
          -D_POSIX_C_SOURCE=200809L -Iinclude -O2

DEBUG_CFLAGS := $(CFLAGS) -g -O1 -fsanitize=address,undefined \
                -fno-omit-frame-pointer

SRCS := src/main.c src/true_toto_emit.c src/true_toto_cli.c
HDRS := include/true_toto.h include/true_toto_emit.h include/true_toto_cli.h

TEST_SRCS := tests/test_runner.c \
             tests/test_scan_no_args.c \
             tests/test_scan_help.c \
             tests/test_scan_help_short.c \
             tests/test_scan_version.c \
             tests/test_scan_version_short.c \
             tests/test_scan_help_wins.c \
             tests/test_scan_ignored_args.c

TEST_BIN := tests/test_core
TEST_IMPL_SRCS := src/true_toto_cli.c src/true_toto_emit.c

.PHONY: all debug test clean install

all: true-toto

true-toto: $(SRCS) $(HDRS)
	$(CC) $(CFLAGS) -o $@ $(SRCS)

debug: true-toto-debug

true-toto-debug: $(SRCS) $(HDRS)
	$(CC) $(DEBUG_CFLAGS) -o $@ $(SRCS)

$(TEST_BIN): $(TEST_SRCS) $(TEST_IMPL_SRCS) $(HDRS) $(wildcard tests/*.h)
	$(CC) $(CFLAGS) -o $@ $(TEST_SRCS) $(TEST_IMPL_SRCS)

test: $(TEST_BIN)
	@if [ -x ./$(TEST_BIN) ]; then \
		./$(TEST_BIN); \
	elif [ -x ./$(TEST_BIN).exe ]; then \
		./$(TEST_BIN).exe; \
	else \
		echo "test binary not found: $(TEST_BIN)" >&2; \
		exit 1; \
	fi

clean:
	rm -f true-toto true-toto-debug $(TEST_BIN) \
	      true-toto.exe true-toto-debug.exe $(TEST_BIN).exe

install: true-toto
	install -m 755 true-toto /usr/local/bin
