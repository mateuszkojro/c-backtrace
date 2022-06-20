#ifndef MK_BACKTRACE_H
#define MK_BACKTRACE_H
#ifdef __cplusplus
extern "C" {
#endif

#include <signal.h>
#include <stdio.h>

int bt_init();

void bt_set_output_file(FILE *output_file);

void bt_print_bactrace();

#ifdef __cplusplus
}
#endif
#endif