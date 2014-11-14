GLOBAL  _read_msw,_lidt
GLOBAL  _int_08_hand
GLOBAL	_int_09_hand
GLOBAL  _mascaraPIC1,_mascaraPIC2,_Cli,_Sti
GLOBAL  _debug
GLOBAL _in
GLOBAL _inb
GLOBAL _syscall
GLOBAL _int_80_hand
GLOBAL _outb
GLOBAL _sidt
GLOBAL _int_00_hand
GLOBAL _div_zero
GLOBAL _invalid_opcode
GLOBAL _int_06_hand
GLOBAL _int_05_hand
GLOBAL _check_bounds
GLOBAl _int_74_hand


EXTERN  int_08
EXTERN  int_80
EXTERN	keyboard_hand
EXTERN	div_by_zero_hand
EXTERN	invalid_opcode_hand
EXTERN  index_out_bounds_hand
EXTERN 	int_74_handler
EXTERN 	shell_init
EXTERN 	kmain



SECTION .text


_Cli:
	cli			; limpia flag de interrupciones
	ret

_Sti:

	sti			; habilita interrupciones por flag
	ret

_mascaraPIC1:			; Escribe mascara del PIC 1
	push    ebp
        mov     ebp, esp
        mov     ax, [ss:ebp+8]  ; ax = mascara de 16 bits
        out	21h,al
        pop     ebp
        retn

_mascaraPIC2:			; Escribe mascara del PIC 2
	push    ebp
        mov     ebp, esp
        mov     ax, [ss:ebp+8]  ; ax = mascara de 16 bits
        out	0A1h,al
        pop     ebp
        retn

_read_msw:
        smsw    ax		; Obtiene la Machine Status Word
        retn


_lidt:				; Carga el IDTR
        push    ebp
        mov     ebp, esp
        push    ebx
        mov     ebx, [ss: ebp + 6] ; ds:bx = puntero a IDTR 
	rol	ebx,16		    	
	lidt    [ds: ebx]          ; carga IDTR
        pop     ebx
        pop     ebp
        retn

_sidt:
	push ebp
	mov ebp, esp
	
	push eax
	mov eax, [ss:ebp + 8]
	sidt &eax
	
	pop eax
	leave
	ret


_int_08_hand:				; Handler de INT 8 ( Timer tick)
        push    ds
        push    es                      ; Se salvan los registros
        pusha                           ; Carga de DS y ES con el valor del selector
        mov     ax, 10h			; a utilizar.
        mov     ds, ax
        mov     es, ax                  
        call    int_08                 
        mov	al,20h			; Envio de EOI generico al PIC
	out	20h,al
	popa                            
        pop     es
        pop     ds
        iret

_int_09_hand:

	pusha
	
	cli
	call keyboard_hand
	sti

	call _eoi
	
	popa
	iret

_int_00_hand:
	pusha	

	call div_by_zero_hand
	
	
	mov al, 20h
	out 20h, al
	
	popa

	iret


_div_zero:
	pusha
	pushf

	mov ax, 0x02
	mov cx, 0x00

	div cx

	popa
	popf
	ret

_invalid_opcode:
	pusha	
	pushf
	
	ud2

	popa
	popf
	
	
	ret

_int_06_hand:
	pusha

	call invalid_opcode_hand

	mov al, 20h
	out 20h, al
		
	popa
	iret


_check_bounds:
	push ebp
	mov ebp, esp
	
	push ecx
	push edx

	mov ecx, [ebp + 8]
	mov edx, [ebp + 12]

	bound edx, [ecx]

	pop ecx
	pop edx
	leave
	ret

_int_05_hand:
	pusha

	call index_out_bounds_hand
	
	mov al, 0x20
	out 0x20, al
	
	popa
	iret
	

_eoi:
	push 	ebp
	mov	ebp, esp
	pusha	

	mov 	al,0x20
	out 	0x20,al

	popa
	leave
	ret

_in:
	push ebp
	mov ebp, esp
	pusha

	mov     edx, [ss:ebp+8]
    	xor     eax, eax
    	in      al, dx

	popa
	leave
	ret

_inb:
    	push    ebp
    	mov     ebp, esp
	
    	push    edx
	
    	mov     edx, [ss:ebp+8]
    	xor     eax, eax
    	in      al, dx
	
    	pop     edx
	
    	mov     esp, ebp
    	pop     ebp
	ret

_outb:
	push ebp
	mov ebp, esp

	push eax
	push edx	
	
	mov edx, [ss:ebp + 8] 
	mov eax, [ss:ebp + 12]

	out dx, al
	
	pop edx
	pop eax
	
	leave
	ret
	

_int_80_hand:
	push	ebp
	mov 	ebp, esp
	
	push 	edx
	push 	ecx
	push 	ebx
	push 	eax
	
	sti
	
	call int_80
	
	pop 	ebx
	pop 	ebx
	pop 	ecx
	pop 	edx
	
	leave
	iret

_syscall:
	push 	ebp
	mov 	ebp, esp

	push 	ebx	
	push 	ecx
	push 	edx

	pushf
	
	mov 	edx, [ebp + 20]
	mov 	ecx, [ebp + 16]
	mov 	ebx, [ebp + 12]
	mov 	eax, [ebp + 8]
	
	int 	80h	

	popf
	
	pop 	edx
	pop 	ecx
	pop 	ebx

	call	_eoi

	leave
	ret

_int_74_hand:
	push ebp
	mov ebp,esp
	
	pusha
	
	in al,60h
	push eax
	call int_74_handler

	mov al, 20h
	out 0xA0, al
	out 0x20, al
	pop eax
	popa

	leave
	iret


; Debug para el BOCHS, detiene la ejecució; Para continuar colocar en el BOCHSDBG: set $eax=0
;


_debug:
        push    bp
        mov     bp, sp
        push	ax
vuelve:	mov     ax, 1
        cmp	ax, 0
	jne	vuelve
	pop	ax
	pop     bp
        retn
