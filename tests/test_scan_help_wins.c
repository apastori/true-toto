/*
 * Responsibility: verify --help wins over --version in either order.
 * Syscalls: none.
 * Heap: none — stack argv only.
 * C standard: ISO C11.
 */

#include "test_scan_help_wins.h"

#include "true_toto_cli.h"

#include <assert.h>
#include <stdio.h>

void test_scan_help_wins(void)
{
    char prog[] = "prog";
    char version[] = "--version";
    char help[] = "--help";
    char *argv_version_first[] = { prog, version, help };
    char *argv_help_first[] = { prog, help, version };

    assert(scan_meta_flags(3, argv_version_first) == TRUE_TOTO_HELP);
    assert(scan_meta_flags(3, argv_help_first) == TRUE_TOTO_HELP);
    printf("PASS: scan_meta_flags gives TRUE_TOTO_HELP when both flags present\n");
}
