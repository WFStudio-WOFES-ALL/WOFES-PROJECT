; boot.asm
[BITS 32]
global start
extern kernel_main

; Multiboot header (обязательно для QEMU)
section .multiboot
align 4
    dd 0x1BADB002          ; магическое число
    dd 0x03                ; флаги
    dd -(0x1BADB002 + 0x03); контрольная сумма

section .text
start:
    mov esp, stack_top
    call kernel_main
    jmp $

section .bss
align 16
stack_bottom: resb 16384
stack_top:
