/* MSL
 * Copyright © 1995-2007 Freescale Corporation.  All rights reserved.
 *
 * $Date: 2007/01/29 18:10:49 $
 * $Revision: 1.2 $
 */

#include <ansi_parms.h>

#if _AEABI_PORTABILITY_LEVEL

#include <errno.h>

volatile int * __aeabi_errno_addr()
{
	return &errno;
	
}	

#endif /* _AEABI_PORTABILITY_LEVEL */

/* Change record:
 * cc  060428 Integrated _AEABI_PORTABILITY_LEVEL work 
 */
 
/* Chipwerks Change Record
 * 6/4/2006	(*__aeabi_errno_addr()),__aeabi_EDOM,__aeabi_ERANGE,__aeabi_EILSEQ defined
 * for _AEABI_PORTABILITY_LEVEL macro. Refer Section 5.4 from "C Library ABI for the ARM architectures.pdf"
 */