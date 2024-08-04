/* MSL
 * Copyright © 1995-2007 Freescale Corporation.  All rights reserved.
 *
 * $Date: 2007/02/02 13:53:20 $
 * $Revision: 1.4 $
 */

#include <ansi_parms.h>

#undef	_MSL_USE_INLINE
#define	_MSL_USE_INLINE 1
#undef	_MSL_INLINE
#define	_MSL_INLINE _MSL_DO_NOT_INLINE

#include <ctype.h>
#include <ctype_api.h>

#if _AEABI_PORTABILITY_LEVEL
unsigned char const __aeabi_ctype_table[__aeabi_cmap_size] =
	{/* Control characters 0-31*/
/*0,1,2,3,4*/				__C,__C,__C,__C,__C,

 	/*5,6,7,8,9*/				__C,__C,__C,__C,0x41,

 	/*10,11,12,13,14*/			0x41,0x41,0x41,0x41,__C,

 	/*15,16,17,18,19*/			__C,__C,__C,__C,__C,

 	/*20,21,22,23,24*/			__C,__C,__C,__C,__C,

 	/*25,26,27,28,29*/			__C,__C,__C,__C,__C,

 	/*30,31,32,33,34*/			__C,__C,0x5,__P,__P,

 	/*35,36,37,38,39*/			__P,__P,__P,__P,__P,

 	/*40,41,42,43,44*/			__P,__P,__P,__P,__P,

 	/*45,46,47,48,49*/			__P,__P,__P,DIGIX,DIGIX,

 	/*50,51,52,53,54*/			DIGIX,DIGIX,DIGIX,DIGIX,DIGIX,

 	/*55,56,57,58,59*/			DIGIX,DIGIX,DIGIX,__P,__P,

 	/*60,61,62,63,64*/			__P,__P,__P,__P,__P,

 	/*65,66,67,68,69*/			UPPCX,UPPCX,UPPCX,UPPCX,UPPCX,

 	/*70,71,72,73,74*/			UPPCX,__U,__U,__U,__U,

 	/*75,76,77,78,79*/			__U,__U,__U,__U,__U,

 	/*80,81,82,83,84*/			__U,__U,__U,__U,__U,

 	/*85,86,87,88,89*/			__U,__U,__U,__U,__U,

 	/*90,91,92,93,94*/			__U,__P,__P,__P,__P,

 	/*95,96,97,98,99*/			__P,__P,LOWCX,LOWCX,LOWCX,

 	/*100,101,102,103,104*/		LOWCX,LOWCX,LOWCX,__L,__L,

 	/*105,106,107,108,109*/		__L,__L,__L,__L,__L,

 	/*110,111,112,113,114*/		__L,__L,__L,__L,__L,

 	/*115,116,117,118,119*/		__L,__L,__L,__L,__L,

 	/*120,121,122,123,124*/		__L,__L,__L,__P,__P,

	/*125,126,127,128,129*/		__P,__P,__C,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0
	};
#if !_MSL_USE_INLINE
	 int isalnum(int c)
   {
   		return ((c < 0) || (c >= __aeabi_cmap_size)) ? 0:((int)(__aeabi_ctype_table[c]) & (__U+__L+__N));
   }
   	 int isblank(int c)
   {
   		   		return ((c < 0) || (c >= __aeabi_cmap_size)) ? 0:((c == 0x9) || (__aeabi_ctype_table[c] & __B));
   }

     int  isalpha(int c)
    {
    	return ((c < 0) || (c >= __aeabi_cmap_size)) ? 0:((int)(__aeabi_ctype_table[c]) & (__U+__L));
    }
     int  iscntrl(int c)
    {
    	return ((c < 0) || (c >= __aeabi_cmap_size)) ? 0:((int)(__aeabi_ctype_table[c]) & __C)	;
    }
     int  isdigit(int c)

    {
    	return ((c < 0) || (c >= __aeabi_cmap_size)) ? 0:((int)(__aeabi_ctype_table[c]) & __N);
    }
     int  isgraph(int c)
    {
    	return ((c < 0) || (c >= __aeabi_cmap_size)) ? 0:((int)(__aeabi_ctype_table[c])&(__L+__U+__N+__X+__P));
    }
     int islower(int c)
    {
    	 return  ((c < 0) || (c >= __aeabi_cmap_size)) ? 0:((int)(__aeabi_ctype_table[c]) & __L);
    }
     int isprint(int c)
    {
    	return ((c < 0) || (c >= __aeabi_cmap_size)) ? 0:((int)(__aeabi_ctype_table[c]) & (__L+__U+__N+__P+__B));
    }
     int ispunct(int c)
    {
    	 return ((c < 0) || (c >= __aeabi_cmap_size)) ? 0:((int)(__aeabi_ctype_table[c]) & __P);
    }
     int isspace(int c)
    {
    	 return ((c < 0) || (c >= __aeabi_cmap_size)) ? 0:((int)(__aeabi_ctype_table[c]) & __S);
    }

     int isupper(int c)
    {
    	return ((c < 0) || (c >= __aeabi_cmap_size)) ? 0:((int)(__aeabi_ctype_table[c]) & __U);
    }
     int isxdigit(int c)
    {
    	return ((c < 0) || (c >= __aeabi_cmap_size)) ? 0:((int)(__aeabi_ctype_table[c]) & __X);
    }

    int toupper(int c)
    {
    	return (((c < 0x61) || (c >= 0x7B)) ? c : (int) (c - 0x20));
    }

	int tolower(int c)
	{
		return (((c < 0x41) || (c >= 0x5B)) ? c : (int) (c + 0x20));
	}
   #endif
#endif /* _AEABI_PORTABILITY_LEVEL*/

/* Change record:
 * cc  060428 Integrated _AEABI_PORTABILITY_LEVEL work
 */

/* Chipwerks Change Record
 * 6/4/2006	__aeabi_ctype_table[] array and non inline functions are added for
 * _AEABI_PORTABILITY_LEVEL macro. Refer Section 5.3 from "C Library ABI for the ARM architecture.pdf"
 */