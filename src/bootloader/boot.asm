; --- FELTIX BOOTLOADER ---

; Bootloader section
section .bootloader

; Start in 16-bit real mode
BITS 16

; Define program entrypoint
global _start

; Disk variable
disk db 0

; Amount of sectors to load
; If something goes wrong without explanation, try incrementing this value
; If you get a disk error, lower it again
sectors db 30

; Program entrypoint
; Here we generally just focus on loading additional sectors and getting 32-bit protected mode up and running
_start:
	; Disable hardware interrupts
	cli
	
        ; Null out segment registers
	xor ax, ax
	mov ds, ax
	mov es, ax

	; Set a simple stack
	mov ax, 0x7A00
	mov ss, ax
	mov ax, 0xFFFE
	mov sp, ax
        mov bp, sp

	; Enable hardware interrupts
	sti

	; Print boot message
	mov si, boot_message
	call print_string_16

	; Load sectors from disk
	mov [disk], dl 		; Disk number
	mov ah, 0x2 		; BIOS interrupt for reading sectors from disk
	mov al, [sectors]	; Sectors to load
	mov ch, 0 		; Cylinder index
	mov dh, 0 		; Head index
	mov cl, 2 		; Sector index
	mov bx, kernel_wrapper 	; Target pointer (MUST be after the boot sector)
	int 0x13 		; Call BIOS
	jc .disk_error		; Jump to .disk_error upon failure
	
	; Set up the 32-bit GDT
	lgdt [gdt32_definition]
	
	; Enable A20 line
	in al, 0x92
	or al, 00000010b    ; Set bit 1 to enable A20
	out 0x92, al

	; Set PE bit in EFLAGS to enable protected mode (32-bit)
	mov eax, cr0	; Get the value of CR0
	or eax, 0x1	; Set the PE (protected mode enable) bit
	mov cr0, eax	; Write back the modified CR0
	
	; Jump to 32-bit entry
	jmp 0x08:protected_mode_entry

; Upon a disk error
.disk_error:
	; Disable hardware interrupts
	cli

	; Print error message
	mov si, disk_error_message
	call print_string_16

	; Wait for keypress
	call wait_for_keypress

	; Reboot the system
	mov al, 0FEh		; Reset command for 8042
	out 64h, al		; Send to keyboard controller

	; If that fails, try undefined
	ud2

	; If that still doesn't do the trick, settle with a hlt
	hlt

; Boot message
boot_message db "Booting Feltix...", 0x0A, 0x0A, 0

; Disk error message
disk_error_message db "Fatal error: Error Loading From Disk", 0x0A, "Press any key to reboot...", 0


; Function for printing strings in 16-bit real mode
print_string_16:
	lodsb			; Load byte at DS:SI into AL, increment SI
	or al, al		; Check for null terminator
	jz .done		; Jump to .done if null terminator
	
	cmp al, 0x0A		; Check for newline (LF)
	jz .newline		; Jump to .newline if newline

	mov ah, 0x0E		; BIOS teletype output function
	mov bh, 0x00		; Page number
	mov bl, 0x07		; Text attribute (light gray on black)
	int 0x10		; Call BIOS
	jmp print_string_16	; Continue the loop

.newline:
	; Print carriage return (\r)
	mov al, 0x0D
	mov ah, 0x0E
	mov bh, 0x00
	mov bl, 0x07
	int 0x10

	; Print line feed (\n)
	mov al, 0x0A
	mov ah, 0x0E
	mov bh, 0x00
	mov bl, 0x07
	int 0x10

	jmp print_string_16	; Continue the loop

.done:
	; Return from the function
	ret


; Function to wait for a keypress to continue
wait_for_keypress:
    xor ah, ah
    int 16h
    ret


; Define the 32-bit GDT (Global Descriptor Table) structure
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

; End of 32-bit GDT
gdt32_end:

; GDT descriptor containing necessary information for LGDT
gdt32_definition:
	dw gdt32_end - gdt32_start
	dd gdt32_start


; 32-bit protected mode entry
BITS 32
protected_mode_entry:
	; Refresh segment registers
	mov ax, 0x10	; Load the data segment descriptor
	mov ds, ax
	mov es, ax
	mov ss, ax	; Stack segment

	; Set up a stack (32-bit ESP)
	mov esp, 0x10000	; Set the stack pointer
	
	; Far jump to the kernel wrapper function
	jmp 0x08:kernel_wrapper


; Other BIOS boot sector formalities
times 510 - ($ - $$) db 0 	; Pad to 510 bytes
dw 0xAA55			; Boot signature


; Start of sector 2
BITS 32


; Kernel wrapper function
kernel_wrapper:
	; Disable hardware interrupts
	cli

	; Call kernel_main
	extern kernel_main
	call kernel_main
	
	; Any following code in this function will only execute if the kernel ever returns
	; (which it probably shouldn't if you've set it up correctly)

	; Just in case, halt the CPU
	hlt


; Pad to 1024 bytes
times 1024 - ($ - $$) db 0

