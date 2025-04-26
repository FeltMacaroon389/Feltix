ENTRY("start")
OUTPUT_FORMAT("elf32-i386")

SECTIONS {
	. = 0x7C00; /* Start at 0x7C00 */

	.text : {
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

