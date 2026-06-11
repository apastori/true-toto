/*
 * Responsibility: verify unknown arguments are ignored (META_NONE).
 * Syscalls: none.
 * Heap: none — stack argv only.
 * C standard: ISO C11.
 */

#include "test_scan_ignored_args.h"

#include "true_toto_cli.h"

#include <assert.h>
#include <stdio.h>

void test_scan_ignored_args(void)
{
    char prog[] = "prog";
    char foo[] = "foo";
    char bar[] = "--bar";
    char *argv[] = { prog, foo, bar };

    assert(scan_meta_flags(3, argv) == META_NONE);
    printf("PASS: scan_meta_flags ignores unknown arguments\n");
}
