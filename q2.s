		AREA MYCODE, CODE, READONLY
		ENTRY
		EXPORT __main

__main	MOV r0,#8
		MOV r1,#0
		CMP r0,r1
		BEQ stop
		AND r1,r0,#1
		CMP r1,#1
		BEQ loop1
		MOV r1,#256
		B stop
loop1	MOV r1,#512
		B stop

stop	B stop
		END


