Testing : 
	push    ax
        push    cx
        push    dx

		test ax,ax ;перевірка на знак, якщо від'ємне- виводяться 16 цифр, якшо додатнє, лише 4
		mov cx,12
		js m1
		jns m5



	m3:mov dl,20h ; пробіл між кожними 4-ма символами
	mov ah,02h
	int 21h 
	dec cx
	jmp m1


	m1:  jcxz m4 ; виведення букв FFFF,які в 16-й  СЧ вказують на від'ємне число
 	mov dl,46h
	mov ah,02h
	int 21h  

	mka: cmp cx,9 ; перевірка для пробіла між 4-ма символами
	jz m3
	cmp cx,5
	jz m3
	cmp cx,0
	jz m3
	jnz m11


	m11: jcxz m4 
	loop m1

             
	m4: mov dl,20h
	mov ah,02h
	int 21h 
	jmp m5
	

	m5:pop dx 
	pop cx
	pop ax
	jmp ShowHex  ; виклик переведення


ShowHex:
 	push    ax
        push    cx
        push    dx
           		   
	mov cl,     12 ; виведення по 4 біти(0...F), переведення числа в рядок
        mov dx,     ax      ; Збереження числа в DX


Steprep:
 
        mov     ax,     dx      ; Відновлення числа з АХ
        shr   ax,      cl       ; Зсув вправо на cl(кожного разу по 4)
        and     al,     0Fh     ; Отримання цифри в Al, від 0 до 15  
	adc     al,     90h     ; special hex conversion sequence
        daa                     ; корекція
        adc     al,     40h
        daa                     ; конвертування молодшого байту ах в аскіі
        int     29h             ; Виведення символа на екран
        sub     cl,     4       ; Зменшення cl на 4 для наступної цифри
        jns     Steprep         ; Якщо CL >= 0, то повторення
       


	mov DL, 104
	mov AH, 2

	int 21h

	mov DL, 0Dh
	mov AH, 2

	int 21h


	mov DL, 0Ah
	mov AH, 2

	int 21h 



	pop     dx
        pop     cx
        pop     ax
        ret



