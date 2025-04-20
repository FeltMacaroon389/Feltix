; --- FELTIX BOOTLOADER ---
; v0.1.0

BITS 16		; Start in 16-bit real mode
ORG 0x7C00	; Origin - The BIOS loads us at 0x7C0

; VGA base address definition
%define VGA_BASE_ADDRESS 0xB8000

; Program entrypoint
; Here we generally just focus on getting 32-bit up and running
start:
	; Disable hardware interrupts
	cli
	
	; Set up segment registers
	xor ax, ax	; Set AX
	mov ds, ax	; Set DS
	mov es, ax	; Set ES
	
	; Set up the 32-bit GDT
	lgdt [gdt32_definition]

	; Set PE bit in EFLAGS to enable protected mode (32-bit)
	mov eax, cr0	; Get the value of CR0
	or eax, 0x1	; Set the PE (protected mode enable) bit
	mov cr0, eax	; Write back the modified CR0
	
	; Jump to 32-bit entry
	jmp 0x08:protected_mode_entry

; Define the 32-bit GDT structure
gdt32_start:
	dq 0x0000000000000000		; Null descriptor
	dq 0x00CF9A000000FFFF		; Code segment (base 0, limit 0xFFFFF, 32-bit)
	dq 0x00CF92000000FFFF		; Data segment

gdt32_definition:
	dw gdt32_end - gdt32_start - 1	; GDT size in bytes
	dd gdt32_start			; Address of the GDT

gdt32_end:


; 32-bit entry
; This is where the *real* program begins
BITS 32
protected_mode_entry:
	; Reload the segment registers
	mov ax, 0x10	; Load the data segment descriptor (index 2)
	mov ds, ax	; Set DS
	mov es, ax	; Set ES
	mov ss, ax	; Set SS (stack segment)

	; Set up the stack (32-bit ESP)
	mov esp, 0x10000	; Set up the stack pointer 
	
	; Variables for keeping track of VGA cursor
	cursor_row db 0
	cursor_col db 0

	; Jump to the main userspace function
	jmp main


; Main userspace function
; Do any I/O functions here
main:
	; Clear the screen
	call clear_screen
	
	; Print welcome message
	mov esi, welcome_message
	call print_string

	; Halt the CPU; we're done here
	hlt


; Function to clear the VGA screen (fill with black spaces)
clear_screen:
	pusha
	mov edi, VGA_BASE_ADDRESS	; Start of VGA text Buffer
	mov ecx, 80 * 25		; Number of cells
	mov ax, 0x0720			; Attribute + space character

.clear_loop:
	stosw				; Store word at [EDI], increment EDI by 2
	loop .clear_loop
	
	; Reset the VGA cursor
	mov byte [cursor_row], 0
	mov byte [cursor_col], 0

	popa
	ret


; Function to print a string to VGA
print_string:
	pusha

	mov edi, VGA_BASE_ADDRESS	; Start of VGA text buffer
	mov ah, 0x07			; Attribute: light grey on black

.print_loop:
	lodsb				; Load byte from ESI into AL, advance ESI
	cmp al, 0			; Check AL for a null terminator
	je .done			; Jump to .done
	
	cmp al, 0x0A			; Check AL for a newline (0x0A)
	je .newline			; Jump to .newline

	; Load VGA cursor position
	movzx ebx, byte [cursor_row]
	movzx ecx, byte [cursor_col]

	; Calculate offset: (row * 80 + col) * 2
	mov edx, ebx
	imul edx, 80
	add edx, ecx
	imul edx, 2			; Each character is 2 bytes
	add edx, 0xB8000		; Start of VGA text buffer

	mov [edx], ax			; Print character + attribute

	; Move cursor forward
	inc byte [cursor_col]
	cmp byte [cursor_col], 80
	jl .print_loop

	; New line
	mov byte [cursor_col], 0
	inc byte [cursor_row]
	cmp byte [cursor_row], 25
	jl .print_loop

	; If we reached the bottom, reset
	mov byte [cursor_row], 0
	jmp .print_loop

.newline:
	mov byte [cursor_col], 0
	inc byte [cursor_row]
	cmp byte [cursor_row], 25
	jl .print_loop

	mov byte [cursor_row], 0
	jmp .print_loop

.done:
	popa
	ret


; Put your message variables here
welcome_message db "Welcome to Feltix!", 0x0A, 0


; Other BIOS boot formalities
times 510 - ($ - $$) db 0 	; Pad to 510 bytes
dw 0xAA55			; Boot signature

