/* Metrowerks ARM Runtime Support Library 
 * Copyright © 2008 Freescale Corporation. All rights reserved. 
 * 
 * $Date: 2008/08/07 22:31:28 $ 
 * $Revision: 1.4 $ 
 */ 



/*
 *	nitro_console_io.c	-	redirect console I/O through NITRO SDK interface
 *    Library must be built with SUPPORT_NITROIO=1  to support printf and cout.
 *	OS_PutChar and OS_PutString only exists in SDK_DEBUG and SDK_RELEASE builds of the nitro SDK. 
 *	They do not exist in SDK_FINALROM.
 *
 */

#include "console_io.h"

#define SUPPORT_NITROIO 0




/*
 *	sys_writec		-	write a character to the console via NITRO SDK interface
 *
 */

static  void sys_writec(register void *cp)
{
#if SUPPORT_NITROIO==1
	OS_PutChar((char)(*(char *)cp));
#endif
}


/*
 *	sys_write0		-	write a nul-terminated string to the console via NITRO SDK interface
 *
 */

static  void sys_write0(register void *str)
{
#if SUPPORT_NITROIO==1
	extern void (*OS_PutString)(char *);
	(*OS_PutString)((char*)str);
#endif
}


/*
 *	sys_readc		-	read a character from the console via NITRO SDK interface
 *
 */

static  int sys_readc(void)
{
	return 0;
}


/*
 *	sys_exit		-	terminate an application via semihosting interface
 *
 */

void sys_exit()
{
	
}


/*
 *	__read_console	-	read from the console into 'buffer' until end-of-line or 'count' characters have been read
 *
 */

int __read_console(__std(__file_handle) handle, unsigned char *buffer, __std(size_t) *count, __std(__ref_con) ref_con)
{
	#pragma unused(handle, ref_con)
	__std(size_t) i, n;

	for (i = 0, n = *count; i < n; i++) {
		buffer[i] = sys_readc();
		/*	Metrowerks debugger returns '\r', while ARM debugger returns '\n',
			for 'return' key */
		if (buffer[i] == '\r' || buffer[i] == '\n')
		{
			*count = i + 1;
			break;
		}
	}
	
	return(__no_io_error);
}


/*
 *	__write_console	-	write 'count' bytes from 'buffer' to the console
 *
 */

int	__write_console(__std(__file_handle) handle, unsigned char *buffer, __std(size_t) *count, __std(__ref_con) ref_con)
{
	#pragma unused(handle, ref_con)
	unsigned char tmp;
	

	if ( *count > 1 ) 
	{
	
		// Save final character and terminate with NULL
		tmp = buffer[*count-1];
		buffer[*count-1] = 0;
		sys_write0(buffer);
		
		// final character
		sys_writec(&tmp);
	}
	else // *count <= 1
	{
		sys_writec(buffer);
	}	

	return(__no_io_error);
}


/*
 *	__close_console	-	close the console
 *
 */

int __close_console(__std(__file_handle) handle)
{
	#pragma unused(handle)

	return(__no_io_error);
}

/* Change record:
 * cc  Use generic reference constant instead of specific idle_proc in file I/O
 */
