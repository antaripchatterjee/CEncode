#include <utf.h>

#ifdef __cplusplus
extern "C" {
#endif

void utf_free(utf_t* utf_data) {
    if(utf_data){
        if(utf_data->w_str){
            free(utf_data->w_str);
        }
        free(utf_data);
        utf_data = NULL;
    }
}


bool copy_as_ustring(const wchar_t* w_str_src, unsigned char* u_str_dest, size_t _copying_ln) {
    if(!w_str_src) return false;
    for(size_t i = 0; i < _copying_ln; i++) {
        u_str_dest[i] = (unsigned char) *(w_str_src + (sizeof(wchar_t) * i));
    }
    return true;
}


bool copy_as_wstring(const unsigned char* u_str_src, wchar_t* w_str_dest, size_t _copying_ln) {
    if(!u_str_src) return false;
    for(size_t i = 0; i < _copying_ln; i++) {
        w_str_dest[i] = (wchar_t) *(u_str_src + (sizeof(unsigned char) * i));
    }
    return true;
}


const char* stringify_utf_method(utf_method method) {
    return method == ENC_UTF_8 ? "ENC_UTF_8" :
        method == DEC_UTF_8 ? "DEC_UTF_8" : UNKNOWN;
} 

void* do_nothing(void* _1, unsigned _2, size_t _3) { return NULL; }

#ifdef __cplusplus
}
#endif