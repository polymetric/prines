#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <gmp.h>
#include <gmpxx.h>
#include "boinc/boinc_api.h"
#include "boinc/filesys.h"

int is_prime_6k(mpz_class& n) {
    mpz_class i;

    if (n <= 3) {
        return n > 1;
    }
    if (n % 2 == 0 || n % 3 == 0) {
        return 0;
    }

    i = 5;
    while (i * i <= n) {
        if (n % i == 0 || n  % (i + 2) == 0) {
            return 0;
        }
        i += 6;
    }

    return 1;
}

void fail(char *msg) {
    fprintf(stderr, "%s", msg);
    boinc_finish(-1);
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
mpz_class start = 0;
mpz_class end = 0;

int main(int argc, char **argv) {
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "--start") == 0) { start = argv[++i]; }
        if (strcmp(argv[i], "--end") == 0) { end = argv[++i]; }
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
    mpz_class n;
    n = start;
    while (!done) {
        //gmp_printf("testing primality of %Zd\n", n);
        if (is_prime_6k(n)) {
            gmp_fprintf(prines_out, "%Zd\n", n);
        }
        mpz_class test_a = (n - start);
        mpz_class test_b = (end - start);
        double progress = test_a.get_d() / test_b.get_d();
        //printf("%6.3f\n", progress * 100);
        boinc_fraction_done(progress);

        if (n >= end) {
            done = 1;
        }
        n++;
    }
    boinc_finish(0);
}
