global main
%include "src\library.inc"
section .data
welcome db "SnakeASM booting...", 10, 0
extern ExitProcess
section .data
    ScoreTitlePrefab db "Score: "
section .bss
    ScoreTitle resb 36
    ScoreNumberFormated resb 29
section .text
main:
    mov ebp, esp; for correct debugging
    push rbp
    mov rbp, rsp
    
    call newLine

    mov rcx, CurrentStdInHandle
    mov rdx, 1
    xor r8, r8
    call printFromMemory


    xor ecx, ecx
    call ExitProcess
    pop rbp
    ret


