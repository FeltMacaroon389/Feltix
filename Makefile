# Feltix Makefile

# Tools
AS = nasm
CC = i386-elf-gcc
OBJCOPY = i386-elf-objcopy

# Parameters
ASFLAGS = -f elf32
CCFLAGS = -nostdlib -ffreestanding -std=gnu99 -T linker.ld -I./include
OBJCOPYFLAGS = -O binary

# Directories
SRC_DIR = src
OBJ_DIR = obj
BUILD_DIR = build

# Output image name
OUT_IMG = feltix.img

# Emulator and flags
EMU = qemu-system-i386
EMUFLAGS = -drive format=raw,file=$(BUILD_DIR)/$(OUT_IMG) -smp 2 -m 64M

# Device to flash image to with "flash" target
# IMPORTANT: All data on this device will be LOST!
# Make sure this is fine before proceeding
FLASH_DEV = /dev/sda

# Phony targets
.PHONY: all help run flash clean

# By default, build the image
all: $(OUT_IMG)

# Display help about this Makefile and its options
help:
	@echo "Usage: make <target>"
	@echo " "
	@echo "Targets:"
	@echo "    <NO OPTIONS> - same as $(OUT_IMG)"
	@echo "    help - Display this help menu"
	@echo "    $(OUT_IMG) - Compile the final output image"
	@echo "    run - Compile the image and run it in an emulator (QEMU by default)"
	@echo "    flash - flash the image to a storage medium (currently $(FLASH_DEV))"
	@echo "    clean - Remove build files"
	@echo " "

# Build the image
$(OUT_IMG):
	mkdir -p $(OBJ_DIR) $(BUILD_DIR)

	$(AS) $(ASFLAGS) $(SRC_DIR)/boot.asm -o $(OBJ_DIR)/boot.o
	$(CC) $(CCFLAGS) $(SRC_DIR)/kernel.c $(OBJ_DIR)/boot.o -o $(OBJ_DIR)/feltix.elf
	
	$(OBJCOPY) $(OBJCOPYFLAGS) $(OBJ_DIR)/feltix.elf $(BUILD_DIR)/$(OUT_IMG)

# Run the image in an emulator
run: $(OUT_IMG)
	$(EMU) $(EMUFLAGS)

flash: $(OUT_IMG)
	dd if=$(BUILD_DIR)/$(OUT_IMG) of=$(FLASH_DEV) status=progress oflag=sync
	sync
	eject $(FLASH_DEV)

	@echo -e "\n$(OUT_IMG) successfully flashed to $(FLASH_DEV)!"
	@echo "You may now safely remove your device"

# Clean build files
clean:
	rm -rf $(OBJ_DIR) $(BUILD_DIR)

