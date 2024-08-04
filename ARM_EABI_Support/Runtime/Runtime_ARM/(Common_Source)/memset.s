#define _AEABI 1

#ifdef _AEABI
		.public __aeabi_memset
		.public __aeabi_memset4
		.public __aeabi_memset8
		
		.extern _memset
		.extern _memset_w
		
		.text 

__aeabi_memset:
         and         r3,r2,#255
         orr         r2,r3,r3,lsl #8
         orr         r2,r2,r2,lsl #16
         b           _memset           
		
__aeabi_memset8:
__aeabi_memset4:
         and         r3,r2,#255
         orr         r2,r3,r3,lsl #8
         orr         r2,r2,r2,lsl #16
         b           _memset_w         

#endif		

/* Chipwerks change record:
* April 07, 2006 Added with reference to 4.3.4 Memory copying, clearing, and setting,
* in RTABIRTABIRUN-TIME ABI FOR THE ARM ARCHITECTURE document
*/