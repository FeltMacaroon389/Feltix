OUTPUT_FORMAT("elf32-i386")
ENTRY(start)

SECTIONS {
	. = 0x7C00; /* Start at 0x7C00 */

	.text : {
		*(.bootloader)
		*(.text)
	}

	.rodata : {
		*(.rodata)
	}

	.data : {
		*(.data)
	}

	.bss : {
		*(COMMON)
		*(.data)
	}
}

