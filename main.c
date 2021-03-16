#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "boinc_api.h"

#define OUTFILE "prines_out.txt"

int is_prime(uint64_t n) {
    uint64_t i;

    if (n <= 1) {
        return 0;
    }

    for (i = 2; i < n - 1; i++) {
        if (n % i == 0) {
            return 0;
        }
    }

    return 1;
}

void fail(char *msg) {
    fprintf(stderr, "%s", msg);
    boinc_finish(-1);
}

uint64_t int_parse(char *a) {
    return atoi(a);
}

FILE *resolve_fopen(char *path, char *mode) {
    char resolved_name[256];
    if(boinc_resolve_filename(path, resolved_name, 256)) {
        char msg[256];
        snprintf(msg, 256, "can't resolve filename %s\n", path);
        fail(msg);
    }
    return boinc_fopen(resolved_name, mode);
}

uint64_t start = 0;
uint64_t end = 0;

int main(int argc, char **argv) {
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "--start") == 0) { start = int_parse(argv[++i]); }
        if (strcmp(argv[i], "--end") == 0) { end = int_parse(argv[++i]); }
    }

    // boinc init
    BOINC_OPTIONS options;

    boinc_options_defaults(options);
    options.multi_thread = 0;

    boinc_init_options(&options);


    FILE *prines_out = resolve_fopen(OUTFILE, "wb");
    int done = 0;
    uint64_t n;
    n = start;
    while (!done) {
        if (is_prime(n)) {
            fprintf(prines_out, "%llu\n", n);
        }

        if (n > end) {
            done = 1;
        }
    }
}
