/*
 * Responsibility: verify --help is detected as TRUE_TOTO_HELP.
 * Syscalls: none.
 * Heap: none — stack argv only.
 * C standard: ISO C11.
 */

#include "test_scan_help.h"

#include "true_toto_cli.h"

#include <assert.h>
#include <stdio.h>

void test_scan_help(void)
{
    char prog[] = "prog";
    char help[] = "--help";
    char *argv[] = { prog, help };

    assert(scan_meta_flags(2, argv) == TRUE_TOTO_HELP);
    printf("PASS: scan_meta_flags detects --help as TRUE_TOTO_HELP\n");
}
