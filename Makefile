# Feltix Makefile

# Tools
AS = nasm
CC = i386-elf-gcc
LD = i386-elf-ld
OBJCOPY = i386-elf-objcopy

# Parameters
ASFLAGS = -f elf32
CCFLAGS = -nostdlib -ffreestanding -std=gnu99 -T linker.ld -I./include
LDFLAGS = -T linker.ld
OBJCOPYFLAGS = -O binary

# Directories
SRC_DIR = src
OBJ_DIR = obj
BUILD_DIR = build

# C source files to compile
SRC_C := $(wildcard $(SRC_DIR)/*.c)

# C objects after compilation
OBJ_C := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_C))

# Output image name
OUT_IMG = feltix.img

# Emulator and flags
EMU = qemu-system-i386
EMUFLAGS = -drive format=raw,file=$(BUILD_DIR)/$(OUT_IMG) -smp 2 -m 64M -audiodev pa,id=speaker -machine pcspk-audiodev=speaker

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
$(OUT_IMG): $(OBJ_C)
	mkdir -p $(OBJ_DIR) $(BUILD_DIR)

	$(AS) $(ASFLAGS) $(SRC_DIR)/bootloader/boot.asm -o $(OBJ_DIR)/boot.o
	$(LD) $(LDFLAGS) $(OBJ_C) $(OBJ_DIR)/boot.o -o $(BUILD_DIR)/kernel.elf
	
	$(OBJCOPY) $(OBJCOPYFLAGS) $(BUILD_DIR)/kernel.elf $(BUILD_DIR)/$(OUT_IMG)

# Compile C source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CCFLAGS) -c $< -o $@

# Create obj directory if missing
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

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

