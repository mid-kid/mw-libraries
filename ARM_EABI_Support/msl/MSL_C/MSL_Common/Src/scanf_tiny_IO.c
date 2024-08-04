/* MSL
 * Copyright © 1995-2007 Freescale Corporation.  All rights reserved.
 *
 * $Date: 2008/04/14 15:30:53 $
 * $Revision: 1.7.2.1 $
 */

/*	Routines
 *	--------
 *		fscanf
 *		fscanf_s
 *		scanf
 *		scanf_s
 *		sscanf
 *		sscanf_s
 *		vfscanf
 *		vfscanf_s
 *		vsscanf
 *		vsscanf_s
 */

#include <ansi_parms.h>

#if _MSL_C_TINY_IO

#include <strtold.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <ctype.h>
#include <strtoul.h>
#include <console_io.h>
#include <limits.h>
#include <stdint.h>

#if _MSL_WIDE_CHAR
#include <weof.h>
#include <wctype.h>
#include <stddef.h>
#include <wcstoul.h>
#endif /* _MSL_WIDE_CHAR */


#ifdef __HC12__
  #pragma MESSAGE DISABLE C12002 /* WARNING C12002: Use DPAGE, PPAGE, EPAGE to specify the page register. Assumed DPAGE */
#endif
#ifdef __HIWARE__
#pragma MESSAGE DISABLE C4001 /* INFORMATION C4001: Condition always FALSE */
#pragma MESSAGE DISABLE C2705 /* Possible loss of data */
#endif

#undef isspace
#undef toupper

#if defined(__SHORT_IS_8BIT__) && defined(__INT_IS_8BIT__) || defined(__SHORT_IS_16BIT__) && defined(__INT_IS_16BIT__) || defined(__SHORT_IS_32BIT__) && defined(__INT_IS_32BIT__) || defined(__SHORT_IS_64BIT__) && defined(__INT_IS_64BIT__)
#define SAME_SIZE_INT_SHORT 1
#else
#define SAME_SIZE_INT_SHORT 0
#endif

#if defined(__SHORT_IS_8BIT__) && defined(__INT_IS_8BIT__) || defined(__SHORT_IS_16BIT__) && defined(__INT_IS_16BIT__) || defined(__SHORT_IS_32BIT__) && defined(__INT_IS_32BIT__) || defined(__SHORT_IS_64BIT__) && defined(__INT_IS_64BIT__)
#define SAME_SIZE_INT_SHORT 1
#else
#define SAME_SIZE_INT_SHORT 0
#endif

#if defined(__FLOAT_IS_IEEE32__) && defined(__DOUBLE_IS_IEEE32__) || defined(__FLOAT_IS_IEEE64__) && defined(__DOUBLE_IS_IEEE64__) || defined(__FLOAT_IS_DSP__) && defined(__DOUBLE_IS_DSP__)
#define SAME_ENCODING_DOUBLE_FLOAT 1
#else
#define SAME_ENCODING_DOUBLE_FLOAT 0
#endif

/*****************************************************/
static int _getNum(const char * *format)
{
   int n = 0;
   char ch = **format;
   while (ch >= '0' && ch <= '9') {
      n = 10*n + ch - '0';
      ch = *(++(*format));
   }
   return n;
} /* end _getNum */

/*****************************************************/
#if 0
#if LIBDEF_MULTI_CHAR_SELECTION
#if LIBDEF_PRINTF_FAR_PTR
static const char *_copyFarList(char *FAR fss, const char *s, const char **nsp, const char *format, int *tasg, int fwi, int ma)
{
   const char *FAR m;
   const char *FAR start;
   char found, sz = 0;
   int count = 0;

   *tasg = 1;
   if(*(++format) == '^') {  /* Set not eql. flag */
      sz = 1; format++;
   }
   start= format;
   if (*format == ']') {
      format++;                   /* Special case */
   }
   while (*format && (*format != ']')) {       /* Set mtchbuf */
      format++;
   }

   while (*s && fwi) {
      fwi--;
      m = start;                            /* Reset m to top */
      while (m != format && *s != *m) { m++; }

      found = (m != format);
      if (sz == found) { 
        if(count == 0) {
          *tasg = 0;
        }
        break;
      }  /* failed */
      if (ma) { *fss++ = *s; }                /* Passed test, next s */
      s++;
      count++;
   }
   if (ma) { *fss = '\0'; }               /* Terminate array */

   *nsp = s;
   return format;
} /* end _copyFarList */
#endif

static const char * _copyList(char *ss, const char * s, const char **nsp, const char * format, int *tasg, int fwi, int ma)
{
   const char * m, start;
   char found, sz = 0;
   int count = 0;

   *tasg = 1;
   if(*(++format) == '^') {  /* Set not eql. flag */
      sz = 1; format++;
   }
   start= format;
   if (*format == ']') {
      format++;                   /* Special case */
   }
   while (*format && (*format != ']')) {       /* Set mtchbuf */
      format++;
   }

   while (*s && fwi) {
      fwi--;
      m = start;                            /* Reset m to top */
      while (m != format && *s != *m) { m++; }

      found = (m != format);
      if (sz == found) { 
        if(count == 0) {
          *tasg = 0; 
        }
        break; 
      }  /* failed */
      if (ma) { *ss++ = *s; }                 /* Passed test, next s */
      s++;
      count++;
   }
   if (ma) { *ss = '\0'; }                       /* Terminate array */

   *nsp = s;
   return format;
} /* end _copyList */
#endif /* LIBDEF_MULTI_CHAR_SELECTION */
#endif
/*****************************************************/
/* only internaly used functions defined in stdlib.c */


/*****************************************************/

int _MSL_CDECL vsscanf(const char * _MSL_RESTRICT ps, const char * format, va_list args)
{
   const char * s=ps;
   char sz, ma, base;           /* Size and no-assign flags  */
   char * nsp;   /* New s position            */
   char * ss= NULL;
   int ok;
   int fwi;                     /* Field width size          */
   const char * sbase; /* base addr of string s     */
   int tasg = 0;                /* Total assignments made    */
   unsigned char nConversion= 0; /* TRUE iff %n conversion was done. Does not count as assignment, but affects the return value */

#if LIBDEF_PRINTF_FAR_PTR
   unsigned char is_far_ptr;    /* Is it a FAR pointer */
   char *FAR far_ptr = NULL;    /* FAR pointer */
#endif

   sbase = s;

   while (*format) {
      sz = fwi = base = 0;
      ma = 1;
      if (isspace(*format)) {  /* White space flag */
         while (isspace(*format)) { ++format; }    /* Eat white space */
         if (isspace(*s)) {
            while(isspace(*s)) {
               ++s;
            }   /* Is white space and was eaten */
         }
#if !LIBDEF_SCANF_DONTCARE_SPACES
         else if (*s) { goto inputFailure; } /* Is no white space, is input failure */ /*lint !e801 Use of goto is not deprecated */
#endif
      }
      if (*format !='%') {/* Read input string */
         if (*s) {
            if (*s++ == *format++) {
               ; /* Character match */
            } else {
               /* non matching character -> match failure-> return number of assignments */
               goto endScan; /*lint !e801 Use of goto is not deprecated */
            }
         } else {
            /* nothing more to match against -> input failure -> return EOF if no assignments done */
            goto inputFailure; /*lint !e801 Use of goto is not deprecated */
         }
      } else {
         /* Conversion specification */
         format++; /* Drop %  */
#if LIBDEF_PRINTF_FAR_PTR
         is_far_ptr = FALSE;
#endif
         if (*format == '*') {
            /* Assignment suppressed */
            format++;
            ma = 0;
#if LIBDEF_PRINTF_FAR_PTR
         } else if (*format == '+') {
            format++;
            is_far_ptr = TRUE;
#endif
         }

         fwi = _getNum(&format);  /* Get max field width if any */

         switch (*format++) {
            case 'h': sz = 1; break;
            case 'l': sz = 2; break;
            case 'L': sz = 3; break;
            default: format--;
         }

         if (*s == 0 && *format != 'n' && *format != 'N' && *format != '%') {
           goto inputFailure;  /* input failure */ /*lint !e801 Use of goto is not deprecated */
         }
         switch(*format) {
            case 'd': base = 10;
            case 'i': 
                    {
                      long l = __strtol(s, &nsp, base, fwi);
                      if (nsp == s) {
                        goto endScan; /* conversion failure */ /*lint !e801 Use of goto is not deprecated */
                      }
                      if (ma)
                      {
#if LIBDEF_PRINTF_FAR_PTR
                         if (is_far_ptr)
                         {
                            switch(sz)
                            {
                               case 1:
                                  *va_arg(args, short int *FAR) = l;
                                  break;
                               case 2:
                               case 3:
                                  *va_arg(args, long int *FAR) = l;
                                  break;
                               default:
                                  *va_arg(args, int *FAR) = l;
                                  break;
                            }
                         } else {
#endif
                            switch(sz)
                            {
                               case 1:
                                  *va_arg(args, short int*) = (short int)l;
                                  break;
                               case 2:
                               case 3:
                                  *va_arg(args, long int*) = l;
                                  break;
                               default:
                                  *va_arg(args, int*) = l;
                                  break;
                            }
#if LIBDEF_PRINTF_FAR_PTR
                         }
#endif
                         tasg++; /* count number of assigned items */
                      }
                      s = nsp;
                      break;
                    }
            case 'o': base = 8;  goto xx; /*lint !e801 Use of goto is not deprecated */
#if LIBDEF_PRINTF_FAR_PTR
            case 'P': sz = 5;
                      base = 16; goto xx; /*lint !e801 Use of goto is not deprecated */
#endif
            case 'p': sz = 4;
            case 'X':
            case 'x': base = 16; goto xx; /*lint !e801 Use of goto is not deprecated */
            case 'u': {
                      unsigned long l;
                      base = 10;
xx:
                      if (*s == '-') {
                        ++s;  /* Strip sign if any */
                        fwi--;
                      }
                      l = __strtol(s, &nsp, base, fwi);
                      if (nsp == s) {
                        goto endScan; /* conversion failure */ /*lint !e801 Use of goto is not deprecated */
                      }
                      if (ma)
                      {
#if LIBDEF_PRINTF_FAR_PTR
                         if (is_far_ptr)
                         {
                            switch(sz)
                            {
                               case 2:
                               case 3:
                                  *va_arg(args, unsigned long int *FAR) = l;
                                  break;
                               case 4:
                                  *va_arg(args, char * *FAR) = (char *) l;
                                  break;
                               case 5:
                                  *va_arg(args, char *FAR *FAR) = (char *FAR) l;
                                  break;
                               case 1:
#if !SAME_SIZE_INT_SHORT
                                  *va_arg(args, unsigned short int *FAR) = l;
                                  break;
#endif
                               default:
                                  *va_arg(args, unsigned int *FAR) = l;
                            }
                         } else {
#endif
                            switch(sz)
                            {
                               case 2:
                               case 3:
                                  *va_arg(args, unsigned long int*) = l;
                                  break;
                               case 4:
                                  *va_arg(args, char**) = (char*)l;
                                  break;
#if LIBDEF_PRINTF_FAR_PTR
                               case 5:
                                  *va_arg(args, char *FAR *) = (char *FAR) l;
                                  break;
#endif
#if !SAME_SIZE_INT_SHORT
                               case 1:
                                  *va_arg(args, unsigned short int*) = (unsigned short int)l;
                                  break;
#endif
                               default:
                                  *va_arg(args, unsigned int*) = l;
                            }
#if LIBDEF_PRINTF_FAR_PTR
                         }
#endif
                        tasg++;
                      }
                      s = nsp;
                      }
                      break;
#if LIBDEF_PRINTF_FLOATING
            case 'e':
            case 'f':
            case 'g':
                    {
                      //double d = _strtod(s, &nsp, fwi);
                      double d = strtod(s, &nsp);
                      if (nsp == s) {
                        goto endScan; /* conversion failure */ /*lint !e801 Use of goto is not deprecated */
                      }
                      if (ma)
                      {
#if LIBDEF_PRINTF_FAR_PTR
                         if (is_far_ptr)
                         {
#if SAME_ENCODING_DOUBLE_FLOAT
                            *va_arg(args, double *FAR) = d;
#else
                            if (sz >= 2) {
                               *va_arg(args, double *FAR) = d;
                            } else {
                               *va_arg(args, float *FAR) = d;
                            }
#endif
                         } else {
#endif
#if SAME_ENCODING_DOUBLE_FLOAT
                            *va_arg(args, double*) = d;
#else
                            if (sz >= 2) {
                               *va_arg(args, double*) = d;
                            } else {
                               *va_arg(args, float*) = d;
                            }
#endif
#if LIBDEF_PRINTF_FAR_PTR
                         }
#endif
                         tasg++;
                       } // if (ma) 
                       s = nsp;
                     }
                     break;
#endif
#if LIBDEF_PRINTF_FAR_PTR
             case 'S':
#endif
             case 's': while (isspace(*s)) { ++s; }               /* Eat spaces */
                       if (!fwi) { fwi = INT_MAX; } /* Set field width */
                       if (ma)
                       {
#if LIBDEF_PRINTF_FAR_PTR
                          if ((*format == 'S') || is_far_ptr)
                          {
                             far_ptr = va_arg(args, char *FAR);   /* Set char pointer */
                             while (!(isspace(*s)) && (fwi-- != 0) &&
                                    (*s != '\0'))                 /* Transfer array */
                             {
                                *far_ptr++ = *s++;
                             }
                             *far_ptr = '\0';                     /* Terminate array */
                          } else {
#endif
                             ss = va_arg(args, char*);   /* Set char pointer */
                             while (!(isspace(*s)) && (fwi-- != 0) &&
                                    (*s != '\0'))        /* Transfer array */
                             {
                                *ss = *s,ss++,s++;

                             }
                             *ss = '\0';                 /* Terminate array */
#if LIBDEF_PRINTF_FAR_PTR
                          }
#endif
                          while (!isspace(*s) && (*s != '\0')) {
                             s++;
                          }
                          tasg++;
                       } else {
                          while (!(isspace(*s)) && (*s != '\0')) {
                            s++;  /* Skip array */
                          }
                       }
                       break;

             case '%':
                       if (*s == '%') {
                         s++; /* tasg++; */ /* eat '%', do not assign */
                       }
                       break;

             case 'c': if (!fwi) { fwi = 1; } /* Set field width */
                       if (ma)
                       {
#if LIBDEF_PRINTF_FAR_PTR
                          if (is_far_ptr)
                          {
                             far_ptr = va_arg(args, char *FAR);   /* Set char pointer */
                             while (*s && fwi--)              /* Transfer array */
                             {
                                *far_ptr++ = *s++;
                             }
                          } else {
#endif
                             ss = va_arg(args, char*);   /* Set char pointer */
                             while (*s && fwi--)         /* Transfer array */
                             {
                                 *ss = *s,ss++,s++;
                             }
#if LIBDEF_PRINTF_FAR_PTR
                          }
#endif
                         tasg++;
                       } else {
                          while (*s && fwi--) { s++; } /* Skip array */
                       }
                       break;

#if LIBDEF_PRINTF_FAR_PTR
             case 'N':
#endif
             case 'n': if (ma)
                       {
                          nConversion= 1;
#if LIBDEF_PRINTF_FAR_PTR
                          if ((*format == 'N') || is_far_ptr)
                          {
                             switch(sz)
                             {
                                case 1:  *va_arg(args, long int *FAR) = s - sbase;
                                         break;
                                case 2:  *va_arg(args, short int *FAR) = s - sbase;
                                         break;
                                default: *va_arg(args, int *FAR) = s - sbase;
                             }
                          } else {
#endif
                             switch(sz)
                             {
                                case 1:  *va_arg(args, long int*) = s - sbase;
                                         break;
                                case 2:  *va_arg(args, short int*) = (short int)(s - sbase);
                                         break;
                                default: *va_arg(args, int*) = s - sbase;
                             }
#if LIBDEF_PRINTF_FAR_PTR
                          }
#endif
                       }

                       break;
#if LIBDEF_MULTI_CHAR_SELECTION
                 case '[':
                       if (ma)
                       {
#if LIBDEF_PRINTF_FAR_PTR
                          if (is_far_ptr) {
                             far_ptr = va_arg(args, char *FAR);   /* Set char pointer */
                          } else {
#endif
                             ss = va_arg(args, char*);            /* Set char pointer */
#if LIBDEF_PRINTF_FAR_PTR
                          }
#endif
                       }
                       if (!fwi) {
                          fwi = INT_MAX;     /* Set field width */
                       }
#if LIBDEF_PRINTF_FAR_PTR
                       if (is_far_ptr) {
                          format = _copyFarList(far_ptr, s, &nsp, format, &ok, fwi, ma);
                       } else {
#endif
                          format = _copyList(ss, s, &nsp, format, &ok, fwi, ma);
#if LIBDEF_PRINTF_FAR_PTR
                       }
#endif
                       s = nsp;
                       if (ma) {
                          tasg += ok;
                       }
#endif /* LIBDEF_MULTI_CHAR_SELECTION */

         }
         format++;
      }  /* end if */
   }  /* end while */

endScan:
   return tasg;

inputFailure:
   if (!tasg && !nConversion) { return EOF; }
   return tasg;
} /* end vsscanf */


/*****************************************************/

int sscanf(const char * s, const char * format, ...)
{
   int i;
   va_list args;

   va_start(args, format);
   i = vsscanf(s, format, args);
   va_end(args);
   return i;
} /* end sscanf */

/*****************************************************/
 
#define LIBDEF_SCANF_BUF_SIZE   256  

int scanf(const char* format, ...) { 
  unsigned char outbuf[LIBDEF_SCANF_BUF_SIZE];
  int i; unsigned long cnt = LIBDEF_SCANF_BUF_SIZE;
  va_list args;
  
  va_start(args, format);
  __read_console(0, outbuf, &cnt, 0L);
  i = vsscanf((const char *)outbuf, format, args);
  va_end(args);
  return i;
}

#if _MSL_WIDE_CHAR

wint_t __wStringRead(void * isc, wint_t ch, int Action)
{
	wchar_t RetVal;
	__wInStrCtrl * Iscp = (__wInStrCtrl*)isc;
	switch(Action)
	{
		case __GetAwChar:
			RetVal = *(Iscp->wNextChar);
			if (RetVal == L'\0')
			{
				Iscp->wNullCharDetected = 1;
				return (WEOF);						/*- mm 990624 -*/
			}
			else
			{
				Iscp->wNextChar++;
				return(RetVal);
			}
		case __UngetAwChar:
			if (!Iscp->wNullCharDetected)			/*- mm 990413 -*/
				Iscp->wNextChar--;					/*- mm 990413 -*/
			else									/*- mm 990413 -*/
				Iscp->wNullCharDetected = 0;		/*- mm 990413 -*/
			return(ch);
		case __TestForwcsError:
			return(Iscp->wNullCharDetected);
	}
	return 0;  /* to satisfy compiler */
}

#endif /* _MSL_WIDE_CHAR */


#if _MSL_C99

int _MSL_CDECL __StringRead(void * isc, int ch, int Action)
{
	char RetVal;
	__InStrCtrl * Iscp = (__InStrCtrl*)isc;
	switch(Action)
	{
		case __GetAChar:
			RetVal = *(Iscp->NextChar);
			if (RetVal == '\0')
			{
				Iscp->NullCharDetected = 1;
				return (EOF);
			}
			else
			{
				Iscp->NextChar++;
				return((unsigned char)RetVal);	/*- mm 010426 -*/
			}
			
		case __UngetAChar:
			if (!Iscp->NullCharDetected)		/*- mm 990413 -*/
				Iscp->NextChar--;				/*- mm 990413 -*/
			else								/*- mm 990413 -*/
				Iscp->NullCharDetected = 0;		/*- mm 990413 -*/
			return(ch);
			
		case __TestForError:
			return(Iscp->NullCharDetected);
	}
	return 0;  /* to satisfy compiler */
}

#endif /* _MSL_C99 */

#if _MSL_WIDE_CHAR


#define bad_conversion			0xFF

typedef unsigned char char_map[32];

#define set_char_map(map, ch)	 map[ch>>3] |= (1 << (ch&7))
#define tst_char_map(map, ch) 	(map[ch>>3] &  (1 << (ch&7)))

typedef struct
{
	unsigned char	suppress_assignment;
	unsigned char 	field_width_specified;
	unsigned char 	argument_options;
	wchar_t			conversion_char;
	int				field_width;
	char_map		char_set;
} scan_format;


enum argument_options
{
	normal_argument,
	char_argument,									/*- blc 980317 -*/
	short_argument,
	long_argument,
	
//#if _MSL_C99_PRINTF_SCANF	
#if _MSL_C99
	intmax_argument,
	size_t_argument,
	ptrdiff_argument,
#if _MSL_LONGLONG
	long_long_argument,
#endif /*_MSL_LONGLONG */
#endif /* _MSL_C99 */
//#endif /* _MSL_C99_PRINTF_SCANF */
	
	double_argument,
	long_double_argument,
	wchar_argument									/*- mm 990407 -*/
};


static const wchar_t * parse_format(const wchar_t * format_string, scan_format * format)
{
	const wchar_t *	s = format_string;
	wchar_t			c;
	int				flag_found, invert;
	/*scan_format		f = {0, 0, normal_argument, 0, INT_MAX, {0}};*/					/*- mm 000419 -*/
	/* The following performs the above initialization without a large static area */	/*- mm 000419 -*/
	scan_format		f;																	/*- mm 000419 -*/
	f.suppress_assignment	 = 0;														/*- mm 000419 -*/
	f.field_width_specified	 = 0;														/*- mm 000419 -*/
	f.argument_options		 = normal_argument;											/*- mm 000419 -*/
	f.conversion_char 		 = 0;														/*- mm 000419 -*/
	f.field_width 			 = INT_MAX;													/*- mm 000419 -*/
	memset(&f.char_set, 0, sizeof(char_map));											/*- mm 000419 -*/

	if ((c = *++s) == L'%')
	{
		f.conversion_char = c;
		*format = f;
		return((const wchar_t *) s + 1);
	}
	
	if (c == L'*')
	{
		f.suppress_assignment = 1;
		
		c = *++s;
	}
	
	if (iswdigit(c))
	{
		f.field_width = 0;
		
		do
		{
			f.field_width = (f.field_width * 10) + (c - L'0');
			c = *++s;
		}
		while (iswdigit(c));
		
		if (f.field_width == 0)
		{
			f.conversion_char = bad_conversion;
			*format = f;
			return((const wchar_t *) s + 1);
		}
		
		f.field_width_specified = 1;
	}
	
	flag_found = 1;
	
	switch (c)
	{
		case L'h':
			
			f.argument_options = short_argument;
			if (s [1] == L'h')							/*- mm 990616 -*/
			{											/*- mm 990616 -*/
				f.argument_options = char_argument;		/*- mm 990616 -*/
				c = *++s; /* move past second h */		/*- mm 990616 -*/
			}											/*- mm 990616 -*/
			
			break;
		
		case L'l':
			
			f.argument_options = long_argument;

#if _MSL_C99_PRINTF_SCANF
#if _MSL_LONGLONG
			if (s [1] == L'l')								/*- mm 990616 -*/
			{												/*- mm 990616 -*/
				f.argument_options = long_long_argument;	/*- mm 990616 -*/
				c = *++s; /* move past second l */			/*- mm 990616 -*/
			}												/*- mm 990616 -*/
#endif /* _MSL_LONGLONG */			
#endif /* _MSL_C99_PRINTF_SCANF */

			break;
		
		case L'L':
			
			f.argument_options = long_double_argument;         /*-mm 961219 -*/	/*- mm 990616 -*/
			
			break;
		
		case L'j':
		
			f.argument_options = intmax_argument;
			break;
			
		case L'z':
		
			f.argument_options = size_t_argument;
			break;
			
		case L't':
		
			f.argument_options = ptrdiff_argument;
			break;
		
		default:
			
			flag_found = 0;
	}
	
	if (flag_found)
		c = *++s;
	
	f.conversion_char = c;
	
	switch (c)
	{
		case L'd':
		case L'i':
		case L'u':
		case L'o':
		case L'x':
		case L'X':
			
			if (f.argument_options == long_double_argument)
			{
				f.conversion_char = bad_conversion;
				break;
			}

			break;
		
#if _MSL_C99_PRINTF_SCANF
		case L'a':
		case L'A':
		case L'F':		
 #endif /* _MSL_C99_PRINTF_SCANF */
 
		case L'f':
		case L'e':
		case L'E':
		case L'g':
		case L'G':
			
	if (f.argument_options == char_argument 
				|| f.argument_options == short_argument 
				
#if _MSL_C99_PRINTF_SCANF
				|| f.argument_options == intmax_argument	/*- mm 020529 -*/
				|| f.argument_options == size_t_argument 
				|| f.argument_options == ptrdiff_argument 	/*- mm 020529 -*/
#if _MSL_LONGLONG
				|| f.argument_options == long_long_argument
#endif /* _MSL_LONGLONG */
#endif
			)
			{
				f.conversion_char = bad_conversion;
				break;
			}
			
			/* 'l' before float identifier means double */

			if (f.argument_options == long_argument)
				f.argument_options = double_argument;
			
			break;
		
		case L'p':
			
			f.argument_options = long_argument;
			f.conversion_char  = L'x';
			
			break;
			
		case L'c':
			
			if (f.argument_options == long_argument)			/*- mm 990407 -*/
				f.argument_options = wchar_argument;			/*- mm 990407 -*/
			else												/*- mm 990407 -*/
				if (f.argument_options != normal_argument)
					f.conversion_char = bad_conversion;
			
			break;
			
		case L's':
			
			if (f.argument_options == long_argument)			/*- mm 990407 -*/
				f.argument_options = wchar_argument;			/*- mm 990407 -*/
			else												/*- mm 990407 -*/
				if (f.argument_options != normal_argument)
					f.conversion_char = bad_conversion;
			
			{
				int		i;
				unsigned char *	p;
				
				for (i = sizeof(f.char_set), p = f.char_set; i; --i)
					*p++ = 0xFF;
				
				f.char_set[1] = 0xC1;	/* sets bits for HT, LF, VT, FF, and CR chars to zero */
				f.char_set[4] = 0xFE;	/* set bit for Sp char to zero */
			}
			
			break;
			
		case L'n':
			
			break;
		
		case L'[':
			if (f.argument_options == long_argument)			/*- mm 990624 -*/
				f.argument_options = wchar_argument;			/*- mm 990624 -*/
			else												/*- mm 990624 -*/
				if (f.argument_options != normal_argument)
					f.conversion_char = bad_conversion;
			
			c = *++s;
			
			invert = 0;
			
			if (c == L'^')
			{
				invert = 1;
				c = *++s;
			}
			
			if (c == L']')
			{
				set_char_map(f.char_set, L']');
				c = *++s;
			}
			
			while (c && c != L']')
			{
				int d;
				
				set_char_map(f.char_set, c);
				
				if (*(s+1) == L'-' && (d = *(s+2)) != 0 && d != L']')
				{
					while (++c <= d)
						set_char_map(f.char_set, c);
					
					c = *(s += 3);
				}
				else
					c = *++s;
			}
			
			if (!c)
			{
				f.conversion_char = bad_conversion;
				break;
			}
			
			if (invert)
			{
				int							i;
				unsigned char *	p;															/*- mm 990408 -*/
				
				for (i = sizeof(f.char_set), p = (unsigned char*)f.char_set; i; --i, ++p)	/*- mm 990408 -*/
					*p = ~*p;
			}
			
			break;
		
		default:
			
			f.conversion_char = bad_conversion;
			
			break;
	}
	
	*format = f;
	
	return((const wchar_t *) s + 1);
}

static int __wsformatter(wint_t (*wReadProc)(void *, wint_t, int), void * wReadProcArg, 
									const wchar_t * format_str, va_list arg, int is_secure)  /*- mm 990325 -*/
{
	int					num_chars, chars_read, items_assigned, conversions, i;
	int					base, negative, overflow;
	const wchar_t *		format_ptr;
	wchar_t				format_char;           /*- mm 961002 -*/
	wchar_t             c;	                 /*- mm 961002 -*/
	scan_format			format;
	long				long_num;
	unsigned long		u_long_num;
	
#if _MSL_C99_PRINTF_SCANF
#if _MSL_LONGLONG                /*- mm 961219 -*/
	long long   		long_long_num = 0;         /*- mm 961219 -*/
	unsigned long long 	u_long_long_num;       /*- mm 961219 -*/
#endif /* _MSL_LONGLONG */                     /*- mm 961219 -*/
#if _MSL_FLOATING_POINT && _MSL_FLOATING_POINT_IO
	long double			long_double_num;
#endif /* _MSL_FLOATING_POINT */
#endif

	wchar_t *			arg_ptr;
	int					elem_valid;
	size_t				elem_maxsize;
	int match_failure = 0;
	int terminate  = 0;			/*- mm 990608 -*/
	
	format_ptr     = format_str;
	chars_read     = 0;
	items_assigned = 0;
	conversions    = 0;
	
	while (!terminate && (format_char = *format_ptr) != 0) /*- mm 990311 -*/	/*- mm 990608 -*/
	{
		if (iswspace(format_char))
		{
			do
				format_char = *++format_ptr;
			while (iswspace(format_char));
			
			if (!match_failure)
			{
				while ((iswspace)(c = (*wReadProc)(wReadProcArg, 0, __GetAwChar)))	/*- mm 990325 -*/  /*- mm 990409 -*/
					++chars_read;
				
				(*wReadProc)(wReadProcArg, c, __UngetAwChar);						/*- mm 990325 -*/
			}
			continue;
		}
		
		if ((format_char != L'%') && (!match_failure))
		{
			if ((c =(*wReadProc)(wReadProcArg, 0, __GetAwChar)) != format_char) /*- mm 990325 -*/
			{
				(*wReadProc)(wReadProcArg, c, __UngetAwChar);					/*- mm 990325 -*/
				if (!is_secure)
					goto exit;
				else
				{
					match_failure = 1;
					++format_ptr;
					continue;
				}
			}
			
			++chars_read;
			++format_ptr;
			
			continue;
		}
		
		format_ptr = parse_format(format_ptr, &format);
		
		if (!format.suppress_assignment && format.conversion_char != L'%')
			arg_ptr = va_arg(arg, wchar_t *);						/*- JWW 011027 -*/
		else
			arg_ptr = 0;
		
		if ((format.conversion_char != L'n') && (!match_failure) && (*wReadProc)(wReadProcArg, 0, __TestForwcsError))	/*- mm 990608 -*/
		{																					/*- mm 990608 -*/
			if (!is_secure)
				goto exit;																	/*- mm 990608 -*/
			else
				match_failure = 1;
		}																					/*- mm 990608 -*/
		
		switch (format.conversion_char)
		{
			case L'd':
				
				base = 10;
				
				goto signed_int;
				
			case L'i':
				
				base = 0;
				
			signed_int:
				
				if (match_failure)
				{
					long_num = 0;
#if _MSL_C99_PRINTF_SCANF
#if _MSL_LONGLONG
					long_long_num = 0;
#endif /* _MSL_LONGLONG */
#endif
				}
				else
				{
#if _MSL_C99_PRINTF_SCANF
#if _MSL_LONGLONG
	                if ((format.argument_options == long_long_argument) || /*- mm 961219 -*/
	                		(format.argument_options == intmax_argument))
	                   u_long_long_num =                               /*- mm 961219 -*/
	                      __wcstoull(base, format.field_width, wReadProc, 
	                      		wReadProcArg, &num_chars, &negative, &overflow);	/*- mm 990325 -*/
	                else                                               /*- mm 961219 -*/
#endif /* _MSL_LONGLONG */
#endif
					u_long_num
						= __wcstoul(base, format.field_width, wReadProc, 
									wReadProcArg, &num_chars, &negative, &overflow);/*- mm 990325 -*/
					
					if (!num_chars)
					{
						if (!is_secure)
							goto exit;
						else
						{
							match_failure = 1;
							long_num = 0;
							
#if _MSL_C99_PRINTF_SCANF
#if _MSL_LONGLONG
							long_long_num = 0;
#endif /* _MSL_LONGLONG */
#endif
							goto signed_int_assign;
						}
					}
					
					chars_read += num_chars;
					
#if _MSL_C99_PRINTF_SCANF
#if _MSL_LONGLONG                                    /*- mm 961219 -*/
	                if ((format.argument_options == long_long_argument) || /*- mm 961219 -*/
	                		(format.argument_options == intmax_argument))
	                   long_long_num = (negative ? -u_long_long_num : u_long_long_num); /*- mm 961219 -*/
	                else                                               /*- mm 961219 -*/
#endif /* _MSL_LONGLONG */                                         /*- mm 961219 -*/
#endif
					long_num = (negative ? -u_long_num : u_long_num);
				}
				
			signed_int_assign:
				if (arg_ptr)
				{
					switch (format.argument_options)
					{
						case normal_argument:  * (int *)         arg_ptr = long_num; break;
						case char_argument:    * (signed char *) arg_ptr = long_num; break;
						case short_argument:   * (short *)       arg_ptr = long_num; break;
						case long_argument:    * (long *)        arg_ptr = long_num; break;
#if _MSL_LONGLONG
#if _MSL_C99_PRINTF_SCANF

						case intmax_argument:  * (intmax_t *)    arg_ptr = long_long_num; break;	/*- mm 020529 -*/ /*- mm 040811 -*/
#endif /* _MSL_C99_PRINTF_SCANF */

#else
						case intmax_argument:  * (intmax_t *)    arg_ptr = long_num; break;	/*- mm 020529 -*/
#endif /* _MSL_LONGLONG */
						case size_t_argument:  * (size_t *) 	 arg_ptr = long_num; break;	/*- mm 020529 -*/
						case ptrdiff_argument: * (ptrdiff_t *) 	 arg_ptr = long_num; break;	/*- mm 020529 -*/
#if _MSL_C99_PRINTF_SCANF
#if _MSL_LONGLONG                                    /*- mm 961219 -*/
                        case long_long_argument: * (long long *) arg_ptr = long_long_num; break;
#endif /* _MSL_LONGLONG */                                             /*- mm 961219 -*/
#endif
					}
					if (!match_failure)
						++items_assigned;
				}
				
				++conversions;
				
				break;
				
			case L'o':
				
				base = 8;
				
				goto unsigned_int;
				
			case L'u':
				
				base = 10;
				
				goto unsigned_int;
				
			case L'x':
			case L'X':
				
				base = 16;
				
			unsigned_int:
				
				if (match_failure)
				{
					u_long_num = 0;
#if _MSL_C99_PRINTF_SCANF
#if _MSL_LONGLONG
					u_long_long_num = 0;
#endif /* _MSL_LONGLONG */
#endif
				}
				else
				{
#if _MSL_C99_PRINTF_SCANF
#if _MSL_LONGLONG			                                    /*- mm 961219 -*/	/*- mm 030317 -*/
	                if ((format.argument_options == long_long_argument) || /*- mm 961219 -*/
	                		(format.argument_options == intmax_argument))
	                   u_long_long_num =                               /*- mm 961219 -*/
	                      __wcstoull(base, format.field_width, wReadProc, 
	                      			wReadProcArg, &num_chars, &negative, &overflow);	/*- mm 990325 -*/
	                else                                               /*- mm 961219 -*/
#endif /* _MSL_LONGLONG */			                            /*- mm 961219 -*/	/*- mm 030317 -*/
#endif
					u_long_num
						= __wcstoul(base, format.field_width, wReadProc, 
									wReadProcArg, &num_chars, &negative, &overflow);	/*- mm 990325 -*/
					
					if (!num_chars)
					{
						if (!is_secure)
							goto exit;
						else
						{
							match_failure = 1;
							u_long_num = 0;
#if _MSL_C99_PRINTF_SCANF
#if _MSL_LONGLONG
							u_long_long_num = 0;
#endif /* _MSL_LONGLONG */
#endif
							goto unsigned_int_assign;
						}
					}
					
					chars_read += num_chars;
					
					if (negative)
#if _MSL_C99_PRINTF_SCANF
#if _MSL_LONGLONG                                    /*- mm 961219 -*/
	                if (format.argument_options == long_long_argument) /*- mm 961219 -*/
						u_long_long_num = -u_long_long_num;            /*- mm 961219 -*/
	                else                                               /*- mm 961219 -*/
#endif /* _MSL_LONGLONG */                                         /*- mm 961219 -*/
#endif /*_MSL_C99_PRINTF_SCANF */

						u_long_num = -u_long_num;
				}
				
			unsigned_int_assign:
				if (arg_ptr)
				{
					switch (format.argument_options)
					{
						case normal_argument:  * (unsigned int *)   	arg_ptr = u_long_num; break;
						case char_argument:    * (unsigned char *)  	arg_ptr = u_long_num; break;
						case short_argument:   * (unsigned short *) 	arg_ptr = u_long_num; break;
						case long_argument:    * (unsigned long *)  	arg_ptr = u_long_num; break;
#if _MSL_LONGLONG
#if _MSL_C99_PRINTF_SCANF
						case intmax_argument:  * (intmax_t *)    	arg_ptr = u_long_long_num; break;	/*- mm 020529 -*/ /*- mm 040811 -*/
#endif
#else
						case intmax_argument:  * (intmax_t *)    	arg_ptr = u_long_num; break;	/*- mm 020529 -*/
#endif /* _MSL_LONGLONG */
						case size_t_argument:  * (size_t *) 	 	arg_ptr = u_long_num; break;	/*- mm 020529 -*/
						case ptrdiff_argument: * (ptrdiff_t *) 	 	arg_ptr = u_long_num; break;	/*- mm 020529 -*/
#if _MSL_C99_PRINTF_SCANF
#if _MSL_LONGLONG                                    /*- mm 961219 -*/
                        case long_long_argument: * (unsigned long long *) arg_ptr = u_long_long_num; break;
#endif /* _MSL_LONGLONG */             					                                            /*- mm 961219 -*/
#endif 
					}
					
					if (!match_failure)
						++items_assigned;
				}
				
				++conversions;
				
				break;
#if _MSL_C99_PRINTF_SCANF
#if _MSL_FLOATING_POINT
#if _MSL_FLOATING_POINT_IO
			case L'a':						/*- mm 990616 -*/
			case L'A':
			case L'f':
			case L'F':
			case L'e':
			case L'E':
			case L'g':
			case L'G':
				if (match_failure)
					long_double_num = NAN;
				else
				{
					long_double_num = __wcstold(format.field_width, wReadProc, 
											wReadProcArg, &num_chars, &overflow);	/*- mm 990325 -*/
					
					if (!num_chars)
					{
						if (!is_secure)
							goto exit;
						else
						{
							match_failure = 1;
							long_double_num = NAN;
							goto assign_float;
						}
					}
					
					chars_read += num_chars;
				}
				
			assign_float:
				if (arg_ptr)
				{
					switch (format.argument_options)
					{
						case normal_argument:      * (float *)       arg_ptr = long_double_num; break;
						case double_argument:      * (double *)      arg_ptr = long_double_num; break;
						case long_double_argument: * (long double *) arg_ptr = long_double_num; break;
					}
					
					if (!match_failure)
						++items_assigned;
				}
				
				++conversions;

				break;

#endif /* _MSL_FLOATING_POINT */
#endif /* _MSL_FLOATING_POINT_IO */
#endif /* _MSL_C99_PRINTF_SCANF */

			case L'c':
				
				if (!format.field_width_specified)
					format.field_width = 1;
				
				if (arg_ptr)
				{
					if (is_secure)
					{
						elem_valid = 1;
						elem_maxsize = va_arg(arg, size_t);
					}
					
					num_chars = 0;
					
					if (match_failure)
					{
						if (elem_maxsize > 0)
							*arg_ptr = 0;
						continue;
					}
					else
					{
						wchar_t * arg_start = arg_ptr;
						
						while (format.field_width-- &&
							(!is_secure || ((elem_valid = (elem_maxsize > num_chars)) != 0)) &&
							(c = (*wReadProc)(wReadProcArg, 0, __GetAwChar)) != WEOF)    /*- mm 980202 -*/ /*- mm 990325 -*/ /*- mm 990624 -*/
						{
							if (format.argument_options == wchar_argument)		/*- mm 990407 -*/
								*arg_ptr++ = c;									/*- mm 990407 -*/
							else												/*- mm 990407 -*/
							{
								i = wctomb((char *)arg_ptr, c);					/*- mm 990407 -*/
								if (i < 0)										/*- mm 990407 -*/
									goto exit;									/*- mm 990407 -*/
								arg_ptr = (wchar_t*)((char *)arg_ptr + i);							/*- mm 990407 -*/
							}
							++num_chars;
						}
						
						if (!num_chars || (is_secure && !elem_valid))
						{
							if (!is_secure)
								goto exit;
							else
							{
								match_failure = 1;
								if (elem_maxsize > 0)
									*arg_start = 0;
								continue;
							}
						}
						
						chars_read += num_chars;
						
						++items_assigned;
					}
				}
				else
				{
					num_chars = 0;
					
					while (format.field_width-- && 
						(c = (*wReadProc)(wReadProcArg, 0, __GetAwChar)) != WEOF)   /*- mm 980202 -*/ /*- mm 990325 -*/ /*- mm 990624 -*/
						++num_chars;
					
					if (!num_chars)
						goto exit;
				}
				
				++conversions;
				
				break;
			
			case L'%':
				if (match_failure)
					continue;
				else
				{
					while ((iswspace)(c = (*wReadProc)(wReadProcArg, 0, __GetAwChar)))		/*- mm 990409 -*/
						++chars_read;

					if (c != L'%')
					{
						(*wReadProc)(wReadProcArg, c, __UngetAwChar);	
						if (!is_secure)
							goto exit;					
						else
						{
							match_failure = 1;
							continue;
						}
					}
					
					++chars_read;
				}
				break;
			
			case L's':
				if (!match_failure)
				{
					c = (*wReadProc)(wReadProcArg, 0, __GetAwChar);           /*- mm 970218 -*/	/*- mm 990325 -*/ /*- mm 990413 -*/
					while(iswspace(c))                                        /*- mm 970218 -*/
					{                                                         /*- mm 970218 -*/
						++chars_read;                                         /*- mm 970218 -*/
						c = (*wReadProc)(wReadProcArg, 0, __GetAwChar); /*- mm 970218 -*/ /*- mm 980130 -*/ /*- mm 990325 -*/
					}                                                        /*- mm 970218 -*/
					
					(*wReadProc)(wReadProcArg, c, __UngetAwChar);			/*- mm 990325 -*/
				}
			case L'[':
				
				if (arg_ptr)
				{
					if (is_secure)
					{
						elem_valid = 1;
						elem_maxsize = va_arg(arg, size_t) - 1;
					}
					
					num_chars = 0;
					
					if (match_failure)
					{
						if (elem_maxsize > 0)
							*arg_ptr = 0;
						continue;
					}
					else
					{
						wchar_t * arg_start = arg_ptr;
						
						while (format.field_width-- && 
							(!is_secure || ((elem_valid = (elem_maxsize >= num_chars)) != 0)) &&
								(c = (*wReadProc)(wReadProcArg, 0, __GetAwChar)) != WEOF && 
									tst_char_map(format.char_set, c)) /*- mm 980202 -*/	/*- mm 990325 -*/ 	/*- mm 990624 -*/
						{
							if (!tst_char_map(format.char_set, c))				/*- mm 011207 -*/
								break;	
												
							if (format.argument_options == wchar_argument)									/*- mm 990407 -*/
							{
								*(wchar_t*)arg_ptr = c;									/*- mm 990407 -*/	/*- mm 990616 -*/
								arg_ptr = (wchar_t*)((char *)arg_ptr + sizeof(wchar_t));/*- mm 990407 -*/ 	/*- mm 990624 -*/
							}																				/*- mm 990420 -*/
							else
							{
								i = wctomb((char *)arg_ptr, c);							/*- mm 990407 -*/
								if (i < 0)												/*- mm 990407 -*/
								{
									if (!is_secure)
										goto exit;											/*- mm 990407 -*/
									else
									{
										match_failure = 1;
										if (elem_maxsize > 0)
											*arg_start = 0;
										continue;
									}
								}
								arg_ptr = (wchar_t*)((char *)arg_ptr + i);				/*- mm 990407 -*/
							}
								
							++num_chars;
						}
						
						if (!num_chars || (is_secure && !elem_valid))
						{
							(*wReadProc)(wReadProcArg, c, __UngetAwChar);  /*- mm 961114 -*/	/*- mm 990325 -*/
							if (!is_secure)
								goto exit;
							else
							{
								match_failure = 1;
								if (elem_maxsize > 0)
									*arg_start = 0;
								continue;
							}
						}
						
						chars_read += num_chars;
						
						if (format.argument_options == wchar_argument)
							*arg_ptr = 0;
						else
							*(char *)arg_ptr = 0;
						
						++items_assigned;
					}
				}
				else
				{
					num_chars = 0;
					
					while (format.field_width-- && 
							(c = (*wReadProc)(wReadProcArg, 0, __GetAwChar)) != WEOF && 
									tst_char_map(format.char_set, c)) /*- mm 980202 -*/	/*- mm 990325 -*/ /*- mm 990624 -*/
						++num_chars;
					
					if (!num_chars)
					{
						(*wReadProc)(wReadProcArg, c, __UngetAwChar);  /*- mm 970513 -*/ /*- mm 990325 -*/
						/*goto exit;*/
						break;
					}
					chars_read += num_chars;          /*- mm 970501 -*/
				}
				
				if (format.field_width >= 0)
					(*wReadProc)(wReadProcArg, c, __UngetAwChar);	/*- mm 990325 -*/
				
				++conversions;
				
				break;
			
			case L'n':
				
				if (arg_ptr)
					switch (format.argument_options)
					{
						case normal_argument: * (int *)   arg_ptr = chars_read; break;
						case short_argument:  * (short *) arg_ptr = chars_read; break;
						case long_argument:   * (long *)  arg_ptr = chars_read; break;
						case char_argument:   * (char *)  arg_ptr = chars_read; break;			/*- mm 990616 -*/
#if _MSL_C99_PRINTF_SCANF
#if _MSL_LONGLONG                                    /*- mm 961219 -*/
                        case long_long_argument: * (long long *) arg_ptr = chars_read; break;
#endif                                                             /*- mm 961219 -*/
#endif
					}
				
				continue;
				
			case bad_conversion:
			default:
				
				goto exit;
		}
		
	}
	
exit:
	
	if ((*wReadProc)(wReadProcArg, 0, __TestForwcsError) && conversions == 0)	/*- mm 990325 -*/
		return(EOF);                                            /*- mm 980202 -*/
	
	return(items_assigned);
}

int _MSL_CDECL vswscanf(const wchar_t * _MSL_RESTRICT s, const wchar_t * _MSL_RESTRICT format, va_list arg)  /*- mm 990828 -*/
{
	__wInStrCtrl wisc;
	wisc.wNextChar         = (wchar_t *)s;
	if ((s == NULL) || (*wisc.wNextChar == L'\0'))	/*- mm 990617 -*/
		return(EOF);							/*- mm 990617 -*/
	wisc.wNullCharDetected = 0;
	
	return(__wsformatter(&__wStringRead, (void *)&wisc, format, arg, 0));
}

int _MSL_CDECL swscanf(const wchar_t * _MSL_RESTRICT s, const wchar_t * _MSL_RESTRICT format, ...)
{
#if (defined(__PPC_EABI__) || defined(__MIPS__))
	va_list args;
	va_start( args, format );
	return(vswscanf(s, format, args));						/*- mm 990828 -*/
#else
	return(vswscanf(s, format, __va_start(format)));		/*- mm 990828 -*/
#endif
}

#endif /*  _MSL_WIDE_CHAR */



#endif /* _MSL_C_TINY_IO      */


/* Change record:
 * JFH 950926 First code release.
 * JFH 950929 Fixed misinterpretation of Standard concerning what to do when EOF
 *			  is reached. Now format string continues to be processed until input
 *			  is absolutely necessary (i.e., '%n' still processed even if preceding
 *			  directive hit EOF).
 * JFH 960212 Fixed longstanding (yet undiscovered) bug in parse_format's handling
 *			  of field widths. field_width was initialized to INT_MAX as a default.
 *			  If a digit was seen, field_width was *not* being zeroed before
 *			  accumulating digits in the usual manner.
 * JFH 960130 Changed vfscanf and vsscanf to __vfscanf and __vsscanf, made them
 *			  non-static, and added their prototypes to <stdio.h>.
 * JFH 960219 added #ifndef around area that handles floating point input. If disabled, you
 *			  can get away with not including MathLib just because you wanted to use scanf.
 *			  There is also some ANSI lib code savings as well.
 * JFH 960304 Fixed bug in handling of strings (%s) and scansets (%[]) where the last char
 *			  fetched was being ungotten *even if* the conversion ended because the
 *			  field width was exhausted (thus causing the last char of the previous field
 *			  to be rescanned).
 * JFH 960421 Fix bug in scanset inversion (*p++ = ~*p is ill-formed because order of
 *			  evaluation is not guaranteed).
 * JFH 960829 added l. you's changes for powertv, no floating point
 * mm  960930 Removed bitfields from scan_format structure to compile with ANSI strict
 * mm  961002 Corrected problem recognizing eof
 * mm  961114 make sure non matching character is left unread
 * mm  961220 Additions for support of long long
 * mm  970218 To make sscanf work with null source string.
 * mm  970501 To count input characters even when assignment suppressed
 * mm  970513 Make sure non matching character is left unread even when assignment suppressed
 * SCM 970709 Converted __va_start() calls to va_start() for PPC_EABI.
 * FS  980113 Converted __va_start() calls to va_start() for MIPS_Bare.
 * mm  971202 To complete mm 970218 
 * mm  980204 Added wide character support
 * blc 980317 Added ll (long long)
 *			  Fixed L (long double) prefix
 *            added a support for decimal input (symmetric to printf)
 *            added hh (char) prefix
 * blc 980318 Changed hh to be (signed char) unless explicitly unsigned
 * mm  980331 Modification to allow characters >= 128, e.g. § or É to be matched from format
 *            string correctly. MW06720
 * mm  981104 Inserted missing setting of *format IL9810-2059
 * vss 990203 Added AltiVec changes (contributed)
 * mm  990325 Changes to split string scanf functions from file i/o
 * mm  990407 Added code to handle %lc
 * mm  990413 Corrected handling of case where source text quits early IL9904-0736
 * mm  990414 Make %hhn work
 * mm  990413 Corrected handling of case where source text quits early IL9904-0736
 * mm  990527 Corrected of string read function in case of unget and made %n work after end of file
 * mm  990617 Correction for case where pointer to source string for sscanf == NULL or source string is null
 * mm  990716 Correction to code for checking format.char_set
 * mm  990817 Deleted include of <string_io.h>
 * mm  990828 Restored vfscanf and vsscanf since they are defined in C9x
 * vss 990909 Fixed Altivec bug with va_args not being assigned on time
 * mm  000404 Corrected detection of null input file
 * mm  000831 Added vscanf since it is defined in C99 WB1-16280
 * mm  001013 Added threadsafety
 * mm  010426 Correction to detect difference between character 0xff and eof.
 * mm  010818 Correction to make sure that if no characters are ignored, scanf doesn't abort.  WB1-26254 
 * cc  011203 Added _MSL_CDECL for new name mangling
 * mm  011207 Changes to detect characters of value 0xff as distinct from EOF 
 * mm  020103 Corrected mm 011207 changes
 * cc  020109 More _MSL_CDECL 
 * mm  020529 Support for C99 length modifiers j, z, and t.
 * mm  020627 Changes to prevent io on stdin, stdout, stderr and general files from interfering with each other
 * JWW 020917 Added _MSL_RESTRICT to get the restrict type specifier for certain C99 functions
 * mm  021217 Changes to bring scanf up to C99
 * JWW 030224 Changed __MSL_LONGLONG_SUPPORT__ flag into the new more configurable _MSL_LONGLONG
 * JWW 030224 Changed __NO_WIDE_CHAR flag into the new more configurable _MSL_WIDE_CHAR
 * mm  030304 Added some _MSL_C99 wrappers
 * mm  030314 Added some more _MSL_C99 wrappers
 * mm  030317 And some more
 * JWW 031030 Added the __STDC_WANT_LIB_EXT1__ secure library extensions
 * cc  040217 Changed _No_Floating_Point to _MSL_FLOATING_POINT 
 * cc  040217 Changed _No_Disk_File_OS_Support to _MSL_OS_DISK_FILE_SUPPORT
 * JWW 040317 Updated the __STDC_WANT_LIB_EXT1__ secure library based on new secure specifications
 * mm  040429 Changes to avoid nesting of critical regions
 * mm  040811 Changes to handle arguments of type intmax_t
 * cc  041014 Added _Old_DSP_IO_Interface checks
 * mm  041029 Changed to handle an empty string under %s and return EOF, not zero.
 * cc  050504 Changed back to old way of handling empty string
 */