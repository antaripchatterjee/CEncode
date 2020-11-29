#include <utf8.h>
#include "test.h"


int main() {
    const wchar_t *wstr = L"Hello\ue000World.\xd8Good\U0001FEFEbye";
    utf_t* utf_encoded = utf8_encode(wstr, 0);
    my_custom_assert(utf_encoded != NULL, {
        printf("Method: %s\n", stringify_utf_method(utf_encoded->method()));
    }, {});
    my_custom_assert(wcslen(utf_encoded->w_str) == utf_encoded->w_size, {
        printf("Encoded String Length: %u\n", (unsigned) utf_encoded->w_size);
        wprintf(L"Encoded String: %ls -> %d\n", utf_encoded->w_str, (int)wcslen(utf_encoded->w_str));
        size_t copying_len = wcslen(utf_encoded->w_str);
        unsigned char* u_string = allocate(unsigned char, copying_len);
        copy_as_ustring(utf_encoded->w_str, u_string, copying_len);
        printf("Encoded String to U_STRING: %s\n", u_string);
        copying_len = ucslen(u_string);
        wchar_t* w_string = allocate(wchar_t, copying_len);
        copy_as_wstring(u_string, w_string, copying_len);
        wprintf(L"U_STRING to W_STRING: %ls\n", w_string);
        free(u_string);
        printf("u_string freed\n");
        _putws(w_string);
        free(w_string);
    }, {
        utf_free(utf_encoded);
    });
    
    utf_t* utf_decoded = utf8_decode(utf_encoded->w_str, utf_encoded->w_size);
    my_custom_assert(utf_decoded != NULL, {
        printf("Method: %s\n", stringify_utf_method(utf_decoded->method()));
    }, {
        utf_free(utf_encoded);
    });
    my_custom_assert(wcslen(utf_decoded->w_str) == wcslen(wstr), {}, {
        utf_free(utf_encoded);
        utf_free(utf_decoded);
    });
    my_custom_assert(wcscmp(utf_decoded->w_str, wstr) == 0, {}, {
        utf_free(utf_encoded);
        utf_free(utf_decoded);
    });

    utf_t* utf_reencoded = utf8_encode(utf_decoded->w_str, 0);
    my_custom_assert(utf_reencoded != NULL, {
        printf("Method: %s\n", stringify_utf_method(utf_decoded->method()));
    }, {
        utf_free(utf_encoded);
        utf_free(utf_decoded);
    });
    my_custom_assert(wcslen(utf_reencoded->w_str) == wcslen(utf_encoded->w_str), {}, {
        utf_free(utf_encoded);
        utf_free(utf_decoded);
        utf_free(utf_reencoded);
    });
    my_custom_assert(wcscmp(utf_reencoded->w_str, utf_encoded->w_str) == 0, {}, {
        utf_free(utf_encoded);
        utf_free(utf_decoded);
        utf_free(utf_reencoded);
    });
    utf_free(utf_encoded);
    utf_free(utf_decoded);
    utf_free(utf_reencoded);
    return 0;
}