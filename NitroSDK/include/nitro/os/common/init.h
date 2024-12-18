/*---------------------------------------------------------------------------*
  Project:  NitroSDK - OS - include
  File:     init.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: init.h,v $
  Revision 1.7  01/18/2006 02:11:19  kitase_hirotake
  do-indent

  Revision 1.6  03/01/2005 01:57:00  yosizaki
  Revised copyright year

  Revision 1.5  02/28/2005 05:26:01  yosizaki
  do-indent.

  Revision 1.4  09/02/2004 06:25:59  yada
  only change comment

  Revision 1.3  04/07/2004 02:03:17  yada
  fix header comment

  Revision 1.2  2004/02/05 07:09:03  yasu
  change SDK prefix iris -> nitro

  Revision 1.1  12/22/2003 01:35:16  yada
  made init.h in accordance with OS_Init() installation  xyxyxy


  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_OS_INIT_H_
#define NITRO_OS_INIT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <nitro/misc.h>
#include <nitro/types.h>


/*---------------------------------------------------------------------------*
  Name:         OS_Init

  Description:  initialize sdk os

  Arguments:    None

  Returns:      None
 *---------------------------------------------------------------------------*/
void    OS_Init(void);



#ifdef __cplusplus
} /* extern "C"*/
#endif

/* NITRO_OS_INIT_H_ */
#endif
