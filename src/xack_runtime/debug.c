#include "common.h"
#include "debug.h"

void disassemble_segment(uint16_t byte)
{
    switch (byte)
    {
        case S_ARGUMENT:
            printf("argument ");
            break;
        case S_LOCAL:
            printf("local ");
            break;
        case S_STATIC:
            printf("static ");
            break;
        case S_CONSTANT:
            printf("constant ");
            break;
        case S_THIS:
            printf("this ");
            break;
        case S_THAT:
            printf("that ");
            break;
        case S_POINTER:
            printf("pointer ");
            break;
        case S_TEMP:
            printf("temp ");
            break;
        default:
            exit(EEC_OP_NOT_KNOWN);
    }
}

void disassemble_int_constant(uint16_t val)
{
    printf("%d", val);
}

void disassemble_chunk(Chunk* chunk)
{
    int i = 0;
    while (i < chunk->count)
    {
        printf("%05d    ", i);
        if (chunk->code[i] == OP_PUSH)
        {
            printf("push ");
            i++;
            disassemble_segment(chunk->code[i]);
            i++;
            disassemble_int_constant(chunk->code[i]);
            printf("\n");
        }
        else if (chunk->code[i] == OP_POP)
        {
            printf("pop ");
            i++;
            disassemble_segment(chunk->code[i]);
            i++;
            disassemble_int_constant(chunk->code[i]);
            printf("\n");
        }
        else if (chunk->code[i] == OP_ADD)
        {
            printf("add\n");
        }
        else if (chunk->code[i] == OP_SUB)
        {
            printf("sub\n");
        }
        else if (chunk->code[i] == OP_NEG)
        {
            printf("neg\n");
        }
        else if (chunk->code[i] == OP_EQ)
        {
            printf("eq\n");
        }
        else if (chunk->code[i] == OP_GT)
        {
            printf("gt\n");
        }
        else if (chunk->code[i] == OP_LT)
        {
            printf("lt\n");
        }
        else if (chunk->code[i] == OP_AND)
        {
            printf("and\n");
        }
        else if (chunk->code[i] == OP_OR)
        {
            printf("or\n");
        }
        else if (chunk->code[i] == OP_NOT)
        {
            printf("not\n");
        }
        else if (chunk->code[i] == OP_GOTO)
        {
            printf("goto %d\n", chunk->code[++i]);
        }
        else if (chunk->code[i] == OP_IF_GOTO)
        {
            printf("if-goto %d\n", chunk->code[++i]);
        }
        else if (chunk->code[i] == OP_RETURN)
        {
            printf("return\n");
        }
        else if (chunk->code[i] == OP_CALL)
        {
            int callIdx = chunk->code[++i];
            FunctionCall callData = chunk->function_calls[callIdx];
            printf("call %d -> %d", callIdx, chunk->functions[callData.function_idx].offset);
            if (callData.is_native)
            {
                printf(" [native]");
            }
            printf("\n");
        }
        else if (chunk->code[i] == OP_NOP)
        {
            printf("noop\n");
        }
        
        else
        {
            printf("Op %d not recognized\n", chunk->code[i]);
            exit(EEC_OP_NOT_KNOWN);
        }
        i++;
    }
}