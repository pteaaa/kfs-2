CFLAGS:=-nostdlib -nodefaultlibs -fno-stack-protector -m32 -ffreestanding -Wall -Wextra
LIBS:= -nostdlib -lk -lgcc
LDFLAGS:=-m32 -T -ffreestanding -O2 -nostdlib

OBJS= kernel.o \
	boot.o \
	tty.o \
	utils.o \
	idt.o \
	handle_key.o \
	terminal_write.o \
	gdt.o \
	gdts.o

LINK_LIST=\
$(LDFLAGS) \
$(OBJS) \

.PHONY: all clean
.SUFFIXES: .o .c .asm

all: myos.kernel

myos.kernel: $(OBJS) linker.ld
	gcc -m32 -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib $(OBJS) 
	mkdir -p isodir/boot/grub
	cp myos.bin isodir/boot/myos.bin                                                    
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o myos.iso isodir
	qemu-system-i386 -cdrom myos.iso


.c.o:
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS)

.asm.o:
	nasm -felf32 boot.asm -o boot.o
	nasm -felf32 gdt.asm -o gdts.o

clean:
	rm -f myos.kernel
	rm -f $(OBJS) *.o 
	rm -f $(OBJS:.o=.d) *.d 
 
fclean: clean
	rm -rf myos.iso mys.bin isodir


-include $(OBJS:.o=.d)
