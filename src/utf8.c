#include <utf8.h>

#ifdef __cplusplus
extern "C" {
#endif

static utf_method _utf8_enc() {
    return ENC_UTF_8;
}

static utf_method _utf8_dec() {
    return DEC_UTF_8;
}

utf_t* utf8_encode(const wchar_t* orig_str, size_t orig_str_len) {
    if(!orig_str) return NULL;
    if(!orig_str_len) orig_str_len = wcslen(orig_str);

    utf_t* utf8 = (utf_t*) malloc(sizeof(utf_t));
    utf8->w_size = 0;
    utf8->w_str = (wchar_t*) malloc(sizeof(wchar_t));
    utf8->method = _utf8_enc;
    wmemset(utf8->w_str, L'\x00', sizeof(wchar_t));
    wchar_t* encoded_char = NULL;
    bool is_surrogate_pair = false;
    unsigned surrogate_multiple = 0;
    for(size_t i = 0; i < orig_str_len; i++) {
        unsigned wch = (unsigned) orig_str[i];
        short byte_len;
        if(is_surrogate_pair) {
            is_surrogate_pair = false;
            if(wch >= 0xdc00 && wch <= 0xdfff) {
                wch = surrogate_multiple * 1024 + (wch  - 0xdc00) + 0x10000;
            } else {
                if(encoded_char) free(encoded_char);
                utf_free(utf8);
                return NULL;
            }
        }
        if(wch >= 0x00 && wch < 0x80) {
            byte_len = 1;
        } else if(wch >= 0x80 && wch < 0x0800) {
            byte_len = 2;
        } else if(wch >= 0x800 && wch < 0x10000) {
            if(wch >= 0xd800 && wch <= 0xdbff) {
                is_surrogate_pair = true;
                surrogate_multiple = wch - 0xd800;
                continue;
            } else if(wch >= 0xdc00 && wch <= 0xdfff) {
                if(encoded_char) free(encoded_char);
                utf_free(utf8);
                return NULL;
            }
            byte_len = 3;
        } else if(wch >= 0x10000 && wch < 0x200000) {
            byte_len = 4;
        } else {
            utf_free(utf8);
            if(encoded_char) free(encoded_char);
            return NULL;
        }
        if(encoded_char) {
            encoded_char = (wchar_t*)realloc(encoded_char, sizeof(wchar_t) * (byte_len + 1));
        } else {
            encoded_char = (wchar_t*) malloc(sizeof(wchar_t) * (byte_len + 1));
        }
        wmemset(encoded_char, L'\x00', sizeof(wchar_t) * (byte_len + 1));
        if(byte_len == 1) {
            encoded_char[0] = wch;
        } else if(byte_len == 2) {
            encoded_char[0] = (wchar_t)((wch >> 6) | 0b11000000);
            encoded_char[1] = (wchar_t)((wch & 0b00111111) | 0b10000000);
        } else if (byte_len == 3) {
            encoded_char[0] = (wchar_t)((wch >> 12) | 0b11100000);
            encoded_char[1] = (wchar_t)(((wch & 0b0000111111000000) >> 6) | 0b10000000);
            encoded_char[2] = (wchar_t)((wch & 0b00111111) | 0b10000000);
        } else {
            encoded_char[0] = (wchar_t)((wch >> 18) | 0b11110000);
            encoded_char[1] = (wchar_t)(((wch >> 12) & 0b00111111) | 0b10000000);
            encoded_char[2] = (wchar_t)(((wch >> 6) & 0b00111111) | 0b10000000);
            encoded_char[3] = (wchar_t)((wch & 0b00111111) | 0b10000000);
        }
        utf8->w_str = (wchar_t*)realloc(utf8->w_str,
                                sizeof(wchar_t) * (byte_len + 1 + wcslen(utf8->w_str)));

        wcscat(utf8->w_str, encoded_char);
        utf8->w_size += byte_len;
        utf8->w_str[utf8->w_size] = L'\x00';
    }
    if(encoded_char) free(encoded_char);
    return utf8;
}
utf_t* utf8_decode(const wchar_t* encoded_str, size_t enc_str_len) {
    if(!encoded_str) return NULL;
    if(!enc_str_len) enc_str_len = wcslen(encoded_str);

    utf_t* utf8 = (utf_t*) malloc(sizeof(utf_t));
    utf8->w_size = 0;
    utf8->w_str = (wchar_t*) malloc(sizeof(wchar_t));
    utf8->method = _utf8_dec;
    wmemset(utf8->w_str, L'\x00', sizeof(wchar_t));
    unsigned w_byte = 0;
    unsigned w_byte_0 = 0, w_byte_1 = 0, w_byte_2 = 0, w_byte_3 = 0;
    for(size_t i = 0; i < enc_str_len; i++) {
        unsigned wch = (unsigned) encoded_str[i];
        short byte_len;
        short _new_w_byte_size = 1;
        if(wch >> 7 == 0) {
            byte_len = 1;
        } else if((wch & 0b00100000) == 0) {
            byte_len = 2;
        } else if((wch & 0b00010000) == 0) {
            byte_len = 3;
        } else if((wch & 0b00001000) == 0) {
            byte_len = 4;
            _new_w_byte_size = 2;
        } else {
            byte_len = -1;
        }
        switch(byte_len) {
            case 1: {
                w_byte = (unsigned) wch;
                break;
            }
            case 2: {
                if(i+1 >= enc_str_len) {
                    utf_free(utf8);
                    return NULL;
                }
                w_byte_0 = (unsigned) wch & 0b00011111;
                w_byte_1 = (unsigned) encoded_str[++i] & 0b00111111;
                w_byte = (w_byte_0 << 6) | w_byte_1;
                break;
            }
            case 3: {
                if(i+2 >= enc_str_len) {
                    utf_free(utf8);
                    return NULL;
                }
                w_byte_0 = (unsigned) wch & 0b00001111;
                w_byte_1 = (unsigned) encoded_str[++i] & 0b00111111;
                w_byte_2 = (unsigned) encoded_str[++i] & 0b00111111;
                w_byte = (w_byte_0 << 12) | ( w_byte_1 << 6) | w_byte_2;
                break;
            }
            case 4: {
                if(i+3 >= enc_str_len) {
                    utf_free(utf8);
                    return NULL;
                }
                w_byte_0 = (unsigned) wch & 0b00001111;
                w_byte_1 = (unsigned) encoded_str[++i] & 0b00111111;
                w_byte_2 = (unsigned) encoded_str[++i] & 0b00111111;
                w_byte_3 = (unsigned) encoded_str[++i] & 0b00111111;
                w_byte = (w_byte_0 << 18) | (w_byte_1 << 12) | (w_byte_2 << 6) | w_byte_3;
                break;
            }
            default: {
                utf_free(utf8);
                return NULL;
            }
        }

        utf8->w_size += _new_w_byte_size;
        utf8->w_str = (wchar_t*) realloc(utf8->w_str, sizeof(wchar_t) * (utf8->w_size + 1));
        if(_new_w_byte_size == 1) {
            utf8->w_str[utf8->w_size - 1] = (wchar_t) w_byte;
        } else {
            w_byte = w_byte - 0x10000;
            utf8->w_str[utf8->w_size - 2] = 0xd800 + w_byte / 1024;
            utf8->w_str[utf8->w_size - 1] = 0xdc00 + w_byte % 1024;
        }
        utf8->w_str[utf8->w_size] = L'\x00';
        w_byte = w_byte_1 = w_byte_2 = w_byte_3 = 0;
    }
    return utf8;
}

#ifdef __cplusplus
}
#endif