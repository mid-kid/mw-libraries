/* MSL
 * Copyright © 1995-2007 Freescale Corporation.  All rights reserved.
 *
 * $Date: 2007/02/19 21:56:10 $
 * $Revision: 1.54 $
 */

/*
 *	Routines
 *	--------
 *		mblen
 *		mbtowc
 *		wctomb
 *		wctomb_s
 *		wcrtomb
 *		wcrtomb_s
 *		mbsrtowcs
 *		mbsrtowcs_s
 *		wcsrtombs
 *		wcsrtombs_s
 *		mbstowcs
 *		mbstowcs_s
 *		wcstombs
 *		wcstombs_s
 *		mbsinit
 */

#pragma ANSI_strict off

#define __STDC_WANT_LIB_EXT1__ 1
#include <ansi_parms.h>

#if _MSL_WIDE_CHAR

#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include <locale_api.h>
#include <mbstring.h>
#include <msl_thread_local_data.h>

int _MSL_CDECL mblen(const char * s, size_t n)
{
	if (s && *s)
		return(mbtowc(0, s, n));
	else
		return(0);
}

static int is_utf8_complete(const char * s, size_t n)
{
	int i, encoded;
	
	if (n <= 0)			/* 0 or fewer characters do not form a valid multibyte character */
		return(-1);
	
	if (*s == 0x00)
		return(0);
	
	if ((*s & 0x80) == 0x00)
		return (1);
	else if ((*s & 0xe0) == 0xc0)
		encoded = 1;
	else if ((*s & 0xf0) == 0xe0)
		encoded = 2;
	else if ((*s & 0xf8) == 0xf0)
		encoded = 3;
	else if ((*s & 0xfc) == 0xf8)
		encoded = 4;
	else if ((*s & 0xfe) == 0xfc)
		encoded = 5;
	else
		return (-1);
	
	for (i = 0; i < encoded; i++)
	{
		if ((*(s+i+1) & 0xc0) != 0x80)
			return (-1);
	}
	if (n < i + 1)							/*- mm 021112 -*/
		return (-2);						/*- mm 021112 -*/
	return (encoded+1);
}

int __utf8_to_unicode(wchar_t * pwc, const char * s, size_t n)		/*- mm 011130 -*/
{

	int i, number_of_bytes;
	int check_byte_count;			/*- mm 010607 -*/ 
	char * source;
#if (_MSL_C99)						/*- mm 030304 -*/
	int32_t result_chr = 0;
#else								/*- mm 030304 -*/
	long int result_chr = 0;		/*- mm 030304 -*/
#endif								/*- mm 030304 -*/
	
	if (!s)           /* We are assuming UTF-8 encoding so return 0 */
		return(0);
	
	if (n <= 0)			/* 0 or fewer characters do not form a valid multibyte character */
		return(-1);
		
	number_of_bytes = is_utf8_complete(s, n);
	if (number_of_bytes < 0)
		return (-1);

	/* if we get this far, we have a valid UTF-8 encoding */		
	source = (char *)s;
	switch (number_of_bytes) /* the cases are meant to drop through! */
	{
		case 6:
			result_chr = (*source & 0x03);
			break;
		case 5:
			result_chr = (*source & 0x07);
			break;
		case 4:
			result_chr = (*source & 0x0f);
			break;
		case 3:
			result_chr = (*source & 0x1f);
			break;
		case 2:
			result_chr = (*source & 0x3f);
			break;
		case 1:
			result_chr = *source;
	}
	
	for (i = number_of_bytes - 1; i > 0; i--)
	{
		source++;
		result_chr <<= 6;
		result_chr |= (*source & 0x7f);
	}
	
	if (result_chr == 0x00000000)					/*- mm 010607 -*/ 
		check_byte_count = 0;						/*- mm 010607 -*/ 
	else if (result_chr < 0x00000080)				/*- mm 010607 -*/ 
		check_byte_count = 1;						/*- mm 010607 -*/ 
	else if (result_chr < 0x00000800)				/*- mm 010607 -*/ 
		check_byte_count = 2;						/*- mm 010607 -*/ 
	else if (result_chr < 0x00010000)				/*- mm 010607 -*/ 
		check_byte_count = 3;						/*- mm 010607 -*/ 
	else if (result_chr < 0x00200000)				/*- mm 010607 -*/ 
		check_byte_count = 4;						/*- mm 010607 -*/ 
	else if (result_chr < 0x04000000)				/*- mm 010607 -*/ 
		check_byte_count = 5;						/*- mm 010607 -*/ 
	else check_byte_count = 6;						/*- mm 010607 -*/ 
	
	if (check_byte_count != number_of_bytes)		/*- mm 010607 -*/ 
		return(-1);									/*- mm 010607 -*/ 
	if (pwc)
		*pwc = result_chr;
	
	return(number_of_bytes);
}

int _MSL_CDECL mbtowc(wchar_t * _MSL_RESTRICT pwc, const char * _MSL_RESTRICT s, size_t n)
{
	return(_MSL_LOCALDATA(_current_locale).ctype_cmpt_ptr->decode_mb(pwc, s, n));		/*- mm 020119 -*/
}

int __unicode_to_UTF8(char * _MSL_RESTRICT s, wchar_t wchar)		/*- mm 011130 -*/
{
	int number_of_bytes;
	wchar_t wide_char;
	char * target_ptr;
	char first_byte_mark[6] = {0x00, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc};
	
	if (!s)           /* We are assuming UTF-8 encoding so return 0 */
		return(0);
	
	wide_char = wchar;
	
	if (wide_char < 0x00000080)
		number_of_bytes = 1;
	else if (wide_char < 0x00000800)
		number_of_bytes = 2;
	else if (wide_char < 0x00010000)
		number_of_bytes = 3;
	else if (wide_char < 0x00200000)
		number_of_bytes = 4;
	else if (wide_char < 0x04000000)
		number_of_bytes = 5;
	else number_of_bytes = 6;
	
	target_ptr = s + number_of_bytes;
	
	switch (number_of_bytes) 
	{				/* Note: the cases are meant to fall through! */
		case 6:
			*--target_ptr = (wide_char & 0x003f) | 0x80;
			wide_char >>= 6;
		case 5:
			*--target_ptr = (wide_char & 0x003f) | 0x80;
			wide_char >>= 6;
		case 4:
			*--target_ptr = (wide_char & 0x003f) | 0x80;
			wide_char >>= 6;
		case 3:
			*--target_ptr = (wide_char & 0x003f) | 0x80;
			wide_char >>= 6;
		case 2:
			*--target_ptr = (wide_char & 0x003f) | 0x80;
			wide_char >>= 6;
		case 1:
			*--target_ptr = wide_char | first_byte_mark[number_of_bytes - 1];
	}
	
	return (number_of_bytes);
}

int __unicode_to_UTF8_s(char * _MSL_RESTRICT s, size_t smax, wchar_t wchar)		/*- mm 011130 -*/
{
	int number_of_bytes;
	wchar_t wide_char;
	char * target_ptr;
	char first_byte_mark[6] = {0x00, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc};
	
	wide_char = wchar;
	
	if (wide_char < 0x00000080)
		number_of_bytes = 1;
	else if (wide_char < 0x00000800)
		number_of_bytes = 2;
	else if (wide_char < 0x00010000)
		number_of_bytes = 3;
	else if (wide_char < 0x00200000)
		number_of_bytes = 4;
	else if (wide_char < 0x04000000)
		number_of_bytes = 5;
	else number_of_bytes = 6;
	
	target_ptr = s + number_of_bytes;
	
	switch (number_of_bytes) 
	{				/* Note: the cases are meant to fall through! */
		case 6:
			if (smax > 6)
				*--target_ptr = (wide_char & 0x003f) | 0x80;
			else
				--target_ptr;
			wide_char >>= 6;
		case 5:
			if (smax > 5)
				*--target_ptr = (wide_char & 0x003f) | 0x80;
			else
				--target_ptr;
			wide_char >>= 6;
		case 4:
			if (smax > 4)
				*--target_ptr = (wide_char & 0x003f) | 0x80;
			else
				--target_ptr;
			wide_char >>= 6;
		case 3:
			if (smax > 3)
				*--target_ptr = (wide_char & 0x003f) | 0x80;
			else
				--target_ptr;
			wide_char >>= 6;
		case 2:
			if (smax > 2)
				*--target_ptr = (wide_char & 0x003f) | 0x80;
			else
				--target_ptr;
			wide_char >>= 6;
		case 1:
			*--target_ptr = wide_char | first_byte_mark[number_of_bytes - 1];
	}
	
	return (number_of_bytes);
}

int __mbtowc_noconv(wchar_t * pwc, const char * s, size_t n)
{
	if (!s)
		return(0);
	
	if (!n)
		return(-1);
	
	if (pwc)
		*pwc = (unsigned char)*s;							/*- mm 030401 -*/
		
	if (!*s)
		return(0);
	
	return(1);
}

int __wctomb_noconv(char * s, wchar_t wchar)
{
	if (!s)
		return(0);
	
	*s = wchar;
	
	return(1);
}

int _MSL_CDECL wctomb(char * s, wchar_t wchar)
{
	return(_MSL_LOCALDATA(_current_locale).ctype_cmpt_ptr->encode_wc(s, wchar));		/*- mm 020119 -*/
}

int _MSL_CDECL wctomb_s(int * _MSL_RESTRICT status, char * _MSL_RESTRICT s, rsize_t smax, wchar_t wchar)
{
	int newstatus;
	int len;
	char wc[MB_CUR_MAX];
	
	if (((s == NULL) && (smax != 0)) || (smax > RSIZE_MAX) || (status == NULL))
	{
		__msl_runtime_constraint_violation_s(NULL, NULL, ERANGE);
		return ERANGE;
	}
	
	if (s == NULL)
	{
		if (_MSL_LOCALDATA(_current_locale).ctype_cmpt_ptr->encode_wc == __wctomb_noconv)
			*status = 0;	/* no state-dependent encoding for noconv encoder */
		else
			*status = 1;	/* assume state-dependent encoding for all other encoders */
		
		return ENOERR;
	}
	
	newstatus = _MSL_LOCALDATA(_current_locale).ctype_cmpt_ptr->encode_wc(wc, wchar);
	len = mblen(wc, sizeof(wc));
	
	if (len > smax)
	{
		__msl_runtime_constraint_violation_s(NULL, NULL, ERANGE);
		return ERANGE;
	}
	
	*status = newstatus;
	memcpy(s, wc, len);
	
	return ENOERR;
}

size_t _MSL_CDECL mbstowcs(wchar_t * _MSL_RESTRICT pwcs, const char * _MSL_RESTRICT s, size_t n)
{
	int     result;
	char *  source;
	int count;
	size_t  source_len;
	
	source_len = strlen(s);

    if (pwcs)
    {
        source      = (char *)s;
        for (count = 0; count < n; count++)
        {
        	if (*source)
        	{
	        	result = mbtowc(pwcs++, source, source_len);
	        	if (result > 0)
	        	{
	        		source += result;
	        		source_len -= result;
	        	}
	        	else
	        		return((size_t)-1);								/*- mm 011102 -*/
	        }
	        else
	        {
	        	*pwcs = 0;
	        	break;
	        }	
        }
        
    }
	else
		count = 0;
			
	return(count);
}

errno_t _MSL_CDECL mbstowcs_s(size_t * _MSL_RESTRICT retval, wchar_t * _MSL_RESTRICT pwcs, rsize_t pwcsmax, const char * _MSL_RESTRICT s, rsize_t n)
{
	int     result;
	char *  source;
	int count;
	size_t  source_len;
	
	if ((retval == NULL) || (s == NULL) || ((pwcs != NULL) && ((pwcsmax > RSIZE_MAX) || (n > RSIZE_MAX) || (pwcsmax < n))))
	{
		__msl_runtime_constraint_violation_s(NULL, NULL, ERANGE);
		if (retval != NULL)
			*retval = (size_t)-1;
		return ERANGE;
}

	source_len = strnlen_s(s, n);

    if (pwcs)
    {
        source      = (char *)s;
        for (count = 0; count < n; count++)
        {
        	if (*source)
        	{
        		if (count < pwcsmax)
		        	result = mbtowc(pwcs++, source, source_len);
	        	
	        	if (result > 0)
	        	{
	        		source += result;
	        		source_len -= result;
	        	}
	        	else
	        		return((size_t)-1);								/*- mm 011102 -*/
	        }
	        else
	        {
	        	*pwcs = 0;
	        	break;
	        }	
        }
        
    }
	else
		count = 0;
			
	*retval = count;
	
	return 0;
}

size_t _MSL_CDECL wcstombs(char * _MSL_RESTRICT s, const wchar_t * _MSL_RESTRICT pwcs, size_t n)
{
	int     chars_written = 0;
	int     result;
	char    temp[MB_LEN_MAX];
	wchar_t * source;
	
	if (!s || !pwcs)
		return (0);
	
	source = (wchar_t*)pwcs;
	while(chars_written <= n)
	{
		if (!*source)
		{
			*(s + chars_written) = '\0';
			break;
		}
		else
		{
			result = wctomb(temp, *source++);
			if ((chars_written + result) <= n)
			{
				strncpy(s + chars_written, temp, result);
				chars_written += result;
			}
			else
				break;
		}
	}
			
	return(chars_written);
}

errno_t _MSL_CDECL wcstombs_s(size_t * _MSL_RESTRICT retval, char * _MSL_RESTRICT s, rsize_t s_max, const wchar_t * _MSL_RESTRICT pwcs, rsize_t n)
{
	int     chars_written = 0;
	int     result;
	char    temp[MB_LEN_MAX];
	wchar_t * source;
	
	if ((retval == NULL) || (pwcs == NULL) || ((s != NULL) && ((s_max > RSIZE_MAX) || (n > RSIZE_MAX) || (s_max < n))))
	{
		__msl_runtime_constraint_violation_s(NULL, NULL, ERANGE);
		if (retval != NULL)
			*retval = (size_t)-1;
		return ERANGE;
	}
	
	if (!s)
	{
		*retval = 0;
		return 0;
	}
	
	source = (wchar_t*)pwcs;
	while(chars_written <= n)
	{
		if (!*source)
		{
			*(s + chars_written) = '\0';
			break;
		}
		else
		{
       		if (chars_written < s_max)
				result = wctomb(temp, *source++);
			
			if ((chars_written + result) <= n)
			{
				strncpy(s + chars_written, temp, result);
				chars_written += result;
			}
			else
				break;
		}
	}
	
	*retval = chars_written;
	
	return 0;
}

#if (_MSL_C99 && _MSL_WIDE_CHAR)
size_t _MSL_CDECL mbrlen(const char * _MSL_RESTRICT s, size_t n, mbstate_t * _MSL_RESTRICT ps)
{
	#pragma unused(ps)
	
	mbstate_t internal;
	mbstate_t * mbs = ps;
	
	return(mbrtowc(NULL, s, n, mbs != NULL ? mbs : &internal));
}

size_t _MSL_CDECL mbrtowc(wchar_t * _MSL_RESTRICT pwc, const char * _MSL_RESTRICT s, size_t n, mbstate_t * _MSL_RESTRICT ps)
{
	#pragma unused(ps)
	size_t num_of_chars;
	
	if (s)
	{
		num_of_chars = is_utf8_complete(s, n);
		if ((num_of_chars != (size_t)(-1)) && (num_of_chars != (size_t)(-2)))
			if (pwc)
				num_of_chars = __utf8_to_unicode(pwc, s, n);	/*- mm 011130 -*/
		else if (num_of_chars == (size_t)-1)
			errno = EILSEQ;
		return (num_of_chars);
	}
	else									/*- mm 010607 -*/ 
		if (pwc)							/*- mm 010607 -*/ 
			*pwc = 0;						/*- mm 010607 -*/ 
	return(0);
			
}

size_t _MSL_CDECL wcrtomb(char * _MSL_RESTRICT s, wchar_t wc, mbstate_t * _MSL_RESTRICT ps)
{
	#pragma unused(ps)

	if (!s)
		return(1);
	
	return(__unicode_to_UTF8(s, wc));		/*- mm 011130 -*/
}

errno_t _MSL_CDECL wcrtomb_s(size_t * _MSL_RESTRICT retval, char * _MSL_RESTRICT s, rsize_t smax, wchar_t wc, mbstate_t * _MSL_RESTRICT ps)
{
	char buf[MB_CUR_MAX + 1];
	char *use_s;
	rsize_t use_smax;
	
	if ((retval == NULL) || (ps == NULL) || ((s != NULL) && ((smax <= 0) || (smax > RSIZE_MAX))))
	{
		__msl_runtime_constraint_violation_s(NULL, NULL, ERANGE);
		if (retval != NULL)
			*retval = (size_t)-1;
		if ((s != NULL) && (smax > 0) && (smax <= RSIZE_MAX))
			s[0] = 0;
		return ERANGE;
	}

	if (s == NULL)
	{
		use_s = buf;
		use_smax = sizeof(buf);
	}
	else
	{
		use_s = s;
		use_smax = smax;
	}
	
	*retval = __unicode_to_UTF8_s(use_s, use_smax, wc);
	
	return ENOERR;
}

size_t _MSL_CDECL mbsrtowcs(wchar_t * _MSL_RESTRICT dst, const char ** _MSL_RESTRICT src, size_t len, mbstate_t * _MSL_RESTRICT ps)
{
	int     result;
	char *  source;
	int 	count;
	size_t  source_len;
	wchar_t local_target;
	
	if(!*src)
		return (0);
	
	
	source_len = (dst == NULL)? 50: strlen(*src);

	source      = (char*)*src;
	
	for (count = 0; count < len; count++)
	{
		if (*source)
		{
		   	result = mbrtowc((dst == NULL) ? &local_target : dst++, source, source_len, ps);
		   	if (result > 0)
		   	{
		   		source += result;
		   		source_len -= result;
		   	}
		   	else
		   		break;
		}
		else
		{
			if (dst != NULL)
			{				
				*dst = 0;
				*src = NULL;
			}
			break;
		}	
	}
	
	return(count);
}

errno_t _MSL_CDECL mbsrtowcs_s(size_t * _MSL_RESTRICT retval, wchar_t * _MSL_RESTRICT dst, rsize_t dstmax, const char ** _MSL_RESTRICT src, rsize_t len, mbstate_t * _MSL_RESTRICT ps)
{
	int     result;
	char *  source;
	int 	count;
	size_t  source_len;
	wchar_t local_target;
	
	if ((retval == NULL) || (src == NULL) || (*src == NULL) || (ps == NULL) || ((dst != NULL) && ((len > RSIZE_MAX) || (dstmax > RSIZE_MAX) || (dstmax < len))))
	{
		__msl_runtime_constraint_violation_s(NULL, NULL, ERANGE);
		if (retval != NULL)
			*retval = (size_t)-1;
		return ERANGE;
	}
	
	source_len = strlen(*src);

	source      = (char*)*src;
	for (count = 0; count < len; count++)
	{
		if (*source)
		{
		   	result = mbrtowc((dst == NULL) ? &local_target : dst++, source, source_len, ps);
		   	if (result > 0)
		   	{
		   		source += result;
		   		source_len -= result;
		   	}
		   	else
		   		break;
		}
		else
		{
			if (dst != NULL)
			{
				*dst = 0;
			  	*src = NULL;
			}
			break;
		}	
	}
	
	*retval = count;
	
	return 0;
}

size_t _MSL_CDECL wcsrtombs(char * _MSL_RESTRICT dst, const wchar_t ** _MSL_RESTRICT src, size_t len, mbstate_t * _MSL_RESTRICT ps)
{

	int     chars_written = 0;
	int     result;
	char    temp[MB_LEN_MAX];
	wchar_t * source;
	
	if (!*src)
		return (0);
	
	source = (wchar_t*)*src;
	while(chars_written <= len)
	{
		if (!*source)
		{
			if (dst != NULL)
			{
				*(dst + chars_written) = '\0';
				*src = NULL;
			}
			break;
		}
		else
		{
			result = wcrtomb(temp, *source++, ps);
			if ((chars_written + result) <= len)
			{
				strncpy(dst + chars_written, temp, result);
				chars_written += result;
			}
			else
				break;
		}
	}
		
	return(chars_written);
}

errno_t _MSL_CDECL wcsrtombs_s(size_t * _MSL_RESTRICT retval, char * _MSL_RESTRICT dst, rsize_t dstmax, const wchar_t ** _MSL_RESTRICT src, rsize_t len, mbstate_t * _MSL_RESTRICT ps)
{

	int     chars_written = 0;
	int     result;
	char    temp[MB_LEN_MAX];
	wchar_t * source;
	
	if ((retval == NULL) || (src == NULL) || (*src == NULL) || (ps == NULL) || ((dst != NULL) && ((len > RSIZE_MAX) || (dstmax > RSIZE_MAX) || (dstmax < len))))
	{
		__msl_runtime_constraint_violation_s(NULL, NULL, ERANGE);
		if (retval != NULL)
			*retval = (size_t)-1;
		return ERANGE;
	}
	
	if (!*src)
	{
		*retval = 0;
		return 0;
	}
	
	source = (wchar_t*)*src;
	while(chars_written <= len)
	{
		if (!*source)
		{
			if (dst)
			{
				*(dst + chars_written) = '\0';
				*src = NULL;
			}
			
			break;
		}
		else
		{
			result = wcrtomb(temp, *source++, ps);
			if ((chars_written + result) <= len)
			{
				if (dst)
					strncpy(dst + chars_written, temp, result);
				chars_written += result;
			}
			else
				break;
		}
}

	*retval = chars_written;
	
	return 0;
}

/*- mm 021210 -*/
int _MSL_CDECL mbsinit(const mbstate_t * ps)
{
	if (ps == NULL)
		return (-1);
	else
		if (*ps == 0)
			return (1);
		else
			return (0);
}
#endif  /* _MSL_C99 */											/*- mm 030304 -*/
/*- mm 021210 -*/
#endif  /*  _MSL_WIDE_CHAR  */

/* Change record:
 * JFH 950724 First code release.
 * vss 990624 protect for wide characters
 * mm  990702 correction to prevent sign extension when assigning char to wchar
 * mm  000204 Rewrote mbstowcs to make action if pwcs is NULL match that of MSDN's implementation.  Thanks to E. Cloninger
 * mm  010528 Complete rewrite to implement UTF-8 as the encoding for multibyte
 * mm  010607 Fixes to UTF-8 conversion
 * mm  011102 Corrects return value of mbstowcs when multibyte string is invalid
 * mm  011130 Changes for implementation of locale
 * cc  011203 Added _MSL_CDECL for new name mangling
 * mm  020119 Further changes for implementation of locale 
 * JWW 020307 Use thread local data to get access to current locale on Windows
 * JWW 020604 Added _MSL_LOCALDATA macro to make multithread code easier to read
 * JWW 020917 Added _MSL_RESTRICT to get the restrict type specifier for certain C99 functions
 * JWW 021016 Enhanced UTF-8 routines to deal with encodings of up to 6 bytes long
 * JWW 021031 Made thread local data available for Mach-O
 * mm  021112 Moved a return statement out of the loop in is_utf8_complete to fix a termination bug
 * mm  021210 Added mbsinit() 
 * JWW 030224 Changed __NO_WIDE_CHAR flag into the new more configurable _MSL_WIDE_CHAR
 * mm  030304 Added _MSL_C99 wrappers
 * mm  030401 correction to prevent sign extension when assigning char to wchar
 */