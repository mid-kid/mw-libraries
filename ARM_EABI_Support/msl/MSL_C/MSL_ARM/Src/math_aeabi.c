/* MSL
 * Copyright © 1995-2007 Freescale Corporation.  All rights reserved.
 *
 * $Date: 2007/01/29 18:10:50 $
 * $Revision: 1.2 $
 */

#include <ansi_parms.h>

#if _AEABI_PORTABILITY_LEVEL

#include <math.h>

const double	__aeabi_HUGE_VAL = (0x7FF0000000000000);
const float	__aeabi_HUGE_VALF = (0x7F800000);
const float __aeabi_INFINITY = (0x7F800000);
const long double	__aeabi_HUGE_VALL = (0x7FF0000000000000);	
const float __aeabi_NAN = 0x7FC00000;

#endif /* _AEABI_PORTABILITY_LEVEL */

/* Change record:
 * cc  060428 Integrated _AEABI_PORTABILITY_LEVEL work 
 */
 
/*Chipwerks Change Record
 *6/4/2006	Refer Section 5.10 of "C Library ABI for the ARM architecture.pdf"
 *__aeabi_HUGE_VAL,__aeabi_HUGE_VALL,__aeabi_HUGE_VALF,__aeabi_INFINITY,
 *__aeabi_NAN variables are defined for _AEABI_PORTABILITY_LEVEL macro
 */