# FeltixBoot Makefile
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
.PHONY: all run clean

# By default, build the image
all: $(OUT_IMG)

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

