/* MSL
 * Copyright © 1995-2007 Freescale Corporation.  All rights reserved.
 *
 * $Date: 2007/01/29 18:11:28 $
 * $Revision: 1.27 $
 */

#pragma ANSI_strict off

#include <ansi_parms.h>

#if !_MSL_THREADSAFE || !_MSL_LOCALDATA_AVAILABLE

#include <errno.h>

	#if !defined(__MACH__)
		int errno;											/*- cc 011128 -*/
	#endif
	
	#if ((__dest_os == __mac_os) || (__dest_os == __mac_os_x))      /*- mm 010412 -*/
		short __MacOSErrNo;								/*- mm 010412 -*/	/*- cc 011128 -*/
	#endif
																/*- mm 010412 -*/
#endif /* _MSL_THREADSAFE */

/* Change record:
 * JFH 950612 First code release.
 * CVT 960415 Add TLS support for Win32
 * mf  980512 wince changes
 * mm  010412 Added global for storing MacOS OSErr values
 * JWW 011027 Added case for Mach-O to use a single errno storage location from the BSD C
 * cc  011128 Made __tls _MSL_TLS
 * JWW 020130 Changed _MWMT to _MSL_THREADSAFE for consistency's sake
 */