
#ifdef ARM_EABI_EXC_HANDLING
	.export newfunc
	.export __ARM_ETInfo
	.text
	.extern __exception_table_start__
  	.extern __exception_table_end__
  	
  	.export eit_base
  	.export eit_limit

newfunc:
__ARM_ETInfo:
 
eit_base:
	.word 	__exception_table_start__-__ARM_ETInfo;
eit_limit: 
	.word 	__exception_table_end__-__ARM_ETInfo;
	
	bx lr
#endif 