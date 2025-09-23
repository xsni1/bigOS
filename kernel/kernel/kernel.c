#include <stdio.h>

#include <kernel/multiboot.h>
#include <kernel/tty.h>

void kernel_main(multiboot_info_t* mbd, unsigned int magic) {
	terminal_initialize();
	printf("Hello, kernel World!\n");

    printf("%d\n", magic);
}

