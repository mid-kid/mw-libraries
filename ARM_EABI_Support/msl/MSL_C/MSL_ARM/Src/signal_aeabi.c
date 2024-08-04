/* MSL
 * Copyright © 1995-2007 Freescale Corporation.  All rights reserved.
 *
 * $Date: 2007/01/29 18:10:51 $
 * $Revision: 1.2 $
 */

#include <ansi_parms.h>

#if _AEABI_PORTABILITY_LEVEL

#include <signal.h>

 const int __aeabi_SIGABRT = 6;
 const int __aeabi_SIGFPE = 8;
 const int __aeabi_SIGILL = 4;
 const int __aeabi_SIGINT = 2;
 const int __aeabi_SIGSEGV = 11;
 const int __aeabi_SIGTERM = 15;
 
 void __aeabi_SIG_DFL(int a) 
	{
		#pragma unused(a)
	}
void  __aeabi_SIG_IGN(int a) 
	{
		#pragma unused(a)

	}
void __aeabi_SIG_ERR(int a) 
	{
		#pragma unused(a)

	}
#endif /* _AEABI_PORTABILITY_LEVEL */

/* Change record:
 * cc  060428 Integrated _AEABI_PORTABILITY_LEVEL work 
 */
 
/*Chipwerks Change Record
 *6/4/2006 Refer Section 5.12 from "C Library ABI for the ARM architecture.pdf"
 *sig_atomic_t,__aeabi_SIGABRT,__aeabi_SIGFPE,__aeabi_SIGILL,__aeabi_SIGINT,
 *__aeabi_SIGSEGV,__aeabi_SIGTERM are defined for _AEABI_PORTABILITY_LEVEL macro
 */