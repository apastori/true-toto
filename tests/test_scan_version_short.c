/*
 * Responsibility: verify --v is detected as META_VERSION.
 * Syscalls: none.
 * Heap: none — stack argv only.
 * C standard: ISO C11.
 */

#include "test_scan_version_short.h"

#include "true_toto_cli.h"

#include <assert.h>
#include <stdio.h>

void test_scan_version_short(void)
{
    char prog[] = "prog";
    char version[] = "--v";
    char *argv[] = { prog, version };

    assert(scan_meta_flags(2, argv) == META_VERSION);
    printf("PASS: scan_meta_flags detects --v as META_VERSION\n");
}
