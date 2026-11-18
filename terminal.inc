extern GetStdHandle
extern WriteConsoleA
section .data
    NEWLINE_MEMORY db 10

print_string: ;RDX - text
    mov rcx, -11
    push rdx
    sub rsp, 40
    call GetStdHandle
    add rsp, 40
    mov rcx, rax
    pop rdx
    xor r8, r8
    .print_string_loop:
        cmp byte[rdx+r8], 0
        je .print_string_loop_end
        inc r8
        jmp .print_string_loop
    .print_string_loop_end:
    
    sub rsp, 40
    lea r9, [rsp + 24]
    mov qword[rsp + 32], 0
    call WriteConsoleA
    add rsp, 40
    ret



newline: 
    mov rcx, -11
    sub rsp, 40
    call GetStdHandle
    add rsp, 40
    mov rcx, rax
    mov rdx, NEWLINE_MEMORY
    mov r8, 1
    sub rsp, 56
    lea r9, [rsp + 24]
    mov qword[rsp + 32], 0
    call WriteConsoleA
    add rsp, 56
    ret
