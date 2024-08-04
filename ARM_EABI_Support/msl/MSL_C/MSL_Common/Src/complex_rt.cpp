/* MSL
 * Copyright © 1995-2007 Freescale Corporation.  All rights reserved.
 *
 * $Date: 2007/04/02 21:33:11 $
 * $Revision: 1.4 $
 */
 
#include <ansi_parms.h>
#if _MSL_COMPLEX
#include <math.h>

extern "C" {
	extern void* __rt_cplx_neg_f(void* result, void* op);
	extern void* __rt_cplx_neg_d(void* result, void* op);
	extern void* __rt_cplx_neg_ld(void* result, void* op);
	extern void* __rt_cplx_mul_f(void* result, void* lhs, void* rhs);
	extern void* __rt_cplx_mul_d(void* result, void* lhs, void* rhs);
	extern void* __rt_cplx_mul_ld(void* result, void* lhs, void* rhs);
	extern void* __rt_cplx_div_f(void* result, void* lhs, void* rhs);
	extern void* __rt_cplx_div_d(void* result, void* lhs, void* rhs);
	extern void* __rt_cplx_div_ld(void* result, void* lhs, void* rhs);
	extern void* __rt_cplx_add_f(void* result, void* lhs, void* rhs);
	extern void* __rt_cplx_add_d(void* result, void* lhs, void* rhs);
	extern void* __rt_cplx_add_ld(void* result, void* lhs, void* rhs);
	extern void* __rt_cplx_sub_f(void* result, void* lhs, void* rhs);
	extern void* __rt_cplx_sub_d(void* result, void* lhs, void* rhs);
	extern void* __rt_cplx_sub_ld(void* result, void* lhs, void* rhs);
}

namespace {

	template<typename T> inline void complex_neg_templ(T* result, T* op)
	{
		result[0] = -op[0];
		result[1] = -op[1];
	}

	template<typename T> inline void complex_mul_templ(T* result, T* rhs)
	{
		T a = result[0];
		T b = result[1];
		T c = rhs[0];
		T d = rhs[1];
		T ac = a * c;
		T bd = b * d;
		T ad = a * d;
		T bc = b * c;
		result[0] = ac - bd;
		result[1] = ad + bc;
		// Recover infinities that computed as NaN+iNaN ...
		if (isnan(result[0]) && isnan(result[1]))
		{
			bool recalc = false;
			if ( isinf(a) || isinf(b) ) // z is infinite
			{
				// "Box" the infinity ...
				a = copysign(isinf(a) ? T(1) : T(0), a);
				b = copysign(isinf(b) ? T(1) : T(0), b);
				// Change NaNs in the other factor to 0 ...
				if (isnan(c))
					c = copysign(T(0), c);
				if (isnan(d))
					d = copysign(T(0), d);
				recalc = true;
			}
			if ( isinf(c) || isinf(d) ) // w is infinite
			{
				// "Box" the infinity ...
				c = copysign(isinf(c) ? T(1) : T(0), c);
				d = copysign(isinf(d) ? T(1) : T(0), d);
				// Change NaNs in the other factor to 0 ...
				if (isnan(a))
					a = copysign(T(0), a);
				if (isnan(b))
					b = copysign(T(0), b);
				recalc = true;
			}
			if (!recalc) {
				// Recover infinities from overflow cases ...
				if (isinf(ac) || isinf(bd) || isinf(ad) || isinf(bc))
				{
					// Change all NaNs to 0 ...
					if (isnan(a))
						a = copysign(T(0), a);
					if (isnan(b))
						b = copysign(T(0), b);
					if (isnan(c))
						c = copysign(T(0), c);
					if (isnan(d))
						d = copysign(T(0), d);
					recalc = true;
				}
			}
			if (recalc)
			{
				result[0] = copysign(T(HUGE_VAL), ( a * c - b * d ));
				result[1] = copysign(T(HUGE_VAL), ( a * d + b * c ));
			}
		}
	}

	template<typename T> inline void complex_div_templ(T* result, T* rhs)
	{
		int ilogbw = 0;
		T a = result[0];
		T b = result[1];
		T c = rhs[0];
		T d = rhs[1];
		T logbw = logb(fmax(fabs(c), fabs(d)));
		if (isfinite(logbw))
		{
			ilogbw = (int)logbw;
			c = scalbn(c, -ilogbw);
			d = scalbn(d, -ilogbw);
		}
		T denom = c * c + d * d;
		result[0] = scalbn((a * c + b * d) / denom, -ilogbw);
		result[1] = scalbn((b * c - a * d) / denom, -ilogbw);

		// Recover infinities and zeros that computed
		// as NaN+iNaN; the only cases are non-zero/zero,
		// infinite/finite, and finite/infinite, ...

		if (isnan(result[0]) && isnan(result[1]))
		{
			if ((denom == 0) && (!isnan(a) || !isnan(b)))
			{
				result[0] = copysign(T(HUGE_VAL), c) * a;
				result[1] = copysign(T(HUGE_VAL), c) * b;
			}
			else if ((isinf(a) || isinf(b)) && isfinite(c) && isfinite(d))
			{
				a = copysign(isinf(a) ? T(1) : T(0), a);
				b = copysign(isinf(b) ? T(1) : T(0), b);
				result[0] = copysign(T(HUGE_VAL), ( a * c + b * d ));
				result[1] = copysign(T(HUGE_VAL), ( b * c - a * d ));
			}
			else if (isinf(logbw) && isfinite(a) && isfinite(b))
			{
				c = copysign(isinf(c) ? T(1) : T(0), c);
				d = copysign(isinf(d) ? T(1) : T(0), d);
				result[0] = T(0) * ( a * c + b * d );
				result[1] = T(0) * ( b * c - a * d );
			}
		}
	}

	template<typename T> inline void complex_add_templ(T* result, T* lhs, T* rhs)
	{
		result[0] = lhs[0] + rhs[0];
		result[1] = lhs[1] + rhs[1];
	}

	template<typename T> inline void complex_sub_templ(T* result, T* lhs, T* rhs)
	{
		result[0] = lhs[0] - rhs[0];
		result[1] = lhs[1] - rhs[1];
	}

}

extern void* __rt_cplx_neg_f(void* result, void* op)
{
	complex_neg_templ<float>((float *)result, (float *)op);
	return result;
}
extern void* __rt_cplx_neg_d(void* result, void* op)
{
	complex_neg_templ<double>((double *)result, (double *)op);
	return result;
}
extern void* __rt_cplx_neg_ld(void* result, void* op)
{
	complex_neg_templ<long double>((long double *)result, (long double *)op);
	return result;
}

extern void* __rt_cplx_mul_f(void* result, void* lhs, void* rhs)
{
	((float *)result)[0] = ((float *)lhs)[0]; 
	((float *)result)[1] = ((float *)lhs)[1]; 
	complex_mul_templ<float>((float *)result, (float *)rhs);
	return result;
}
extern void* __rt_cplx_mul_d(void* result, void* lhs, void* rhs)
{
	((double *)result)[0] = ((double *)lhs)[0]; 
	((double *)result)[1] = ((double *)lhs)[1]; 
	complex_mul_templ<double>((double *)result, (double *)rhs);
	return result;
}
extern void* __rt_cplx_mul_ld(void* result, void* lhs, void* rhs)
{
	((long double *)result)[0] = ((long double *)lhs)[0]; 
	((long double *)result)[1] = ((long double *)lhs)[1]; 
	complex_mul_templ<long double>((long double *)result, (long double *)rhs);
	return result;
}

extern void* __rt_cplx_div_f(void* result, void* lhs, void* rhs)
{
	((float *)result)[0] = ((float *)lhs)[0]; 
	((float *)result)[1] = ((float *)lhs)[1]; 
	complex_div_templ<float>((float *)result, (float *)rhs);
	return result;
}
extern void* __rt_cplx_div_d(void* result, void* lhs, void* rhs)
{
	((double *)result)[0] = ((double *)lhs)[0]; 
	((double *)result)[1] = ((double *)lhs)[1]; 
	complex_div_templ<double>((double *)result, (double *)rhs);
	return result;
}
extern void* __rt_cplx_div_ld(void* result, void* lhs, void* rhs)
{
	((long double *)result)[0] = ((long double *)lhs)[0]; 
	((long double *)result)[1] = ((long double *)lhs)[1]; 
	complex_div_templ<long double>((long double *)result, (long double *)rhs);
	return result;
}

extern void* __rt_cplx_add_f(void* result, void* lhs, void* rhs)
{
	complex_add_templ<float>((float *)result, (float *)lhs, (float *)rhs);
	return result;
}
extern void* __rt_cplx_add_d(void* result, void* lhs, void* rhs)
{
	complex_add_templ<double>((double *)result, (double *)lhs, (double *)rhs);
	return result;
}
extern void* __rt_cplx_add_ld(void* result, void* lhs, void* rhs)
{
	complex_add_templ<long double>((long double *)result, (long double *)lhs, (long double *)rhs);
	return result;
}

extern void* __rt_cplx_sub_f(void* result, void* lhs, void* rhs)
{
	complex_sub_templ<float>((float *)result, (float *)lhs, (float *)rhs);
	return result;
}
extern void* __rt_cplx_sub_d(void* result, void* lhs, void* rhs)
{
	complex_sub_templ<double>((double *)result, (double *)lhs, (double *)rhs);
	return result;
}
extern void* __rt_cplx_sub_ld(void* result, void* lhs, void* rhs)
{
	complex_sub_templ<long double>((long double *)result, (long double *)lhs, (long double *)rhs);
	return result;
}
#endif /* _MSL_COMPLEX */