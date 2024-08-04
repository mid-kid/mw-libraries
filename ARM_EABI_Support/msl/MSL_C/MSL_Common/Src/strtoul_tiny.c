/* MSL
 * Copyright © 1995-2007 Freescale Corporation.  All rights reserved.
 *
 * $Date: 2008/04/14 15:30:53 $
 * $Revision: 1.2.4.1 $
 */

/*
 *	Routines
 *	--------
 *		
 *
 *	Implementation
 *	--------------
 *			
 *		The string scanner is implemented as an extended Finite State Machine.
 *		A state diagram for it can be found in an accompanying TeachText
 *		document, 'strtoul syntax' (too bad pictures can't be imbedded in
 *		comments) in the "MSL Technical Notes" directory. A textual description 
 *      of it follows.
 *			
 *		The state transition loop dispatches to the appropriate code for the
 *		current state, while simultaneously watching for terminating
 *		conditions (field width exhausted, EOF encountered, final state
 *		reached).
 *			
 *		start
 *			
 *			Skip leading spaces. Process optional sign. Once a non-space is seen,
 *			trasition to next state.
 *			
 *		check_for_zero
 *			
 *			If 'base' is zero, then the base is either octal if there is a leading
 *			'0', hexadecimal if there is a leading '0X', or decimal if there is no
 *			leading zero at all. Also, if 'base' is 16, the leading '0X' may be
 *			optionally preset.
 *			
 *			If 'base' is zero or 16, check for a leading zero. If there one,
 *			transition to the next state. Otherwise, skip to state 'need_digit' to
 *			look for at least one digit (here a 'digit' is any alphanumeric; which
 *			'digits' are actually valid depends on the determined number base).
 *			
 *		leading_zero
 *			
 *			Having seen a leading zero, look for a subsequent 'X' (or 'x'). If
 *			present, the base is 16: transition to state 'need_digit' to look for
 *			at least one digit. If 'base' is zero, then the base must be 8.
 *			Transition to the state 'digit_loop' to scan the rest of the number.
 *			
 *		need_digit
 *		digit_loop
 *			
 *			The actions of these two states are identical. However, 'digit_loop'
 *			is a final state, whereas 'need_digit' is not (i.e., if scanning
 *			terminates in 'need_digit', the scan is invalid.
 *			
 *			If 'base' is still zero at this point, then the base must be 10.
 *			
 *			Loop on valid digits for the established base in this state,
 *			accumulating the corresponding numerical value. Keep on the lookout
 *			for overflow.
 *			
 *		finished
 *		failure
 *			
 *			These states are forced upon seeing the end of the numeric string in
 *			the combined need_digit/digit_loop state to signal whether the
 *			termination was valid or not.
 *
 *
 */

#include <ansi_parms.h>

#if _MSL_C_TINY_IO 

#include <ctype.h>
#include <limits.h>
#include <strtoul.h>
#include <strtold.h>
#include <stdlib.h>

unsigned long int __HI_strtoul(const char * nptr, char * *endptr, int base, unsigned int len){
  /* len == 0 -> now length specified */
  /* len > 0 -> length of digits == len */
  /* spaces, sign are not counted !! */
  unsigned long int lsum;
  const char * nptr0 = nptr;
  int val;
  unsigned char xCase= 0;

#if LIBDEF_ENABLE_OVERFLOW_CHECK
  char _errno= ERESET;
#endif
  lsum = 0;
  while (isspace((unsigned char)(*nptr))) {
    ++nptr;   /* Eat any white spaces    */
    if (--len == 0) {
      goto done; /*lint !e801 Use of goto is not deprecated */
    }
  }
  if (*nptr == '+') {
    ++nptr;
    if (--len == 0) {
      goto done;  /*lint !e801 Use of goto is not deprecated */
    }
  }
  if (base == 16) {                  /* Remove 0x or 0X, if any */
    if (*nptr == '0') {
      char nextCh= nptr[1];
      if (toupper((unsigned char)nextCh) == 'X') {
        nptr++;
        if (--len == 0) {
          goto done; /*lint !e801 Use of goto is not deprecated */
        }
        ++nptr;
        if (--len == 0) {
          goto done; /*lint !e801 Use of goto is not deprecated */
        }
        xCase= 1;
      }
    } /* end if */
  } else if (!base) {               /* Need to find base prefix */
    if (*nptr == '0') {              /* Hex or octal */
      char nextCh= nptr[1];
       if (toupper((unsigned char)nextCh) == 'X') {
         nptr++;
         if (--len == 0) {
           goto done; /*lint !e801 Use of goto is not deprecated */
         }
         base = 16; ++nptr;         /* Hex */
         if (--len == 0) {
           goto done; /*lint !e801 Use of goto is not deprecated */
         }
         xCase= 1;
       } else {
         base = 8;                  /* Octal */
       }
    } else {
      base = 10;                    /* Decimal */
    }
  } /* end if */
  /* check if first digit is legal */
  if (!CheckCharWithBase(*nptr, base, &val)) {
    if (xCase) {
      /* case _strtoul("0x?", NULL, 0, 100) */
      /* we already skipped the x, but now the 0 alone is the legal number */
      nptr--;
      len++;
      goto done; /*lint !e801 Use of goto is not deprecated */
    }
    /* we did not scan a legal number */
    nptr = nptr0;
    goto done; /*lint !e801 Use of goto is not deprecated */
  }
  if (base < 37) {
    while (CheckCharWithBase(*nptr, base, &val)) {
      CHECK_OVERFLOW(lsum, >, (ULONG_MAX - val) / base, ERANGE);
      lsum = lsum * base + val;
      ++nptr;
      if (--len == 0) {
        goto done; /*lint !e801 Use of goto is not deprecated */
      }
    } /* end while */
  } /* end if */
  done:
  if (endptr) {
    *endptr = (char *)nptr;
  }
#if LIBDEF_ENABLE_OVERFLOW_CHECK
  errno= _errno;
  if (_errno == ERANGE) {
    return ULONG_MAX;
  }
#endif
  return lsum;
} /* end strtoul */

long int __strtol(const char * nptr, char * *endptr, int base, unsigned int len) {
  /* len == 0 -> now length specified */
  /* len > 0 -> length of digits == len */
  /* spaces, sign are not counted !! */
   long int lsum;
   char nsgn;
   const char * nptr0 = nptr;

   lsum = 0; nsgn = 0;
   while (isspace((unsigned char)(*nptr))) {
     ++nptr;   /* Eat any white spaces */
     if (--len == 0) {
       if (endptr != NULL) {
         *endptr= (char *)nptr;
       }
       return 0;
     }
   }
   switch (*nptr) {
      case '-': nsgn = 1;            /* Set negative sign flag */
                /*lint -fallthrough */
      case '+': ++nptr;
                if (--len == 0) {
                  if (endptr != NULL) {
                     *endptr= (char *)nptr;
                  }
                  return 0;
                }
                /*lint -fallthrough */
      default:
        if (!(isdigit((unsigned char)(*nptr)))) {
          len += (nptr-nptr0);  /* << R2414: in case of moving back the pointer, adapt len */
          nptr = nptr0;
        }
   } /* end switch */
   lsum = __HI_strtoul(nptr, endptr, base, len);
   if (endptr != NULL && *endptr == nptr) {
     *endptr= (char * )nptr0; /* undo skipping of spaces/sign for illegal numbers */
   }
#if LIBDEF_ENABLE_OVERFLOW_CHECK
   if (errno == ERANGE) {
     return nsgn ? LONG_MIN : LONG_MAX;
   }
#endif
   if (nsgn) {
     return -lsum;
   }
   return lsum;
} /* end strtol */


unsigned long _MSL_CDECL strtoul(const char * _MSL_RESTRICT str, char ** _MSL_RESTRICT end, int base)
{
	return __HI_strtoul(str, end, base,0);
}


long _MSL_CDECL strtol(const char * _MSL_RESTRICT str, char ** _MSL_RESTRICT end, int base)
{
	return __strtol(str,end,base, 0);
}


static char CheckCharWithBase(char ch, int base, int *val) {
/* returns true, if character is compatible to base and sets val, returns false otherwise */
  if (ch >= '0' && ch <= '9') {
    *val = ch - '0';
  } else {
    ch = (char)toupper((unsigned char)ch);
    if (ch >= 'A' && ch <= 'Z') {
      *val = ch - 'A' + 10;
    } else {
      return 0; /* fail */
    }
  }
  if (*val < base) {
    return 1; /* ok */
  } else {
    return 0; /* fail */
  }
} /* CheckCharWithBase */



#if LIBDEF_HAS_ATOI_ATOL_ATOLL
int _MSL_CDECL atoi(const char * str)
{
        return(strtol(str, NULL, 10));
}

long _MSL_CDECL atol(const char * str)
{
        return(strtol(str, NULL, 10));
}

#if _MSL_C99
#if _MSL_LONGLONG
                        /*- cc 021209 -*/
long long _MSL_CDECL atoll(const char * str)
{
        return(strtoll(str, NULL, 10));
}
#endif
#endif /* _MSL_C99 */
#endif /* LIBDEF_HAS_ATOI_ATOL_ATOLL */

#endif /* _MSL_C_TINY_IO    */



/* Change record:
 * JFH 950616 First code release.
 * JFH 950727 Added code to ensure that *digits* as well as letters are within the acceptable
 *								 range for the numeric base.
 * JFH 951127 Merged relevant portions of strconv.c into this file.
 * JFH 960425 Fixed a bug where a char was pushed back into input stream at the end of
 *								 '__strtoul' after it was already converted to a binary digit.
 * mm  961220 Added code to support long long
 * mm  970102 Repaired strtoll and strtoull
 * mm  970110 Changed wrappers for msl long long support
 * mm  980720 Added support for inttypes.h
 * mm  981023 added wrappers round long long support
 * mm  981029 provided non long long support for strtoimax and strtoumax
 * mm  990325 Changes to allow use of input functions passed by pointer
 * mm  990817 Deleted include of <string_io.h
 * mm  000515 Removed definitions of strtoimax and strtoumax, now covered in cinttypes
 * mm  010423 Correction to prevent leading white space counting in field width in strtoul and strtoull
 * mm  010506 Correction to mm 010423 to make sure that in the event of failure, chars_scanned is set to zero.
 * cc  011203 Added _MSL_CDECL for new name mangling 
 * BLC 020829 implicit conversion errors fixes, atoi/atol not defined for Palm OS
 * JWW 020917 Added _MSL_RESTRICT to get the restrict type specifier for certain C99 functions
 * cc  021209 Added atoll
 * JWW 030224 Changed __MSL_LONGLONG_SUPPORT__ flag into the new more configurable _MSL_LONGLONG
 * mm  030225 Added C99 wrappers for LLONG_MAX and ULLONG_MAX
 * ejs 030723 Fix incorrect typecast in strtoll()
 * cc  070125 Added _MSL_C_TINY_IO
 */