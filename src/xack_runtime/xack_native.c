#include "xack_native.h"

NativeFunction native_functions[] = {
    {"Memory.alloc", native_mem_alloc},
    {"", 0}
};

void native_mem_alloc()
{

}