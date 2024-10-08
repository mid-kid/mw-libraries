/*---------------------------------------------------------------------------*
  Project:  NitroSDK - OS - include
  File:     printf.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: printf.h,v $
  Revision 1.19  01/18/2006 02:12:28  kitase_hirotake
  do-indent

  Revision 1.18  10/12/2005 08:32:38  yada
  OS_PutString() is deadstripped in case of SDK_FINALROM

  Revision 1.17  02/28/2005 05:26:01  yosizaki
  do-indent.

  Revision 1.16  02/28/2005 04:26:12  yosizaki
  Minor revisions related to SDK_NO_MESSAGE

  Revision 1.15  2004/10/04 10:06:12  yasu
  support SDK_NO_MESSAGE

  Revision 1.14  2004/09/11 06:00:47  yasu
  Add OS_TPrintf

  Revision 1.13  06/08/2004 00:30:20  yada
  invalidate debug functions(OS_Printf, etc.) when FINALROM

  Revision 1.12  04/07/2004 02:03:17  yada
  fix header comment

  Revision 1.11  03/26/2004 06:51:33  yosizaki
  add OS_SPrintf, OS_VSPrintf, OS_SNPrintf, and OS_VSNPrintf.

  Revision 1.10  2004/03/04 12:40:37  yasu
  change function typedef name

  Revision 1.9  2004/02/14 09:26:08  yasu
  move printserver into os_printf

  Revision 1.8  2004/02/05 07:09:03  yasu
  change SDK prefix iris -> nitro

  Revision 1.7  2003/12/29 04:27:24  yasu
  workaround for OS_Warning, OS_Panic

  Revision 1.6  2003/12/02 02:39:18  yasu
  First step of embedding 'printout' into ISDebugger

  Revision 1.5  2003/11/25 11:18:20  yasu
  Enabled OS_PutChar switching

  Revision 1.4  2003/11/25 00:05:04  yasu
  Added 'include' file in step with opening of OS_VPrintf   xyxyxy

  Revision 1.3  11/21/2003 12:21:10  yada
  Added REG_EMU_CONSOLE_OUT and reg_OS_EMU_CONSOLE_OUT

  Revision 1.2  2003/11/17 00:35:05  yasu
  Added OS_Halt

  Revision 1.1  2003/11/17 00:22:26  yasu
  Separated from os.h

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_OS_COMMON_PRINTF_H_
#define NITRO_OS_COMMON_PRINTF_H_

#pragma  warn_padding off
#include <stdio.h>                     // Stop the stdio.h PADDING warning
#pragma  warn_padding reset
#include <stdarg.h>
#include <nitro/types.h>


#ifdef __cplusplus
extern "C" {
#endif

//
//  Ensata controls
//
#define REG_EMU_CONSOLE_OUT      0x4fff000
#define reg_OS_EMU_CONSOLE_OUT   (*((REGType8v *)REG_EMU_CONSOLE_OUT))


//
//  Prototypes
//
#ifndef SDK_FINALROM
extern void (*OS_PutString) (const char *str);
#else
#define OS_PutString(x)   ((void)0)
#endif

int     OS_SPrintf(char *dst, const char *fmt, ...);
int     OS_VSPrintf(char *dst, const char *fmt, va_list vlist);
int     OS_SNPrintf(char *dst, size_t len, const char *fmt, ...);
int     OS_VSNPrintf(char *dst, size_t len, const char *fmt, va_list vlist);

#ifndef SDK_FINALROM
void    OS_PutChar(char c);
void    OS_VPrintf(const char *fmt, va_list vlist);
void    OS_TVPrintf(const char *fmt, va_list vlist);
void    OS_Printf(const char *fmt, ...);
void    OS_TPrintf(const char *fmt, ...);
#ifndef SDK_NO_MESSAGE
void    OSi_Warning(const char *file, int line, const char *fmt, ...);
void    OSi_TWarning(const char *file, int line, const char *fmt, ...);
void    OSi_Panic(const char *file, int line, const char *fmt, ...);
void    OSi_TPanic(const char *file, int line, const char *fmt, ...);
#else
void    OS_Terminate();
#define OSi_Warning( file, line, ... )    ((void)0)
#define OSi_TWarning( file, line, ... )   ((void)0)
#define OSi_Panic( file, line, ... )      OS_Terminate()
#define OSi_TPanic( file, line, ... )     OS_Terminate()
#endif

#define OS_Warning( ... )   OSi_Warning( __FILE__, __LINE__, __VA_ARGS__ );
#define OS_Panic( ... )     OSi_Panic( __FILE__, __LINE__, __VA_ARGS__ );
#define OS_TWarning( ... )  OSi_TWarning( __FILE__, __LINE__, __VA_ARGS__ );
#define OS_TPanic( ... )    OSi_TPanic( __FILE__, __LINE__, __VA_ARGS__ );

#else
//---- invalidate debug functions when FINALROM
#define OS_PutChar( ... )                       ((void)0)
#define OS_VPrintf( fmt, ... )                  ((void)0)
#define OS_Printf( ... )                        ((void)0)
#define OSi_Warning( file, line, ... )          ((void)0)
#define OSi_Panic( file, line, ... )            OS_Terminate()
#define OS_Warning( ... )                       ((void)0)
#define OS_Panic( ... )                         OS_Terminate()

#define OS_TVPrintf( fmt, ... )                 ((void)0)
#define OS_TPrintf( ... )                       ((void)0)
#define OSi_TWarning( file, line, ... )         ((void)0)
#define OSi_TPanic( file, line, ... )           OS_Terminate()
#define OS_TWarning( ... )                      ((void)0)
#define OS_TPanic( ... )                        OS_Terminate()
#endif

//
//  PrintServer
//
typedef union
{
    u16     s;
    char    c[2];
}
OSPrintWChar;

#define OS_PRINTSRV_BUFFERSIZE  1024
#define OS_PRINTSRV_WCHARSIZE   (OS_PRINTSRV_BUFFERSIZE/sizeof(OSPrintWChar))

typedef volatile struct
{
    u32     in;
    u32     out;
    OSPrintWChar buffer[OS_PRINTSRV_WCHARSIZE];

}
OSPrintServerBuffer;

#ifdef   SDK_ARM9
#ifndef SDK_FINALROM
void    OS_InitPrintServer(void);
void    OS_PrintServer(void);
#else
#define OS_InitPrintServer()                    ((void)0)
#define OS_PrintServer()                        ((void)0)
#endif
#endif

#ifdef __cplusplus
} /* extern "C"*/
#endif

/* NITRO_OS_COMMON_PRINTF_H_*/
#endif
