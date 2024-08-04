#define _AEABI 1
	
#ifdef _AEABI

	.public __rt_memclr
	.public __rt_memclr_w
	
	.public __aeabi_memclr
	.public __aeabi_memclr4
	.public __aeabi_memclr8
	
	.public _memset
	.public _memset_w
	
	.text 

__rt_memclr:
__aeabi_memclr:
         mov         r2,#0
_memset:
         cmp         r1,#4
         bcc         *+40            
         ands        r12,r0,#3
         beq         _memset_w       
         rsb         r12,r12,#4
         strb        r2,[r0],#1
         cmp         r12,#2
         strgeb      r2,[r0],#1
         sub         r1,r1,r12
         strgtb      r2,[r0],#1
         b           _memset_w       
_Bytes:
         movs        r12,r1,lsl #31
         strcsb      r2,[r0],#1
         strcsb      r2,[r0],#1
         strmib      r2,[r0],#1
         mov 		 pc,lr


__rt_memclr_w:
__aeabi_memclr8:
__aeabi_memclr4:
         mov         r2,#0
_memset_w:
         subs        r1,r1,#32
         stmfd       sp!,{lr}
         mov         lr,r2
         mov         r3,r2
         mov         r12,r2
_loop:
         stmcsia     r0!,{r2-r3,r12,lr}
         stmcsia     r0!,{r2-r3,r12,lr}
         subcss      r1,r1,#32
         bcs         *-12                   
         movs        r1,r1,lsl #28
         stmcsia     r0!,{r2-r3,r12,lr}
         stmmiia     r0!,{r2-r3}
         movs        r1,r1,lsl #2
         ldmfd       sp!,{lr}
         strcs       r2,[r0],#4
         mov 		 pc,lr
         strmib      r2,[r0],#1
         strmib      r2,[r0],#1
         tst         r1,#1073741824
         strneb      r2,[r0],#1
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