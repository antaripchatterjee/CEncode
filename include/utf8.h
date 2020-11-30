#ifndef __UTF_8_H__
#define __UTF_8_H__

#include "utf.h"

#ifdef __cplusplus
extern "C" {
#endif

extern utf_t* utf8_encode(const wchar_t*, size_t);
extern utf_t* utf8_decode(const wchar_t*, size_t);

#ifdef __cplusplus
}
#endif
#endif // __UTF_8_H__
