#ifndef H_NATIVE
#define H_NATIVE

typedef void (*NativeFn)();

typedef struct {
    const char* name;
    NativeFn fn;
} NativeFunction;

extern NativeFunction native_functions[];

#endif