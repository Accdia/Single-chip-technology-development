BUF		EQU   33H       ;存放计数值
SBF		EQU   32H       ;存放秒值
MBF		EQU   31H       ;存放分值
HBF		EQU	  30H

ORG 0000H
	LJMP START
ORG 001BH
	LJMP CLOCK
ORG 0100H
START:
	MOV R0,#40H  ;40H-47H显示缓冲区，依次存放
	MOV A,#00H  	;时高位、分低位，0A，分高位、分低位、0A（横线）
	
	MOV @R0,A    ;以及秒高位、秒底位
	INC R0
	
	MOV @R0,A
	INC R0
	
	MOV A,#0AH   ;
	MOV @R0,A    ;42H(横线)
	INC R0
	
	MOV A,#00H	 ;
	MOV @R0,A	 ;43H
	INC R0
	
	MOV @R0,A	 ;44H
	INC R0
	
	MOV A,#0AH	 ;45H(横线)
	MOV @R0,A
	INC R0
	
	MOV A,#00H
	MOV @R0,A	 ;46H
	INC R0
	
	MOV @R0,A	 ;47H
	
	MOV BUF,#00H   	;置0
	MOV SBF,#00H
	MOV MBF,#00H
	MOV	HBF,#00H

	MOV SP,#0EFH
	
	MOV 36H,#0FH
	MOV 37H,#
	
	MOV TMOD,#2
	MOV TL0,#6
	MOV TH0,#6
	SETB TR0
	MOV IE,#82H
	MOV IP,#2
	
	DS1:
		MOV R0,#40H    	;置显示缓冲区首址
		MOV R2,#01H   ;置扫描初值,点亮最右边的LED6
		
		DS2:  
			MOV A,@R0     ;得到的段显码输出到段数据口
			
			ACALL TABLE
			
			MOV P0,A
			MOV A,R2       	;向位数据口P1输出位显码
			CPL A
			MOV P1,A   
			MOV R3,#0FFH   	;延时一小段时间
			
			DEL:
				NOP
			DJNZ R3,DEL
			
			INC R0         	;显示缓冲字节加一
			CLR C
			MOV A,R2
			RLC A          	;显码右移一位
			MOV R2,A      ;最末一位是否显示完毕?,如无则
		JNZ DS2        	;继续往下显示
			
		MOV R0,#47H
		MOV A,SBF      ;把秒值分别放于46H,47H中
		
		ACALL GET
		
		DEC R0         ;跳过负责显示"-"的两个字节
		;DEC R0
		MOV A,MBF      ;把分值分别放入43H,44H中
		
		ACALL GET
		
		DEC R0
		;DEC R0
		MOV A,HBF		;把时值分别放入43H,44H中
		
		LCALL GET
		
	LJMP DS1        	;转DS1从头显示起

	TABLE:
		INC A          	;取与数字对应的段码
		MOVC A,@A+PC
		RET
			
		DB 3FH,06H,5BH,4FH,66H,6DH,7DH, 07H, 7FH,6FH, 40H
			 
	GET:
		MOV R1,A     ;把从分或秒字节中取来的值的高
		ANL A,#0FH    	;位屏蔽掉,并送入缓冲区
		
		MOV @R0,A
		DEC R0
		
		MOV A,R1     ;把从分或秒字节中取来的值的低
		SWAP A         	;位屏蔽掉,并送入缓冲区
		ANL A,#0FH
		
		MOV @R0,A
		DEC R0        	;R0指针下移一位
	RET

	CLOCK:
		PUSH PSW
		PUSH ACC
		
		MOV PSW,#8
		
		DJNZ 37H,PTFOR
		
			DJNZ 36H,PTFOR
			
				MOV 36H,#0FH
				MOV 37H,#0A0H
				
				MOV R0,#32H
				MOV A,@R0
				
				ADD A,#1
				DA A
				
				MOV @R0,A
				
				CJNE A,#60H,PTFOR
					MOV @R0,#0
					DEC R0
					
					MOV A,@R0
					
					ADD A,#1
					DA A
					
					MOV @R0,A
					
					CJNE A,#60H,PTFOR
						MOV @R0,#0
						DEC R0
						
						MOV A,@R0
						
						ADD A,#1
						DA A
						
						MOV @R0,A
						
						CJNE A,#24,PTFOR
							MOV @R0,#0
		PTFOR:
		POP ACC
		POP PSW 
	RETI               ;中断返回
	
END
