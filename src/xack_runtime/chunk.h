#ifndef H_CHUNK
#define H_CHUNK
#include "common.h"

typedef enum {
    OP_PUSH,
    OP_POP,
    OP_ADD,
    OP_SUB,
    OP_NEG
} OpCode;

typedef enum {
    S_ARGUMENT,
    S_LOCAL,
    S_STATIC,
    S_CONSTANT,
    S_THIS,
    S_THAT,
    S_POINTER,
    S_TEMP
} Segment;

typedef struct {
    int count;
    int capacity;
    uint16_t* code;
} Chunk;

void init_chunk(Chunk* chunk);
void write_chunk(Chunk* chunk, uint16_t byte);

#endif