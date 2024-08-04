/* MSL
 * Copyright © 1995-2007 Freescale Corporation.  All rights reserved.
 *
 * $Date: 2007/01/29 18:10:49 $
 * $Revision: 1.2 $
 */

/*
 *	Routines
 *	--------
 *		__msl_assertion_failed
 */

#include <ansi_parms.h>

#if _AEABI_PORTABILITY_LEVEL

#include <assert.h>
#include <assert_api.h>
#include <stdio.h>
#include <stdlib.h>

void __aeabi_assert(char const *condition, char const *filename, int lineno)
{
#if !_MSL_OS_DISK_FILE_SUPPORT

	#if _MSL_CONSOLE_SUPPORT
	#if _MSL_ASSERT_DISPLAYS_FUNC
		printf("Assertion (%s) failed in \"%s\", [ Function Name not available ] line %d\n", condition, filename, lineno);
	#else
		printf("Assertion (%s) failed in \"%s\", line %d\n", condition, filename, lineno);
	#endif /* _MSL_ASSERT_DISPLAYS_FUNC */
	#endif /* _MSL_CONSOLE_SUPPORT */

#else /* _MSL_OS_DISK_FILE_SUPPORT */

	#if _MSL_ASSERT_DISPLAYS_FUNC
		fprintf(stderr, "Assertion (%s) failed in \"%s\", function \"%s\", line %d\n", condition, filename, funcname, lineno);
	#else
		fprintf(stderr, "Assertion (%s) failed in \"%s\", line %d\n", condition, filename, lineno);
	#endif /* _MSL_ASSERT_DISPLAYS_FUNC*/

#endif /* _MSL_OS_DISK_FILE_SUPPORT */

abort();
}

#endif /* _AEABI_PORTABILITY_LEVEL */

/* Change record:
 * cc  060428 Integrated _AEABI_PORTABILITY_LEVEL work 
 */
 
/*Chipwerks Change Record
 * 6/4/2006	__aeabi_assert(..) definiton added.	Refer Section No. 5.2 from "C Library ABI for the ARM architecture.pdf" 
 */