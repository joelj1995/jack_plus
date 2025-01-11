#ifndef H_VM
#define H_VM

#include "common.h"
#include "chunk.h"

#define MAX_STACK 256

typedef enum {
    INTERPRET_OK,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;

typedef struct {
    Chunk* chunk;
    uint16_t* ip;
    uint16_t stack[MAX_STACK];
    uint16_t* stack_top;
} VM;

extern VM vm;

int execute(Chunk* chunk);

#endif