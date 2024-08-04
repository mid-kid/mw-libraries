/* MSL
 * Copyright © 1995-2007 Freescale Corporation.  All rights reserved.
 *
 * $Date: 2008/04/14 15:30:53 $
 * $Revision: 1.5.2.2 $
 */

/*	Functions:
 *	---------	
 *		parse_format
 *		long2str
 *		longlong2str
 *		double2hex
 *		round_decimal
 *		float2str
 *		__pformatter
 *		__FileWrite
 *		__StringWrite
 *
 *	Routines
 *	--------
 *		
 *		vfprintf
 *		vfprintf_s
 *		fprintf
 *		fprintf_s
 *
 *		vprintf
 *		vprintf_s
 *		printf
 *		printf_s
 *
 *		vsprintf
 *		vsprintf_s
 *      vsnprintf
 *      vsnprintf_s
 *		sprintf
 *		sprintf_s
 *		snprintf
 *		snprintf_s
 */


#define __STDC_WANT_LIB_EXT1__ 1

#include <ansi_parms.h>

#if _MSL_C_TINY_IO 

#include <critical_regions.h>
#include <ctype.h>
#include <limits.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <console_io.h>



/******************************************************/
/**
* @file libdefs.h
* Library configuration definitions.
* This file contains all defines to configure the library build.
* Normally they can be set on the compiler command line during library build,
* e.g. the compiler option
*   -DLIBDEF_FAR_HEAP=1
* would enable that the library is build for a 'far' memory used by malloc, free,...
* NOTE: you have to set the define to zero or one, just -DLIBDEF_FAR_HEAP is wrong!
*
* If the following defines are NOT set on the compiler command line, a default is assumed.
* Note that not all configuration defines may be available for a target, e.g. if the

/*****************************************************
     printf.c - ANSI-C library: sprintf, vprintf                  
 ----------------------------------------------------
   Copyright (c) Metrowerks, Basel, Switzerland
               All rights reserved
                  Do not modify!
 *****************************************************/
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#include <errno.h>
#include <ctype.h>
//#include <hidef.h>
//#include <libdefs.h>
#if _MSL_WIDE_CHAR
#include <wctype.h>
#endif
#if _MSL_TESTING_TINY_IO
#include <buffer_io.h>
#endif

#ifdef __HC12__
  #pragma MESSAGE DISABLE C12002 /* WARNING C12002: Use DPAGE, PPAGE, EPAGE to specify the page register. Assumed DPAGE */
  #pragma MESSAGE DISABLE C12056 /* WARNING C12056: SP debug info incorrect because of optimization or inline assembler */
#endif

#if defined(__M68K__) && defined(__CPU81__)
  #pragma OPTION ADD PMC81NC "-Pmc81nC"
#endif

#if defined(__COLDFIRE__)
#ifndef LIBDEF_PRINTF_LONG
#define LIBDEF_PRINTF_LONG 1
#endif
#endif

/* Is ok in these cases : */
//#pragma MESSAGE DISABLE C5919 /* WARNING C5919: Conversion of floating to unsigned integral */
/* OK for cases like sizeof(...) == sizeof(...) */
//#pragma MESSAGE DISABLE C4001 /* INFORMATION C4001: Condition always is FALSE */
/* OK for this case */
//#pragma MESSAGE DISABLE C5703 /* INFORMATION C5703: This: parameter declared in function outc_callback but not referenced */

/* flag bits (vprintf) */

#if LIBDEF_PRINTF_LONG
  #define _PRINTF_INTEG long
#else
  #define _PRINTF_INTEG int
#endif

#define _PRINTF_OCTINT  0x1
#define _PRINTF_HEXINT  0x2
#define _PRINTF_NOT_DEC (_PRINTF_HEXINT | _PRINTF_OCTINT)

#if LIBDEF_PRINTF_FLOATING
  #define _PRINTF_ETYPE 0x1
  #define _PRINTF_FTYPE 0x2
  #define _PRINTF_GTYPE (_PRINTF_ETYPE | _PRINTF_FTYPE)
#endif

#define _PRINTF_BLANK      0x4
#define _PRINTF_SIGNED     0x8
#define _PRINTF_NEG       (_PRINTF_SIGNED | _PRINTF_BLANK)

#define _PRINTF_UPPER     0x10
#define _PRINTF_LEFT      0x20
#define _PRINTF_ZEROPAD   0x40
#define _PRINTF_ALT       0x80
#define _PRINTF_LONGVAL  0x100
#define _PRINTF_SHORTVAL 0x200
#define _PRINTF_PREC     0x400
#define _PRINTF_PTR      0x800

#if LIBDEF_PRINTF_FAR_PTR
  #define _PRINTF_FARVAL 0x1000
#endif

#ifdef __XGATE__ /* for the XGATE all constants have to be in RAM. Variables have to be distinct from the HCS12X */
#define pbuf    _X_pbuf /* XGATE/HCS12X should use seperate buffers for XGATE */
#define pow10   _X_pow10
#define pow16   _X_pow16
#define pow8    _X_pow8
#define fpow10  _X_fpow10
#define fpow_10  _X_fpow_10
#endif /* __XGATE__ */

#if !LIBDEF_REENTRANT_PRINTF

static struct __print_buf {
  char * s;
  void (*outc)(char);
  unsigned int i;
} 
pbuf;
#endif /* !LIBDEF_REENTRANT_PRINTF */


//#pragma MESSAGE DISABLE C2402 /* Variable pow10  allocated in ROM */

static const unsigned _PRINTF_INTEG pow10[] = {1, 10, 100, 1000, 10000
#if LIBDEF_PRINTF_LONG
        , 100000, 1000000, 10000000, 100000000, 1000000000
#endif
        };
static const unsigned _PRINTF_INTEG pow16[] = {1, 0x10, 0x100, 0x1000
#if LIBDEF_PRINTF_LONG
        , 0x10000, 0x100000, 0x1000000, 0x10000000
#endif
        };

//#pragma MESSAGE DISABLE C2706
static const unsigned _PRINTF_INTEG pow8[] = {1, 010, 0100, 01000, 010000, 0100000
#if LIBDEF_PRINTF_LONG
        , 01000000, 010000000, 0100000000, 01000000000, 010000000000
#endif
        };
#if defined(__arm)
#if LIBDEF_PRINTF_FLOATING
  static const double fpow10[] = {1e0, 1e1, 1e2, 1e3, 1e4, 1e5, 1e6, 1e7, 1e8, 1e16, 1e24, 1e32};
  static const double fpow_10[] = {1e0, 1e-1, 1e-2, 1e-3, 1e-4, 1e-5, 1e-6, 1e-7, 1e-8, 1e-16, 1e-24, 1e-32};

  #ifdef __DOUBLE_IS_IEEE64__
    #define EXPON int
  #else
    #define EXPON signed char
  #endif
#endif

#if LIBDEF_PRINTF_FLOATING
static double Ten(EXPON e) {
  const double * arr= fpow10;

  if (e < 0) {
    arr= fpow_10;
    e = -e;
  }
  if (e <= 8) {
    return arr[e];
  } else {
    double res=1;
    unsigned int i;
    i= e >> 3; /*lint !e702 allow signed right shift, its positive anyway */
    if (i > 4) {
      i= 4;
    }
    e -= i << 3;
    res= arr[i+7];
    while (e > 8) {
      i= e >> 3;
      if (i > 4) {
        i= 4;
      }
      e -= i << 3;
      res*= arr[i+7];
    }
    return res*arr[e];
  }
}
#endif
#endif

#if defined(__DOUBLE_IS_IEEE32__)
  #define DIGITS  6
  #define BOUND   1.0E-6F
#elif defined (__DOUBLE_IS_DSP__)
  #define DIGITS  4
  #define BOUND   1.0E-4F
#else
  #if !defined(__DOUBLE_IS_IEEE64__)
    /* assume double is IEEE64 by default */
    #pragma warning "assume double is IEEE64"
  #endif

  #define DIGITS  14
  #define BOUND   1.0E-14F
#endif

/*****************************************************/
#define MyAbs(v)     ((v) < 0 ? -(v) : (v))
/*****************************************************/

#define LEN(array)  (sizeof(array)/sizeof(array[0]))
#define F_DIGITS  (LEN(pow10)-2)

#if defined (__PPC__) || defined(__HC12__) || defined(__M68K__) || defined(__MCORE__) || defined(__XA__)
#define USE_UNION 0
#else
#define USE_UNION 1
#endif

#if USE_UNION
#define str _local._str
#define val _local._num._val
#define pwr _local._num._pow
#define fval  _local._num._flt
#define expon  _local._num._exp
#define exp0 _local._int
#endif

#define dig c


#if LIBDEF_REENTRANT_PRINTF
static void _out(char c, struct __print_buf* desc);
#define out(c) _out(c,desc); pbuf_i++
#else
static void _out(char c);
#define out(c) _out((c))
#define pbuf_i pbuf.i
#endif

#if LIBDEF_REENTRANT_PRINTF
int __vprintf_desc(const char * format, va_list args, struct __print_buf* desc) {   /* reentrant version of printf */
#else
int vprintf(const char * format, va_list args) {
#endif
  unsigned int flags;
#if LIBDEF_PRINTF_PREC
  unsigned int prec;
#endif
  unsigned int len;
  int width;

  char c;
#if 1 /* the address of c1 is taken. By using a separate var, more optimizations with c are possible */
  char c1;
#else
#define c1 c
#endif

#if USE_UNION
  union {
#if LIBDEF_PRINTF_FAR_PTR
    char *_FAR _str;
#else
    char * _str;
#endif
    int _int;
    struct {
      unsigned _PRINTF_INTEG _val;
      unsigned _PRINTF_INTEG _pow;
#if LIBDEF_PRINTF_FLOATING
      double _flt;
      EXPON _exp;
#endif
    } _num;
  } _local;
#else  /* USE_UNION */
#if LIBDEF_PRINTF_FAR_PTR
  char *_FAR str;
#else
  char * str;
#endif
  int exp0;
  unsigned _PRINTF_INTEG val;
  unsigned _PRINTF_INTEG pwr;
#if LIBDEF_PRINTF_FLOATING
  double fval;
  EXPON expon;
#endif
#endif /* USE_UNION */
#if LIBDEF_REENTRANT_PRINTF
  int pbuf_i=0;
#endif
  while (*format) {
    if (*format != '%') {
      out(*format);
      ++format;
      continue;
    } else {
      flags = 0;
#if LIBDEF_PRINTF_PREC
      prec = 0;
#endif
      width = 0;
      for (;;) {
        ++format;
        switch (*format) {
          case '-':
            flags |= _PRINTF_LEFT;
            continue;
          case '+':
            flags |= _PRINTF_SIGNED;
            continue;
          case ' ':
            flags |= _PRINTF_BLANK;
            continue;
          case '0':
            flags |= _PRINTF_ZEROPAD;
            continue;
          case '#':
            flags |= _PRINTF_ALT;
            continue;
        }
        break;
      }
      if (flags & _PRINTF_SIGNED) {
        flags &= ~_PRINTF_BLANK;
      }
      if (flags & _PRINTF_LEFT) {
        flags &= ~_PRINTF_ZEROPAD;
      }

      /* field width */
      if (*format == '*') {
        width = va_arg(args, int);
        ++format;
      } else {
        c = *format;
        while (c >= '0' && c <= '9') {
          width = 10*width + c - '0';
          ++format;
          c = *format;
        }
      }
#if LIBDEF_PRINTF_PREC
      /* precision */
      if (*format == '.') {
        flags |= _PRINTF_PREC;
        ++format;
        if (*format == '*') {
          prec = va_arg(args, unsigned short);
          ++format;
        } else {
          c = *format;
          while (c >= '0' && c <= '9') {
            prec = 10*prec + c - '0';
            ++format;
            c = *format;
          }
        }
      }
#endif /* LIBDEF_PRINTF_PREC */
      /* long or short argument */
#if LIBDEF_PRINTF_LONG
      if (*format == 'L' || *format == 'l') {
        flags |= _PRINTF_LONGVAL;
        ++format;
      } else 
#endif
      if (*format == 'h') {
        flags |= _PRINTF_SHORTVAL;
        ++format;
      }
      
      /* conversions */
      
      switch (*format++) {
        case '%':
          out('%');
          continue;

#if LIBDEF_PRINTF_NOF_CHAR
#if LIBDEF_PRINTF_FAR_PTR
        case 'N': /* return nof chars */
          if (flags & _PRINTF_SHORTVAL) {
            *va_arg(args, short int *FAR) = pbuf_i;
#if LIBDEF_PRINTF_LONG
          } else if (flags & _PRINTF_LONGVAL) {
            *va_arg(args, long int *FAR) = pbuf_i;
#endif
          } else {
            *va_arg(args, int *FAR) = pbuf_i;
          }
          continue;
#endif
        case 'n': /* return nof chars */
          if (flags & _PRINTF_SHORTVAL) {
            *va_arg(args, short int*) =(short int)pbuf_i;
#if LIBDEF_PRINTF_LONG
          } else if (flags & _PRINTF_LONGVAL) {
            *va_arg(args, long int*) = pbuf_i;
#endif
          } else {
            *va_arg(args, int*) = pbuf_i;
          }
          continue;
#endif /* LIBDEF_PRINTF_NOF_CHAR */

#if LIBDEF_PRINTF_CHAR
        case 'c': /* char */
          c1 = (char)va_arg(args, int);
          str = (char *) &c1;
          len = 1;
          goto string; /*lint !e801 Use of goto is not deprecated */
#endif

#if LIBDEF_PRINTF_FAR_PTR
        case 'S':
          flags |= _PRINTF_FARVAL;
          str = va_arg(args, char *FAR);
          len = 0;
          if (str) {
            while (str[len]) {
              ++len;
            }
          }
          goto string; /*lint !e801 Use of goto is not deprecated */
#endif
        case 's':  /* string */
          str = va_arg(args, char *);
          len = 0;
          if (str) {
            while (str[len]) {
              ++len;
            }
          }
string:
        
#if LIBDEF_PRINTF_PREC
          /* adjust length to precision */
          if (prec && (prec < len)) {
            len = prec;
          }
#endif
          if (width > len) {
            width -=len;
          } else {
            width = 0;
          }
          /* pad left */
          if (!(flags & _PRINTF_LEFT)) {
            while (width) {
              out(' '); --width;
            }
          }            
          /* output string */
          while (len) {
            out(*str); ++str; --len; /*lint !e613 Possible use of null pointer 'str' in argument */
          }
          /* pad right */
          while (width) {
            out(' '); --width;
          }
          continue;

#if LIBDEF_PRINTF_FAR_PTR
        case 'P':
          flags |= _PRINTF_FARVAL;
          /*lint -fallthrough */
#endif
#if LIBDEF_PRINTF_PTR
        case 'p':
          if (sizeof(void*) != sizeof(unsigned int)) {
            flags |= _PRINTF_PTR;
          }
          /*lint -fallthrough */
#endif
#if LIBDEF_PRINTF_ALLOW_HEXINT
        case 'X': /* _PRINTF_INTEGer */
          flags |= _PRINTF_UPPER;
          /*lint -fallthrough */
        case 'x':
          flags |= _PRINTF_HEXINT;
          goto unsig_int; /*lint !e801 Use of goto is not deprecated */
#endif
#if LIBDEF_PRINTF_ALLOW_OCTINT
        case 'o':
          flags |= _PRINTF_OCTINT;
          /*lint -fallthrough */
#endif        
        case 'u':

unsig_int:
          /* get unsigned _PRINTF_INTEGer */
          flags &= ~_PRINTF_NEG;
#if LIBDEF_PRINTF_FAR_PTR
          if (flags & _PRINTF_FARVAL) {
            val = (unsigned _PRINTF_INTEG) va_arg(args, char *FAR);
          } else
#endif
          if (flags & _PRINTF_SHORTVAL) {
            val = va_arg(args, unsigned short);
#if LIBDEF_PRINTF_LONG
          } else if (flags & _PRINTF_LONGVAL) {
            val = va_arg(args, unsigned long);
#endif
          } else {
#if LIBDEF_PRINTF_PTR
            if (sizeof(void*) != sizeof(unsigned int) && (flags & _PRINTF_PTR) != 0) { /* support for %p for targets with non int pointer sizes */
              val = (unsigned _PRINTF_INTEG)va_arg(args, void*);
            } else {
              val = va_arg(args, unsigned int);
            }
#else
            val = va_arg(args, unsigned int);
#endif /* LIBDEF_PRINTF_PTR */
          }
          goto integer; /*lint !e801 Use of goto is not deprecated */

        case 'i':
        case 'd':
          /* get signed integer */
          if (flags & _PRINTF_SHORTVAL) {
            val = va_arg(args, short);
#if LIBDEF_PRINTF_LONG
          } else if (flags & _PRINTF_LONGVAL) {
            val = va_arg(args, long);
#endif
          } else {
            val = va_arg(args, int);
          }

          if ((_PRINTF_INTEG) val < 0) {
            val = (-(_PRINTF_INTEG)val);
            flags |= _PRINTF_NEG;
          }

integer:

          len = 1;
#if LIBDEF_PRINTF_ALLOW_OCTINT && LIBDEF_PRINTF_ALLOW_HEXINT
          if (flags & _PRINTF_OCTINT) {
            while (len < LEN(pow8) && val >= pow8[len]) { ++len; }
          } else if (flags & _PRINTF_HEXINT) {
            while (len < LEN(pow16) && val >= pow16[len]) { ++len; }
          } else {
            while (len < LEN(pow10) && val >= pow10[len]) { ++len; }
          }
#elif LIBDEF_PRINTF_ALLOW_OCTINT
          if (flags & _PRINTF_OCTINT) {
            while (len < LEN(pow8) && val >= pow8[len]) { ++len; }
          } else {
            while (len < LEN(pow10) && val >= pow10[len]) { ++len; }
          }
#elif LIBDEF_PRINTF_ALLOW_HEXINT
         if (flags & _PRINTF_HEXINT) {
            while (len < LEN(pow16) && val >= pow16[len]) { ++len; }
          } else {
            while (len < LEN(pow10) && val >= pow10[len]) { ++len; }
          }
#else 
          while (len < LEN(pow10) && val >= pow10[len]) { ++len; }
#endif
          
#if LIBDEF_PRINTF_PREC
          /* width of integer */
          if (prec > len)  {
            prec -= len;
          } else {
            prec = 0;
          }
          width -= (prec + len);
#else
          width -= len;
#endif /* LIBDEF_PRINTF_PREC */

#if LIBDEF_PRINTF_ALLOW_OCTINT && LIBDEF_PRINTF_ALLOW_HEXINT
          if (flags & _PRINTF_ALT) {
            if (flags & _PRINTF_OCTINT) {
              --width;
            } else if (flags & _PRINTF_HEXINT) {
              width -= 2;
            }
          }
#elif LIBDEF_PRINTF_ALLOW_OCTINT
          if ((flags & (_PRINTF_ALT|_PRINTF_OCTINT))==(_PRINTF_ALT|_PRINTF_OCTINT)) {
            --width;
          } 
#elif LIBDEF_PRINTF_ALLOW_HEXINT
          if ((flags & (_PRINTF_ALT|_PRINTF_HEXINT))==(_PRINTF_ALT|_PRINTF_HEXINT)) {
            width -= 2;
          } 
#endif
          if (flags & _PRINTF_NEG) {
            --width;
          }
          
          if (width < 0) {
            width = 0;
          }
          
          /* pad left */
          if (width && !(flags & _PRINTF_LEFT)) {
            if (!(flags & _PRINTF_ZEROPAD)) {/* pad with spaces */
              do {
                out(' '); --width;
              } while (width);
            } else {
#if LIBDEF_PRINTF_PREC
              prec += width; 
#endif
              width = 0; /* pad with zeros */
            }
          }

          /* alternate form of integers for oct and hex numbers */
#if LIBDEF_PRINTF_ALLOW_HEXINT && LIBDEF_PRINTF_ALLOW_OCTINT
          if ((flags & _PRINTF_ALT) && (flags & _PRINTF_NOT_DEC)) {
            out('0');
            if (flags & _PRINTF_HEXINT) {
              if (flags & _PRINTF_UPPER) {
                out('X');
              } else {
                out('x');
              }
            }
          }
#elif LIBDEF_PRINTF_ALLOW_HEXINT
          if ((flags & (_PRINTF_ALT|_PRINTF_HEXINT)) == (_PRINTF_ALT|_PRINTF_HEXINT)) {
            out('0');
            if (flags & _PRINTF_UPPER) {
              out('X');
            } else {
              out('x');
            }
          }
#elif LIBDEF_PRINTF_ALLOW_OCTINT
          if ((flags & (_PRINTF_ALT|_PRINTF_OCTINT)) == (_PRINTF_ALT|_PRINTF_OCTINT)) {
            out('0');
          }
#endif

          /* sign */
          if (flags & _PRINTF_SIGNED) {
            if (flags & _PRINTF_BLANK) {
              out('-');
            } else {
              out('+');
            }
          } else if (flags & _PRINTF_BLANK) {
            out(' ');
          }

#if LIBDEF_PRINTF_PREC
          /* pad with zeros to precision */
          while (prec) {
            out('0'); --prec;
          }
#endif
          /* output conversion. par: val, len; local: dig, pwr*/
          do {
            dig = 0;
            --len;
#if LIBDEF_PRINTF_ALLOW_OCTINT && LIBDEF_PRINTF_ALLOW_HEXINT
            if (flags & _PRINTF_OCTINT) {
              pwr = pow8[len];
            } else if (flags & _PRINTF_HEXINT) {
              pwr = pow16[len];
            } else {
              pwr = pow10[len];
            }
#elif LIBDEF_PRINTF_ALLOW_OCTINT
            if (flags & _PRINTF_OCTINT) {
              pwr = pow8[len];
            } else {
              pwr = pow10[len];
            }
#elif LIBDEF_PRINTF_ALLOW_HEXINT
            if (flags & _PRINTF_HEXINT) {
              pwr = pow16[len];
            } else {
              pwr = pow10[len];
            }
#else
            pwr = pow10[len];
#endif

            while (val >= pwr) {
              val -= pwr;
              ++dig;
            }
#if LIBDEF_PRINTF_ALLOW_HEXINT
            if (dig < 10) {
              out((char)(dig + '0'));
            } else if (flags & _PRINTF_UPPER) {
              out((char)(dig + 'A' - 10));
            } else {
              out((char)(dig + 'a' - 10));
            }
#else 
            out(dig + '0');
#endif
          } while (len);

          /* append spaces to field width */
          while (width) {
            out(' '); --width;
          }
          continue;

#if LIBDEF_PRINTF_FLOATING
        case 'E': /* float */
          flags |= _PRINTF_UPPER;
          /* fall through */
        case 'e':
          flags |= _PRINTF_ETYPE;
          goto real; /*lint !e801 Use of goto is not deprecated */

        case 'f':
          flags |= _PRINTF_FTYPE;
          goto real; /*lint !e801 Use of goto is not deprecated */

        case 'G':
          flags |= _PRINTF_UPPER;
          /* fall through */
        case 'g':
          flags |= _PRINTF_GTYPE;
          /* fall through */
real:
          if (!(flags & _PRINTF_PREC)) {/* default precision */
            prec = 6;
          }
          fval = va_arg(args, double);
          if (fval < 0.0) {
            fval = (-fval);
            flags |= _PRINTF_NEG;
          }
          
          expon = 0;
          if (fval != 0.0) {
#ifdef __DOUBLE_IS_IEEE32__
            (void)frexpf(fval, &exp0);
#else
            (void)frexp(fval, &exp0);
#endif
            expon = (EXPON)((exp0 * 3) / 10);  /*ln(2)/ln(10) = 0.30102999..*/
          }
          if (flags & _PRINTF_ETYPE && (!(flags & _PRINTF_FTYPE) || (expon < -4) || (expon >= (int) prec))) {
            /* base conversion */
            if (fval != 0.0) {
              fval *= Ten(-expon);
              if (fval != 0.0) {
                while (fval >= 10.0) {
                  fval *= 1e-1; ++expon;
                }
                while (fval < 1.0) {
                  fval *= 10.0; --expon;
                }
              }
            }
            /* x = fval * 10 ^ expon; 1 <= fval < 10 */
            /* e type conversion */
            if (prec && flags & _PRINTF_FTYPE) {/* for g type: prec = nof significant digits */
              --prec;
            }
            if (prec < F_DIGITS) {
              fval += 0.5*Ten(-(EXPON)prec);
            }
#if 1 /* if rounding causes overflow */
            if (fval >= 10.0) {
              fval *= 1e-1; ++expon;
            }
#endif              
            /*adjust precision for g type conversion (remove trailing zeros)*/
            if (prec && flags & _PRINTF_FTYPE && !(flags & _PRINTF_ALT)) {
              if (prec > F_DIGITS) {
                prec = F_DIGITS;
              }
                
              val = fval * Ten((EXPON)prec);

              if (val) {
                while (prec && (val % 10 == 0)) {
                  val /= 10; --prec;
                }
              } else {
                prec = 0;
              }
            }
            flags &= ~_PRINTF_FTYPE;
            
            /* width of e type conversion */
            width -= (5 + prec);    /*minimum: dE+dd*/
            if (prec || flags & _PRINTF_ALT) { /*decimal point*/
              --width;
            }
            if (flags & _PRINTF_NEG) {     /*sign or blank*/
              --width;
            }
            if (MyAbs(expon) >= 100) {       /*additional digit for exponent*/
              --width;
            }

            val = fval;
            fval -= (double) val;
            len = 1;
          } else  {/* f type conversion */
            /*float = fval * 10 ^ expon; fval is not restricted to 1 <= fval < 10 !!!*/
            
            /*adjust precision for g type conversion (trailing zeros)*/
            if (prec && flags & _PRINTF_ETYPE && !(flags & _PRINTF_ALT)) {
              prec -= (expon+1);  /*prec >= expon*/
              if (expon < 0 || fval < 1.0) { /*leading 0 is not significant*/
                ++prec;
              }
              if (prec > F_DIGITS) {
                prec = F_DIGITS;
              }
              val = fval*Ten((EXPON)prec)+0.5;
              while (prec && !(val % 10)) {
                val /= 10; --prec;
              }
            }
            flags &= ~_PRINTF_ETYPE;
            
            if ((EXPON) (expon-F_DIGITS) >= -(EXPON)prec) {
              fval += 0.5*Ten(expon-F_DIGITS);
            } else {
              fval += 0.5*Ten(-(EXPON)prec);
            }

            /* width of type f conversion */
            if (expon >= 0) {/* (expon + 1) digits before dec pt */
              if (expon > F_DIGITS) {
                expon -= F_DIGITS;
                val = fval * Ten(-expon);
                fval = 0.0;
              } else {
                val = fval;
                fval -= (double) val;
                expon = 0;
              }
            } else {
              val = 0;
              expon = 0;
            }

            len = 1;
            while (len < LEN(pow10) && val >= pow10[len]) {
              ++len;
            }
            
            width -= (prec + len + expon);
            
            if (prec || flags & _PRINTF_ALT) { /*decimal point*/
              --width;
            }
            if (flags & _PRINTF_NEG) {     /*sign or blank*/
              --width;
            }

          }

          if (width < 0)
            width = 0;

          /* pad left */
          if (!(flags & _PRINTF_LEFT)) {
            if (!(flags & _PRINTF_ZEROPAD)) {/*pad with spaces before sign*/
              while (width) {
                out(' '); --width;
              }
            }
          }
          /*!(flags & _PRINTF_LEFT) && !(flags & _PRINTF_ZEROPAD) => (width == 0)*/

          /*sign*/
          if (flags & _PRINTF_SIGNED) {
            if (flags & _PRINTF_BLANK) {
              out('-');
            } else {
              out('+');
            }
          } else if (flags & _PRINTF_BLANK) {
            out(' ');
          }

          if (!(flags & _PRINTF_LEFT)) { /*pad with zeros after sign (if width still > 0)*/
            while (width) {
              out('0'); --width;
            }
          }
          
          /* float conversion */

          /*print all digits before decimal point*/
          do {
            --len;
            dig = '0';
            pwr = pow10[len];
            while (val >= pwr) {
              val -= pwr; ++dig;
            }
            out(dig);
          } while (len);
          
          if (flags & _PRINTF_FTYPE) {/* add zeros before decimal point */
            while (expon > 0) {
              out('0'); --expon;
            }
          }
          
          if (prec || flags & _PRINTF_ALT) {
            out('.');
            if(prec > 0) {
              if (prec > F_DIGITS) {
                len = F_DIGITS;
              } else {
                len = prec;
              }
              
              prec -= len;
  
              if (flags & _PRINTF_FTYPE) {
                val = fval * Ten((EXPON)(len - expon)); /*10^(-expon) --> 1 <= fval < 10 */
              } else {
                val = fval * Ten((EXPON)len);
              }
              
              /*out int val */
              do {
                --len;
                dig = '0';
                pwr = pow10[len];
                while (val >= pwr) {
                  val -= pwr; ++dig;
                }
                out(dig);
              } while (len);
              
              while (prec) {
                out('0'); --prec;
              }
            } /* if prec > 0 */
          } 
          if (flags & _PRINTF_ETYPE) { /*exponent*/
            if (flags & _PRINTF_UPPER) {
              out('E');
            } else {
              out('e');
            }
            if (expon < 0) {
              expon = (-expon);
              out('-');
            } else {
              out('+');
            }
          
            if (expon >= 100) {
              out((char)(expon / 100 + '0'));
              expon = (EXPON)(expon % 100);
            }
            out((char)(expon / 10 + '0'));
            out((char)(expon % 10 + '0'));
          }

          /* pad right */
          while (width) {
            out(' '); --width;
          }
#else
        case 'E':
        case 'e':
        case 'f':
        case 'G':
        case 'g':
          va_arg(args, double); /* drop it */
#endif
        default:
          continue;

      } /* switch (*format++) */
    } /* if (*format != '%') */
  } /* while (*format) */
  return (pbuf_i);
} /* vprintf */


#if LIBDEF_REENTRANT_PRINTF
 /* support of non-reentrant version of vprintf */
static void (*f_callback)(char);
static void outc_callback(char c, struct __print_buf* This) {
  f_callback(c);
}
static struct __print_buf pbuf={(__printf_callback)outc_callback};
void set_printf(void (*f)(char)) {
  f_callback = f;
}

int vprintf(const char * format, va_list args) {    
  return __vprintf_desc(format, args, &pbuf);
}

/* sprintf */
struct __sprintfBuf {
  struct __print_buf p;
  char * s;
  int i;
};

static void deposit_char(char c, struct __sprintfBuf* p) {
  p->s[p->i] = c;
  p->i++;
}

int sprintf(char * s, const char * format, ...) {
  va_list args;
  struct __sprintfBuf p;
 
  p.i = 0;
  p.s = s;
  p.p.outc = (__printf_callback)deposit_char;
  va_start(args, format);
  (void)__vprintf_desc(format, args, (struct __print_buf*)&p);
  p.s[p.i] = 0;
  va_end(args);
  return p.i;
}

int vsprintf(char * s, const char * format, va_list args) {
  struct __sprintfBuf p;
  p.i = 0;
  p.s = s;
  p.p.outc = (__printf_callback)deposit_char;
  (void)__vprintf_desc(format, args, (struct __print_buf*)&p);
  p.s[p.i] = 0;
  return p.i;
}

static void _out(char c, struct __print_buf* desc) {
  desc->outc((c),(desc));
}

#else

#ifdef __RS08__
static unsigned int _save_pc;
#pragma NO_ENTRY
#pragma NO_EXIT
static void _out(char c) {
  __asm {
    STA   c
    SHA        
    STA   _save_pc
    SLA        
    STA   _save_pc+1
  }
  pbuf.outc(c);
  ++pbuf.i;
  __asm {
    LDA   _save_pc
    SHA        
    LDA   _save_pc+1
    SLA        
  }  
}
#else
static void _out(char c) {
  pbuf.outc(c);
  ++pbuf.i;
}
#endif

void set_printf(void (*f)(char));

void set_printf(void (*f)(char)) {
  /* installs a handler function to write to the terminal */ 
  pbuf.outc = f;
  pbuf.s = NULL;
  pbuf.i = 0;
}


/* sprintf */
static void deposit_char(char c) {
  pbuf.s[pbuf.i] = c;
}

int sprintf(char * s, const char * format, ...) {
  va_list args;
  
  pbuf.i = 0;
  pbuf.s = s;
  pbuf.outc = deposit_char;
  va_start(args, format);
  (void)vprintf(format, args);
  pbuf.s[pbuf.i] = 0;
  va_end(args);
  return (pbuf.i);
}

int vsprintf(char * s, const char * format, va_list args) {
  pbuf.i = 0;
  pbuf.s = s;
  pbuf.outc = deposit_char;
  (void)vprintf(format, args);
  pbuf.s[pbuf.i] = 0;
  return (pbuf.i);
}

  void TERMIO_PutChar( char ch)
{
size_t cnt = 1;
    __write_console(1, (unsigned char *)&ch, &cnt, 0L);
}

char TERMIO_GetChar( void )
{
size_t cnt = 1;
char ch;
    __read_console(0, (unsigned char *)&ch, &cnt, 0L);
    return ch;
}


#if _MSL_CONSOLE_SUPPORT

 int printf(const char*, ...); 
int printf(const char* format, ...) {
  int i;
  va_list args;
  
  set_printf(TERMIO_PutChar); /* set up TERMIO_PutChar for writing */
  va_start(args, format);
  i = vprintf(format, args);
  va_end(args);
  return i;
}
#endif /* _MSL_CONSOLE_SUPPORT */

#endif


#if _MSL_TESTING_TINY_IO

#define conversion_buff_size	512

typedef struct 
{
	unsigned char	justification_options;
	unsigned char 	sign_options;
	unsigned char 	precision_specified;
	unsigned char	alternate_form;
	unsigned char 	argument_options;
	unsigned char	conversion_char;
	int			  	field_width;
	int				precision;
#ifdef __ALTIVEC__
	int		vecCount;			/* number of vector fields to convert (4, 8, 16) 		*/
	char 	*vecSeperator;		/* separator string to insert between vector fields 	*/
	char 	*c_vecSeperator;	/* separator string to use for %c vector conversion		*/
	int		vecSepLen;			/* length of *vecSeperator or *c_vecSeperator string	*/
	int		useSepString;		/* @ -- asking for a separator string instead of char	*/
	int		fbad;				/* used to control standard flags parsing				*/
	int		vecwidth,vecprec;	/* width and prec value before each conversion 			*/
	int 	useVecDefault;		/* default to "appropriate" vec access if none specified*/
	int		flagAllowed;		/* true means a flag is still possible					*/
	enum 						/* state of vector formatting parse... 					*/
	{ 
		FLAG_OR_Vcode_OK,		/*   initial state: sep flag or 'v' code allowed  		*/
		Vcode_REQUIRED,			/*   set to this state when sep flag seen  reqiring 'v'	*/
		FLAG_OR_Vcode_NOT_OK	/*   set this state when 'v' code qualifier seen 		*/
	} vec_state;
	enum 						/* how to access vector fields (as chars,shorts,longs)	*/
	{
		U8, U16, U32
	} vec_access;
#endif /* __ALTIVEC__ */
} print_format;

enum justification_options
{
	left_justification,
	right_justification,
	zero_fill
};

enum sign_options
{
	only_minus,
	sign_always,
	space_holder
};

enum argument_options
{
	normal_argument,
	char_argument,
	short_argument,
	long_argument,
	
#if _MSL_C99_PRINTF_SCANF
#if _MSL_C99	
#if _MSL_LONGLONG
	long_long_argument,
#endif /* _MSL_LONGLONG */
#endif /* _MSL_C99 */
#endif /*_MSL_C99_PRINTF_SCANF*/

	
#if _MSL_WIDE_CHAR
	wchar_argument,
#endif /* _MSL_WIDE_CHAR */
	
//#if _MSL_C99_PRINTF_SCANF
#if _MSL_C99
	intmax_argument,
	size_t_argument,
	ptrdiff_argument,
#endif /* _MSL_C99 */
//#endif /* _MSL_C99_PRINTF_SCANF */
	
#ifdef __ALTIVEC__
	vector_argument,
#endif /* __ALTIVEC__ */
	
	long_double_argument
};

#define conversion_max			509
#define bad_conversion			0xFF

static unsigned int set_base(char conversion_char)
{
	unsigned int base;
	
	switch (conversion_char)
	{
		case 'o':
			base =   8;
			break;
		
		case 'u':
			base =  10;
			break;
		
		case 'x':
		case 'X':
			base =  16;
			break;
	}
	
	return base;
}

static wchar_t * wjustify_conversion(unsigned int base, int digits, int minus, wchar_t * p,
	wchar_t * buff, print_format format)
{
	if (base == 8 && format.alternate_form && *p != L'0')
	{
		*--p = L'0';
		++digits;
	}
	
	if (format.justification_options == zero_fill)
	{
		format.precision = format.field_width;
		
		if (minus || format.sign_options != only_minus)
			--format.precision;
		
		if (base == 16 && format.alternate_form)
			format.precision -= 2;
	}
	
	if (buff - p + format.precision > conversion_max)
		return (NULL);
	
	while (digits < format.precision)
	{
		*--p = L'0';
		++digits;
	}
	
	if (base == 16 && format.alternate_form)
	{
		*--p = format.conversion_char;
		*--p = L'0';
	}
	
	if (minus)
		*--p = L'-';
	else if (format.sign_options == sign_always)
		*--p = L'+';
	else if (format.sign_options == space_holder)
		*--p = L' ';
	
	return (p);
}

static wchar_t * wlong2str(long num, wchar_t * buff, print_format format)
{
	unsigned long	unsigned_num, base;
	wchar_t *		p;
	int				n, digits;
	int				minus = 0;
	
	unsigned_num = num;
	minus        =   0;
	
	p = buff;
	
	*--p = 0;
	
	digits = 0;
	
	if (!num && !format.precision && !(format.alternate_form && format.conversion_char == L'o'))
		return (p);
	
	if ((format.conversion_char == L'd') || (format.conversion_char == L'i'))
	{
			base =  10;
			
			if (num < 0)
			{
				if (num != 0x8000000000000000LL)								/*- mm 050104 -*/
					unsigned_num = -num;										/*- mm 050104 -*/
				minus        = 1;
			}
	}
	else
	{
		base = set_base(format.conversion_char);
		format.sign_options = only_minus;
	}
	
	do
	{
		n = unsigned_num % base;
		
		unsigned_num /= base;
		
		if (n < 10)
			n += L'0';
		else
		{
			n -= 10;
			
			if (format.conversion_char == L'x')
				n += L'a';
			else
				n += L'A';
		}
		
		*--p = n;
		
		++digits;
	}
	while (unsigned_num != 0);
	
	return wjustify_conversion(base, digits, minus, p, buff, format);
}



/* Parse the format specifiers so appropriate types, precision, and formatting are used */
static const char * parse_format(const char * format_string, va_list * arg, print_format * format)
{
	print_format	f;
	const char *	s = format_string;
	int				c;
	int				flag_found;
	
	f.justification_options	= right_justification;
	f.sign_options			= only_minus;
	f.precision_specified   = 0;
	f.alternate_form		= 0;
	f.argument_options		= normal_argument;
	f.field_width			= 0;
	f.precision				= 0;
	
	if ((c = *++s) == '%')
	{
		f.conversion_char = c;
		*format = f;
		return ((const char *) s + 1);
	}
	
#ifdef __ALTIVEC__
	f.vec_state 	 = FLAG_OR_Vcode_OK;
	f.vecSeperator   = " ";
	f.c_vecSeperator = "";
	f.vecSepLen	   	 = 1;
getFlags:
	f.useSepString = 0;
#endif /* __ALTIVEC__ */
	
	for (;;)
	{
		flag_found = 1;
		
		switch (c)
		{
			/* PREFIX -  left justify output */
			case '-':
				f.justification_options = left_justification;
				break;
			
			/* PREFIX +  always display the numeric sign */
			case '+':
				f.sign_options = sign_always;
				break;
			
			/* PREFIX space  prefix positive numbers with a space (sign placeholder) */
			case ' ':
				if (f.sign_options != sign_always)
					f.sign_options = space_holder;
				break;
			
			/* PREFIX #  use "alternate form" for output format */
			case '#':
				f.alternate_form = 1;
				break;
			
			/* PREFIX 0  zero fill instead of filling justification with spaces */
			case '0':
				if (f.justification_options != left_justification)
					f.justification_options = zero_fill;
				break;
			
#ifdef __ALTIVEC__
			/* PREFIX @  AltiVec extension, next argument provides vector separator string */
			case '@':
				if (f.vec_state == FLAG_OR_Vcode_OK)
				{
					f.useSepString = 1;
					break;
				}
				/* fall through */
#endif /* __ALTIVEC__ */
			
			/* Any other prefix character is not a flag, so continue processing format arguments */
			default:
				flag_found = 0;
				break;
		}
		
		if (flag_found)
		{
#ifdef __ALTIVEC__
			f.c_vecSeperator = (char *) s;
			f.vecSepLen	   	 = 1;
#endif /* __ALTIVEC__ */
			c = *++s;
		}
		else
			break;
	}
	
#ifdef __ALTIVEC__
	if (f.useSepString)
	{
		/* PREFIX @ was used, so obtain the next argument to find the separator string */
		f.vecSeperator = va_arg(*arg, char *);
		f.vecSepLen    = strlen(f.vecSeperator);
	}
#endif /* __ALTIVEC__ */
	
	/* Specifier * means next argument provides the field length */
	if (c == '*')
	{
		if ((f.field_width = va_arg(*arg, int)) < 0)
		{
			f.justification_options = left_justification;
			f.field_width           = -f.field_width;
		}
		
		c = *++s;
	}
	else
	{
		/* Field length specified by a decimal number, parse the number */
		while (isdigit(c))
		{
			f.field_width = (f.field_width * 10) + (c - '0');
			c = *++s;
		}
	}
	
	if (f.field_width > conversion_max)
	{
		f.conversion_char = bad_conversion;
		*format = f;
		return ((const char *) s + 1);
	}
	
	/* Specifier . means floating point precision or string length comes next */
	if (c == '.')
	{
		f.precision_specified = 1;
		
		/* Specifier * means next argument provides the precision or string length */
		if ((c = *++s) == '*')
		{
			if ((f.precision = va_arg(*arg, int)) < 0)
				f.precision_specified = 0;
			
			c = *++s;
		}
		else
		{
			/* Precision or string length specified by a decimal number, parse the number */
			while (isdigit(c))
			{
				f.precision = (f.precision * 10) + (c - '0');
				c = *++s;
			}
		}
	}
	
	flag_found = 1;
	
#ifdef __ALTIVEC__
	f.useVecDefault = 1;			/* use vec default access if none specified below 	*/
	
	if (c == 'v')					/* allow 'v' to qualify length or format code 		*/
	{
		f.vec_state = FLAG_OR_Vcode_NOT_OK;
		f.argument_options = vector_argument;
		c = *++s;
	}
#endif /* __ALTIVEC__ */		
	
	switch (c)
	{
		/* Specifier h  argument will be of type short */
		case 'h':
#ifdef __ALTIVEC__
			if (f.argument_options == normal_argument)	
				f.argument_options = short_argument;
			f.vecCount  	= 8;
			f.vec_access	= U16;
			f.useVecDefault = 0;
#else
			f.argument_options = short_argument;
#endif /* __ALTIVEC__ */
			
#if _MSL_C99						/*- mm 030218 -*/
			/* Specifier hh  argument will be of type char */
			if (s[1] == 'h')
			{
				f.argument_options = char_argument;
				c = *++s; /* move past second h */
			}
#endif /* _MSL_C99 */					/*- mm 030218 -*/
			
#ifdef __ALTIVEC__
			/* Specifier hv  argument will be of type vector short */
			if (s[1] == 'v')			/*- mm 030218 -*/ 
			{
				if (f.vec_state != FLAG_OR_Vcode_NOT_OK)
				{
					f.vec_state = FLAG_OR_Vcode_NOT_OK;
					f.argument_options = vector_argument;
					c = *++s;
				}
			}
#endif /* __ALTIVEC__ */
			break;
		
		/* Specifier l  argument will be of type long */
		case 'l':
#ifdef __ALTIVEC__
			if (f.argument_options == normal_argument)	
				f.argument_options = long_argument;
			f.vecCount		= 4;
			f.vec_access	= U32;
			f.useVecDefault = 0;
			/* Specifier lv  argument will be of type vector long */
			if (s[1] == 'v')
			{
				if (f.vec_state != FLAG_OR_Vcode_NOT_OK)
				{
					f.vec_state = FLAG_OR_Vcode_NOT_OK;
					f.argument_options = vector_argument;
					c = *++s;
				}
			}
#else
			f.argument_options = long_argument;
#endif /* __ALTIVEC__ */
			
#if _MSL_C99_PRINTF_SCANF			
#if _MSL_C99
#if _MSL_LONGLONG
			/* Specifier ll  argument will be of type long long */
			if (s[1] == 'l')
			{
				f.argument_options = long_long_argument;
				c = *++s; /* move past second l */
#ifdef __ALTIVEC__
				f.vec_state = FLAG_OR_Vcode_NOT_OK;
#endif /* __ALTIVEC__ */
			}
#endif /* _MSL_LONGLONG */
#endif /* _MSL_C99 */					/*- mm 030218 -*/			
#endif /*_MSL_C99_PRINTF_SCANF */

			break;
		
		/* Specifier L  argument will be of type long double */
		case 'L':
			f.argument_options = long_double_argument;
#ifdef __ALTIVEC__
			f.vec_state = FLAG_OR_Vcode_NOT_OK;
#endif /* __ALTIVEC__ */
			break;

#if _MSL_C99_PRINTF_SCANF
#if _MSL_C99
		/* Specifier j  argument will be of type intmax_t */
		case 'j':
			f.argument_options = intmax_argument;
			break;
		
		/* Specifier t  argument will be of type ptrdiff_t */
		case 't':
			f.argument_options = ptrdiff_argument;
			break;
		
		/* Specifier z  argument will be of type size_t */
		case 'z':
			f.argument_options = size_t_argument;
			break;
#endif /* _MSL_C99 */
#endif /*_MSL_C99_PRINTF_SCANF*/
		
		default:
			flag_found = 0;
			break;
	}
	
	if (flag_found)
		c = *++s;
	
#ifdef __ALTIVEC__
	if (f.vec_state == Vcode_REQUIRED && f.argument_options != vector_argument)
	{
		f.conversion_char = bad_conversion;
		*format = f;
		return s;
	}
#endif /* __ALTIVEC__ */
	
	f.conversion_char = c;
	
	switch (c)
	{
		/* CONVERSION diuoxX  argument is either type int (di) or unsigned int (uoxX) */
		case 'd':
		case 'i':
		case 'u':
		case 'o':
		case 'x':
		case 'X':
#ifdef __ALTIVEC__
			if (f.argument_options != vector_argument)
#endif /* __ALTIVEC__ */
			{
				if (f.argument_options == long_double_argument)
				{
					f.conversion_char = bad_conversion;      /*- mm 961219 -*/
					break;                                   /*- mm 961219 -*/
				}
			}
			if (!f.precision_specified)
				f.precision = 1;
			else if (f.justification_options == zero_fill)
				f.justification_options = right_justification;
			break;
		
		/* CONVERSION fF  argument is type double */
		case 'f':
#if _MSL_C99_PRINTF_SCANF
#if _MSL_C99						/*- mm 030218 -*/
		case 'F':					/*- mm 990430 -*/
#endif /* _MSL_C99 */				/*- mm 030218 -*/
#endif /*_MSL_C99_PRINTF_SCANF */

#ifdef __ALTIVEC__
			if (f.argument_options != vector_argument)
#endif /* __ALTIVEC__ */
			{
				if (f.argument_options == short_argument

#if _MSL_C99_PRINTF_SCANF
#if _MSL_C99																/*- mm 030304 -*/  
					|| f.argument_options == intmax_argument				/*- mm 020529 -*/
					|| f.argument_options == size_t_argument
					|| f.argument_options == ptrdiff_argument				/*- mm 020529 -*/
#if _MSL_LONGLONG
					|| f.argument_options == long_long_argument
#endif /* _MSL_LONGLONG */
#endif /* _MSL_C99 */
#endif /*_MSL_C99_PRINTF_SCANF */

				)  /*  defacto standard %lf is a double */
				{
					f.conversion_char = bad_conversion;
					break;
				}
			}
			
			if (!f.precision_specified)
				f.precision = 6;
			break;
#if _MSL_C99_PRINTF_SCANF
#if _MSL_C99													/*- mm 030314 -*/
		/* CONVERSION aA  argument is type double */
	    case 'a':								
		case 'A':
		#if _MSL_FLOATING_POINT_IO
			if (!f.precision_specified)					
				f.precision = TARGET_FLOAT_MANT_BITS / 4;				
		#endif /* _MSL_FLOATING_POINT_IO */
			if (f.argument_options == short_argument
				|| f.argument_options == intmax_argument		/*- mm 020529 -*/
				|| f.argument_options == size_t_argument
				|| f.argument_options == ptrdiff_argument	 	/*- mm 020529 -*/
#if _MSL_LONGLONG
				|| f.argument_options == long_long_argument
#endif /* _MSL_LONGLONG */
				|| f.argument_options == char_argument)
			{
				f.conversion_char = bad_conversion;
			}
			break;
#endif /* _MSL_C99 */											/*- mm 030314 -*/
#endif /* _MSL_C99_PRINTF_SCANF */		
		/* CONVERSION gG  argument is type double */
	    case 'g':
		case 'G':
			if (!f.precision)
				f.precision = 1;
			/* fall through */
		
		/* CONVERSION eE  argument is type double */
		case 'e':
		case 'E':
#ifdef __ALTIVEC__
			if (f.argument_options != vector_argument)
#endif /* __ALTIVEC__ */
			if (f.argument_options == short_argument
				|| f.argument_options == char_argument			
#if _MSL_C99_PRINTF_SCANF
#if _MSL_C99
				|| f.argument_options == intmax_argument
				|| f.argument_options == size_t_argument
				|| f.argument_options == ptrdiff_argument
#if _MSL_LONGLONG
				|| f.argument_options == long_long_argument
#endif /* _MSL_LONGLONG */
#endif /* _MSL_C99 */														/*- mm 030304 -*/
#endif /* _MSL_C99_PRINTF_SCANF */
				)
			{
				f.conversion_char = bad_conversion;
				break;
			}
			
			if (!f.precision_specified)
				f.precision = 6;
			break;
		
		/* CONVERSION p  argument is type pointer to (void *) */
		case 'p':
			f.conversion_char  = 'x';
			f.alternate_form   = 1;
			
#ifdef __ALTIVEC__
			/* For AltiVec, precision is 8 with non-vector arguments, 1 with vector arguments */
			if (f.argument_options != vector_argument)
			{
				f.argument_options = long_argument;
				f.precision        = 8;
			} else
				f.precision        = 1;
			
#elif (__dest_os == __m56800_os  || __dest_os == __m56800E_os) && !defined(__m56800E_lmm__)
			/* For dsp56800x, use 16-bit pointers */
    	    f.argument_options = short_argument;
    		f.precision        = 4;
#else
		    
		    /* For everyone else, use precision 8 and long pointers */
		    f.argument_options = long_argument;
    		f.precision        = 8;
#endif /* __ALTIVEC__ */
			break;
		
		/* CONVERSION c  argument is type char (lc = wchar_t) */
		case 'c':
#ifdef __ALTIVEC__
			if (f.argument_options != vector_argument)
#endif /* __ALTIVEC__ */
#if _MSL_WIDE_CHAR				
			if (f.argument_options == long_argument)			/*- mm 990325 -*/
				f.argument_options = wchar_argument;			/*- mm 990325 -*/
			else												/*- mm 990325 -*/
#endif /* _MSL_WIDE_CHAR */										/*- mm 990325 -*/
			if (f.precision_specified || f.argument_options != normal_argument)
				f.conversion_char = bad_conversion;
			break;
		
		/* CONVERSION s  argument is string type (char *) (ls = (wchar_t *) */
		case 's':
#ifdef __ALTIVEC__
			if (f.argument_options == vector_argument)
				f.argument_options = normal_argument;
			else
#endif /* __ALTIVEC__ */
#if _MSL_WIDE_CHAR				
			if (f.argument_options == long_argument)			/*- mm 990325 -*/
				f.argument_options = wchar_argument;			/*- mm 990325 -*/
			else												/*- mm 990325 -*/
#endif /* _MSL_WIDE_CHAR */										/*- mm 990325 -*/
#if __dest_os == __win32_os
			if (f.argument_options == short_argument)
				f.argument_options = normal_argument;			/*- ejs 020218 -*/
			else
#endif /* __dest_os == __win32_os*/
			if (f.argument_options != normal_argument)			/*- mm 990325 -*/
				f.conversion_char = bad_conversion;
			break;
		
		/* CONVERSION n  argument is (int *) where number of written characters is to be placed */
		case 'n':
			if (f.argument_options == long_double_argument)
				f.conversion_char = bad_conversion;         	/*- mm 961219 -*/
			break;
		
/* EJS 021226 */
#if defined(__POWERPC__) && defined(__SPE__)
#if _MSL_C99_PRINTF_SCANF
#if _MSL_FLOATING_POINT_IO
		/* CONVERSION rR  argument is type fractional */
		case 'R':
		case 'r':
			/*	Fractional types */
			/*	Note, the maximum number of digits, assuming 2^b = 10^d, 
				is: 16-bit fraction = 4.8 decimal digits, 
					32-bit fraction = 9.6 decimal digits, 
				and 64-bit fraction = 19.2 decimal digits. */
			if (!f.precision_specified)
				f.precision = 6;
			if (f.argument_options != short_argument
			&&	f.argument_options != normal_argument
			&&	f.argument_options != long_argument)
				f.conversion_char = bad_conversion;
			break;
#endif /* _MSL_FLOATING_POINT_IO */
#endif /*_MSL_C99_PRINTF_SCANF */
#endif /* __POWERPC__ && __SPE__ */
		
		default:
#ifdef __ALTIVEC__
			if (f.vec_state == FLAG_OR_Vcode_OK)
			{
				f.vec_state = Vcode_REQUIRED;
				f.vecSeperator = f.c_vecSeperator = (char *) s;
				f.vecSepLen = 1;
				c = *++s;
				goto getFlags;
			}
#endif /* __ALTIVEC__ */
			
			f.conversion_char = bad_conversion;
			break;
	}
	
#ifdef __ALTIVEC__
	f.vecprec  = f.precision;		/* save original prec/width for vec conversions  	*/
	f.vecwidth = f.field_width;
#endif /* __ALTIVEC__ */
	
	*format = f;
	
	return ((const char *) s + 1);
}


static char * justify_conversion(unsigned int base, int digits, int minus, char * p,
	char * buff, print_format format)
{
	if (base == 8 && format.alternate_form && *p != '0')
	{
		*--p = '0';
		++digits;
	}
	
	if (format.justification_options == zero_fill)
	{
		format.precision = format.field_width;
		
		if (minus || format.sign_options != only_minus)
			--format.precision;
		
		if (base == 16 && format.alternate_form)
			format.precision -= 2;
	}
	
	if (buff - p + format.precision > conversion_max)
		return (NULL);
	
	while (digits < format.precision)
	{
		*--p = '0';
		++digits;
	}
	
	if (base == 16 && format.alternate_form)
	{
		*--p = format.conversion_char;
		*--p = '0';
	}
	
	if (minus)
		*--p = '-';
	else if (format.sign_options == sign_always)
		*--p = '+';
	else if (format.sign_options == space_holder)
		*--p = ' ';
	
	return (p);
}


static char * long2str(long num, char * buff, print_format format)
{
	unsigned long	unsigned_num, base;
	char *			p;
	int				n, digits;
	int				minus = 0;
	
	unsigned_num = num;
	minus        =   0;
	
	p = buff;
	
	*--p = 0;
	
	digits = 0;
	
	if (!num && !format.precision && !(format.alternate_form && format.conversion_char == 'o'))
		return (p);
	
	if ((format.conversion_char == 'd') || (format.conversion_char == 'i'))
	{
			base =  10;
			
			if (num < 0)
			{
				if (num != 0x8000000000000000L)									/*- mm 050104 -*/
					unsigned_num = -num;										/*- mm 050104 -*/
				minus        = 1;
			}
	}
	else
	{
		base = set_base(format.conversion_char);
		format.sign_options = only_minus;
	}
	
	do
	{
		n = unsigned_num % base;
		
		unsigned_num /= base;
		
		if (n < 10)
			n += '0';
		else
		{
			n -= 10;
			
			if (format.conversion_char == 'x')
				n += 'a';
			else
				n += 'A';
		}
		
		*--p = n;
		
		++digits;
	}
	while (unsigned_num != 0);
	
	return justify_conversion(base, digits, minus, p, buff, format);
}


static int __pformatter(void *(_MSL_CDECL *WriteProc)(void *, const char *, size_t), void * WriteProcArg, 
														const char * _MSL_RESTRICT format_str, va_list arg, int is_secure)	/*- mm 990325 -*/ /*- cc 020108 -*/
{
	int				num_chars, chars_written, field_width;
	const char *	format_ptr;
	const char *	curr_format;
	print_format	format;
	long			long_num;
#if _MSL_C99_PRINTF_SCANF
#if _MSL_LONGLONG
	long long   	long_long_num;
#endif /* _MSL_LONGLONG */
#if _MSL_FLOATING_POINT_IO
#if _MSL_FLOATING_POINT 
	long double		long_double_num;
#endif /* _MSL_FLOATING_POINT_IO */
#endif /* _MSL_FLOATING_POINT */
#endif
	char			buff[conversion_buff_size];
	char *			buff_ptr;
	char *			string_end;
	char            fill_char = ' ';       /*- mm 960722 -*/
	
#ifdef __ALTIVEC__
	int vecIndex;				/* counts vector elements							*/
	MWVector128 vec_val;
#endif /* __ALTIVEC__ */

	format_ptr    = format_str;
	chars_written = 0;
	
	while (*format_ptr)
	{
		if (!(curr_format = strchr(format_ptr, '%')))
		{
			num_chars      = strlen(format_ptr);
			chars_written += num_chars;
			
			if (num_chars && !(*WriteProc)(WriteProcArg, format_ptr, num_chars))	/*- mm 990325 -*/
				return(-1);
			
			break;
		}
		
		num_chars      = curr_format - format_ptr;
		chars_written += num_chars;
		
		if (num_chars && !(*WriteProc)(WriteProcArg, format_ptr, num_chars))		/*- mm 990325 -*/
			return(-1);
		
		format_ptr = curr_format;
		
#if defined(__PPC_EABI__)				/*- cc 010821 -*/
		format_ptr = parse_format(format_ptr, (va_list *)arg, &format);
#else
		format_ptr = parse_format(format_ptr, (va_list *)&arg, &format);
#endif			

#ifdef __ALTIVEC__
		vecIndex = 0;
		do {				/* can be done repeatedly for each vector field */
#endif /* __ALTIVEC__ */
		
		switch (format.conversion_char)
		{
			case 'd':
			case 'i':
#ifdef __ALTIVEC__
				if (format.argument_options == vector_argument)
				{
					if (vecIndex == 0)
					{
						if (format.useVecDefault)	/* establish default vec access */
						{	
							format.vecCount   = 16;
							format.vec_access = U8;
						}
						#if defined(__VEC__)
							vec_val = va_arg(arg, MWVector128);
						#else
							va_arg_replacement1(arg, vec_val);
						#endif
					}
					switch (format.vec_access)
					{
						case U8:  long_num = vec_val.s8 [vecIndex]; break;
						case U16: long_num = vec_val.s16[vecIndex]; break;
						case U32: long_num = vec_val.s32[vecIndex]; break;
					}
				}
				else
#endif /* __ALTIVEC__ */
				if (format.argument_options == long_argument)
					long_num = va_arg(arg, long);
				
#if _MSL_C99_PRINTF_SCANF
#if _MSL_C99				
#if _MSL_LONGLONG
	            else if (format.argument_options == long_long_argument)  /*- mm 961219 -*/
					long_long_num = va_arg(arg, long long);              /*- mm 961219 -*/
#endif /* _MSL_LONGLONG */                                    /*- mm 961219 -*/
				else if (format.argument_options == intmax_argument)	 /*- mm 020529 -*/
#if _MSL_LONGLONG
					long_long_num = va_arg(arg, intmax_t);				 /*- mm 020529 -*/  /*- mm 040811 -*/
#else
					long_num = va_arg(arg, intmax_t);					 /*- mm 020529 -*/
#endif /* _MSL_LONGLONG */
				else if (format.argument_options == size_t_argument)	 /*- mm 020529 -*/
					long_num = va_arg(arg, size_t);					 	 /*- mm 020529 -*/  
				else if (format.argument_options == ptrdiff_argument)	 /*- mm 020529 -*/
					long_num = va_arg(arg, ptrdiff_t);					 /*- mm 020529 -*/
#endif /* _MSL_C99 */													 /*- mm 030304 -*/
#endif /*_MSL_C99_PRINTF_SCANF */

				else
					long_num = va_arg(arg, int);
				
				if (format.argument_options == short_argument)
					long_num = (short) long_num;
				if (format.argument_options == char_argument)
					long_num = (signed char) long_num;
					
#if _MSL_C99_PRINTF_SCANF					
#if _MSL_C99                                      /*- mm 961219 -*/
#if _MSL_LONGLONG    
                if ((format.argument_options == long_long_argument) ||   /*- mm 961219 -*/ /*- mm 040811 -*/
                		(format.argument_options == intmax_argument))	 /*- mm 040811 -*/
				{														 /*- bb 971019 -*/
				   if (!(buff_ptr = wlonglong2str(long_long_num,          /*- mm 961219 -*/
				                   buff + conversion_buff_size, format)))/*- mm 961219 -*/
					   goto conversion_error;                            /*- mm 961219 -*/
				}														 /*- bb 971019 -*/
				else 
#endif /* _MSL_LONGLONG */                                    /*- mm 961219 -*/
#endif /* _MSL_C99 */
#endif /*_MSL_C99_PRINTF_SCANF	*/				

				if (!(buff_ptr = long2str(long_num, buff + conversion_buff_size, format)))
					goto conversion_error;
				
				num_chars = buff + conversion_buff_size - 1 - buff_ptr;
				
				break;
				
			case 'o':
			case 'u':
			case 'x':
			case 'X':
#ifdef __ALTIVEC__
				if (format.argument_options == vector_argument)
				{
					if (vecIndex == 0)
					{
						if (format.useVecDefault)	/* establish default vec access */
						{	
							format.vecCount   = 16;
							format.vec_access = U8;
						}
						#if defined(__VEC__)
							vec_val = va_arg(arg, MWVector128);
						#else
							va_arg_replacement1(arg, vec_val);
						#endif
					}
					switch (format.vec_access)
					{
						case U8:  long_num = vec_val.u8 [vecIndex]; break;
						case U16: long_num = vec_val.u16[vecIndex]; break;
						case U32: long_num = vec_val.u32[vecIndex]; break;
					}
				}
				else
#endif /* __ALTIVEC__ */
				if (format.argument_options == long_argument)
					long_num = va_arg(arg, unsigned long);

#if _MSL_C99_PRINTF_SCANF					
#if _MSL_C99				
#if _MSL_LONGLONG
	            else if (format.argument_options == long_long_argument)  /*- mm 961219 -*/
					long_long_num = va_arg(arg, long long);              /*- mm 961219 -*/
#endif /* _MSL_LONGLONG */                                    /*- mm 961219 -*/
				else if (format.argument_options == intmax_argument)	 /*- mm 020529 -*/
#if _MSL_LONGLONG
					long_long_num = va_arg(arg, intmax_t);				 /*- mm 020529 -*/ /*- mm 040811 -*/
#else
					long_num = va_arg(arg, intmax_t);					 /*- mm 020529 -*/
#endif /* _MSL_LONGLONG */
				else if (format.argument_options == size_t_argument)	 /*- mm 020529 -*/
					long_num = va_arg(arg, size_t);						 /*- mm 020529 -*/
				else if (format.argument_options == ptrdiff_argument)	 /*- mm 020529 -*/
					long_num = va_arg(arg, ptrdiff_t);					 /*- mm 020529 -*/
#endif /* _MSL_C99 */													 /*- mm 030304 -*/
#endif /* _MSL_C99_PRINTF_SCANF */					

				else
					long_num = va_arg(arg, unsigned int);
				
				if (format.argument_options == short_argument)
					long_num = (unsigned short) long_num;
				if (format.argument_options == char_argument)
					long_num = (unsigned char) long_num;
					
#if _MSL_C99_PRINTF_SCANF					
#if _MSL_LONGLONG 
#if _MSL_C99                                         /*- mm 961219 -*/
                if ((format.argument_options == long_long_argument) ||   /*- mm 961219 -*/ /*- mm 040811 -*/
                		(format.argument_options == intmax_argument))	 /*- mm 040811 -*/
                {														 /*- mf 971020 -*/
				   if (!(buff_ptr = longlong2str(long_long_num,          /*- mm 961219 -*/
				                   buff + conversion_buff_size, format)))/*- mm 961219 -*/
					   goto conversion_error;                            /*- mm 961219 -*/
				} 														 /*- mf 971020 -*/
				else   
#endif /* _MSL_C99 */				                                                  /*- mm 961219 -*/
#endif /* _MSL_LONGLONG */                                   /*- mm 961219 -*/
#endif /*_MSL_C99_PRINTF_SCANF */					

				if (!(buff_ptr = long2str(long_num, buff + conversion_buff_size, format)))
					goto conversion_error;
				
				num_chars = buff + conversion_buff_size - 1 - buff_ptr;
				
				break;
#if _MSL_C99_PRINTF_SCANF					
#if _MSL_FLOATING_POINT_IO
#if _MSL_FLOATING_POINT
			case 'f':
#if _MSL_C99						/*- mm 030218 -*/
			case 'F':													/*- mm 990430 -*/
#endif /* _MSL_C99	*/					/*- mm 030218 -*/
			case 'e':
			case 'E':
			case 'g':
			case 'G':
#ifdef __ALTIVEC__
				if (format.argument_options == vector_argument) 
				{
					if (vecIndex == 0) 
					{
						if (format.useVecDefault) 	/* establish default vec access */
						{		
							format.vecCount   = 4;
							format.vec_access = U32;
						}
						#if defined(__VEC__)
							vec_val = va_arg(arg, MWVector128);
						#else
							va_arg_replacement1(arg, vec_val);
						#endif
					}
					switch (format.vec_access)
					{
						case U8:  long_double_num = vec_val.u8 [vecIndex]; break;
						case U16: long_double_num = vec_val.u16[vecIndex]; break;
						case U32: long_double_num = vec_val.f32[vecIndex]; break;
					}
				}
				else
#endif /* __ALTIVEC__ */
				if (format.argument_options == long_double_argument)
					long_double_num = va_arg(arg, long double);
				else
					long_double_num = va_arg(arg, double);
				
				if (!(buff_ptr = float2str(long_double_num, buff + conversion_buff_size, format)))
					goto conversion_error;
				
				num_chars = buff + conversion_buff_size - 1 - buff_ptr;
				break;

#if _MSL_C99
			case 'a':
			case 'A':
				if (format.argument_options == long_double_argument)
					long_double_num = va_arg(arg, long double);
				else
					long_double_num = va_arg(arg, double);
				
				if (!(buff_ptr = double2hex(long_double_num, buff + conversion_buff_size, format)))
					goto conversion_error;
				
				num_chars = buff + conversion_buff_size - 1 - buff_ptr;
				break;
#endif /* _MSL_C99 */							/*- mm 000414 -*/
#endif /* _MSL_FLOATING_POINT */
#endif /* _MSL_FLOATING_POINT_IO */
#endif /* _MSL_C99_PRINTF_SCANF */					
			
			case 's':
			  #if _MSL_WIDE_CHAR  /*- vss 990624 -*/
				if (format.argument_options == wchar_argument)			/*- mm 990325 -*/
				{														/*- mm 990325 -*/
					wchar_t * wcs_ptr = va_arg(arg, wchar_t*);			/*- mm 990325 -*/
					if (is_secure && wcs_ptr == NULL)
					{
						__msl_runtime_constraint_violation_s(NULL, NULL, -1);
						return -1;
					}
					if (wcs_ptr == NULL)
						wcs_ptr = L"";
					if ((num_chars = wcstombs(buff, wcs_ptr, sizeof(buff))) < 0)
						goto conversion_error;
					buff_ptr = &buff[0];								/*- mm 990325 -*/
				}
				else
			  #endif /* _MSL_WIDE_CHAR */
					buff_ptr = va_arg(arg, char *);
				if (is_secure && buff_ptr == NULL)
				{
					__msl_runtime_constraint_violation_s(NULL, NULL, -1);
					return -1;
				}
				if (buff_ptr == NULL)    /*- mm 970708 -*/
  					buff_ptr = "";       /*- mm 970708 -*/
				if (format.alternate_form)
				{
					num_chars = (unsigned char) *buff_ptr++;
					
					if (format.precision_specified && num_chars > format.precision)
						num_chars = format.precision;
				}
				else if (format.precision_specified)
				{
					num_chars = format.precision;
					
					if ((string_end = (char *) memchr(buff_ptr, 0, num_chars)) != 0)
						num_chars = string_end - buff_ptr;
				}
				else
					num_chars = strlen(buff_ptr);
				break;
			
			case 'n':
			{
				if (is_secure)
				{
					__msl_runtime_constraint_violation_s(NULL, NULL, -1);
					return -1;
				}
				
#if defined(__m56800E__)
				int *buff_ptr;
				buff_ptr = va_arg(arg, int *);
#else
				buff_ptr = va_arg(arg, char *);
#endif /* __m56800E__ */				
				
				switch (format.argument_options)
				{
					case normal_argument:    * (int *)       buff_ptr = chars_written; break;
					case short_argument:     * (short *)     buff_ptr = chars_written; break;
					case long_argument:      * (long *)      buff_ptr = chars_written; break;

#if _MSL_C99_PRINTF_SCANF					
#if _MSL_C99
					case intmax_argument:    * (intmax_t *)  buff_ptr = chars_written; break;
					case size_t_argument:    * (size_t *) 	 buff_ptr = chars_written; break;
					case ptrdiff_argument:   * (ptrdiff_t *) buff_ptr = chars_written; break;
#if _MSL_LONGLONG                                          /*- mm 961219 -*/
					case long_long_argument: * (long long *) buff_ptr = chars_written; break;
#endif /* _MSL_LONGLONG */
#endif /* _MSL_C99 */
#endif /* _MSL_C99_PRINTF_SCANF */	
				}
				
				continue;
			}
			
			case 'c':
				buff_ptr = buff;
#ifdef __ALTIVEC__
				if (format.argument_options == vector_argument)
				{
					if (vecIndex == 0) 
					{
						if (format.useVecDefault) 	/* establish default vec access */
						{	
							format.vecCount   = 16;
							format.vec_access = U8;
						}
						if (!format.useSepString)
						{
							format.vecSeperator = format.c_vecSeperator;
							format.vecSepLen    = *format.c_vecSeperator ? 1 : 0;
						}
						#if defined(__VEC__)
							vec_val  = va_arg(arg, MWVector128);
						#else
							va_arg_replacement1(arg, vec_val);
						#endif
					}
					switch (format.vec_access)
					{
						case U8:  *buff_ptr = vec_val.u8 [vecIndex]; break;
						case U16: *buff_ptr = vec_val.u16[vecIndex]; break;
						case U32: *buff_ptr = vec_val.u32[vecIndex]; break;
					}
					
				}
				else
#endif /* __ALTIVEC__ */		
				*buff_ptr = va_arg(arg, int);
				
				num_chars = 1;
				break;
			
/* EJS 021226 */
#if defined(__POWERPC__) && defined(__SPE__)
#if _MSL_C99_PRINTF_SCANF					
#if _MSL_FLOATING_POINT_IO
			case 'r':
				/* signed fixed-point */
				if (format.argument_options == short_argument)
					long_double_num = (short)va_arg(arg, long) / (long double)0x8000;
				else if (format.argument_options == normal_argument)
					long_double_num = va_arg(arg, long) / (long double)0x80000000UL;
				else
					long_double_num = va_arg(arg, long long) / (long double)0x8000000000000000ULL;

				format.conversion_char = 'f';
				if (!(buff_ptr = float2str(long_double_num, buff + conversion_buff_size, format)))
					goto conversion_error;
				
				num_chars = buff + conversion_buff_size - 1 - buff_ptr;
				break;
			
			case 'R':
				/* unsigned fixed-point */
				if (format.argument_options == short_argument)
					long_double_num = (unsigned short)va_arg(arg, unsigned long) / (long double)0x10000;
				else if (format.argument_options == normal_argument)
					long_double_num = va_arg(arg, unsigned long) / (long double)0x100000000ULL;
				else
					long_double_num = va_arg(arg, unsigned long long) / (2.0*(long double)0x8000000000000000ULL);

				format.conversion_char = 'f';
				if (!(buff_ptr = float2str(long_double_num, buff + conversion_buff_size, format)))
					goto conversion_error;
				
				num_chars = buff + conversion_buff_size - 1 - buff_ptr;
				break;
#endif /* _MSL_FLOATING_POINT_IO */
#endif /* __POWERPC__ && __SPE__ */
#endif /*_MSL_C99_PRINTF_SCANF	*/				

			case '%':
				buff_ptr = buff;
				
				*buff_ptr = '%';
				
				num_chars = 1;
				break;
				
			case bad_conversion:
			default:
			conversion_error:
				num_chars      = strlen(curr_format);
				chars_written += num_chars;
				
				if (num_chars && !(*WriteProc)(WriteProcArg, curr_format, num_chars))	/*- mm 990325 -*/
					return(-1);
				
				return(chars_written);
				break;
		}
		
		field_width = num_chars;
		
		if (format.justification_options != left_justification)
		{                                                                         /*- mm 960722 -*/
			fill_char = (format.justification_options == zero_fill) ? '0' : ' ';  /*- mm 960722 -*/
			if (((*buff_ptr == '+') || (*buff_ptr == '-') || (*buff_ptr == ' ')) 
														&& (fill_char == '0')) 	  /*- mm 970206 -*/ /*- mm 990831 -*/
			{	                                                                  /*- mm 970206 -*/
					if ((*WriteProc)(WriteProcArg, buff_ptr, 1) == 0)			  /*- mm 990325 -*/
					return(-1);                                                   /*- mm 970206 -*/
				++buff_ptr;                                                       /*- mm 970206 -*/
				num_chars--;                                                      /*- mm 970723 -*/
			}
			
			if ((format.justification_options == zero_fill) && ((format.conversion_char == 'a') || (format.conversion_char == 'A')))
			{
				if (num_chars < 2)
					return(-1);
				if ((*WriteProc)(WriteProcArg, buff_ptr, 2) == 0)
					return(-1);
				num_chars -= 2;
				buff_ptr += 2;
			}
			
			while (field_width < format.field_width)
			{
				if ((*WriteProc)(WriteProcArg, &fill_char, 1) == 0)  				/*- mm 990325 -*/
					return(-1);
					
				++field_width;
			}
		}                                                                       /*- mm 960722 -*/
		
		if (num_chars && !(*WriteProc)(WriteProcArg, buff_ptr, num_chars))		/*- mm 990325 -*/
			return(-1);
		
		if (format.justification_options == left_justification)
			while (field_width < format.field_width)
			{
				char blank = ' ';
				if ((*WriteProc)(WriteProcArg, &blank, 1) == 0)  				/*- mm 990325 -*/
					return(-1);
					
				++field_width;
			}
		
		chars_written += field_width;

#ifdef __ALTIVEC__
		/* Process vec types specially... */
		
		if (format.argument_options == vector_argument && ++vecIndex < format.vecCount) {
			if (format.vecSeperator && format.vecSepLen > 0) {
				if (format.vecSepLen == 1) 
				{
					if ((*WriteProc)(WriteProcArg, format.vecSeperator, 1) == 0)  /*- mm 990325 -*/
						return (-1);
				} else
					if (!(*WriteProc)(WriteProcArg, format.vecSeperator, format.vecSepLen)) /*- mm 990325 -*/
						return (-1);
				chars_written += format.vecSepLen;
			}
			format.field_width = format.vecwidth;
			format.precision   = format.vecprec;
			fill_char = ' ';
		}
		} while (format.argument_options == vector_argument && vecIndex < format.vecCount);
#endif /* __ALTIVEC__ */
	}
	
	return (chars_written);
}

void _MSL_CDECL __prep_buffer(FILE * file)
{
	file->buffer_ptr    = file->buffer;
	file->buffer_len    = file->buffer_size;	
	file->buffer_len   -= file->position & file->buffer_alignment;
	file->buffer_pos    = file->position;
}



void * _MSL_CDECL __StringWrite(void * osc, const char * Buffer, size_t NumChars) /*- cc 020108 -*/
{
	size_t CharsToBeWritten;
	void * MemCpyResult;
	__OutStrCtrl * Oscp = (__OutStrCtrl*)osc;
	
	CharsToBeWritten = ((Oscp->CharsWritten + NumChars) <= Oscp->MaxCharCount) ? NumChars : 
															Oscp->MaxCharCount - Oscp->CharsWritten;
	MemCpyResult = (void *)memcpy(Oscp->CharStr + Oscp->CharsWritten, Buffer, CharsToBeWritten);
	Oscp->CharsWritten += CharsToBeWritten;
	/*return(MemCpyResult);*/										/*- mm 000404 -*/
	return((void*)1);												/*- mm 000404 -*/
}

void _MSL_CDECL __convert_from_newlines(unsigned char * p, size_t * n)
{
#pragma unused(p,n)
}

#define set_error(file)			\
do								\
{								\
	(file)->state.error = 1;	\
	(file)->buffer_len = 0;		\
}								\
while (0)

int _MSL_CDECL __flush_buffer(FILE * file, size_t * bytes_flushed)
{
	size_t buffer_len;
	int ioresult;

	buffer_len = file->buffer_ptr - file->buffer;
	
	if (buffer_len)
	{
		file->buffer_len = buffer_len;
		
		if (!file->mode.binary_io)
			__convert_from_newlines(file->buffer, (size_t *) &file->buffer_len);
		
		ioresult = (*file->write_proc)(file->handle, file->buffer, (size_t *) &file->buffer_len, file->ref_con);
		
		if (bytes_flushed)
			*bytes_flushed = file->buffer_len;
		
		if (ioresult)
			return(ioresult);
		
		file->position += file->buffer_len;
	}
	
	__prep_buffer(file);
	
	return(__no_io_error);
}

#if _MSL_WIDE_CHAR
int _MSL_CDECL fwide(FILE* stream, int mode)
{
	int orientation;
	int result;
	
	if ((stream == NULL) || (stream->mode.file_kind == __closed_file))  /*- mm 990618 -*/
		return 0;   /* there is no associated stream therefore no orientation */
	orientation = stream->mode.file_orientation;
	switch (orientation)
	{
		case __unoriented:
			if (mode > 0)
				stream->mode.file_orientation = __wide_oriented;
			else if (mode < 0)
				stream->mode.file_orientation = __char_oriented;
			result = mode;
			break;
			
		case __wide_oriented:
			result = 1;
			break;
			
		case __char_oriented:
			result = -1;
			break;
	}
	return result;
}
 

/* This does all the work of fwrite but is not threadsafe it exists so that other
   library functions can do fwrites in a loop from within a critical region mm 001018*/			
size_t _MSL_CDECL __fwrite(const void * ptr, size_t memb_size, size_t num_memb, FILE * file)
{
	unsigned char *	write_ptr;
	size_t			num_bytes, bytes_to_go, bytes_written;
	int				ioresult, always_buffer;
	
	
#if _MSL_WIDE_CHAR && _MSL_C99							/*- mm 980205 -*/	/*- mm 030314 -*/
	if (fwide(file, 0) == 0)
		fwide(file, -1);
#endif /* _MSL_WIDE_CHAR && _MSL_C99 */                 /*- mm 980205 -*/	/*- mm 030314 -*/

	bytes_to_go = memb_size * num_memb;
	
	if (!bytes_to_go || file->state.error || file->mode.file_kind == __closed_file)
		return(0);
#if _MSL_OS_DISK_FILE_SUPPORT
	if (file->mode.file_kind == __console_file)
		__stdio_atexit();
#endif
	
	always_buffer = !file->mode.binary_io ||
					 file->mode.buffer_mode == _IOFBF           ||  /*- mm 961107 -*/
					 file->mode.buffer_mode == _IOLBF;
	
	if (file->state.io_state == __neutral)
		if (file->mode.io_mode & __write)
		{
#if !defined(__BEOS__) && _MSL_OS_DISK_FILE_SUPPORT   /* we do O_APPEND on open */ /*- mm 970708 -*/
			if (file->mode.io_mode & __append)
				if (_fseek(file, 0, SEEK_END))			/*- mm 040427 -*/
					return(0);
#endif /* !defined(__BEOS__) && _MSL_OS_DISK_FILE_SUPPORT */		/*- mm 970708 -*/
						
			file->state.io_state = __writing;
			
			__prep_buffer(file);
		}
	
	if (file->state.io_state != __writing)
	{
		set_error(file);
		return(0);
	}

	write_ptr     = (unsigned char *) ptr;
	bytes_written = 0;
	
	if (bytes_to_go && (file->buffer_ptr != file->buffer || always_buffer))
	{
		file->buffer_len = file->buffer_size - (file->buffer_ptr - file->buffer);
		
		do
		{
			unsigned char *	newline = NULL;
			
			num_bytes = file->buffer_len;
			
			if (num_bytes > bytes_to_go)
				num_bytes = bytes_to_go;
			
#if _MSL_BUFFERED_IO

			if (file->mode.buffer_mode == _IOLBF && num_bytes)
				if((newline = (unsigned char *) __memrchr(write_ptr, '\n', num_bytes)) != NULL)
					num_bytes = newline + 1 - write_ptr;
			
#endif /* _MSL_BUFFERED_IO */
			
			if (num_bytes)
			{
				memcpy(file->buffer_ptr, write_ptr, num_bytes);
				
				write_ptr     += num_bytes;
				bytes_to_go   -= num_bytes;
				
				file->buffer_ptr += num_bytes;
				file->buffer_len -= num_bytes;
			}
			if (!file->buffer_len || newline != NULL || (file->mode.buffer_mode == _IONBF))  /*- mm 970716 -*/
			{
				ioresult = __flush_buffer(file, NULL);
				
				if (ioresult)
				{
					set_error(file);
					bytes_to_go = 0;

					break;
				}
			}
			bytes_written += num_bytes;                						/*- mm 040128 -*/
		}
		while (bytes_to_go && always_buffer);
	}
	
	if (bytes_to_go && !always_buffer)
	{
		unsigned char *	save_buffer = file->buffer;
		size_t			save_size   = file->buffer_size;
		
		file->buffer      = write_ptr;
		file->buffer_size = bytes_to_go;
		file->buffer_ptr  = write_ptr + bytes_to_go;
		
		if (__flush_buffer(file, &num_bytes) != __no_io_error)
			set_error(file);
		else												/*- mm 031230 -*/
			bytes_written += num_bytes;						/*- mm 031230 -*/
		
		file->buffer      = save_buffer;
		file->buffer_size = save_size;
		
		__prep_buffer(file);
		
		file->buffer_len = 0;
	}
	
	if (file->mode.buffer_mode != _IOFBF)
		file->buffer_len = 0;
		
	return(bytes_written / memb_size);						/*- mm 031230 -*/
}

void * _MSL_CDECL __FileWrite(void *File, const char * Buffer, size_t NumChars) /*- cc 020108 -*/
{
	return (__fwrite(Buffer, 1, NumChars, (FILE *)File) == NumChars ? File : 0);	/*- mm 040428 -*/
}
#endif /* wide char */

int _MSL_CDECL vfprintf(FILE * _MSL_RESTRICT file, const char * _MSL_RESTRICT format, va_list arg)
{
	int retval;											/*- mm 001013 -*/
	int crtrgn;
												/*- mm 020627 -*/
#if _MSL_WIDE_CHAR
#if _MSL_C99_PRINTF_SCANF
#if _MSL_C99							/*- mm 030314 -*/					
	if (fwide(file, -1) >= 0)
		return(-1);
#endif /* _MSL_C99 */
#endif /* _MSL_C99_PRINTF_SCANF */
#endif /* _MSL_WIDE_CHAR */                                 

	if (file == stdout)						/*- mm 020627 -*/
		crtrgn = stdout_access;				/*- mm 020627 -*/
	else if (file == stderr)				/*- mm 020627 -*/
		crtrgn = stderr_access;				/*- mm 020627 -*/
	else									/*- mm 020627 -*/
		crtrgn = files_access;				/*- mm 020627 -*/
  	__begin_critical_region(crtrgn);		 /*- mm 001013 -*/			/*- mm 020627 -*/
	retval = __pformatter(&__FileWrite, (void *)file, format, arg, 0);/*- mm 001013 -*/
	__end_critical_region(crtrgn);				/*- mm 001013 -*//*- mm 020627 -*/
	return(retval);										/*- mm 001013 -*/
}

int _MSL_CDECL vsnprintf(char * _MSL_RESTRICT s, size_t n, const char * _MSL_RESTRICT format, va_list arg)
{
	int		end;
	__OutStrCtrl osc;
	
	osc.CharStr      = s;
	osc.MaxCharCount = n;
	osc.CharsWritten = 0;
	
	end = __pformatter(&__StringWrite, &osc, format, arg, 0);
	
	if (s)													/*- mm 000404 -*/
		if (end < n)										/*- mm 030924 -*/
			s[end] = '\0';									/*- mm 030924 -*/
		else												/*- mm 030924 -*/
			if (n > 0)										/*- mm 030924 -*/
				s[n - 1] = '\0';							/*- mm 030924 -*/
	
	return(end);
}



int _MSL_CDECL snprintf(char * _MSL_RESTRICT s, size_t n, const char * _MSL_RESTRICT format, ...)	
{
#if defined(__PPC_EABI__) || defined(__MIPS__)									/*- cc 010821 -*/
{
	va_list args;                        
	va_start( args, format );            
	return(vsnprintf(s, n, format, args));					
} 
#else                                    
	return(vsnprintf(s, n, format, __va_start(format)));	
#endif /* __PPC_EABI__ || __MIPS__ */
}


/*
	swprintf
	
	Description
	
	The swprintf function is equivalent to fwprintf, except
	that the argument s specifies an array of wide character
	into which the generated output is to be written, rather
	than written to a stream. No more that n wide characters are
	written, including a terminating null wide character, which
	is always added (unless n is zero)
	
	
	Returns
	
      [#3]  The  swprintf  function  returns  the  number  of wide
       characters  written  in  the   array,   not   counting   the
       terminating  null  wide character, or a negative value if an
       encoding error occurred or if n or more wide characters were
       requested to be written.
	
*/
#if _MSL_WIDE_CHAR


static const wchar_t * wparse_format(const wchar_t * format_string, va_list * arg, print_format * format)
{
	print_format	f;
	const wchar_t *	s = format_string;
	wchar_t			c;
	int				flag_found;
	
	f.justification_options	= right_justification;
	f.sign_options			= only_minus;
	f.precision_specified   = 0;
	f.alternate_form		= 0;
	f.argument_options		= normal_argument;
	f.field_width			= 0;
	f.precision				= 0;
	
	if ((c = *++s) == L'%')
	{
		f.conversion_char = c;
		*format = f;
		return ((const wchar_t *) s + 1);
	}
	
	for (;;)
	{
		flag_found = 1;
		
		switch (c)
		{
			/* PREFIX -  left justify output */
			case L'-':
				f.justification_options = left_justification;
				break;
			
			/* PREFIX +  always display the numeric sign */
			case L'+':
				f.sign_options = sign_always;
				break;
			
			/* PREFIX space  prefix positive numbers with a space (sign placeholder) */
			case L' ':
				if (f.sign_options != sign_always)
					f.sign_options = space_holder;
				break;
			
			/* PREFIX #  use "alternate form" for output format */
			case L'#':
				f.alternate_form = 1;
				break;
			
			/* PREFIX 0  zero fill instead of filling justification with spaces */
			case L'0':
				if (f.justification_options != left_justification)
					f.justification_options = zero_fill;
				break;
			
			/* Any other prefix character is not a flag, so continue processing format arguments */
			default:
				flag_found = 0;
				break;
		}
		
		if (flag_found)
			c = *++s;
		else
			break;
	}
	
	/* Specifier * means next argument provides the field length */
	if (c == L'*')
	{
		if ((f.field_width = va_arg(*arg, int)) < 0)
		{
			f.justification_options = left_justification;
			f.field_width           = -f.field_width;
		}
		
		c = *++s;
	}
	else
	{
		/* Field length specified by a decimal number, parse the number */
		while (iswdigit(c))
		{
			f.field_width = (f.field_width * 10) + (c - L'0');
			c = *++s;
		}
	}
	
	if (f.field_width > conversion_max)
	{
		f.conversion_char = bad_conversion;
		*format = f;
		return ((const wchar_t *) s + 1);
	}
	
	/* Specifier . means floating point precision or string length comes next */
	if (c == L'.')
	{
		f.precision_specified = 1;
		
		/* Specifier * means next argument provides the precision or string length */
		if ((c = *++s) == L'*')
		{
			if ((f.precision = va_arg(*arg, int)) < 0)
				f.precision_specified = 0;
			
			c = *++s;
		}
		else
		{
			/* Precision or string length specified by a decimal number, parse the number */
			while (iswdigit(c))
			{
				f.precision = (f.precision * 10) + (c - L'0');
				c = *++s;
			}
		}
	}
	
	flag_found = 1;
	
	switch (c)
	{
		/* Specifier h  argument will be of type short */
		case L'h':
			f.argument_options = short_argument;
			
#if _MSL_C99_PRINTF_SCANF
			/* Specifier hh  argument will be of type char */
			if (s[1] == L'h')								/*- mm 990630 -*/
			{												/*- mm 990630 -*/
				f.argument_options = char_argument;			/*- mm 990630 -*/
				c = *++s; /* move past second h */			/*- mm 990630 -*/
			}
#endif  /* _MSL_C99_PRINTF_SCANF */
			break;
		
		/* Specifier l  argument will be of type long */
		case L'l':
			f.argument_options = long_argument;
			
#if _MSL_C99_PRINTF_SCANF			
#if _MSL_LONGLONG
			if (s[1] == L'l')										/*- mm 990701 -*/
			{														/*- mm 990701 -*/
				f.argument_options = long_long_argument;			/*- mm 990701 -*/
				c = *++s; /* move past second l */					/*- mm 990701 -*/
			}														/*- mm 990701 -*/
#endif /* _MSL_LONGLONG */
#endif
			break;
		
		/* Specifier L  argument will be of type long double */
		case L'L':
			f.argument_options = long_double_argument;
			break;
		
#if _MSL_C99_PRINTF_SCANF		
		/* Specifier j  argument will be of type intmax_t */
		case L'j':
			f.argument_options = intmax_argument;
			break;
		
		/* Specifier t  argument will be of type ptrdiff_t */
		case L't':
			f.argument_options = ptrdiff_argument;
			break;
		
		/* Specifier z  argument will be of type size_t */
		case L'z':
			f.argument_options = size_t_argument;
			break;
#endif /* _MSL_C99_PRINTF_SCANF */
		
		default:
			flag_found = 0;
			break;
	}
	
	if (flag_found)
		c = *++s;
	
	f.conversion_char = c;
	
	switch (c)
	{
		/* CONVERSION diuoxX  argument is either type int (di) or unsigned int (uoxX) */
		case L'd':
		case L'i':
		case L'u':
		case L'o':
		case L'x':
		case L'X':
			
			if (f.argument_options == long_double_argument)
			{

#if _MSL_LONGLONG
#if _MSL_C99_PRINTF_SCANF
				f.argument_options = long_long_argument;
#endif
#else                                                    /*- mm 961220 -*/
				f.conversion_char = bad_conversion;      /*- mm 961219 -*/
				break;                                   /*- mm 961219 -*/
#endif                                                   /*- mm 961219 -*/
			}
			if (!f.precision_specified)
				f.precision = 1;
			else if (f.justification_options == zero_fill)
				f.justification_options = right_justification;
			break;
		
		/* CONVERSION fF  argument is type double */
		case L'f':

#if _MSL_C99_PRINTF_SCANF
		case L'F':										/*- mm 990430 -*/
#endif /* _MSL_C99_PRINTF_SCANF */

			if (f.argument_options == short_argument
#if _MSL_C99_PRINTF_SCANF
				|| f.argument_options == intmax_argument
				|| f.argument_options == size_t_argument
				|| f.argument_options == ptrdiff_argument
#if _MSL_LONGLONG
				|| f.argument_options == long_long_argument
#endif /* _MSL_LONGLONG */
#endif /* _MSL_C99_PRINTF_SCANF */
			)  /*  defacto standard %lf is a double */
			{
				f.conversion_char = bad_conversion;
				break;
			}
			
			if (!f.precision_specified)
				f.precision = 6;
			break;
#if _MSL_C99_PRINTF_SCANF		
		/* CONVERSION aA  argument is type double */
	    case L'a':								
		case L'A':
		#if _MSL_FLOATING_POINT_IO
			if (!f.precision_specified)					
				f.precision = TARGET_FLOAT_MANT_BITS / 4;				
		#endif /* _MSL_FLOATING_POINT_IO */
			if (f.argument_options == short_argument
				|| f.argument_options == intmax_argument		/*- mm 020529 -*/
				|| f.argument_options == size_t_argument
				|| f.argument_options == ptrdiff_argument	 	/*- mm 020529 -*/
#if _MSL_LONGLONG
				|| f.argument_options == long_long_argument
#endif /* _MSL_LONGLONG */
				|| f.argument_options == char_argument)
			{
				f.conversion_char = bad_conversion;
			}
			break;
#endif /* _MSL_C99_PRINTF_SCANF */
		
		/* CONVERSION gG  argument is type double */
		case L'g':
		case L'G':
			if (!f.precision)
				f.precision = 1;
			/* fall through */
		
		/* CONVERSION eE  argument is type double */
		case L'e':
		case L'E':
			if (f.argument_options == short_argument 
				|| f.argument_options == char_argument        /*- mm 990208 -*/
 #if _MSL_C99_PRINTF_SCANF
				|| f.argument_options == intmax_argument
				|| f.argument_options == size_t_argument
				|| f.argument_options == ptrdiff_argument
#if _MSL_LONGLONG
				|| f.argument_options == long_long_argument
#endif
#endif /*_MSL_C99_PRINTF_SCANF */		
			   )
			{
				f.conversion_char = bad_conversion;
				break;
			}
			
			if (!f.precision_specified)
				f.precision = 6;
			break;
		
		/* CONVERSION p  argument is type pointer to (void *) */
		case L'p':
			f.argument_options = long_argument;
			f.alternate_form   = 1;
			f.conversion_char  = L'x';
			f.precision        = 8;
			break;
			
		/* CONVERSION c  argument is type char (lc = wchar_t) */
		case L'c':
			if (f.argument_options == long_argument)			/*- mm 990322 -*/
				f.argument_options = wchar_argument;			/*- mm 990322 -*/
			else												/*- mm 990322 -*/
			if (f.precision_specified || f.argument_options != normal_argument)
				f.conversion_char = bad_conversion;
			break;
		
		/* CONVERSION s  argument is string type (char *) (ls = (wchar_t *) */
		case L's':
			if (f.argument_options == long_argument)			/*- mm 990322 -*/
				f.argument_options = wchar_argument;			/*- mm 990322 -*/
			else												/*- mm 990322 -*/
#if __dest_os == __win32_os
			if (f.argument_options == short_argument)
				f.argument_options = normal_argument;			/*- ejs 020218 -*/
			else
#endif /* __dest_os == __win32_os*/
			if (f.argument_options != normal_argument)			/*- mm 990322 -*/
				f.conversion_char = bad_conversion;
			break;
		
		/* CONVERSION n  argument is (int *) where number of written characters is to be placed */
		case L'n':
			if (f.argument_options == long_double_argument)
#if _MSL_LONGLONG                             /*- mm 961219 -*/
#if _MSL_C99_PRINTF_SCANF
				f.argument_options = long_long_argument;    /*- mm 961219 -*/
#endif
#else                                                       /*- mm 961220 -*/
				f.conversion_char = bad_conversion;         /*- mm 961219 -*/
#endif                                                      /*- mm 961219 -*/
			break;
			
		default:
			f.conversion_char = bad_conversion;
			break;
	}
	
	*format = f;
	
	return ((const wchar_t *) s + 1);
}


static int __wpformatter(void *(_MSL_CDECL *wWriteProc)(void *, const wchar_t *, size_t), void * WriteProcArg, 
													const wchar_t * format_str, va_list arg, int is_secure)	/*- mm 990325 -*/
{
	int				num_chars, chars_written, field_width;
	const wchar_t *	format_ptr;
	const wchar_t *	curr_format;
	print_format	format;
	long			long_num;
	
#if _MSL_C99_PRINTF_SCANF
#if _MSL_LONGLONG          /*- mm 961219 -*/
	long long   	long_long_num;       /*- mm 961219 -*/
#endif /* _MSL_LONGLONG */  /*- mm 961219 -*/
#if _MSL_FLOATING_POINT && _MSL_FLOATING_POINT_IO
	long double		long_double_num;
#endif /* _MSL_FLOATING_POINT */
#endif /* _MSL_C99_PRINTF_SCANF */

	wchar_t			buff[conversion_buff_size];
	wchar_t *		buff_ptr;
	wchar_t *		wstring_end;				/*- mm 990323 -*/
	char *			cstring_end;				/*- mm 990323 -*/
	wchar_t         fill_char = L' ';       	/*- mm 960722 -*/
	char * 			strptr;
	
	format_ptr    = format_str;
	chars_written = 0;
	
	while (*format_ptr)
	{
		if (!(curr_format = wcschr(format_ptr, L'%')))
		{
			num_chars      = wcslen(format_ptr);
			chars_written += num_chars;
			
			if (num_chars && !(*wWriteProc)(WriteProcArg, format_ptr, num_chars))	/*- mm 990325 -*/
				return(-1);
			
			break;
		}
		
		num_chars      = curr_format - format_ptr;
		chars_written += num_chars;
		
		if (num_chars && !(*wWriteProc)(WriteProcArg, format_ptr, num_chars))	/*- mm 990325 -*/
			return(-1);
		
		format_ptr = curr_format;
		
#if defined(__PPC_EABI__)				/*- cc 010821 -*/
		format_ptr = wparse_format(format_ptr, (va_list *)arg, &format);
#else
		format_ptr = wparse_format(format_ptr, (va_list *)&arg, &format); /*- scm 970709 -*/
#endif			
		
		switch (format.conversion_char)
		{
			case L'd':
			case L'i':
				
				if (format.argument_options == long_argument)
					long_num = va_arg(arg, long);
				
#if _MSL_C99_PRINTF_SCANF				
#if _MSL_LONGLONG
	            else if (format.argument_options == long_long_argument)  /*- mm 961219 -*/
					long_long_num = va_arg(arg, long long);              /*- mm 961219 -*/
#endif /* _MSL_LONGLONG */
				else if (format.argument_options == intmax_argument)
#if _MSL_LONGLONG
					long_long_num = va_arg(arg, intmax_t);
#else
					long_num = va_arg(arg, intmax_t);
#endif /* _MSL_LONGLONG */
#endif /* _MSL_C99_PRINTF_SCANF */

				else if (format.argument_options == size_t_argument)	 /*- mm 020529 -*/
					long_num = va_arg(arg, size_t);					 	 /*- mm 020529 -*/  
				else if (format.argument_options == ptrdiff_argument)	 /*- mm 020529 -*/
					long_num = va_arg(arg, ptrdiff_t);					 /*- mm 020529 -*/
				else
					long_num = va_arg(arg, int);
				
				if (format.argument_options == short_argument)
					long_num = (short) long_num;
					
#if _MSL_C99_PRINTF_SCANF					
#if _MSL_LONGLONG                                          /*- mm 961219 -*/
                if ((format.argument_options == long_long_argument) ||   /*- mm 961219 -*/ /*- mm 040811 -*/
                		(format.argument_options == intmax_argument))	 /*- mm 040811 -*/
				{														 /*- bb 971019 -*/
				   if (!(buff_ptr = longlong2str(long_long_num,          /*- mm 961219 -*/
				                   buff + conversion_buff_size, format)))/*- mm 961219 -*/
					   goto conversion_error;                            /*- mm 961219 -*/
				}														 /*- bb 971019 -*/
				else 
#endif /* _MSL_LONGLONG */                                    /*- mm 961219 -*/
#endif /* _MSL_C99_PRINTF_SCANF */

				if (!(buff_ptr = wlong2str(long_num, buff + conversion_buff_size, format)))
					goto conversion_error;
				
				num_chars = buff + conversion_buff_size - 1 - buff_ptr;
				
				break;
				
			case L'o':
			case L'u':
			case L'x':
			case L'X':
				
				if (format.argument_options == long_argument)
					long_num = va_arg(arg, unsigned long);
				
#if _MSL_C99_PRINTF_SCANF			
#if _MSL_LONGLONG                                          /*- mm 961219 -*/
	            else if (format.argument_options == long_long_argument)  /*- mm 961219 -*/
					long_long_num = va_arg(arg, long long);              /*- mm 961219 -*/
#endif /* _MSL_LONGLONG */                                    /*- mm 961219 -*/
				else if (format.argument_options == intmax_argument)	 /*- mm 020529 -*/
#if _MSL_LONGLONG
					long_long_num = va_arg(arg, intmax_t);				 /*- mm 020529 -*/ /*- mm 040811 -*/
#else
					long_num = va_arg(arg, intmax_t);					 /*- mm 020529 -*/
#endif /* _MSL_LONGLONG */
#endif /*_MSL_C99_PRINTF_SCANF	*/				

				else if (format.argument_options == size_t_argument)	 /*- mm 020529 -*/
					long_num = va_arg(arg, size_t);						 /*- mm 020529 -*/
				else if (format.argument_options == ptrdiff_argument)	 /*- mm 020529 -*/
					long_num = va_arg(arg, ptrdiff_t);					 /*- mm 020529 -*/
				else
					long_num = va_arg(arg, unsigned int);
				
				if (format.argument_options == short_argument)
					long_num = (unsigned short) long_num;
					
#if _MSL_C99_PRINTF_SCANF					
#if _MSL_LONGLONG                                          /*- mm 961219 -*/
                if ((format.argument_options == long_long_argument) ||   /*- mm 961219 -*/ /*- mm 040811 -*/
                		(format.argument_options == intmax_argument))	 /*- mm 040811 -*/
                {														 /*- mf 971020 -*/
				   if (!(buff_ptr = longlong2str(long_long_num,          /*- mm 961219 -*/
				                   buff + conversion_buff_size, format)))/*- mm 961219 -*/
					   goto conversion_error;                            /*- mm 961219 -*/
				} 														 /*- mf 971020 -*/
				else   
#endif /* _MSL_LONGLONG */
#endif /*_MSL_C99_PRINTF_SCANF		*/			

				if (!(buff_ptr = wlong2str(long_num, buff + conversion_buff_size, format)))
					goto conversion_error;
				
				num_chars = buff + conversion_buff_size - 1 - buff_ptr;
				
				break;
#if _MSL_C99_PRINTF_SCANF					
#if _MSL_FLOATING_POINT_IO
#if _MSL_FLOATING_POINT
			case L'f':
			case L'F':
			case L'e':
			case L'E':
			case L'g':
			case L'G':
				
				if (format.argument_options == long_double_argument)
					long_double_num = va_arg(arg, long double);
				else
					long_double_num = va_arg(arg, double);
				
				if (!(buff_ptr = float2str(long_double_num, buff + conversion_buff_size, format)))
					goto conversion_error;
				
				num_chars = buff + conversion_buff_size - 1 - buff_ptr;
				break;

			case 'a':
			case 'A':
				if (format.argument_options == long_double_argument)
					long_double_num = va_arg(arg, long double);
				else
					long_double_num = va_arg(arg, double);
				
				if (!(buff_ptr = double2hex(long_double_num, buff + conversion_buff_size, format)))
					goto conversion_error;
				
				num_chars = buff + conversion_buff_size - 1 - buff_ptr;
				break;
#endif /* _MSL_FLOATING_POINT */
#endif /* _MSL_FLOATING_POINT_IO */
#endif /*_MSL_C99_PRINTF_SCANF	*/				
			
			case L's':
				if (format.argument_options == wchar_argument)			/*- mm 990322 -*/
				{
					buff_ptr = va_arg(arg, wchar_t *);
					if (is_secure && buff_ptr == NULL)
					{
						__msl_runtime_constraint_violation_s(NULL, NULL, -1);
						return -1;
					}
					if (buff_ptr == NULL)    /*- mm 970708 -*/
	  					buff_ptr = L"";      /*- mm 970708 -*/
					if (format.alternate_form)
					{
						num_chars = (unsigned char) *buff_ptr++;
						
						if (format.precision_specified && num_chars > format.precision)
							num_chars = format.precision;
					}
					else if (format.precision_specified)
					{
						num_chars = format.precision;
						
						if ((wstring_end = (wchar_t *) wmemchr(buff_ptr, 0, num_chars)) != 0)  /*- mm 990322 -*/
							num_chars = wstring_end - buff_ptr;
					}
					else
						num_chars = wcslen(buff_ptr);
				}
				else
				{
					
					strptr = va_arg(arg, char *);
					if (is_secure && strptr == NULL)
					{
						__msl_runtime_constraint_violation_s(NULL, NULL, -1);
						return -1;
					}
					if (strptr == NULL)    /*- mm 970708 -*/
	  					strptr = "";       /*- mm 970708 -*/
					if (format.alternate_form)
					{
						num_chars = (unsigned char) *buff_ptr++;
						
						if (format.precision_specified && num_chars > format.precision)
							num_chars = format.precision;
					}
					else if (format.precision_specified)
					{
						num_chars = format.precision;
						
						if ((cstring_end = (char *) memchr(strptr, 0, num_chars)) != 0)  /*- mm 990322 -*/
							num_chars = cstring_end - strptr;
					}
					else
						num_chars = strlen(strptr);
	  				if ((num_chars = mbstowcs(buff, strptr, num_chars)) < 0)
						goto conversion_error;
	  				
	  				buff_ptr = &buff[0];
				}	
				break;
				
			case L'n':
				if (is_secure)
				{
					__msl_runtime_constraint_violation_s(NULL, NULL, -1);
					return -1;
				}
				
				buff_ptr = va_arg(arg, wchar_t *);
				
				switch (format.argument_options)
				{
					case normal_argument:    * (int *)       buff_ptr = chars_written; break;
					case short_argument:     * (short *)     buff_ptr = chars_written; break;
					case long_argument:      * (long *)      buff_ptr = chars_written; break;
					case intmax_argument:    * (intmax_t *)  buff_ptr = chars_written; break;
					case size_t_argument:    * (size_t *) 	 buff_ptr = chars_written; break;
					case ptrdiff_argument:   * (ptrdiff_t *) buff_ptr = chars_written; break;

#if _MSL_C99_PRINTF_SCANF					
#if _MSL_LONGLONG                                          /*-mm 961219 -*/
					case long_long_argument: * (long long *) buff_ptr = chars_written; break;
#endif /* _MSL_LONGLONG */                                  /*- mm 961219 -*/
#endif /*_MSL_C99_PRINTF_SCANF */					
 
				}
				
				continue;
			
			case L'c':
				buff_ptr = buff;
				if (format.argument_options == wchar_argument)			/*- mm 990322 -*/
				{
				
					*buff_ptr = va_arg(arg, int);
					
					num_chars = 1;
				}
				else
				{
					char chint = va_arg(arg, int);
					num_chars = mbtowc(buff, &chint, 1);
				}
				
				break;
			
			case L'%':
				buff_ptr = buff;
				
				*buff_ptr = L'%';
				
				num_chars = 1;
				break;
				
			case bad_conversion:
			default:
			conversion_error:
				num_chars      = wcslen(curr_format);
				chars_written += num_chars;
				
				if (num_chars && !(*wWriteProc)(WriteProcArg, curr_format, num_chars))	/*- mm 990325 -*/
					return(-1);
				
				return(chars_written);
				break;
		}
		
		field_width = num_chars;
		
		if (format.justification_options != left_justification)
		{                                                                         		/*- mm 960722 -*/
			fill_char = (format.justification_options == zero_fill) ? L'0' : L' ';  	/*- mm 960722 -*/
			if (((*buff_ptr == L'+') || (*buff_ptr == L'-') || (*buff_ptr == L' ')) 
															&& (fill_char == L'0')) 	/*- mm 990905 -*/	
			{	                                                                  		/*- mm 970206 -*/
				if ((*wWriteProc)(WriteProcArg, buff_ptr, 1) == 0)                      /*- mm 990325 -*/
					return(-1);                                                   		/*- mm 970206 -*/
				++buff_ptr;                                                       		/*- mm 970206 -*/
				num_chars--;                                                      		/*- mm 970723 -*/
			}
			
			if ((format.justification_options == zero_fill) && ((format.conversion_char == L'a') || (format.conversion_char == L'A')))
			{
				if (num_chars < 2)
					return(-1);
				if ((*wWriteProc)(WriteProcArg, buff_ptr, 2) == 0)
					return(-1);
				num_chars -= 2;
				buff_ptr += 2;
			} /*- jw P73257.c Execution passed -*/

			while (field_width < format.field_width)
			{
				if ((*wWriteProc)(WriteProcArg, &fill_char, 1) == 0)                       /*- mm 990325 -*/
					return(-1);
					
				++field_width;
			}
		}                                                                       		/*- mm 960722 -*/
		
		if (num_chars && !(*wWriteProc)(WriteProcArg, buff_ptr, num_chars))	/*- mm 990325 -*/
			return(-1);
		
		if (format.justification_options == left_justification)
			while (field_width < format.field_width)
			{
				wchar_t blank = L' ';
				if ((*wWriteProc)(WriteProcArg, &blank, 1) == 0)  				/*- mm 990311 -*/
					return(-1);
					
				++field_width;
			}
		
		chars_written += field_width;
	}
	
	return (chars_written);
}

void * _MSL_CDECL __wStringWrite(void * wosc, const wchar_t * Buffer, size_t NumChars) /*- cc 020108 -*/
{
	size_t wCharsToBeWritten;
	void * MemCpyResult;
	__wOutStrCtrl * wOscp = (__wOutStrCtrl*)wosc;
	
	wCharsToBeWritten = ((wOscp->CharsWritten + NumChars) <= wOscp->MaxCharCount) ? NumChars : 
															wOscp->MaxCharCount - wOscp->CharsWritten;
	MemCpyResult = (void *)wmemcpy(wOscp->wCharStr + wOscp->CharsWritten, Buffer, wCharsToBeWritten);
	wOscp->CharsWritten += wCharsToBeWritten;
	return(MemCpyResult);
}


/*
	vswprintf
	
	Description
	
	The vswprintf function is equivalent to swprintf with
	the variable argument list replaced by arg, which shall have
	been initialized by the va_start macro (and possibly
	subsequent va_arg calls). The vswprintf function does not
	invoke the va_end macro.
	
	
	Returns
	
	The vswprintf function returns the number of wide 
	characters written in the array, not counting the
	terminating null wide character, or a negative value if n or
	more wide characters were requested to be generated.
	
*/

int _MSL_CDECL vswprintf(wchar_t * _MSL_RESTRICT s, size_t n, const wchar_t * _MSL_RESTRICT format, va_list arg)
{
	int		count;
	__wOutStrCtrl wosc;
	
	wosc.wCharStr     = s;
	wosc.MaxCharCount = n;
	wosc.CharsWritten = 0;
	
	count = __wpformatter(&__wStringWrite, &wosc, format, arg, 0);
	
	if (count >= 0)				/*- mm 990316 -*/
		if (count < n)			/*- mm 990316 -*/
			s[count] = 0;		/*- mm 990316 -*/
		else					/*- mm 990316 -*/
		{						/*- mm 990316 -*/
			s[n-1] = 0;			/*- mm 990316 -*/
			count  = -1;		/*- mm 990316 -*/
		}						/*- mm 990316 -*/
	
	return(count);
}



int _MSL_CDECL swprintf(wchar_t * _MSL_RESTRICT s, size_t n, const wchar_t * _MSL_RESTRICT format, ...)
{
#if (defined(__PPC_EABI__)    || defined(__MIPS__))
	va_list args;                        							/*- scm 970709 -*/
	va_start( args, format );            							/*- scm 970709 -*/
	return(vswprintf(s, n, format, args));   						/*- scm 970709 -*/
#else                                    							/*- scm 970709 -*/
	return(vswprintf(s, n, format, __va_start(format)));
#endif                                   							/*- scm 970709 -*/
}



#endif /* _MSL_WIDE_CHAR */


#endif /*  _MSL_TESTING_TINY_IO */

#endif /* _MSL_C_TINY_IO */


/* Change record:
 * JFH 950918 First code release.
 * JFH 950929 Fixed bug in 'f' format where a zero fractional part would be suppressed
 *			  regardless of the precision.
 * JFH 951010 Changed long2str to comply with Standard saying: "The result of converting
 *			  a zero value with a precision of zero is no characters."
 * JFH 951030 Corrected handling of 'g','G' conversions using the alternate form (#).
 * JFH 960222 Added casts from (void *) for C++ compatibility.
 * JFH 960219 Added #ifndef around area that handles floating point output. If disabled, you
 *			  can get away with not including MathLib just because you wanted to use printf.
 *			  There is also some ANSI lib code savings as well.
 * JFH 960907 Fixed bug in round_decimal where it *wasn't* rounding anything if all the
 *			  precision digits were zero.
 * JFH 960919 Changed handling of '+' flag so it doesn't affect how unsigned values (i.e.,
 *			  o,u,x,X) are displayed.
 * JFH 960924 Changed "round_decimal" to do rounding using more conventional rules of
 *			  arithmetic. :-)
 * MM  960722 Fill with zeros when required.
 * bkoz960829 add l.you's changes for powertv, defines for no floating point
 * mm  960930 Removed bitfields from printformat structure to compile with ANSI strict
 * mm  961220 Support for long long.
 * mani970101 Don't choke if a NULL string is passed to %s. Just print "(null)".
 * mm  970206 Corrected position of sign and left zero fill
 * mm  970213 Made to print -Inf for negative infinite values
 * mm  970609 Set the max number of significant digits tolarger than DBL_DIG
 * mm  970614 Modifications to remove trailing blanks for g format and to round to nearest or even
 * mm  970702 Modified Mani's fix to conform to Standard
 * mm  970708 Inserted Be changes
 * SCM 970709 Converted __va_start() to va_start() for PPC_EABI
 * mm  970723 Further correction to change of 970206  BW01232
 * beb 971019 Cleaned up confusing nested if statements
 * mf  971020 found another bad if block under long long support
 * FS  980113 Converted __va_start() to va_start() for MIPS_bare
 * mm  980206 Added wide-character support
 * BLC 980301 added vsnprintf, snprintf functions
 * BLC 980309 added format string support for 'll' and 'hh' type mods from C9X
 * MEA 980320 Changed the call to parse_format for PPC_EABI
 * mf  060298 should print 0 with correct sign(i.e. -0 when the number is minus zero(0x80000000)
 * mm  980715 corrected placement of null char in result of vsnprintf MW07942
 * ad  990128 guarded printf() and sprintf() with if __dest_os != __n64_os
 * vss 990203 Add AltiVec changes (contributed)
 * mm  990208 Change to make %lE, %le, %lG, and %lg be accepted but ignore the l (C9x Clause 7.13.6.1 para #3)
 * mm  990317 ReCorrected placement of null char in result of vsnprintf to match C9x (IL9903-1264)
 * mm  990325 Modified to make split between string functions andfile i/o
 * mm  990430 Added code for %F in accordance with C9x
 * mm  990430 Brought printing of inf into line with C9x
 * vss 990624 Added NO_WIDE_CHAR wrappers
 * mm  990430 Brought printing of nan into line with C9x
 * mm  990817 Deleted include of <string_io.h>
 * mm  990722 Added code for %a %A
 * mm  990722 Brought printing of NaN into line with C9x
 * mm  990831 Move blank where there is zero fill and a blank sign space holder IL9908-4231
 * mm  990901 Print correct sign for zero.  IL9908-4232
 * mm  991102 Corrected fix of 970614
 * mm  000404 Corrected problem with passing null string to snprintf  WB1-12370
 * mm  000414 Excluded %a %A from 68k because algorithm not correct for it
 * mm  001013 Threadsafety changes for fprintf, printf, vfprintf, vprintf
 * PMK 010703 Double2Hex( ) function will now work for little endian (X-86) architecture.
 * mm  010710 Corrected rounding to fix WB1-24254
 * cc  010821 Added EPPC to core
 * mm  011130 Changes for implementation of locale
 * cc  011203 Added _MSL_CDECL for new name mangling
 * JWW 020130 Changed _MWMT to _MSL_THREADSAFE for consistency's sake
 * ejs 020218 Support MS extension for %hs == %s
 * mm  020529 Support for C99 length modifiers j, z, and t.
 * JWW 020604 Added _MSL_LOCALDATA macro to make multithread code easier to read
 * mm  020627 Changes to prevent io on stdin, stdout, stderr and general files from interfering with each other
 * JWW 020917 Added _MSL_RESTRICT to get the restrict type specifier for certain C99 functions
 * ejs 021002 Fix little-endian and portability bugs in doubletohex()
 * cc  021004 Added _MSL_C_LOCALE_ONLY
 * ejs 021009 Make hex float printing really independent of 64-bit double format
 * JWW 021031 Made thread local data available for Mach-O
 * ejs 021226 Added %hR,%R,%lR,%hr,%r,%lr for e500 SPE PIM
 * mm  030218 Added some C99 wrappers
 * JWW 030224 Changed __MSL_LONGLONG_SUPPORT__ flag into the new more configurable _MSL_LONGLONG
 * JWW 030224 Changed __NO_WIDE_CHAR flag into the new more configurable _MSL_WIDE_CHAR
 * mm  030304 Added some more C99 wrappers
 * mm  030314 And more _MSL_C99 wrappers
 * mm  030422 Modifications to print the value zero under %a and %A with a zero exponent for C99
 * ejs 030627 Fix bug in %hh specifier with signed argument (use "signed char", not "char" conversion)
 * mm  030924 Fix to correct action of vsnprintf() invoked with n=0.  Thanks to Bogdan Marinescu
 * cc  040217 Changed _No_Floating_Point to _MSL_FLOATING_POINT
 * cc  040217 Changed _No_Disk_File_OS_Support to _MSL_OS_DISK_FILE_SUPPORT
 * mm  040428 Change to call __fwrite instead of fwrite to avoid nested critical regions.
 * mm  040811 Changes to correct handling arguments of type intmax_t  MTWX14449
 * mm  050104 Changes to correct handling of long and longlong arguments that are close to zero.
 * cc  060306 Redid 0 case
 */
