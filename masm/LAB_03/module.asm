EXTRN LETTER:byte
PUBLIC scan

SC2 SEGMENT para public 'CODE'
	assume CS:SC2
scan:
    mov ah, 08h
	int 21h	

    mov LETTER, al

	retf
SC2 ENDS
END