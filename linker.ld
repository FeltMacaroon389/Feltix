OUTPUT_FORMAT("elf32-i386")
ENTRY(start)

SECTIONS {
	. = 0x7C00;

	.text : {
		*(.bootloader)
		*(.text)
	} :text

	.rodata : {
		*(.rodata)
	} :text

	.data : {
		*(.data)
	} :data

	.bss : {
		*(.bss)
		*(COMMON)
	} :data
}

// Define program headers with permissions
PHDRS {
	text PT_LOAD FLAGS(0x5); // Read + Execute
	data PT_LOAD FLAGS(0x6); // Read + Write
}

