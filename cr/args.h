#ifndef _ARGS_H_
#define _ARGS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <getopt.h>

// Short option flags
const char s_opts[] = "h";

// Long options flags
const option l_opts[] = {
    {"help", no_argument, nullptr, 'h'},
    {nullptr, no_argument, nullptr, 0}
};

// Parse arguments from command line
void parse_args (int argc, char **argv) {
    int opt;
    while ((opt = getopt_long(argc, argv, s_opts, l_opts, nullptr)) != -1) {
        switch (opt) {
        case 'h':
        case '?':
        default:
            printf("Show help options\n");
            break;
        }
    }
}

#ifdef __cplusplus
} // end of extern "C"
#endif

#endif //_ARGS_H_