/*
 * Responsibility: run all scan_meta_flags unit test suites in fixed order.
 * Syscalls: none.
 * Heap: none.
 * C standard: ISO C11.
 */

#include "test_scan_help.h"
#include "test_scan_help_short.h"
#include "test_scan_help_wins.h"
#include "test_scan_ignored_args.h"
#include "test_scan_no_args.h"
#include "test_scan_version.h"
#include "test_scan_version_short.h"

int main(void)
{
    test_scan_no_args();
    test_scan_help();
    test_scan_help_short();
    test_scan_version();
    test_scan_version_short();
    test_scan_help_wins();
    test_scan_ignored_args();
    return 0;
}
