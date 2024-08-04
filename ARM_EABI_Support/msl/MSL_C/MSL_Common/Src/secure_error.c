/* MSL
 * Copyright © 1995-2007 Freescale Corporation.  All rights reserved.
 *
 * $Date: 2007/07/26 21:16:26 $
 * $Revision: 1.10 $
 */

#define __STDC_WANT_LIB_EXT1__ 1
#include <ansi_parms.h>
#include <stdio.h>
#include <stdlib.h>


#ifndef _MSL_DEFAULT_CONSTRAINT_HANDLER
	#define _MSL_DEFAULT_CONSTRAINT_HANDLER ignore_handler_s
#endif /* _MSL_DEFAULT_CONSTRAINT_HANDLER */


static constraint_handler_t __msl_constraint_handler = NULL;

void _MSL_CDECL __msl_runtime_constraint_violation_s(const char * _MSL_RESTRICT msg, void * _MSL_RESTRICT ptr, errno_t error)
{
	if (__msl_constraint_handler)
		(*__msl_constraint_handler)(msg, ptr, error);
	else
		_MSL_DEFAULT_CONSTRAINT_HANDLER(msg, ptr, error);
}

constraint_handler_t _MSL_CDECL set_constraint_handler_s(constraint_handler_t handler)
{
	constraint_handler_t previous_handler;
	
	previous_handler = __msl_constraint_handler;
	if (previous_handler == NULL)
		previous_handler = &_MSL_DEFAULT_CONSTRAINT_HANDLER;
	__msl_constraint_handler = handler;
	
	return previous_handler;
}

void _MSL_CDECL abort_handler_s(const char * _MSL_RESTRICT msg, void * _MSL_RESTRICT ptr, errno_t error)
{
	#pragma unused(ptr)
#if !_MSL_OS_DISK_FILE_SUPPORT
	#pragma unused(msg,error)
#endif
	
#if _MSL_OS_DISK_FILE_SUPPORT
	if (msg)
		fprintf(stderr, "Error %d: %s\n", error, msg);
#endif /* _MSL_OS_DISK_FILE_SUPPORT */
	
	abort();
}

void _MSL_CDECL ignore_handler_s(const char * _MSL_RESTRICT msg, void * _MSL_RESTRICT ptr, errno_t error)
{
	#pragma unused(msg, ptr, error)
}

void _MSL_CDECL strict_handler_s(const char * _MSL_RESTRICT msg, void * _MSL_RESTRICT ptr, errno_t error)
{
	#pragma unused(ptr)
#if !_MSL_OS_DISK_FILE_SUPPORT
	#pragma unused(msg,error)
#endif
	
#if _MSL_OS_DISK_FILE_SUPPORT
	if (msg)
		fprintf(stderr, "Error %d: %s\n", error, msg);
#endif /* _MSL_OS_DISK_FILE_SUPPORT */
}

/* Change record:
 * JWW 050111 New file to handle diagnosed runtime constraint violations in secure library routines
 */