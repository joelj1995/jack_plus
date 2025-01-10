#include "common.h"
#include "memory.h"

void* reallocate(void* pointer, size_t oldSize, size_t newSize)
{
    if (newSize == 0) return NULL;

    void* result = realloc(pointer, newSize);
    if (result == NULL) exit(EEC_OUT_OF_MEM);
    return result;
}