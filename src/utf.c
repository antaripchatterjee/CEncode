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


int copy_as_ustring(const wchar_t* w_str_src, unsigned char* u_str_dest, size_t _copying_ln) {
    if(!w_str_src) return -1;
    memset(u_str_dest, '\0', _copying_ln);
    return wcstombs((char*) u_str_dest, w_str_src, _copying_ln - 1);
}


int copy_as_wstring(const unsigned char* u_str_src, wchar_t* w_str_dest, size_t _copying_ln) {
    if(!u_str_src) return -1;
    wmemset(w_str_dest, L'\x00', _copying_ln);
    return mbstowcs(w_str_dest, (const char*) u_str_src, _copying_ln -1);
}

// wchar_t* to_wstring(const unsigned char* u_str, size_t u_str_len) {
//     if(!u_str) return NULL;
//     if(u_str_len <= 0) u_str_len = ucslen(u_str);
//     wchar_t* w_str = (wchar_t*) malloc(sizeof(wchar_t) * (u_str_len + 1));
//     wmemset(w_str, L'\x00', sizeof(wchar_t) * (u_str_len + 1));

//     for(size_t i = 0; i < u_str_len; i++) {
//         w_str[i] = (wchar_t) *(u_str + (sizeof(wchar_t) * i));
//     }
//     return w_str;
// }


// unsigned char* to_ustring(const wchar_t* w_str, size_t w_str_len) {
//     if(!w_str) return NULL;
//     if(!w_str_len) w_str_len = wcslen(w_str);
//     unsigned char* u_str = (unsigned char*) malloc(sizeof(unsigned char) * (w_str_len + 1));
//     memset(u_str, '\0', sizeof(unsigned char) * (w_str_len + 1));
//     for(size_t i = 0; i < w_str_len; i++) {
//         u_str[i] = (unsigned char) *(w_str + (sizeof(unsigned char) * i));
//     }
//     return u_str;
// }


const char* stringify_utf_method(utf_method method) {
    return method == ENC_UTF_8 ? "ENC_UTF_8" :
        method == DEC_UTF_8 ? "DEC_UTF_8" : UNKNOWN;
} 

void* do_nothing(void* _1, unsigned _2, size_t _3) { return NULL; }

#ifdef __cplusplus
}
#endif