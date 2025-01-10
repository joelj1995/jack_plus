#ifndef H_CHUNK
#define H_CHUNK
#include "common.h"

typedef enum {
    OP_PUSH,
    OP_POP,
    OP_ADD,
    OP_SUB
} OpCode;

typedef struct {
    int count;
    int capacity;
    uint16_t* code;
} Chunk;

void init_chunk(Chunk* chunk);
void write_chunk(Chunk* chunk, uint16_t byte, int line);

#endif H_CHUNK