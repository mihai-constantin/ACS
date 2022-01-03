BITS 32
extern print_line
global mystery1:function
global mystery2:function
global mystery3:function
global mystery4:function
global mystery6:function
global mystery7:function
global mystery8:function
global mystery9:function

section .text

; SAMPLE FUNCTION
; Description: adds two integers and returns their sum
; @arg1: int a - the first number
; @arg2: int b - the second number
; Return value: int
; Suggested name: add
mystery0:
  push ebp
  mov ebp, esp
  mov eax, [ebp+8]
  mov ebx, [ebp+12]
  add eax, ebx
  leave
  ret

mystery1:
  push ebp
  mov ebp, esp
  leave
  ret

mystery2:
  push ebp
  mov ebp, esp
  leave
  ret

mystery3:
  push ebp
  mov ebp, esp
  leave
  ret

mystery4:
  push ebp
  mov ebp, esp
  leave
  ret

mystery5:
  push ebp
  mov ebp, esp
  leave
  ret

mystery6:
  push ebp
  mov ebp, esp
  leave
  ret

mystery7:
  push ebp
  mov ebp, esp
  leave
  ret

mystery8:
  push ebp
  mov ebp, esp
  leave
  ret

mystery9:
  push ebp
  mov ebp, esp
  leave
  ret
