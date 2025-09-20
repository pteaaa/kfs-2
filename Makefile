CFLAGS:=-nostdlib -nodefaultlibs -fno-stack-protector -m32 -ffreestanding -Wall -Wextra
LIBS:= -nostdlib -lk -lgcc
LDFLAGS:=-m32 -T -ffreestanding -O2 -nostdlib

SRC_DIR:= srcs
OBJ_DIR:= objs

SRCS := $(wildcard $(SRC_DIR)/*.c)
ASM_SRCS :=	$(wildcard $(SRC_DIR)/*.asm) 

OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS)) \
    	$(OBJ_DIR)/boot.o \
		$(OBJ_DIR)/gdts.o

LINK_LIST=\
$(LDFLAGS) \
$(OBJS) \

.PHONY: all clean
.SUFFIXES: .o .c .asm

all: myos.bin

myos.bin: $(OBJS) linker.ld
	gcc -m32 -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib $(OBJS) 
	mkdir -p isodir/boot/grub
	cp myos.bin isodir/boot/myos.bin                                                    
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o myos.iso isodir
	qemu-system-i386 -cdrom myos.iso


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS)

# Compilation de l'assembleur
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.asm
	@mkdir -p $(OBJ_DIR)
	nasm -felf32 $< -o $@


clean:
	rm -f myos.kernel
	rm -f $(OBJS) *.o 
	rm -f $(OBJS:.o=.d) *.d 
 
fclean: clean
	rm -rf myos.iso myos.bin isodir $(OBJ_DIR)


-include $(OBJS:.o=.d)
