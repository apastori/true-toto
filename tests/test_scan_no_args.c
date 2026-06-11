/*
 * Responsibility: verify scan_meta_flags with no arguments returns META_NONE.
 * Syscalls: none.
 * Heap: none — stack argv only.
 * C standard: ISO C11.
 */

#include "test_scan_no_args.h"

#include "true_toto_cli.h"

#include <assert.h>
#include <stdio.h>

void test_scan_no_args(void)
{
    char prog[] = "prog";
    char *argv[] = { prog };

    assert(scan_meta_flags(1, argv) == META_NONE);
    printf("PASS: scan_meta_flags with no args returns META_NONE\n");
}
