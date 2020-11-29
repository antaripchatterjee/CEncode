CC=gcc
CFLAGS=-Wall -lm -std=c11 -static-libgcc
INCLUDES=./include
BUILD_D=./build/debug
BUILD_R=./build/release
OBJECTS=./objects
AR=ar


all: test_utf8.o cencode
	$(CC) $(CFLAGS) -I$(INCLUDES) $(OBJECTS)/test_utf8.o $(BUILD_D)/cencode.a -o test_utf8

install: utf.o utf8.o
	$(AR) -rcs $(BUILD_R)/cencode.a $(OBJECTS)/utf.o $(OBJECTS)/utf8.o 

cencode: utf.o utf8.o
	$(AR) -rc $(BUILD_D)/cencode.a $(OBJECTS)/utf.o $(OBJECTS)/utf8.o 

utf.o: ./src/utf.c
	$(CC) $(CFLAGS) -I$(INCLUDES) -c ./src/utf.c -o $(OBJECTS)/utf.o

utf8.o: ./src/utf8.c
	$(CC) $(CFLAGS) -I$(INCLUDES) -c ./src/utf8.c -o $(OBJECTS)/utf8.o

test_utf8.o: ./test_utf8.c
	$(CC) $(CFLAGS) -I$(INCLUDES) -c ./test_utf8.c -o $(OBJECTS)/test_utf8.o

clean:
	rm -rf $(OBJECTS)/*.o
	rm -rf $(BUILD_R)/*.a
	rm -rf $(BUILD_D)/*.a
	rm -rf $(BUILD_D)/*.dll
	rm -rf $(BUILD_R)/*.dll
	rm -f test_utf8.exe
	rm -f test_utf8