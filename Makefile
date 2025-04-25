# Feltix Makefile

# Tools
AS = nasm
LD = i386-elf-ld
OBJCOPY = i386-elf-objcopy

# Parameters
ASFLAGS = -f elf32
LDFLAGS = -m elf_i386 -T linker.ld
OBJCOPYFLAGS = -O binary

# Directories
SRC_DIR = src
OBJ_DIR = obj
BUILD_DIR = build

# Output image name
OUT_IMG = feltix.img

# Emulator and flags
EMU = qemu-system-i386
EMUFLAGS = -drive format=raw,file=$(BUILD_DIR)/$(OUT_IMG)

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
	$(LD) $(LDFLAGS) -o $(BUILD_DIR)/feltix.elf $(OBJ_DIR)/boot.o
	$(OBJCOPY) $(OBJCOPYFLAGS) $(BUILD_DIR)/feltix.elf $(BUILD_DIR)/$(OUT_IMG)

# Run the image in an emulator
run: $(OUT_IMG)
	$(EMU) $(EMUFLAGS)

# Clean build files
clean:
	rm -rf $(OBJ_DIR) $(BUILD_DIR)

