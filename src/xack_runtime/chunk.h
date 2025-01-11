#ifndef H_CHUNK
#define H_CHUNK
#include "common.h"

typedef enum {
    OP_NOP,
    OP_PUSH,
    OP_POP,
    OP_ADD,
    OP_SUB,
    OP_NEG,
    OP_EQ,
    OP_GT,
    OP_LT,
    OP_AND,
    OP_OR,
    OP_NOT,
    OP_GOTO
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

typedef struct CodeLabel {
    char* name;
    uint16_t offset;
} CodeLabel;

typedef struct {
    int count;
    int capacity;
    uint16_t* code;
    CodeLabel labels[256];
    int label_count;
    char* goto_labels[1024];
    int goto_label_count;
} Chunk;

void init_chunk(Chunk* chunk);
void write_chunk(Chunk* chunk, uint16_t byte);
void label_goto(Chunk* chunk, uint16_t op, char* label);
void label_chunk(Chunk* chunk, char* label);
void replace_labels(Chunk* chunk);

#endif