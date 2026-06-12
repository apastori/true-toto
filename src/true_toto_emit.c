/*
 * Responsibility: emit one-line diagnostics to stderr on I/O failure.
 * Syscalls: write(STDERR_FILENO, …)
 * Heap: none — stack buffer only.
 * C standard: ISO C11 with POSIX.1-2008 (_POSIX_C_SOURCE=200809L).
 */

#include "true_toto_emit.h"

#include <errno.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>

/*
 * Write all bytes to fd, retrying partial writes.
 * Best-effort only: on failure, return silently (cannot recurse into
 * true_toto_emit_error).
 */
static void write_best_effort(int fd, const char *buf, size_t len)
{
    size_t written = 0U;

    while (written < len) {
        ssize_t n = write(fd, buf + written, len - written);

        if (n < 0) {
            return;
        }

        written += (size_t)n;
    }
}

void true_toto_emit_error(const char *context)
{
    const char prefix[] = "true-toto: ";
    const char sep[] = ": ";
    const char newline[] = "\n";
    const char *errmsg;
    size_t context_len;
    size_t errmsg_len;

    if (context == NULL) {
        context = "unknown";
    }

    errmsg = strerror(errno);
    if (errmsg == NULL) {
        errmsg = "unknown error";
    }

    context_len = strlen(context);
    errmsg_len = strlen(errmsg);

    write_best_effort(STDERR_FILENO, prefix, sizeof(prefix) - 1U);
    write_best_effort(STDERR_FILENO, context, context_len);
    write_best_effort(STDERR_FILENO, sep, sizeof(sep) - 1U);
    write_best_effort(STDERR_FILENO, errmsg, errmsg_len);
    write_best_effort(STDERR_FILENO, newline, sizeof(newline) - 1U);
}
