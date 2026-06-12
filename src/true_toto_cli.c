/*
 * Responsibility: scan argv for meta flags; print help/version/extra-args
 * notice to stdout.
 * Syscalls: write(STDOUT_FILENO, …)
 * Heap: none — stack and static string literals only.
 * C standard: ISO C11 with POSIX.1-2008 (_POSIX_C_SOURCE=200809L).
 */

#include "true_toto_cli.h"
#include "true_toto.h"
#include "true_toto_emit.h"

#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static const char HELP_TEXT[] =
    "Usage: true-toto [ignored command line arguments]\n"
    "  or:  true-toto OPTION\n"
    "Return a successful result.\n"
    "\n"
    "  --help        display this help and exit\n"
    "  --version     output version information and exit\n";

static const char EXTRA_ARGS_TEXT[] =
    "true-toto: ignoring extra arguments\n";

static int is_help_flag(const char *arg)
{
    return strcmp(arg, "--help") == 0 || strcmp(arg, "--h") == 0;
}

static int is_version_flag(const char *arg)
{
    return strcmp(arg, "--version") == 0 || strcmp(arg, "--v") == 0;
}

/*
 * Write all bytes from buf to fd, retrying on partial writes.
 * Returns 0 on success.
 * On failure: emits error diagnostic and exits with TRUE_TOTO_EXIT_WRITE_ERR.
 */
static int write_all(int fd, const char *buf, size_t len)
{
    size_t written = 0U;

    while (written < len) {
        ssize_t n = write(fd, buf + written, len - written);

        if (n < 0) {
            true_toto_emit_error("write");
            exit(TRUE_TOTO_EXIT_WRITE_ERR);
        }

        written += (size_t)n;
    }

    return 0;
}

/*
 * Preconditions: argc >= 1; argv is a valid null-terminated array.
 * Postcondition: scan_meta_flags() performs no I/O; main() may call
 *         print_extra_args_notice() when TRUE_TOTO_NONE and argc > 1.
 * Return: TRUE_TOTO_HELP if any arg is --help or --h (takes precedence);
 *         TRUE_TOTO_VERSION if any arg is --version or --v and no help flag;
 *         TRUE_TOTO_NONE otherwise.
 */
true_toto_flag scan_meta_flags(int argc, char *argv[])
{
    int i;

    for (i = 1; i < argc; i++) {
        if (is_help_flag(argv[i])) {
            return TRUE_TOTO_HELP;
        }
    }

    for (i = 1; i < argc; i++) {
        if (is_version_flag(argv[i])) {
            return TRUE_TOTO_VERSION;
        }
    }

    return TRUE_TOTO_NONE;
}

void print_help(void)
{
    (void)write_all(STDOUT_FILENO, HELP_TEXT, sizeof(HELP_TEXT) - 1U);
}

void print_version(void)
{
    static const char prefix[] = "true-toto ";
    static const char newline[] = "\n";
    size_t version_len = strlen(TRUE_TOTO_VERSION_STRING);

    (void)write_all(STDOUT_FILENO, prefix, sizeof(prefix) - 1U);
    (void)write_all(STDOUT_FILENO, TRUE_TOTO_VERSION_STRING, version_len);
    (void)write_all(STDOUT_FILENO, newline, sizeof(newline) - 1U);
}

void print_extra_args_notice(void)
{
    (void)write_all(STDOUT_FILENO, EXTRA_ARGS_TEXT,
                    sizeof(EXTRA_ARGS_TEXT) - 1U);
}
