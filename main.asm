%include "terminal.inc"
%include "structs.inc"


struc Sprite
    .y resb 1
    .x resb 1
    .tile_id resb 1
    .attr resb 1
endstruc

section .data
    is_running db 0 ;FLAG-BOOLEAN
    SCREEN_WIDTH equ 20
    SCREEN_HEIGHT equ 18
    testmsg db "Hello World!",0
    
section .bss
    frame_buffer resb 360
section .text
    global CMAIN

CMAIN:
    mov rbp, rsp; for correct debugging


    sub rsp, 40
    mov rdx, testmsg
    call print_string
    add rsp, 40
    sub rsp, 40
    call newline
    add rsp, 40
    sub rsp, 40
    mov rdx, testmsg
    call print_string
    add rsp, 40
    game_loop:

    ;gamecode




    ;[CHECKING: is_running -> false=end,true=gameloop]
    xor rax,rax
    mov al, byte[is_running]
    test al,al
    jnz game_loop
    end:
    ret

