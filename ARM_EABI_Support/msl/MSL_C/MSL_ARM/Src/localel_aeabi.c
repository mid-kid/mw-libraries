/* MSL
 * Copyright © 1995-2007 Freescale Corporation.  All rights reserved.
 *
 * $Date: 2007/01/29 18:10:50 $
 * $Revision: 1.2 $
 */

#include <ansi_parms.h>

#if _AEABI_PORTABILITY_LEVEL

#include<locale.h>

const int 	__aeabi_LC_COLLATE  = 0x01;
const int 	__aeabi_LC_CTYPE    = 0x02;
const int 	__aeabi_LC_MONETARY = 0x04;
const int 	__aeabi_LC_NUMERIC  = 0x08;
const int 	__aeabi_LC_TIME     = 0x10;
const int 	__aeabi_LC_ALL      = 0x1F;

#endif /* _AEABI_PORTABILITY_LEVEL */

/* Change record:
 * cc  060428 Integrated _AEABI_PORTABILITY_LEVEL work 
 */
 
/* Chipwerks Change Record
 * 6/4/2006	For _AEABI_PORTABILITY_LEVEL macro,
 * __aeabi_localeconv() is defined.
 * __aeabi_LC_COLLATE,__aeabi_LC_CTYPE,__aeabi_LC_MONETARY,__aeabi_LC_NUMERIC,
 * __aeabi_LC_TIME,__aeabi_LC_ALL are defined for _AEABI_PORTABILITY_LEVEL macro
 */