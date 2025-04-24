; --- FELTIX BOOTLOADER ---
; v0.1.1

BITS 16		; Start in 16-bit real mode
ORG 0x7C00	; Origin - The BIOS loads us at 0x7C00

; VGA base address definition
%define VGA_BASE_ADDRESS 0xB8000

; Disk variable
disk db 0

; Program entrypoint
; Here we generally just focus on loading additional sectors and getting 32-bit up and running
start:
	; Disable hardware interrupts
	cli
	
        ; Set up segment registers
        xor ax, ax      ; Set AX
        mov ds, ax      ; Set DS
        mov es, ax      ; Set ES

	; Load sectors from disk
	mov [disk], dl 				; Stashing disk number
	mov ah, 0x2 				; BIOS interrupt for reading sectors from disk
	mov al, 1 				; Sectors to read
	mov ch, 0 				; Cylinder index
	mov dh, 0 				; Head index
	mov cl, 2 				; Sector index
	mov dl, [disk] 				; Disk index
	mov bx, main	 			; Target pointer (MUST be after the boot sector)
	int 0x13 				; Call BIOS
	
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
	dq 0x0		; Null descriptor

; Code segment
gdt32_code:
	dw 0xFFFF
	dw 0x0
	db 0x0
	db 10011010b
	db 11001111b
	db 0x0

; Data segment
gdt32_data:
	dw 0xFFFF
	dw 0x0
	db 0x0
	db 10010010b
	db 11001111b
	db 0x0

; GDT descriptor containing necessary information for LGDT
gdt32_definition:
	dw gdt32_end - gdt32_start
	dd gdt32_start

; End of GDT
gdt32_end:


; 32-bit entry
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
	jmp 0x08:main	; Far jump


; Other BIOS boot sector formalities
times 510 - ($ - $$) db 0 	; Pad to 510 bytes
dw 0xAA55			; Boot signature
; --- END OF BOOT SECTOR ---


; Start of sector 2
BITS 32


; Main userspace function
; Add any I/O functionality here
main:
	; Clear the screen
	call clear_screen
	
	; Print welcome message
	mov esi, welcome_message
	call print_string
	
	; Halt the CPU; we're done here
	cli
	hlt


; Function to clear the VGA screen (fill with black spaces)
clear_screen:
        pusha
        mov edi, VGA_BASE_ADDRESS       ; Start of VGA text Buffer
        mov ecx, 80 * 25                ; Number of cells
        mov ax, 0x0720                  ; Attribute + space character

.clear_loop:
        stosw                           ; Store word at [EDI], increment EDI by 2
        loop .clear_loop

        ; Reset the VGA cursor
        mov byte [cursor_row], 0
        mov byte [cursor_col], 0

        popa
        ret


; Function to print a string to VGA
print_string:
        pusha

        mov edi, VGA_BASE_ADDRESS       ; Start of VGA text buffer
        mov ah, 0x07                    ; Attribute: light grey on black

.print_loop:
        lodsb                           ; Load byte from ESI into AL, advance ESI
        cmp al, 0                       ; Check AL for a null terminator
        je .done                        ; Jump to .done

        cmp al, 0x0A                    ; Check AL for a newline (0x0A)
        je .newline                     ; Jump to .newline

        ; Load VGA cursor position
        movzx ebx, byte [cursor_row]
        movzx ecx, byte [cursor_col]

        ; Calculate offset: (row * 80 + col) * 2
        mov edx, ebx
        imul edx, 80
        add edx, ecx
        imul edx, 2                     ; Each character is 2 bytes
        add edx, 0xB8000                ; Start of VGA text buffer

        mov [edx], ax                   ; Print character + attribute

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


; Pad to 1024 bytes
times 1024 - ($ - $$) db 0

