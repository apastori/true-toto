/*
 * Responsibility: entry point — dispatch meta flags, extra-args notice, then
 * exit successfully.
 * Syscalls: none directly (delegated to true_toto_cli).
 * Heap: none.
 * C standard: ISO C11 with POSIX.1-2008 (_POSIX_C_SOURCE=200809L).
 */

#include "true_toto_cli.h"

#include <stdlib.h>

int main(int argc, char *argv[])
{
    true_toto_flag flag = scan_meta_flags(argc, argv);

    switch (flag) {
        case TRUE_TOTO_HELP:
            print_help();
            break;
        case TRUE_TOTO_VERSION:
            print_version();
            break;
        case TRUE_TOTO_NONE:
            if (argc > 1) {
                print_extra_args_notice();
            }
            break;
    }

    return EXIT_SUCCESS;
}
