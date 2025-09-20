#!/bin/bash

gcc -c kernel.c -o kernel.o -nostdlib -nodefaultlibs -fno-stack-protector -m32      
gcc -m32 -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

cp myos.bin isodir/boot/myos.bin                                                    
cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o myos.iso isodir
qemu-system-i386 -cdrom myos.iso

