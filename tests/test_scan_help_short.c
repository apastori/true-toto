/*
 * Responsibility: verify --h is detected as META_HELP.
 * Syscalls: none.
 * Heap: none — stack argv only.
 * C standard: ISO C11.
 */

#include "test_scan_help_short.h"

#include "true_toto_cli.h"

#include <assert.h>
#include <stdio.h>

void test_scan_help_short(void)
{
    char prog[] = "prog";
    char help[] = "--h";
    char *argv[] = { prog, help };

    assert(scan_meta_flags(2, argv) == META_HELP);
    printf("PASS: scan_meta_flags detects --h as META_HELP\n");
}
