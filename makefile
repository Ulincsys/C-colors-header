# Add the build dir to the shared lib path for testing without installation
export LD_LIBRARY_PATH := build:$(LD_LIBRARY_PATH)

build:
	mkdir build
	gcc -c -Wall -Werror -Wpedantic -fpic --std=c11 -o build/colors.o colors.c
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
	# Link `colorTest.c` with the dynamic lib compiled in build:
	gcc -Wall -Werror -Wpedantic --std=c11 -L build/ -o build/color-test.out colorTest.c -lcolors
	./build/color-test.out

clean:
	rm -rf build
