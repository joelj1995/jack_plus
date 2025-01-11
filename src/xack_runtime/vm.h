#ifndef H_VM
#define H_VM

#include "common.h"
#include "chunk.h"

#define MAX_STACK 256

typedef struct {
    Chunk* chunk;
    uint16_t* ip;
    uint16_t stack[MAX_STACK];
} VM;

extern VM vm;

#endif