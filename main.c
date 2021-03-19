#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "boinc/boinc_api.h"
#include "boinc/filesys.h"

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

// end is an exclusive bound, like a for loop
uint64_t start = 0;
uint64_t end = 0;

int main(int argc, char **argv) {
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "--start") == 0) { start = int_parse(argv[++i]); }
        if (strcmp(argv[i], "--end") == 0) { end = int_parse(argv[++i]); }
    }

    // boinc init
    BOINC_OPTIONS options;

    // defaults
//    options.main_program = 1;
//    options.check_heartbeat = 1;
//    options.handle_process_control = 1;
//    options.send_status_msgs = 1;
//    options.direct_process_action = 1;
//    options.normal_thread_priority = 0;
//    options.multi_thread = 0;
//    options.multi_process = 0;

    options.main_program = 1;
    options.check_heartbeat = 1;
    options.handle_process_control = 1;
    options.send_status_msgs = 1;
    options.direct_process_action = 1;
    options.normal_thread_priority = 0;
    options.multi_thread = 0;
    options.multi_process = 0;

    boinc_init_options(&options);

    FILE *prines_out = resolve_fopen("prinesout.txt", "wb");
    int done = 0;
    uint64_t n;
    n = start;
    while (!done) {
        if (is_prime(n)) {
            fprintf(prines_out, "%" PRIu64 "\n", n);
        }
        boinc_fraction_done((double) (n - start) / (end - start));

        if (n >= end) {
            done = 1;
        }
        n++;
    }
    boinc_finish(0);
}
