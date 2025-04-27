# Feltix Makefile

# Tools
AS = nasm
CC = i386-elf-gcc
OBJCOPY = i386-elf-objcopy

# Parameters
ASFLAGS = -f elf32
CCFLAGS = -nostdinc -nostdlib -ffreestanding -T linker.ld -I./include -std=gnu99
OBJCOPYFLAGS = -O binary

# Directories
SRC_DIR = src
OBJ_DIR = obj
BUILD_DIR = build

# Output image name
OUT_IMG = feltix.img

# Emulator
EMU = qemu-system-i386 -drive format=raw,file=$(BUILD_DIR)/$(OUT_IMG)

# Phony targets
.PHONY: all help run clean

# By default, build the image
all: $(OUT_IMG)

# Display help about this Makefile and its options
help:
	@echo "Usage: make <target>"
	@echo " "
	@echo "Targets:"
	@echo "    $(OUT_IMG) - Compile the final output image"
	@echo "    run - Compile the image and run it in an emulator (QEMU by default)"
	@echo "    clean - Remove build files"
	@echo " "

# Build the image
$(OUT_IMG):
	mkdir -p $(OBJ_DIR) $(BUILD_DIR)

	$(AS) $(ASFLAGS) $(SRC_DIR)/boot.asm -o $(OBJ_DIR)/boot.o
	$(CC) $(CCFLAGS) $(SRC_DIR)/kernel.c $(OBJ_DIR)/boot.o -o $(OBJ_DIR)/feltix.o
	
	$(OBJCOPY) $(OBJCOPYFLAGS) $(OBJ_DIR)/feltix.o $(BUILD_DIR)/$(OUT_IMG)

# Run the image in an emulator
run: $(OUT_IMG)
	$(EMU)

# Clean build files
clean:
	rm -rf $(OBJ_DIR) $(BUILD_DIR)

