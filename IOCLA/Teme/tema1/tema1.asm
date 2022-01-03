; CONSTANTIN MIHAI - 321CD

%include "io.inc"

%define MAX_INPUT_SIZE 4096

section .data
    negative db 0
    aux dd 0
    val1 dd 0
    val2 dd 0
    aux_eax dd 0; copy of eax register
    aux_ecx dd 0; copy of ecx register

section .bss
	expr: resb MAX_INPUT_SIZE

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    
    GET_STRING expr, MAX_INPUT_SIZE

    ; initialize the registers
    xor eax, eax
    xor ebx, ebx
    xor ecx, ecx
    xor edx, edx
    
convert:
    mov al, byte [expr + ecx]
    
    test al, al; end of file
    je exit
    
    cmp al, 32; SPACE
    je space
    
    cmp al, 43; + operator
    je plus
    
    cmp al, 45; - operator
    je minus
    
    cmp al, 42; * operator
    je multiplication
    
    cmp al, 47; / operator
    je division
    
    sub al, 48; convert from ASCII to decimal
    imul edx, 10
    add edx, eax
    
    inc ecx
    jmp convert
    
minus:
    mov byte [negative], 1
    
    ; verify next character
    inc ecx
    mov al, byte [expr + ecx]
    
    cmp al, 48
    jge convert; digit character
    
    mov byte [negative], 0
    
    pop dword [val1]
    pop dword [val2]
    
    mov dword [aux_eax], eax
    
    mov eax, dword[val2]
    sub eax, dword[val1]
    
    push eax
    mov eax, dword [aux_eax]
    
    inc ecx
    jmp convert
    
plus:
    pop dword [val1]
    pop dword [val2]
    
    mov dword [aux_eax], eax
    
    mov eax, dword [val1]
    add eax, dword [val2]
    
    push eax
    
    mov eax, dword [aux_eax]
    
    add ecx, 2
    jmp convert

multiplication:
    pop dword [val1]
    pop dword [val2]
    
    mov dword [aux_eax], eax
    mov dword [aux_ecx], ecx
    
    mov eax, dword [val1]
    mov ecx, dword [val2]
    imul ecx
    
    push eax
    mov eax, dword [aux_eax]
    mov ecx, dword [aux_ecx]
    
    add ecx, 2
    xor edx, edx
    jmp convert
    
division:
    pop dword [val1]
    pop dword [val2]
    
    mov dword [aux_eax], eax
    mov dword [aux_ecx], ecx
    
    mov eax, dword [val2]
    cdq
    mov ecx, dword [val1]
    idiv ecx
    
    push eax
    mov eax, dword [aux_eax]
    mov ecx, dword [aux_ecx]
    
    add ecx, 2
    xor edx, edx
    jmp convert

space:
    cmp byte [negative], 1
    je negative_number
   
    jmp push_element

continue:
    mov byte [negative], 0
    xor edx, edx
    
    inc ecx
    jmp convert
    
negative_number:
    ; edx = edx - 2 * edx
    mov dword [aux], edx
    add dword [aux], edx
    sub edx, dword [aux]
    
push_element:
    push edx
    jmp continue
    
exit:
    pop eax
    PRINT_DEC 4, eax
    
    ret
