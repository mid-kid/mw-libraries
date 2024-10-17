/* MSL
 * Copyright � 1995-2006 Freescale Corporation.  All rights reserved.
 *
 * $Date: 2006/02/08 20:33:05 $
 * $Revision: 1.23.2.2 $
 */
 
#ifndef _MSL_FLOAT_H
#define _MSL_FLOAT_H

#include <ansi_parms.h>

#if !_MSL_USING_MW_C_HEADERS
	#error You must have the non-MSL C header file access path before the MSL access path
#else

#include <cfloat>

#endif /* _MSL_USING_MW_C_HEADERS */

#endif /* _MSL_FLOAT_H */

/*
 * Change record
 * hh  971206 Created.
 * hh  991112 fixed "using bug"
 * JWW 001208 Added case for targeting Mach-O
 * JWW 011027 Use _MSL_USING_MW_C_HEADERS as generic header test instead of specific Mach-O test
 */