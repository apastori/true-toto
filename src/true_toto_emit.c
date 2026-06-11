/*
 * Responsibility: emit one-line diagnostics to stderr on I/O failure.
 * Syscalls: write(STDERR_FILENO, …)
 * Heap: none — stack buffer only.
 * C standard: ISO C11 with POSIX.1-2008 (_POSIX_C_SOURCE=200809L).
 */

#include "true_toto_emit.h"

#include <errno.h>
#include <string.h>
#include <unistd.h>

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

    (void)write(STDERR_FILENO, prefix, sizeof(prefix) - 1U);
    (void)write(STDERR_FILENO, context, context_len);
    (void)write(STDERR_FILENO, sep, sizeof(sep) - 1U);
    (void)write(STDERR_FILENO, errmsg, errmsg_len);
    (void)write(STDERR_FILENO, newline, sizeof(newline) - 1U);
}
