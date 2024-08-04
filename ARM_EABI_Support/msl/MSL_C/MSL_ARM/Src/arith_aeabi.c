/* MSL
 * Copyright © 1995-2007 Freescale Corporation.  All rights reserved.
 *
 * $Date: 2007/01/29 18:10:49 $
 * $Revision: 1.2 $
 */


#include <ansi_parms.h>

#if _AEABI_PORTABILITY_LEVEL

#include "arith.h"
#include <limits.h>
#include <stdlib.h>

	const int __aeabi_MB_LEN_MAX = MB_LEN_MAX;
	const int __aeabi_JMP_BUF_SIZE;

	int __aeabi_MB_CUR_MAX(void)
	{
		return _MSL_MB_CUR_MAX;	
	}
#endif	/* _AEABI_PORTABILITY_LEVEL */

/* Change record:
 * cc  060428 Integrated _AEABI_PORTABILITY_LEVEL work 
 */
 
/* Chipwerks Change Record
 * 6/4/2006	__aeabi_MB_LEN_MAX,__aeabi_JMP_BUF_SIZE variables defined for _AEABI_PORTABILITY_LEVEL macro
 */