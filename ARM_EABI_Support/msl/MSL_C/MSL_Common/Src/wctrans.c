/* MSL
 * Copyright © 1995-2007 Freescale Corporation.  All rights reserved.
 *
 * $Date: 2007/02/19 21:56:12 $
 * $Revision: 1.30 $
 */

/*
 *	Routines
 *	--------
 *	
 *	towctrans
 *	wctrans
 *
 */

#pragma ANSI_strict off

#include <ansi_parms.h>

#if (_MSL_WIDE_CHAR || !_MSL_C_TINY_IO)
#if _MSL_C99									/*- mm 030305 -*/
#pragma ANSI_strict reset

#include <wctrans.h>
#include <string.h>
#include <wctype.h>

static const struct wctable 
{
	const char *string;
	wctype_t	value;
} 

wtable[] = 
{
	{"tolower", 1}, /*- cc P40043.c Execution passed -*/
	{"toupper", 2},
	{(const char *)0, 0}
};

wint_t _MSL_CDECL towctrans(wint_t c, wctrans_t value)
{
	return (value == 1 ? towlower(c):towupper(c)); /*- cc P40043.c Execution passed -*/
}

wctrans_t _MSL_CDECL wctrans(const char *name)
{
	int	i;
	
	for(i=0; wtable[i].string != 0; ++i)
	{
		if(strcmp(wtable[i].string, name) == 0)
		{
			return (wtable[i].value);
		}
	
	}

	return 0;
}

#endif /* _MSL_C99 */					/*- mm 030305 -*/
#endif /* #if _MSL_WIDE_CHAR */        /*- mm 981030 -*/

/* Change record:
 * JCM 980126 JCM  First code release.
 * mm  981030 Added #if _MSL_WIDE_CHAR wrappers
 * mm  990809 Changed includes 
 * cc  011203 Added _MSL_CDECL for new name mangling 
 * JWW 030224 Changed __NO_WIDE_CHAR flag into the new more configurable _MSL_WIDE_CHAR
 * mm  030305 Added _MSL_C99 wrapper
 * cc  060220 Changed the values of the mapping in wtable to be non-zero.  Modified 
 *            towctrans to map correctly with wtable.
 */