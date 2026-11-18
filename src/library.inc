bits 64
extern GetStdHandle
extern WriteConsoleA
extern WriteConsoleW
section .data
    NEWLINE db 10
section .bss
    VolatileStore resq 7
    CommonBuffer resb 32
    CurrentConsoleSettings resd 1
    CurrentStdInHandle resq 1
    CurrentStdOutHandle resq 1
section .text

StdOutHandle: ; RAX -> console handle
    sub rsp, 40
    mov rcx, -11 ; STD_OUTPUT_HANDLE
    call GetStdHandle
    mov [CurrentStdOutHandle], rax ; Store the console handle in CurrentStdOutHandle
    add rsp, 40
    ret

StdInHandle: ; RAX -> console handle
    sub rsp, 40
    mov rcx, -10 ; STD_INPUT_HANDLE
    call GetStdHandle
    mov [CurrentStdInHandle], rax ; Store the console handle in CurrentStdInHandle
    add rsp, 40
    ret
 



printFromMemory: ;RCX = text memory pointer, RDX = Ascii=1 UTF-16=2, <r8> = length of string 
    sub rsp, 40
    mov r10, rdx ; Store Ascii/UTF-16 flag in local variable
    mov rdx, rcx ; Store text memory pointer in local variable
    
    cmp Qword [CurrentStdOutHandle], 0
    jnz .handle_exists
    push r10
    push rdx
    call StdOutHandle 
    pop rdx
    pop r10
    .handle_exists:
    mov rcx, [CurrentStdOutHandle]
    

    test r8, r8
    jnz .write

    xor r8, r8  ; If length is not provided, set it to 0 to calculate length
    ; Validate Ascii/UTF-16 flag
    cmp r10, 1
    je .loop_ascii
    cmp r10, 2
    je .loop_utf16
    jmp .loop_ascii ; Default to Ascii if invalid flag

    ; Calculate string length
    .loop_ascii:
    cmp byte [rdx + r8], 0
    je .write
    inc r8
    jmp .loop_ascii

    .loop_utf16:
    cmp word [rdx + r8 * 2], 0
    je .write
    inc r8
    jmp .loop_utf16
    

    ; Write to console
    .write:
    sub rsp, 48

    lea r9, [rsp + 40] ; lpNumberOfCharsWritten (pointer to variable that receives the number of characters written)
    mov qword[rsp + 32], 0 ; lpReserved (must be NULL)
    

    cmp r10, 1
    jne .write_utf16
    call WriteConsoleA
    jmp .end_write
    
    .write_utf16:
    call WriteConsoleW
    
    .end_write:
    add rsp, 48
    xor r8, r8 ; Clear r8 to avoid side effects
    add rsp, 40
    ret



newLine: 
    sub rsp, 40
    cmp Qword [CurrentStdOutHandle], 0
    jnz .handle_exists
    call StdOutHandle ; Get console handle
    .handle_exists:
    mov rcx, [CurrentStdOutHandle] ; Console handle

    lea rdx, NEWLINE
    mov r8, 1 
    
    sub rsp, 48
    lea r9, [rsp + 40]
    mov qword[rsp + 32], 0
    
    call WriteConsoleA
    xor r8, r8 ; Clear r8 to avoid side effects
    add rsp, 88
    ret

