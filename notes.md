### Cross-compiling

- Cross compiling in simple words is a process to compile code on host but targeting some other platform - which 
may be completely different CPU, OS, executable format.
- We will be compiling targeting i868 architecture, note that it belongs to the family of x86 (hence the name).
- i686-elf will be the target - it means that the compiled executable will be compatible with i686 arch and
will use ELF executable format.
- Building a cross compiler is essentialy very simple - using source code of gcc and binutils we compile it
targeting our target platform - that's all - such executables can be used to compile our OS targeting target platform
- Some claim that i686 = x86 32-bit - not sure? most likely not true!!

### Linker, ELF

- From my understanding it is linker's responsibility to create an ELF file
- In linker script we can define stuff like sections to organize how different stuff should be placed in the memory (and also in the ELF file), for example in linker script of this kernel we define that the multiboot header section should be placed early in the file.
- Those sections that we manage in linker file can/are defined in the assembly.
- I don't exactly know which part of the toolchain takes this linker and how it maps those different sections to virtual memory. 
        - GCC during compilation takes linker script.
        - Different sections are mmap'd into proper locations in the memory - section at some file offset => virtual memory address.
        https://wiki.osdev.org/ELF

### Multiboot format

This kernel is compatible with multiboot format, which means that every bootloader that is also compatible with this specification will be able to load it.
GRUB is one of such bootloaders.
How it works - in the first 8KB of the kernel binary there is couple of values that allow bootloader to determine what to do.
Those values include stuff like magic (it is used to locate the mutliboot header), flags oto configure some stuff and checksum of magic and flags.

### VGA Text Mode

This feels magic, I didn't expect much magic at such a low level but it still is.
There is some segment of memory, that is being 24/7 scanned/polled (?) by VGA (GPU?) and being drawn to the screen by this hardware.

### Header files

Headers are located in /usr/include directory - those are OS specific headers (libc etc.) (provided by the OS) - it seems like those are the headers that are omitted when compiling
gcc from sources with --without-headers flag. On the other hand, headers located in /lib/gcc/... (THOSE ARE STANDARD LIBRARY C HEADERS? - not really standard C library headers are split - some like stddef are defined in /lib/gcc, while other like stdio.h in /usr/include) are headers that are always with the compiler, even when compiling
freestading binary.

### Default library

Standard library is a set of functionalities defined by ISO standards (probably) - basically standard specifies names of those HEADERS - and it makes a lot of sense,
because if we have some C program that uses some standard C library functionalities it has to be portable on all OSes. If everyone used differenly named headers
it would not be possible.
So, ISO defines how our headers should be named and what functionalities they have to define - concrete libc implementation just implements those headers.

As I already know, each OS provides user-space library, that provides basic functionalities like strlen, printf etc.
Important thing to know is that kernel itself cannot use it! It is quite logical - we could cause circular dependency + those functions
quite ofte use syscalls that are implemented by kernel too.


### Build process

 1. make install-headers wrzuca headery w sysroot/usr/include/kernel/
 2 poniewaz do kompilacji dodawana jest flaga isystem=$INCLDUEDIR (INCLDUEDIR = /usr/include), kompilator wie gdzie szuakc headerow

     pytanie czemu inclduedir nie ma /sysroot/ - ok, nie ma /sysroot/, bo dodajemy flage --sysroot=$SYSROOT

     ok, tak offtopowo jeszzce: kompilator sam w sobie pracuje na jednym pliku, produkujac object jako output.
     on nie sprawdza czy header istnieje itp. to tez jest pewna forma "decouplowania",
     definiujemy sobie w ramach modulu czego oczekujemy od innej libki przy pomocy headera, i kompilujemy.
     a w osobnym juz stepie linker bierze nasz obiekt + obiekt libki, ktora to implementuje funkcjonalnosci ktorej my oczekujemy (to definijemy przy pomocy headera).



vars used:
export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

ABI (Application Binary Interface) refers to the calling conventions between functions, meaning what registers are used and what sizes the various C data types are. ISA (Instruction Set Architecture) refers to the instructions and registers a CPU has available.

Compiler - as an input takes a text (written in programming language) and outputs object (in assembly?)
Linker - links objects together, for example in the case of kernel, we take some assembly code that implements mutliboot header and using linker, link it together with kernel code that is written in C.
This multiboot header has to be in first 8KB (or so) of kernel - linker can do such thing.
