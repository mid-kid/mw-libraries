/*****************************************************
    stdlib.c - ANSI-C library: various functions
 ----------------------------------------------------
   Copyright (c) Metrowerks, Basel, Switzerland
               All rights reserved
                  Do not modify!
 *****************************************************/

#include <errno.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include <ctype.h>
#include <stdio.h>

#undef toupper
#undef isspace
#undef isdigit

#define _100TEN     1.0e100
#define _10TEN      1.0e010
#define _1TEN       1.0e001
#define _TEN1       1.0e-001
#define _TEN10      1.0e-010
#define _TEN100     1.0e-100

#if LIBDEF_ENABLE_OVERFLOW_CHECK
  #define CHECK_OVERFLOW(val, rel, lim, error) if ((val) rel (lim)) {_errno = (error); }
#else
  #define CHECK_OVERFLOW(val, rel, lim, error)
#endif
/*****************************************************/
/*****************************************************/
typedef char * LIBDEF_StringPtr;
typedef const char * LIBDEF_ConstStringPtr;

#ifndef __NO_FLOAT__
static double _strtod (LIBDEF_ConstStringPtr nptr, LIBDEF_StringPtr *endptr, unsigned int len) {
  /* len == 0 -> now length specified */
  double dsum, fplc;
  char nsgn, ensgn;
  LIBDEF_ConstStringPtr nptr0 = nptr;
  char _errno=0;

  dsum = 0.0; fplc = 10.0;
  nsgn = 0; ensgn = 0;

  while (isspace((unsigned char)(*nptr))) {
    ++nptr;   /* Eat any white spaces */
  }
  if (!(isdigit((unsigned char)(*nptr)))) {         /* Check for sign */
    switch (*nptr) {
       case '-': nsgn=1;           /* Set negative sign flag */
                 /*lint -fallthrough */
       case '+': ++nptr;
                 if (--len == 0) {
                   _errno= 1;
                   goto rt; /*lint !e801 Use of goto is not deprecated */
                 }
                 /*lint -fallthrough */
       case '.': break;
       default :
         nptr = nptr0;
         _errno = 1;
         goto rt;          /* Neither digit, '.' or sign */ /*lint !e801 Use of goto is not deprecated */
    } /* end switch */
  } /* end if */
  while (isdigit((unsigned char)(*nptr))) {         /* Set integer portion */
    CHECK_OVERFLOW(dsum, >, DBL_MAX/10.0, 1);
    dsum *= 10.0;
    CHECK_OVERFLOW(dsum, >, DBL_MAX - *nptr + '0', 1);
    dsum += (*nptr++ - '0');
    if (--len == 0) {
      goto rt; /*lint !e801 Use of goto is not deprecated */
    }
    if (--len == 0) {
      goto rt; /*lint !e801 Use of goto is not deprecated */
    }
  } /* end while */
  switch (*nptr) {                  /* Check char */
    default: goto rt;              /* End of 'double' | string */ /*lint !e801 Use of goto is not deprecated */
    case 'e' :
    case 'E' : goto xp;            /* Goto set exponent */ /*lint !e801 Use of goto is not deprecated */
    case '.' : ++nptr;             /* Check locale for decimal . */
               if (--len == 0) {
                 goto rt; /*lint !e801 Use of goto is not deprecated */
               }
  } /* end switch */
  while (isdigit((unsigned char)(*nptr))) {         /* Set fractional portion */
#if LIBDEF_STRTOD_EXTENDED_PREC
    dsum*=10;
    dsum += (*nptr++ - '0');
#else
    dsum += (*nptr++ - '0') / fplc;
#endif

#if LIBDEF_STRTOD_EXTENDED_PREC
    if (--len == 0) {
      dsum/=fplc;
      goto rt; /*lint !e801 Use of goto is not deprecated */
    }
    fplc *= 10;
#else
    fplc *= 10;
    if (--len == 0) {
      goto rt; /*lint !e801 Use of goto is not deprecated */
    }
#endif
  } /* end while */
#if LIBDEF_STRTOD_EXTENDED_PREC
  dsum/=(fplc/10);
#endif

xp:
  if (toupper((unsigned char)(*nptr)) == 'E') {    /* Is there an exponent */
    int xp;

    xp = 0;
    switch (*++nptr) {
      case '-' : ensgn = 1;
        /*lint -fallthrough */
      case '+' : ++nptr;
      if (--len == 0) {
        goto rt; /*lint !e801 Use of goto is not deprecated */
      }
    } /* end switch */
    while (isdigit((unsigned char)(*nptr))) {      /* Get exponent value */
      CHECK_OVERFLOW(xp, >, INT_MAX/10, ensgn ? -1 : 1);
#if LIBDEF_ENABLE_OVERFLOW_CHECK
      if (_errno == 0) {
#endif
        xp *= 10;
#if LIBDEF_ENABLE_OVERFLOW_CHECK
      }
#endif
      CHECK_OVERFLOW(xp, >, INT_MAX - *nptr + '0', ensgn ? -1 : 1);
#if LIBDEF_ENABLE_OVERFLOW_CHECK
      if (_errno == 0) {
#endif
        xp += (*nptr++ - '0');
#if LIBDEF_ENABLE_OVERFLOW_CHECK
      } else {
        nptr++;
      }
#endif
      if (--len == 0) {
        break;
      }
    } /* end while */
/*
    if (ensgn) fplc = 0.001; else fplc = 1000.0;
    while (xp >= 100) {
      dsum *= fplc; xp -= 100;
    };
    if (ensgn) fplc = 0.01; else fplc = 100.0;
    while ( xp >= 10) {
      dsum *= fplc; xp -= 10;
    };
    if (ensgn) fplc = 0.1; else fplc = 10.0;
    while (xp) {
      dsum *= fplc; --xp;
    };
*/
#if LIBDEF_ENABLE_OVERFLOW_CHECK
    if (_errno != 0) { /* over or under flow */
      goto rt; /*lint !e801 Use of goto is not deprecated */
    }
#endif
    if (ensgn) { fplc = _TEN100; } else { fplc = _100TEN; }
    /* Set to exponent */
    while (xp >= 100) {
      if (ensgn) {
        CHECK_OVERFLOW(dsum, ==, 0.0, -1);
      } else {
        CHECK_OVERFLOW(dsum, >, DBL_MAX / fplc, 1);
      }
      dsum *= fplc; xp -= 100;
    } /* end while */
    if (ensgn) { fplc = _TEN10; } else { fplc = _10TEN; }
    while ( xp >= 10) {
      if (ensgn) {
        CHECK_OVERFLOW(dsum, ==, 0.0, -1);
      } else {
        CHECK_OVERFLOW(dsum, >, DBL_MAX / fplc, 1);
      }
      dsum *= fplc; xp -= 10;
    } /* end while */
    if (ensgn) { fplc = _TEN1; } else { fplc = _1TEN; }
    while (xp) {
      if (ensgn) {
        CHECK_OVERFLOW(dsum, ==, 0.0, -1);
      } else {
        CHECK_OVERFLOW(dsum, >, DBL_MAX / fplc, 1);
      }
      dsum *= fplc; --xp;
    } /* end while */
  } /* end if */

rt:
#if LIBDEF_ENABLE_OVERFLOW_CHECK
  if (nptr0 != nptr) { /* something read */
    if (_errno == 1)  {
      _errno=ERANGE; dsum = HUGE_VAL;
    } else if (_errno == -1) {
      _errno=ERANGE; dsum = 0;
    }
  }
#endif
  if (endptr) { *endptr = (LIBDEF_StringPtr)nptr; }
  if (_errno != 0) {
    errno= _errno;
  }
  if (nsgn) { return -dsum; } else { return dsum; }
} /* end strtod */
/*****************************************************/
double strtod (const char *nptr, char **endptr) {
  return _strtod (nptr, endptr, 0);
}

double _atof(const char * str)
{
 return(strtod(str, NULL));
}
 
#endif /* __NO_FLOAT__ */

/* end strtold_tiny.c */
