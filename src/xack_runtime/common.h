#ifndef H_COMMON
#define H_COMMON

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum {
    EEC_OUT_OF_MEM,
    EEC_OP_NOT_KNOWN,
    EEC_OVERLOW,
    EEC_BAD_STATE,
    EEC_COMPILATION_ERROR
} ExitErrorCode;

#endif