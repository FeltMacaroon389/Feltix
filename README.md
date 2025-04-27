# Feltix

### Build instructions

- Install [dependencies](https://github.com/FeltMacaroon389/Feltix/tree/master#dependency-installation)

- Clone the repository: `git clone https://github.com/FeltMacaroon389/Feltix.git`

- Build with: `make`

For a list of Make commands and targets, run: `make help`

The output image will be located in the `build` directory.

### Dependency installation

#### **Required**:

**Arch Linux**: 
- Run: `sudo pacman -Sy git nasm make`
- You will also require **GNU GCC** for the **i386** CPU architecture. This can be installed from the [AUR](https://aur.archlinux.org/packages/i386-elf-gcc)
  - Run: `git clone https://aur.archlinux.org/i386-elf-gcc.git`
  - Next, `cd i386-elf-gcc`
  - Finally, `makepkg -si`
  - You may be prompted for your password during this.

**Debian/Ubuntu**: 
- Run: `sudo apt update && sudo apt install git nasm make`
- You will also require **GNU GCC** for the **i386** CPU architecture. We suggest you follow [this guide](https://wiki.osdev.org/GCC_Cross-Compiler).

#### **Optional**:

**Arch Linux**: 
- Run: `sudo pacman -Sy qemu-full`

**Debian/Ubuntu**:
- Run: `sudo apt update && sudo apt install qemu`

