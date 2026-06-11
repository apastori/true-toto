/*
 * Responsibility: verify --version is detected as META_VERSION.
 * Syscalls: none.
 * Heap: none — stack argv only.
 * C standard: ISO C11.
 */

#include "test_scan_version.h"

#include "true_toto_cli.h"

#include <assert.h>
#include <stdio.h>

void test_scan_version(void)
{
    char prog[] = "prog";
    char version[] = "--version";
    char *argv[] = { prog, version };

    assert(scan_meta_flags(2, argv) == META_VERSION);
    printf("PASS: scan_meta_flags detects --version as META_VERSION\n");
}
