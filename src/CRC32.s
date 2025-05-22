section .note.GNU-stack noalloc noexec nowrite progbits ; for non-executable stack
section .text

global CRC32_ASM

CRC32_ASM:
    mov eax, 0xFFFFFFFF                 ; hash value in eax
    mov rcx, rsi                        ; remaining length in rcx (full length is in rsi)
    add rdi, rsi                        ; end of data in rdi

symbol:
    test  rcx, rcx                      ; finish if all the data computed (rcx = 0)
    jz    finish                        ;

    sub   rdi, rcx
    mov   dl, [rdi]
    add   rdi, rcx
    crc32 eax, dl
    dec   rcx
    jmp   symbol


finish:
    xor eax, 0xFFFFFFFF
    ret
