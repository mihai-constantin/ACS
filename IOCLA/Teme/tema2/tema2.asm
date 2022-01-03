;CONSTANTIN MIHAI - 321CD

extern puts
extern printf
extern strlen

%define BAD_ARG_EXIT_CODE -1

section .data
filename: db "./input0.dat", 0
inputlen: dd 2263

fmtstr:            db "Key: %d",0xa, 0
usage:             db "Usage: %s <task-no> (task-no can be 1,2,3,4,5,6)", 10, 0
error_no_file:     db "Error: No input file %s", 10, 0
error_cannot_read: db "Error: Cannot read input file %s", 10, 0

section .text
global main

xor_strings:
        ;TASK 1
        enter 0, 0
        
        mov eax, dword [ebp + 8]    ;adresa de inceput pentru encoded_string
        mov ebx, dword [ebp + 12]   ;adresa de inceput a cheii
        
        push eax                    ;salvam valoarea pointer-ului pe stiva
        
iterate:
        mov dl, byte [eax]          ;parcurg byte cu byte string-ul
        test dl, dl
        je end_of_string
        xor dl, byte [ebx]
        mov byte [eax], dl
        inc eax
        inc ebx
        jmp iterate
       
end_of_string:
        pop eax                      ;restauram valoarea initiala a pointer-ului
        leave
        ret

rolling_xor:
	;TASK 2
        enter 0, 0
      
        mov eax, dword [ebp + 8]        ;adresa de inceput pentru encoded_string
        push eax                        ;salvam adresa de inceput a string-ului pe stiva
        mov bl, byte [eax]              ;memoram primul byte din sirul criptat
        inc eax

iterate_2:
        mov dl, byte [eax]
        test dl, dl                     ; verificam daca am ajuns la finalul sirului
        je end_of_string2
        
        mov cl, dl 
        xor dl, bl
        mov byte [eax], dl              ;salvam in eax valoarea data de operatia xor
        mov bl, cl
        inc eax
        jmp iterate_2
        
end_of_string2:
        pop eax     ;restauram adresa de inceput a string-ului   
        leave
        ret

xor_hex_strings:
       ;TASK 3
       enter 0, 0
       
       mov eax, dword [ebp + 8]     ;adresa de inceput pentru encoded_string
       mov ebx, dword [ebp + 12]    ;adresa de inceput a cheii
       
       push eax                     ;punem pe stiva adresa de inceput a string-ului
       push ebx                     ;punem pe stiva adresa de inceput a cheii
       
       xor ecx, ecx
       
iterate_two_bytes:
       mov dl, byte [eax + ecx]     ;iau primul caracter
       test dl, dl
       je end_iteration_two_bytes
       
       ;verific daca e litera
       cmp dl, 60
       jg letter
       
       ; caracterul este cifra
       sub dl, 48
       jmp shiftare
       
letter:
       sub dl, 87
shiftare:
       shl dl, 4                        ;shiftare la stanga cu 4 pozitii
       
       mov bl, byte [eax + ecx + 1]     ;iau al doilea caracter
       
       ;verific daca e litera
       cmp bl, 60
       jg letter2
       
       ; caracterul este cifra
       sub bl, 48
       jmp adunare
letter2:
       sub bl, 87
adunare:
       add dl, bl
       push ecx
       shr ecx, 1
       mov byte [eax + ecx], dl
       pop ecx
       add ecx, 2
       jmp iterate_two_bytes
       
end_iteration_two_bytes:
        mov byte [eax + ecx], 0
       
        xor ecx, ecx
        pop ebx         ;restauram adresa de inceput a cheii
        
iterate_two_bytes_key:
        ; adresa cheii e in ebx
        mov dl, byte [ebx + ecx]
        test dl, dl
        je end_iteration_two_bytes_key
        
        ;verific daca e litera
        cmp dl, 60
        jg letter_key
       
        ; caracterul este cifra
        sub dl, 48
        jmp shiftare_key
       
letter_key:
       sub dl, 87
shiftare_key:
       shl dl, 4                        ;shiftare la stanga cu 4 pozitii
       
       mov al, byte [ebx + ecx + 1]     ;iau al doilea caracter
       
       ;verific daca e litera
       cmp al, 60
       jg letter2_key
       
       ; caracterul este cifra
       sub al, 48
       jmp adunare_key
letter2_key:
       sub al, 87
adunare_key:       
       add dl, al
       push ecx
       shr ecx, 1
       mov byte [ebx + ecx], dl
       pop ecx
       add ecx, 2
       jmp iterate_two_bytes_key
        
end_iteration_two_bytes_key:
        mov byte [ebx + ecx], 0
        
        xor ecx, ecx
        pop eax         ;restaruram adresa de inceput a string-ului
        
        ;apelam functia de la task-ul 1 
        push ebx
        push eax
        call xor_strings
        pop eax
        add esp, 4

        leave
        ret
       
base32decode:
	;TASK 4
        enter 0, 0
        
        mov eax, dword [ebp + 8]    ;adresa de inceput pentru encoded_string
        mov ebx, eax                ;copiez adresa de inceput a string-ului in ebx
        
        xor ecx, ecx
        
iterate4:
        mov dl, byte [eax + ecx]
        cmp dl, 61                  ; verific daca am ajuns la semnul '='
        je done_iteration4
        
        ;verific daca e litera mare
        cmp dl, 64
        jg capital_letter
       
        ;caracterul este cifra
        sub dl, 24                  ; scad 24 pentru a obtine codificarea pentru cifre
        mov byte [eax + ecx], dl
        jmp continue_iteration4
       
capital_letter:
        sub dl, 65                  ; scad 65 pentru a obtine codificarea pentru litere
        mov byte [eax + ecx], dl
        
continue_iteration4:
        inc ecx
        jmp iterate4
        
done_iteration4:
        mov byte [eax + ecx], 0         ; pun terminatorul de sir la finalul string-ului
        
        xor ecx, ecx
        
iterate_eight_bytes:
        cmp byte [eax + ecx], 61          ;verific daca am ajuns la caracterul '='
        je end_of_string4
      
        ; primul byte
        mov dl, byte [eax + ecx]
        shl dl, 3
        inc ecx
        mov dh, byte [eax + ecx]
        shr dh, 2
        add dl, dh
        mov byte [ebx], dl
        
        ; al doilea byte
        mov dl, byte [eax + ecx]
        shl dl, 6
        inc ecx
        mov dh, byte [eax + ecx]
        shl dh, 1
        add dl, dh
        inc ecx
        mov dh, byte [eax + ecx]
        shr dh, 4
        add dl, dh
        inc ebx
        mov byte [ebx], dl
        
        ; al treilea byte
        mov dl, byte [eax + ecx]
        shl dl, 4
        inc ecx
        mov dh, byte [eax + ecx]
        shr dh, 1
        add dl, dh
        inc ebx
        mov byte [ebx], dl
        
        ; al patrulea byte
        mov dl, byte [eax + ecx]
        shl dl, 7
        inc ecx
        mov dh, byte [eax + ecx]
        shl dh, 2
        add dl, dh
        inc ecx
        mov dh, byte [eax + ecx]
        shr dh, 3
        add dl, dh
        inc ebx
        mov byte [ebx], dl
        
        ; al cincilea byte
        mov dl, byte [eax + ecx]
        shl dl, 5
        inc ecx
        mov dh, byte [eax + ecx]
        add dl, dh
        inc ebx
        mov byte [ebx], dl
        
        inc ecx
        inc ebx
        jmp iterate_eight_bytes
        
end_of_string4:
        leave
	ret

bruteforce_singlebyte_xor:
	; TASK 5
        enter 0, 0
        
        mov edx, dword [ebp + 8]    ;adresa de inceput a string-ului
        mov al, 0                   ;cheia initiala
        
        ;verificam daca string-ul obtinut dupa decodificare contine 'force'
        ;daca nu, incrementam cheia
        ;intervalul valorilor pentru cheie: [0x00, 0xFF]
repeat_until_find_key:
        xor ebx, ebx
        
iterate_5:
        mov cl, byte [edx + ebx]
        test cl, cl
        je finish_iterate
        xor cl, al
        mov byte [edx + ebx], cl
        inc ebx
        jmp iterate_5

finish_iterate:
       xor ebx, ebx
       
search_force:
        
        mov cl, byte [edx + ebx]
        test cl, cl
        je increment_key
        cmp byte [edx + ebx], 'f'           ;verific daca caracterul este egal cu 'f'
        jne not_equal
        
        mov cl, byte [edx + ebx + 1]
        test cl, cl
        je increment_key
        cmp byte [edx + ebx + 1], 'o'       ;verific daca caracterul este egal cu 'o'
        jne not_equal
        
        mov cl, byte [edx + ebx + 2]
        test cl, cl
        je increment_key
        cmp byte [edx + ebx + 2], 'r'       ;verific daca caracterul este egal cu 'r'
        jne not_equal
        
        mov cl, byte [edx + ebx + 3]
        test cl, cl
        je increment_key
        cmp byte [edx + ebx + 3], 'c'       ;verific daca caracterul este egal cu 'c'
        jne not_equal
        
        mov cl, byte [edx + ebx + 4]
        test cl, cl
        je increment_key
        cmp byte [edx + ebx + 4], 'e'       ;verific daca caracterul este egal cu 'e'
        jne not_equal
        
        ; aici am gasit substringul 'force'
        jmp finish_task5
        
not_equal:
        inc ebx
        jmp search_force
        
increment_key:       
        xor ebx, ebx
        
restore_string:
        ;trebuie sa fac restore ca sa obtin string-ul initial
       
        mov cl, byte [edx + ebx]
        test cl, cl
        je end_restore
        xor cl, al
        mov byte [edx + ebx], cl
        inc ebx
        jmp restore_string

end_restore:
        inc al              ;incrementez valoarea cheii
        cmp al, 0xFF
        jne repeat_until_find_key
        
finish_task5:
        mov ecx, edx         ;pun in ecx adresa de inceput a string-ului
        leave
        ret
        
decode_vigenere:
	;TASK 6
        enter 0, 0
        
        mov eax, dword [ebp + 8]        ;adresa de inceput pentru encoded_string
        mov ebx, dword [ebp + 12]       ;adresa de inceput a cheii
      
        push eax                        ;salvam adresa de inceput a string-ului pe stiva
        push ebx                        ;salvam adresa de inceput a cheii pe stiva
        
iterate6:
        mov dl, byte [eax]
        test dl, dl
        je end_of_string6
        
        mov cl, byte [ebx]
        test cl, cl
        je end_of_key

cont_iteraion6:
        ;verific daca caracterul curent este litera
        cmp dl, 97
        jl continue_it
    
        cmp dl, 122
        jg continue_it
        
        ; caracter litera
        mov ch, cl
        sub ch, 97
        
        mov dh, dl
        sub dh, 97
        
        ; verific daca prin scaderea valorii din ch cu valoarea din dh 
        ; voi obtine un cod mai mic decat cel al lui 'a'
        ; daca da, ma duc la 'z' si ma intorc atatea pozitii cate imi raman
        cmp ch, dh
        jg queue
        
        ; aici nu este nevoie de intoarcerea la 'z'
        sub dl, ch
        mov byte [eax], dl
        jmp continue_iteration
        
queue:
        sub ch, dh
        mov cl, 122
        sub cl, ch
        inc cl
        mov byte [eax], cl
        
continue_iteration:
        inc eax
        inc ebx
        jmp iterate6
        
end_of_key:
        pop ebx
        push ebx
        jmp iterate6
        
continue_it:
        inc eax
        jmp iterate6
       
end_of_string6:
        pop ebx ;restauram adresa de inceput a cheii
        pop eax ;restauram adresa de inceput a string-ului
        leave
        ret

main:
	push ebp
	mov ebp, esp
	sub esp, 2300

	; test argc
	mov eax, [ebp + 8]
	cmp eax, 2
	jne exit_bad_arg

	; get task no
	mov ebx, [ebp + 12]
	mov eax, [ebx + 4]
	xor ebx, ebx
	mov bl, [eax]
	sub ebx, '0'
	push ebx

	; verify if task no is in range
	cmp ebx, 1
	jb exit_bad_arg
	cmp ebx, 6
	ja exit_bad_arg

	; create the filename
	lea ecx, [filename + 7]
	add bl, '0'
	mov byte [ecx], bl

	; fd = open("./input{i}.dat", O_RDONLY):
	mov eax, 5
	mov ebx, filename
	xor ecx, ecx
	xor edx, edx
	int 0x80
	cmp eax, 0
	jl exit_no_input

	; read(fd, ebp - 2300, inputlen):
	mov ebx, eax
	mov eax, 3
	lea ecx, [ebp-2300]
	mov edx, [inputlen]
	int 0x80
	cmp eax, 0
	jl exit_cannot_read

	; close(fd):
	mov eax, 6
	int 0x80

	; all input{i}.dat contents are now in ecx (address on stack)
	pop eax
	cmp eax, 1
	je task1
	cmp eax, 2
	je task2
	cmp eax, 3
	je task3
	cmp eax, 4
	je task4
	cmp eax, 5
	je task5
	cmp eax, 6
	je task6
	jmp task_done

task1:
	; TASK 1: Simple XOR between two byte streams

	; TODO TASK 1: find the address for the string and the key
	; TODO TASK 1: call the xor_strings function
     
        push ecx
        call strlen
        pop ecx

	add eax, ecx
	inc eax

	push eax
	push ecx                   ;ecx = address of input string 
	call xor_strings
	pop ecx
	add esp, 4

	push ecx
	call puts
	add esp, 4

	jmp task_done

task2:
	; TASK 2: Rolling XOR

	; TODO TASK 2: call the rolling_xor function
        push ecx
        call rolling_xor
        add esp, 4
    
	push eax
	call puts
	add esp, 4

	jmp task_done

task3:
	; TASK 3: XORing strings represented as hex strings

	; TODO TASK 1: find the addresses of both strings
	; TODO TASK 1: call the xor_hex_strings function

        push ecx
        call strlen
        pop ecx

	add eax, ecx
	inc eax

	push eax
	push ecx                   ;ecx = address of input string 
	call xor_hex_strings
	pop ecx
	add esp, 4

	push ecx
	call puts
	add esp, 4

	jmp task_done

task4:
	; TASK 4: decoding a base32-encoded string

	; TODO TASK 4: call the base32decode function
	
        push ecx
        call base32decode
        add esp, 4

	push eax
	call puts                    ;print resulting string
	add esp, 4
	
	jmp task_done

task5:
	; TASK 5: Find the single-byte key used in a XOR encoding

	; TODO TASK 5: call the bruteforce_singlebyte_xor function

        push ecx
        call bruteforce_singlebyte_xor
        add esp, 4
        
        push eax ;salvez valoarea cheii
        
	push ecx                    ;print resulting string
	call puts
	pop ecx
    
        pop eax ;restaurez valoarea cheii
        
	push eax                    ;eax = key value
	push fmtstr
	call printf                 ;print key value
	add esp, 8

	jmp task_done

task6:
	; TASK 6: decode Vignere cipher

	; TODO TASK 6: find the addresses for the input string and key
	; TODO TASK 6: call the decode_vigenere function

	push ecx
	call strlen
	pop ecx

	add eax, ecx
	inc eax

	push eax
	push ecx                   ;ecx = address of input string 
	call decode_vigenere
	pop ecx
	add esp, 4

	push ecx
	call puts
	add esp, 4

task_done:
	xor eax, eax
	jmp exit

exit_bad_arg:
	mov ebx, [ebp + 12]
	mov ecx , [ebx]
	push ecx
	push usage
	call printf
	add esp, 8
	jmp exit

exit_no_input:
	push filename
	push error_no_file
	call printf
	add esp, 8
	jmp exit

exit_cannot_read:
	push filename
	push error_cannot_read
	call printf
	add esp, 8
	jmp exit

exit:
	mov esp, ebp
	pop ebp
	ret
