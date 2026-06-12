#ifndef TRUE_TOTO_CLI_H
#define TRUE_TOTO_CLI_H

typedef enum {
    TRUE_TOTO_NONE,
    TRUE_TOTO_HELP,
    TRUE_TOTO_VERSION
} true_toto_flag;

true_toto_flag scan_meta_flags(int argc, char *argv[]);
void print_help(void);
void print_version(void);
void print_extra_args_notice(void);

#endif /* TRUE_TOTO_CLI_H */
