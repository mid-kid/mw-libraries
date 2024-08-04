/* MSL
 * Copyright © 1995-2007 Freescale Corporation.  All rights reserved.
 *
 * $Date: 2007/01/29 18:10:50 $
 * $Revision: 1.2 $
 */

#include <ansi_parms.h>

#if _AEABI_PORTABILITY_LEVEL

#include <file_io.h>

const int __aeabi_IONBF=_IONBF;
const int __aeabi_IOLBF=_IOLBF;
const int __aeabi_IOFBF=_IOFBF;
const int __aeabi_BUFSIZ=256;

const int __aeabi_FOPEN_MAX=8;
const int __aeabi_TMP_MAX=256;
const int __aeabi_FILENAME_MAX=256;
const int __aeabi_L_tmpnam=256;

FILE *__aeabi_stdin =(&__std(__files[0]));

FILE *__aeabi_stdout =(&__std(__files[1]));

FILE *__aeabi_stderr =(&__std(__files[2]));

#endif /* _AEABI_PORTABILITY_LEVEL */

/* Change record:
 * cc  060428 Integrated _AEABI_PORTABILITY_LEVEL work 
 */