# Feltix Makefile
# v0.1.0

# Assembler and flags
AS = nasm
ASFLAGS = -f bin

# Directories
SRC_DIR = src
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
	mkdir -p $(BUILD_DIR)
	$(AS) $(ASFLAGS) $(SRC_DIR)/boot.asm -o $(BUILD_DIR)/$(OUT_IMG)

# Run the image in an emulator
run: $(OUT_IMG)
	$(EMU)

# Clean build files
clean:
	rm -rf $(BUILD_DIR)

