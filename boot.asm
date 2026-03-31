; boot.asm
[BITS 32]
global start
extern kernel_main

start:
    mov esp, stack_top
    call kernel_main
    jmp $

section .bss
align 16
stack_bottom: resb 16384
stack_top: