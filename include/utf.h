#ifndef __UTF_H__
#define __UTF_H__

#include <wchar.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif


// #define _memset_fn(_mem) _Generic((_mem), \
//     wchar_t*: wmemset, \
//     unsigned char*: memset, \
//     char*: memset, \
//     default: do_nothing \
// )

// #define ucslen(__ucs) strlen((const char*) __ucs)
// #define allocate(_T, _s) ({ \
//     _T* _mem = (_T*) malloc((_s + 1) * sizeof(_T)); \
//     _memset_fn(_mem)(_mem, (_T) 0, sizeof(_T) * (_s + 1)); \
//     _mem; \
// })

enum __utf_method {
    UNKNOWN,
    ENC_UTF_8,
    DEC_UTF_8
};


typedef enum __utf_method utf_method;

struct __utf_t {
    wchar_t *w_str;
    size_t w_size;
    utf_method (*method)();
};

typedef struct __utf_t utf_t;


extern void utf_free(utf_t*);
extern int copy_as_ustring(const wchar_t*, unsigned char*, size_t);
extern int copy_as_wstring(const unsigned char*, wchar_t*, size_t);
// extern wchar_t* to_wstring(const unsigned char*, size_t);
// extern unsigned char* to_ustring(const wchar_t*, size_t);
extern const char* stringify_utf_method(utf_method);
extern void* do_nothing(void*, unsigned, size_t);

#ifdef __cplusplus
}
#endif

#endif // __UTF_H__
