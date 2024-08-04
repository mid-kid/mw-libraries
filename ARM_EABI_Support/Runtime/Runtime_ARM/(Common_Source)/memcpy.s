#define _AEABI 1
	
#ifdef _AEABI

	.public __rt_memcpy
	.public __rt_memcpy_w
	
	.public __aeabi_memcpy4
	.public __aeabi_memcpy8

	.text

__rt_memcpy:
         cmp         r2,#3
         bls         _memcpy_lastbytes   
         ands        r12,r0,#3
         beq         *+40                
         ldrb        r3,[r1],#1
         cmp         r12,#2
         add         r2,r2,r12
         ldrlsb      r12,[r1],#1
         strb        r3,[r0],#1
         ldrccb      r3,[r1],#1
         strlsb      r12,[r0],#1
         sub         r2,r2,#4
         strccb      r3,[r0],#1
_memcpy_dest_aligned:
         ands        r3,r1,#3
         beq         __rt_memcpy_w       
         subs        r2,r2,#4
         bcc         _memcpy_lastbytes   
         ldr         r12,[r1,-r3]!
         cmp         r3,#2
         beq         *+40                
         bhi         *+68                
_memcpy_src1_loop:
         mov         r3,r12,lsr #8
         ldr         r12,[r1,#4]!
         subs        r2,r2,#4
         orr         r3,r3,r12,lsl #24
         str         r3,[r0],#4
         bcs         *-20                
         add         r1,r1,#1
         b           _memcpy_lastbytes   
_memcpy_src2_loop:
         mov         r3,r12,lsr #16
         ldr         r12,[r1,#4]!
         subs        r2,r2,#4
         orr         r3,r3,r12,lsl #16
         str         r3,[r0],#4
         bcs         *-20                
         add         r1,r1,#2
         b           _memcpy_lastbytes   
_memcpy_src3_loop:
         mov         r3,r12,lsr #24
         ldr         r12,[r1,#4]!
         subs        r2,r2,#4
         orr         r3,r3,r12,lsl #8
         str         r3,[r0],#4
         bcs         *-20                
         add         r1,r1,#3
         b           _memcpy_lastbytes   
         
__aeabi_memcpy4:
__rt_memcpy_w:
__aeabi_memcpy8:
         						     			
         mov r6,#0
         mov r7,r4								
      up: 
      	  ldrb r3,[r7],#1					
      	  strb r3,[r6,r5]
      	  add r6,r6,#1 
          cmp r6,r2 
   	      bne up
   	      
   	     #ifdef THUMB
         	bxeq lr
         #else	
         	mov 		 pc,lr							               
   	      
_memcpy_aligned_loop:
         ldmcsia     r1!,{r3-r4,r12,lr}
         stmcsia     r0!,{r3-r4,r12,lr}
         ldmcsia     r1!,{r3-r4,r12,lr}
         stmcsia     r0!,{r3-r4,r12,lr}
         subcss      r2,r2,#32
         bcs         *-20                 
         
         #endif
_memcpy_lastbytes:
         movs        r2,r2,lsl #31
         ldrmib      r2,[r1],#1
         ldrcsb      r3,[r1],#1
         ldrcsb      r12,[r1],#1
         strmib      r2,[r0],#1
         strcsb      r3,[r0],#1
         strcsb      r12,[r0],#1
         #ifdef THUMB
         	bx lr
         #else	
         	mov 		 pc,lr
         #endif

#endif         

/* Chipwerks change record:
* April 07, 2006 Added with reference to 4.3.4 Memory copying, clearing, and setting,
* in RUN-TIME ABI FOR THE ARM ARCHITECTURE document
*/