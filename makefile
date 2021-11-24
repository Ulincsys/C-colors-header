
build:
	mkdir build
	gcc -c -Wall -Werror -fpic -o build/colors.o colors.c
	gcc -shared -o build/libcolors.so build/colors.o

install: build
	cp build/libcolors.so /usr/lib
	cp colors.h /usr/include

clean:
	rm -rf build
