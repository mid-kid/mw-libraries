/* MSL
 * Copyright © 1995-2007 Freescale Corporation.  All rights reserved.
 *
 * $Date: 2007/01/29 18:10:50 $
 * $Revision: 1.7 $
 */

/* $Id: fenv_arm_ms.c,v 1.7 2007/01/29 18:10:50 cgalvan Exp $ */
#include <float.h>
#include <fenv.h>

#if _MSL_C99

_MSL_BEGIN_EXTERN_C

/*
 * The Microsoft <float.h> extensions.
 *
 * unsigned _controlfp(unsigned new, unsigned mask)
 *   Controls exception traps and rounding modes. For every bit of mask that is 
 *   zero, the corresponding control word bit is unchanged. For every bit of 
 *   mask that is nonzero, the corresponding control word bit is set to the 
 *   value of the corresponding bit of new.
 *        
 * unsigned _clearfp(void)
 *   Clears all five exception sticky flags, and returns their previous value.
 *
 * unsigned _statusfp(void)  
 *   Returns the current value of the exception sticky flags.
 */
 
/*
 * Because the _EM_ constants are shared between _controlfp (masks)
 * and _statusfp (sticky bits), we adopt the convention that
 * _controlfp will shift its arguments left by 8 bits before using
 * them.
 */

unsigned _controlfp(unsigned newCtrlBits, unsigned mask)
  {  
  mask <<= 8;
  newCtrlBits = (newCtrlBits << 8) & mask;
  return __ieee_status(newCtrlBits, mask) >> 8;
  }

unsigned _clearfp(void)
  {
  return __ieee_status(FE_IEEE_ALL_EXCEPT, 0) & _MCW_EM;
  }

unsigned _statusfp(void)
  {
  return __ieee_status(0,0) & _MCW_EM;
  }

_MSL_END_EXTERN_C
#endif /* _MSL_C99 */

/* Change record: 
 * cc  040128 Added C99 flag
 */