ALL=microprintf

all: ${ALL}
clean:
			rm -f ${ALL} *.o

# microprintf
microprintf: microprintf.c
	gcc -nostdlib -nostartfiles -fno-builtin -fno-stack-protector -O0 microprintf.c -o microprintf

