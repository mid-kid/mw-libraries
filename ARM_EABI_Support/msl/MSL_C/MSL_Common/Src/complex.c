/* MSL
 * Copyright © 1995-2007 Freescale Corporation.  All rights reserved.
 *
 * $Date: 2007/01/29 18:11:26 $
 * $Revision: 1.4 $
 */

#include <ansi_parms.h>

#if _MSL_COMPLEX

#include <complex.h>
#include <math.h>

/* Helper functions */
static _MSL_INLINE double complex polar(double r, double theta)
{
	return r * cos(theta) + I * (r * sin(theta));
}

static _MSL_INLINE float complex polarf(float r, float theta)
{
	return r * cosf(theta) + I * (r * sinf(theta));
}

static _MSL_INLINE long double complex polarl(long double r, long double theta)
{
	return r * cosl(theta) + I * (r * sinl(theta));
}

/* Trigonometric functions */

double complex       _MSL_CDECL cacos (double complex z)
{
	double complex y = clog(z + csqrt(z * z - 1.0));
	if (cimag(y)<0.0)
		return -cimag(y) + creal(y) * I;

	return cimag(y) - creal(y) * I;
}

float complex        _MSL_CDECL cacosf(float complex z)
{
	float complex y = clogf(z + csqrtf(z * z - 1.0f));
	if (cimagf(y)<0.0f)
		return -cimagf(y) + crealf(y) * I;

	return cimagf(y) - crealf(y) * I;
}

long double complex  _MSL_CDECL cacosl(long double complex z)
{
	long double complex y = clogl(z + csqrtl(z * z - 1.0));
	if (cimagl(y)<0.0)
		return -cimagl(y) + creall(y) * I;

	return cimagl(y) - creall(y) * I;
}


double complex       _MSL_CDECL casin (double complex z)
{
	double complex y = clog(csqrt(1.0 - z * z) - cimag(z) + creal(z) * I);
	return cimag(y) - creal(y) * I;
}

float complex        _MSL_CDECL casinf(float complex z)
{
	float complex y = clogf(csqrtf(1.0f - z * z) - cimagf(z) + crealf(z) * I);
	return cimagf(y)  - crealf(y) * I;
}

long double complex  _MSL_CDECL casinl(long double complex z)
{
	long double complex y = clogl(csqrtl(1.0 - z * z) - cimagl(z) + creall(z) * I);
	return cimagl(y)  - creall(y) * I;
}


double complex       _MSL_CDECL catan (double complex z)
{
	double complex y = creal(z) * I - cimag(z);
	double rx,ry;
	y = clog((1+y)/(1-y));
	rx = cimag(y)/2.0;
	ry = -creal(y)/2.0;
	return rx + I * ry;
}

float complex        _MSL_CDECL catanf(float complex z)
{
	float complex y = crealf(z) * I - cimagf(z);
	float rx,ry;
	y = clogf((1+y)/(1-y));
	rx = cimagf(y)/2.0f;
	ry = -crealf(y)/2.0f;
	return rx + I * ry;
}

long double complex  _MSL_CDECL catanl(long double complex z)
{
	long double complex y = creall(z) * I - cimagl(z);
	long double rx,ry;
	y = clogl((1+y)/(1-y));
	rx = cimagl(y)/2.0;
	ry = -creall(y)/2.0;
	return rx + I * ry;
}


double complex       _MSL_CDECL ccos (double complex z)
{
	return (cos(creal(z)) * cosh(cimag(z))) + I * (-sin(creal(z)) * sinh(cimag(z)));
}

float complex        _MSL_CDECL ccosf(float complex z)
{
	return (cosf(crealf(z)) * coshf(cimagf(z))) + I * (-sinf(crealf(z)) * sinhf(cimagf(z)));
}

long double complex  _MSL_CDECL ccosl(long double complex z)
{
	return (cosl(creall(z)) * coshl(cimagl(z))) + I * (-sinl(creall(z)) * sinhl(cimagl(z)));
}


double complex       _MSL_CDECL csin (double complex z)
{
	return (sin(creal(z)) * cosh(cimag(z))) + I * (cos(creal(z)) * sinh(cimag(z)));
}

float complex        _MSL_CDECL csinf(float complex z)
{
	return (sinf(crealf(z)) * coshf(cimagf(z))) + I * (cosf(crealf(z)) * sinhf(cimagf(z)));
}

long double complex  _MSL_CDECL csinl(long double complex z)
{
	return (sinl(creall(z)) * coshl(cimagl(z))) + I * (cosl(creall(z)) * sinhl(cimagl(z)));
}


double complex       _MSL_CDECL ctan (double complex z)
{
	double u2 = 2.0 * creal(z);
	double v2 = 2.0 * cimag(z);
	double denom = cos(u2) + cosh(v2);
	double rx = sin(u2)/denom;
	double ry = sinh(v2)/denom;
	return rx + I * ry;
}

float complex        _MSL_CDECL ctanf(float complex z)
{
	float u2 = 2.0f * crealf(z);
	float v2 = 2.0f * cimagf(z);
	float denom = cosf(u2) + coshf(v2);
	float rx = sinf(u2)/denom;
	float ry = sinhf(v2)/denom;
	return rx + I * ry;
}

long double complex  _MSL_CDECL ctanl(long double complex z)
{
	long double u2 = 2.0 * creall(z);
	long double v2 = 2.0 * cimagl(z);
	long double denom = cosl(u2) + coshl(v2);
	long double rx = sinl(u2)/denom;
	long double ry = sinhl(v2)/denom;
	return rx + I * ry;
}


/* Hyperbolic functions */

double complex       _MSL_CDECL cacosh (double complex z)
{
	double complex y = clog(z + csqrt(z*z - 1.0));
	if (creal(y) < 0.0)
		return -y;
	return y;
}

float complex        _MSL_CDECL cacoshf(float complex z)
{
	float complex y = clogf(z + csqrtf(z*z - 1.0f));
	if (crealf(y) < 0.0f)
		return -y;
	return y;
}

long double complex  _MSL_CDECL cacoshl(long double complex z)
{
	long double complex y = clogl(z + csqrtl(z*z - 1.0));
	if (creall(y) < 0.0)
		return -y;
	return y;
}


double complex       _MSL_CDECL casinh (double complex z)
{
	return clog(z + csqrt(z*z + 1.0));
}

float complex        _MSL_CDECL casinhf(float complex z)
{
	return clogf(z + csqrtf(z*z + 1.0f));
}

long double complex  _MSL_CDECL casinhl(long double complex z)
{
	return clogl(z + csqrtl(z*z + 1.0));
}


double complex       _MSL_CDECL catanh (double complex z)
{
	return clog((1.0 + z) / (1.0 - z)) / 2.0;
}

float complex        _MSL_CDECL catanhf(float complex z)
{
	return clogf((1.0f + z) / (1.0f - z)) / 2.0f;
}

long double complex  _MSL_CDECL catanhl(long double complex z)
{
	return clogl((1.0 + z) / (1.0 - z)) / 2.0;
}


double complex       _MSL_CDECL ccosh (double complex z)
{
	return (cosh(creal(z)) * cos(cimag(z))) + I * (-sinh(creal(z)) * sin(cimag(z)));
}

float complex        _MSL_CDECL ccoshf(float complex z)
{
	return (coshf(crealf(z)) * cosf(cimagf(z))) + I * (-sinhf(crealf(z)) * sinf(cimagf(z)));
}

long double complex  _MSL_CDECL ccoshl(long double complex z)
{
	return (coshl(creall(z)) * cosl(cimagl(z))) + I * (-sinhl(creall(z)) * sinl(cimagl(z)));
}


double complex       _MSL_CDECL csinh (double complex z)
{
	return (sinh(creal(z)) * cos(cimag(z))) + I * (cosh(creal(z)) * sin(cimag(z)));
}

float complex        _MSL_CDECL csinhf(float complex z)
{
	return (sinhf(crealf(z)) * cosf(cimagf(z))) + I * (coshf(crealf(z)) * sinf(cimagf(z)));
}

long double complex  _MSL_CDECL csinhl(long double complex z)
{
	return (sinhl(creall(z)) * cosl(cimagl(z))) + I * (coshl(creall(z)) * sinl(cimagl(z)));
}


double complex       _MSL_CDECL ctanh (double complex z)
{
	double u2 = 2.0 * creal(z);
	double v2 = 2.0 * cimag(z);
	double denom = cosh(u2) + cos(v2);
	double rx = sinh(u2)/denom;
	double ry = sin(v2)/denom;
	return rx + I * ry;
}

float complex        _MSL_CDECL ctanhf(float complex z)
{
	float u2 = 2.0f * crealf(z);
	float v2 = 2.0f * cimagf(z);
	float denom = coshf(u2) + cosf(v2);
	float rx = sinhf(u2)/denom;
	float ry = sinf(v2)/denom;
	return rx + I * ry;
}

long double complex  _MSL_CDECL ctanhl(long double complex z)
{
	long double u2 = 2.0 * creall(z);
	long double v2 = 2.0 * cimagl(z);
	long double denom = coshl(u2) + cosl(v2);
	long double rx = sinhl(u2)/denom;
	long double ry = sinl(v2)/denom;
	return rx + I * ry;
}


/* Exponential and logarithmic functions */

double complex       _MSL_CDECL cexp (double complex z)
{
	double exp_x = exp(creal(z));
	return (exp_x * cos(cimag(z))) + I * (exp_x * sin(cimag(z)));
}

float complex        _MSL_CDECL cexpf(float complex z)
{
	double exp_x = expf(crealf(z));
	return (exp_x * cosf(cimagf(z))) + I * (exp_x * sinf(cimagf(z)));
}

long double complex  _MSL_CDECL cexpl(long double complex z)
{
	double exp_x = exp(creall(z));
	return (exp_x * cosl(cimagl(z))) + I * (exp_x * sinl(cimagl(z)));
}


double complex       _MSL_CDECL clog (double complex z)
{
	return log(cabs(z)) + I * carg(z);
}

float complex        _MSL_CDECL clogf(float complex z)
{
	return logf(cabsf(z)) + I * cargf(z);
}

long double complex  _MSL_CDECL clogl(long double complex z)
{
	return logl(cabsl(z)) + I * cargl(z);
}


/* Power and absolute value functions */

double      _MSL_CDECL cabs (double complex z)
{
	return hypot(creal(z),cimag(z));
}

float       _MSL_CDECL cabsf(float complex z)
{
	return hypotf(crealf(z),cimagf(z));
}

long double _MSL_CDECL cabsl(long double complex z)
{
	return hypotl(creall(z),cimagl(z));
}


double complex       _MSL_CDECL cpow (double complex x, double complex y)
{
	return cexp(y * clog(x));
}

float complex        _MSL_CDECL cpowf(float complex x, float complex y)
{
	return cexpf(y * clogf(x));
}

long double complex  _MSL_CDECL cpowl(long double complex x, long double complex y)
{
	return cexpl(y * clogl(x));
}


double complex       _MSL_CDECL csqrt (double complex z)
{
	if (z == (double complex)0)
		return (double complex)0;
	
	return polar(sqrt(cabs(z)), 0.5*carg(z));
}

float complex        _MSL_CDECL csqrtf(float complex z)
{
	if (z == (float complex)0)
		return (float complex)0;
	
	return polarf(sqrtf(cabsf(z)), 0.5f*cargf(z));
}

long double complex  _MSL_CDECL csqrtl(long double complex z)
{
	if (z == (long double complex)0)
		return (long double complex)0;
	
	return polarl(sqrtl(cabsl(z)), 0.5*cargl(z));
}


/* Manipulation functions */

double      _MSL_CDECL carg (double complex z)
{
	return atan2(cimag(z),creal(z));
}

float       _MSL_CDECL cargf(float complex z)
{
	return atan2f(cimagf(z),crealf(z));
}

long double _MSL_CDECL cargl(long double complex z)
{
	return atan2l(cimagl(z),creall(z));
}

double complex       _MSL_CDECL conj (double complex z)
{
	return creal(z) + I * (-cimag(z));
}

float complex        _MSL_CDECL conjf(float complex z)
{
	return crealf(z) + I * (-cimagf(z));
}

long double complex  _MSL_CDECL conjl(long double complex z)
{
	return creall(z) + I * (-cimagl(z));
}


double complex       _MSL_CDECL cproj (double complex z)
{
	if (!isfinite(creal(z)) || !isfinite(cimag(z)))
	{
		return INFINITY  + I * copysign(0.0, cimag(z));
	}
	return z;
}

float complex        _MSL_CDECL cprojf(float complex z)
{
	if (!isfinite(crealf(z)) || !isfinite(cimagf(z)))
	{
		return INFINITY  + I * copysign(0.0f, cimagf(z));
	}
	return z;
}

long double complex  _MSL_CDECL cprojl(long double complex z)
{
	if (!isfinite(creall(z)) || !isfinite(cimagl(z)))
	{
		return INFINITY  + I * copysign(0.0f, cimagl(z));
	}
	return z;
}



#endif /* _MSL_COMPLEX */

/* Change record: 
 * bn  060605 Initial implementation
 */
