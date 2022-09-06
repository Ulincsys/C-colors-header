
build:
	mkdir build
	gcc -c -Wall -Werror -fpic -o build/colors.o colors.c
	gcc -shared -o build/libcolors.so build/colors.o

install: build
	cp build/libcolors.so /usr/lib
	cp colors.h /usr/include
	chmod 0755 /usr/lib/libcolors.so
	ldconfig

.PHONY: remove
uninstall:
	rm /usr/lib/libcolors.so
	rm /usr/include/colors.h

test: build
	cd build && gcc -Wall -Werror -o color-test.out ../colorTest.c ../colors.c
	cd build && ./color-test.out

clean:
	rm -rf build
