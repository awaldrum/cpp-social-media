//
// Created by alec on 2024-11-27.
//

#include <stdio.h>
#include <stdarg.h>

#define DEBUG 0

#define debug_print(fmt, ...) \
            do { if (DEBUG) fprintf(stdout,"     -----DEBUG "); fprintf(stdout, fmt, __VA_ARGS__); } while (0)