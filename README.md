# CENCODE

This is a c library which encodes C string into various formats, however till now, only UTF-8 encoding-decoding has been implemented.

## Version

Current version is `0.0.4 ALPHA`.

## Platforms

It is a cross platform C11 library which has been built and run successfully in `Windows 10` and `Ubuntu Linux`. Please raise concern in case of any issues.

## Installation

You can clone the repository and simply use `make` to build the library.

```bash
git clone https://github.com/antaripchatterjee/CEncode.git
cd CEncode
make
```

The above commands will only build the debug version of the library, and it will also build an executable to test it's functionalities.

Use the below command to test them.

```bash
./test_utf8
```

Incase of any failed test case, please raise a concern.

If everything is fine, just execute the below command to build the stable static libraries.

```bash
make install
```

Use below command to clear all the builds and objects.

```bash
make clear
```

## API Usage

To encode your string into UTF-8 format, add the library and header files into your project and then you must include `utf8.h` header in your source code. It contains minimal number of C functions which let us encode the string data.

```C
#include <utf8.h>
...
```

### Type definitions

#### utf_method

The below `enum` are some methods which are used to identify the encoding or decoing operation.

```C
enum __utf_method {
    UNKNOWN,                            // Unknown method
    ENC_UTF_8,                          // Encoded to UTF-8 text
    DEC_UTF_8                           // Decoded from UTF-8 text
};

typedef enum __utf_method utf_method;   // Type definition of __utf_method
```

#### utf_t

The C structure `utf_t` is used as the return type of the function `utf8_encode` and `utf8_decode` function.

```C
struct __utf_t {
    wchar_t *w_str;                     // Holds the actual encoded or decoded text
    size_t w_size;                      // Can be used to get the lenght of the property w_str
    utf_method (*method)();             // Can be used to check if the property w_str is UTF-8 encoded or decoded string.
};

typedef struct __utf_t utf_t;           // Type definition for __utf_t
```

### Functions

#### utf8_encode

C function `utf8_encode` can be used to encode a text into UTF-8 format. The function signature is as below.

```C
extern utf_t* utf8_encode(const wchar_t*, size_t);
```

It takes two arguments, the first argument is the pointer of `wchar_t` and the second argument is the size of the input string, but if we keep it as `0`, then the function will recalculate the size of the input string.

#### utf8_decode

C function `utf8_decode` can be used to decode an encoded text into UTF-8 format. The function signature is as below.

```C
extern utf_t* utf8_decode(const wchar_t*, size_t);
```

It also takes two arguments, the first argument is the pointer of `wchar_t` which indeed an encoded text, and the second argument is the size of the encoded string, but if we keep it as `0`, then the function will recalculate the size of the encoded string.

#### copy_as_ustring

This C function is used to convert a pointer of `wchar_t` to the pointer of `unsigned char`.

```C
extern int copy_as_ustring(const wchar_t*, unsigned char*, size_t);
```

#### copy_as_wstring

This C function does a opposite job that the C function `copy_as_u_string`.

```C
extern int copy_as_wstring(const unsigned char*, wchar_t*, size_t);
```

>P.S: For both of the above functions, always add +1 to the length of the input string and pass it as a third argument.

#### stringify_utf_method

This function stringify the encoding or decoding method.

```C
extern const char* stringify_utf_method(utf_method);
```

As of now, the methods can be one of the below.
* "UNKNOW"
* "ENC_UTF_8"
* "DEC_UTF_8"

#### utf_free

This C function free the allocated memory of a valid pointer of `utf_t`. Signature is given below.

```C
extern void utf_free(utf_t*);
```

### Macros

#### ucslen

This C macro takes a valid pointer of `unsigned char` to calculate it's length.

```C
#define ucslen(__ucs) strlen((const char*) __ucs)
```

## License

This C library comes with [MIT]((https://github.com/antaripchatterjee/CEncode/LICENSE)) License.

## Development

Some major and minor changes will be applied in the future versions, however this library can be used safely.
