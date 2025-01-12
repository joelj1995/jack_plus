#ifndef H_VM
#define H_VM

#include "common.h"
#include "chunk.h"

#define MAX_STACK 256
#define MEMORY_LENGTH 24577

#define JACK_BOOL(b) (b) ? -1 : 0

typedef enum {
    INTERPRET_OK,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;

typedef struct {
    Chunk* chunk;
    uint16_t* ip;
    int16_t ram[MEMORY_LENGTH];
} VM;

extern VM vm;

int execute(Chunk* chunk);

#endif