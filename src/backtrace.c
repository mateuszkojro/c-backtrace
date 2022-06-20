#include <stdlib.h>
#include <stdio.h>
#include <execinfo.h>

#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

FILE* output_file_ = 0;

#define bt_printf(...) fprintf(output_file_,"[backtrace] " __VA_ARGS__)

void bt_print_bactrace() {
	const int traces_size = 100;
	void* traces[traces_size];
	int backtrace_size = backtrace(traces, traces_size);
	char** trace_with_symbols = backtrace_symbols(traces, backtrace_size);
	for (int i = 0; i < backtrace_size; i++) {
		bt_printf("%s\n", trace_with_symbols[i]);	
	}
	free(trace_with_symbols);
}

void bt_handler(int signo, siginfo_t *info, void* context) {
	bt_printf("Signal caught: %s\n", strsignal(signo));
	bt_print_bactrace();
	exit(EXIT_FAILURE);
}

int bt_init_internal() {
	struct sigaction act = { 0 };
	act.sa_flags = SA_SIGINFO; //| SA_UNSUPPORTED | SA_EXPOSE_TAGBITS;
	act.sa_sigaction = &bt_handler;

	int error = sigaction(SIGABRT, &act, NULL);
	if (error == -1) {
		return error; 
	}

	return 0;
}

int bt_init() {
	output_file_ = stdout;
	return bt_init_internal();
}

void bt_set_output_file(FILE* output_file) {
	output_file_ = output_file;
}

