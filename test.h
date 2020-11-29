#ifndef __TEST_H__
#define __TEST_H__

#ifdef __cplusplus
extern "C" {
#endif

static int __test_case_id;

#define my_custom_assert(expr, _iftr, _iffa) ({\
    printf("[TEST %d] %s : ", ++__test_case_id, #expr); \
    if(expr) {\
        puts("PASSED"); \
        (_iftr); \
    } else { \
        puts("FAILED"); \
        (_iffa); \
        printf("\nAssertion Failed at " __FILE__ " :%d \n", __LINE__); \
        printf("In function %s: %s\n", __FUNCTION__, #expr); \
        exit(-999); \
    } \
})


#ifdef __cplusplus
}
#endif

#endif