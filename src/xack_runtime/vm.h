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
    uint16_t pheap;
    uint16_t pheadend;
    uint16_t free;
} VM;

extern VM vm;

int execute(Chunk* chunk);

void push(int16_t word);
int16_t pop();


#endif