#ifndef	NITROSDK_VERSION_H_
#define	NITROSDK_VERSION_H_
#define	SDK_VERSION_DATE		20060125
#define	SDK_VERSION_TIME		405
#define	SDK_VERSION_MAJOR		3
#define	SDK_VERSION_MINOR		0
#define	SDK_VERSION_RELSTEP		30000
#define	SDK_BUILDINFO_CW_CC		74
#define	SDK_BUILDINFO_CW_LD		72
#if 0	// for Makefile
NITRO_VERSION_DATE_AND_TIME	=	060125 0405
NITRO_VERSION_DATE		=	20060125
NITRO_VERSION_TIME		=	405
NITRO_VERSION_MAJOR		=	3
NITRO_VERSION_MINOR		=	0
NITRO_VERSION_RELSTEP		=	30000
NITRO_VERSION_BUILDINFO_CW_CC	=	74
NITRO_VERSION_BUILDINFO_CW_LD	=	72
#
#  RELSTEP PR1=10100 PR2=10200 ...
#          RC1=20100 RC2=20200 ...
#          RELEASE=30000
#
#endif

#ifndef SDK_VERSION_NUMBER
#define SDK_VERSION_NUMBER(major, minor, relstep) \
(((major) << 24) | ((minor) << 16) | ((relstep) << 0))
#define SDK_CURRENT_VERSION_NUMBER \
SDK_VERSION_NUMBER(SDK_VERSION_MAJOR, SDK_VERSION_MINOR, SDK_VERSION_RELSTEP)
#endif

#if LIBVER <= LIBVER_ds_1_2_sp2
#undef SDK_VERSION_MAJOR
#define SDK_VERSION_MAJOR 2
#endif

#endif
