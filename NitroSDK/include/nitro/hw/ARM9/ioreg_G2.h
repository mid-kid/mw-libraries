/*---------------------------------------------------------------------------*
  Project:  NitroSDK - IO Register List - 
  File:     nitro/hw/ARM9/ioreg_G2.h

  Copyright 2003-2004 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

 *---------------------------------------------------------------------------*/
//
//  I was generated automatically, don't edit me directly!!!
//
#ifndef NITRO_HW_ARM9_IOREG_G2_H_
#define NITRO_HW_ARM9_IOREG_G2_H_

#ifndef SDK_ASM
#include <nitro/types.h>
#include <nitro/hw/ARM9/mmap_global.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Definition of Register offsets, addresses and variables.
 */


/* BG0CNT */

#define REG_BG0CNT_OFFSET                                  0x008
#define REG_BG0CNT_ADDR                                    (HW_REG_BASE + REG_BG0CNT_OFFSET)
#define reg_G2_BG0CNT                                      (*( REGType16v *) REG_BG0CNT_ADDR)

/* BG1CNT */

#define REG_BG1CNT_OFFSET                                  0x00a
#define REG_BG1CNT_ADDR                                    (HW_REG_BASE + REG_BG1CNT_OFFSET)
#define reg_G2_BG1CNT                                      (*( REGType16v *) REG_BG1CNT_ADDR)

/* BG2CNT */

#define REG_BG2CNT_OFFSET                                  0x00c
#define REG_BG2CNT_ADDR                                    (HW_REG_BASE + REG_BG2CNT_OFFSET)
#define reg_G2_BG2CNT                                      (*( REGType16v *) REG_BG2CNT_ADDR)

/* BG3CNT */

#define REG_BG3CNT_OFFSET                                  0x00e
#define REG_BG3CNT_ADDR                                    (HW_REG_BASE + REG_BG3CNT_OFFSET)
#define reg_G2_BG3CNT                                      (*( REGType16v *) REG_BG3CNT_ADDR)

/* BG0OFS */

#define REG_BG0OFS_OFFSET                                  0x010
#define REG_BG0OFS_ADDR                                    (HW_REG_BASE + REG_BG0OFS_OFFSET)
#define reg_G2_BG0OFS                                      (*( REGType32v *) REG_BG0OFS_ADDR)

/* BG0HOFS */

#define REG_BG0HOFS_OFFSET                                 0x010
#define REG_BG0HOFS_ADDR                                   (HW_REG_BASE + REG_BG0HOFS_OFFSET)
#define reg_G2_BG0HOFS                                     (*( REGType16v *) REG_BG0HOFS_ADDR)

/* BG0VOFS */

#define REG_BG0VOFS_OFFSET                                 0x012
#define REG_BG0VOFS_ADDR                                   (HW_REG_BASE + REG_BG0VOFS_OFFSET)
#define reg_G2_BG0VOFS                                     (*( REGType16v *) REG_BG0VOFS_ADDR)

/* BG1OFS */

#define REG_BG1OFS_OFFSET                                  0x014
#define REG_BG1OFS_ADDR                                    (HW_REG_BASE + REG_BG1OFS_OFFSET)
#define reg_G2_BG1OFS                                      (*( REGType32v *) REG_BG1OFS_ADDR)

/* BG1HOFS */

#define REG_BG1HOFS_OFFSET                                 0x014
#define REG_BG1HOFS_ADDR                                   (HW_REG_BASE + REG_BG1HOFS_OFFSET)
#define reg_G2_BG1HOFS                                     (*( REGType16v *) REG_BG1HOFS_ADDR)

/* BG1VOFS */

#define REG_BG1VOFS_OFFSET                                 0x016
#define REG_BG1VOFS_ADDR                                   (HW_REG_BASE + REG_BG1VOFS_OFFSET)
#define reg_G2_BG1VOFS                                     (*( REGType16v *) REG_BG1VOFS_ADDR)

/* BG2OFS */

#define REG_BG2OFS_OFFSET                                  0x018
#define REG_BG2OFS_ADDR                                    (HW_REG_BASE + REG_BG2OFS_OFFSET)
#define reg_G2_BG2OFS                                      (*( REGType32v *) REG_BG2OFS_ADDR)

/* BG2HOFS */

#define REG_BG2HOFS_OFFSET                                 0x018
#define REG_BG2HOFS_ADDR                                   (HW_REG_BASE + REG_BG2HOFS_OFFSET)
#define reg_G2_BG2HOFS                                     (*( REGType16v *) REG_BG2HOFS_ADDR)

/* BG2VOFS */

#define REG_BG2VOFS_OFFSET                                 0x01a
#define REG_BG2VOFS_ADDR                                   (HW_REG_BASE + REG_BG2VOFS_OFFSET)
#define reg_G2_BG2VOFS                                     (*( REGType16v *) REG_BG2VOFS_ADDR)

/* BG3OFS */

#define REG_BG3OFS_OFFSET                                  0x01c
#define REG_BG3OFS_ADDR                                    (HW_REG_BASE + REG_BG3OFS_OFFSET)
#define reg_G2_BG3OFS                                      (*( REGType32v *) REG_BG3OFS_ADDR)

/* BG3HOFS */

#define REG_BG3HOFS_OFFSET                                 0x01c
#define REG_BG3HOFS_ADDR                                   (HW_REG_BASE + REG_BG3HOFS_OFFSET)
#define reg_G2_BG3HOFS                                     (*( REGType16v *) REG_BG3HOFS_ADDR)

/* BG3VOFS */

#define REG_BG3VOFS_OFFSET                                 0x01e
#define REG_BG3VOFS_ADDR                                   (HW_REG_BASE + REG_BG3VOFS_OFFSET)
#define reg_G2_BG3VOFS                                     (*( REGType16v *) REG_BG3VOFS_ADDR)

/* BG2PA */

#define REG_BG2PA_OFFSET                                   0x020
#define REG_BG2PA_ADDR                                     (HW_REG_BASE + REG_BG2PA_OFFSET)
#define reg_G2_BG2PA                                       (*( REGType16v *) REG_BG2PA_ADDR)

/* BG2PB */

#define REG_BG2PB_OFFSET                                   0x022
#define REG_BG2PB_ADDR                                     (HW_REG_BASE + REG_BG2PB_OFFSET)
#define reg_G2_BG2PB                                       (*( REGType16v *) REG_BG2PB_ADDR)

/* BG2PC */

#define REG_BG2PC_OFFSET                                   0x024
#define REG_BG2PC_ADDR                                     (HW_REG_BASE + REG_BG2PC_OFFSET)
#define reg_G2_BG2PC                                       (*( REGType16v *) REG_BG2PC_ADDR)

/* BG2PD */

#define REG_BG2PD_OFFSET                                   0x026
#define REG_BG2PD_ADDR                                     (HW_REG_BASE + REG_BG2PD_OFFSET)
#define reg_G2_BG2PD                                       (*( REGType16v *) REG_BG2PD_ADDR)

/* BG2X */

#define REG_BG2X_OFFSET                                    0x028
#define REG_BG2X_ADDR                                      (HW_REG_BASE + REG_BG2X_OFFSET)
#define reg_G2_BG2X                                        (*( REGType32v *) REG_BG2X_ADDR)

/* BG2Y */

#define REG_BG2Y_OFFSET                                    0x02c
#define REG_BG2Y_ADDR                                      (HW_REG_BASE + REG_BG2Y_OFFSET)
#define reg_G2_BG2Y                                        (*( REGType32v *) REG_BG2Y_ADDR)

/* BG3PA */

#define REG_BG3PA_OFFSET                                   0x030
#define REG_BG3PA_ADDR                                     (HW_REG_BASE + REG_BG3PA_OFFSET)
#define reg_G2_BG3PA                                       (*( REGType16v *) REG_BG3PA_ADDR)

/* BG3PB */

#define REG_BG3PB_OFFSET                                   0x032
#define REG_BG3PB_ADDR                                     (HW_REG_BASE + REG_BG3PB_OFFSET)
#define reg_G2_BG3PB                                       (*( REGType16v *) REG_BG3PB_ADDR)

/* BG3PC */

#define REG_BG3PC_OFFSET                                   0x034
#define REG_BG3PC_ADDR                                     (HW_REG_BASE + REG_BG3PC_OFFSET)
#define reg_G2_BG3PC                                       (*( REGType16v *) REG_BG3PC_ADDR)

/* BG3PD */

#define REG_BG3PD_OFFSET                                   0x036
#define REG_BG3PD_ADDR                                     (HW_REG_BASE + REG_BG3PD_OFFSET)
#define reg_G2_BG3PD                                       (*( REGType16v *) REG_BG3PD_ADDR)

/* BG3X */

#define REG_BG3X_OFFSET                                    0x038
#define REG_BG3X_ADDR                                      (HW_REG_BASE + REG_BG3X_OFFSET)
#define reg_G2_BG3X                                        (*( REGType32v *) REG_BG3X_ADDR)

/* BG3Y */

#define REG_BG3Y_OFFSET                                    0x03c
#define REG_BG3Y_ADDR                                      (HW_REG_BASE + REG_BG3Y_OFFSET)
#define reg_G2_BG3Y                                        (*( REGType32v *) REG_BG3Y_ADDR)

/* WIN0H */

#define REG_WIN0H_OFFSET                                   0x040
#define REG_WIN0H_ADDR                                     (HW_REG_BASE + REG_WIN0H_OFFSET)
#define reg_G2_WIN0H                                       (*( REGType16v *) REG_WIN0H_ADDR)

/* WIN1H */

#define REG_WIN1H_OFFSET                                   0x042
#define REG_WIN1H_ADDR                                     (HW_REG_BASE + REG_WIN1H_OFFSET)
#define reg_G2_WIN1H                                       (*( REGType16v *) REG_WIN1H_ADDR)

/* WIN0V */

#define REG_WIN0V_OFFSET                                   0x044
#define REG_WIN0V_ADDR                                     (HW_REG_BASE + REG_WIN0V_OFFSET)
#define reg_G2_WIN0V                                       (*( REGType16v *) REG_WIN0V_ADDR)

/* WIN1V */

#define REG_WIN1V_OFFSET                                   0x046
#define REG_WIN1V_ADDR                                     (HW_REG_BASE + REG_WIN1V_OFFSET)
#define reg_G2_WIN1V                                       (*( REGType16v *) REG_WIN1V_ADDR)

/* WININ */

#define REG_WININ_OFFSET                                   0x048
#define REG_WININ_ADDR                                     (HW_REG_BASE + REG_WININ_OFFSET)
#define reg_G2_WININ                                       (*( REGType16v *) REG_WININ_ADDR)

/* WINOUT */

#define REG_WINOUT_OFFSET                                  0x04a
#define REG_WINOUT_ADDR                                    (HW_REG_BASE + REG_WINOUT_OFFSET)
#define reg_G2_WINOUT                                      (*( REGType16v *) REG_WINOUT_ADDR)

/* MOSAIC */

#define REG_MOSAIC_OFFSET                                  0x04c
#define REG_MOSAIC_ADDR                                    (HW_REG_BASE + REG_MOSAIC_OFFSET)
#define reg_G2_MOSAIC                                      (*( REGType16v *) REG_MOSAIC_ADDR)

/* BLDCNT */

#define REG_BLDCNT_OFFSET                                  0x050
#define REG_BLDCNT_ADDR                                    (HW_REG_BASE + REG_BLDCNT_OFFSET)
#define reg_G2_BLDCNT                                      (*( REGType16v *) REG_BLDCNT_ADDR)

/* BLDALPHA */

#define REG_BLDALPHA_OFFSET                                0x052
#define REG_BLDALPHA_ADDR                                  (HW_REG_BASE + REG_BLDALPHA_OFFSET)
#define reg_G2_BLDALPHA                                    (*( REGType16v *) REG_BLDALPHA_ADDR)

/* BLDY */

#define REG_BLDY_OFFSET                                    0x054
#define REG_BLDY_ADDR                                      (HW_REG_BASE + REG_BLDY_OFFSET)
#define reg_G2_BLDY                                        (*( REGType16v *) REG_BLDY_ADDR)


/*
 * Definitions of Register fields
 */


/* BG0CNT */

#define REG_G2_BG0CNT_SCREENSIZE_SHIFT                     14
#define REG_G2_BG0CNT_SCREENSIZE_SIZE                      2
#define REG_G2_BG0CNT_SCREENSIZE_MASK                      0xc000

#define REG_G2_BG0CNT_BGPLTTSLOT_SHIFT                     13
#define REG_G2_BG0CNT_BGPLTTSLOT_SIZE                      1
#define REG_G2_BG0CNT_BGPLTTSLOT_MASK                      0x2000

#define REG_G2_BG0CNT_SCREENBASE_SHIFT                     8
#define REG_G2_BG0CNT_SCREENBASE_SIZE                      5
#define REG_G2_BG0CNT_SCREENBASE_MASK                      0x1f00

#define REG_G2_BG0CNT_COLORMODE_SHIFT                      7
#define REG_G2_BG0CNT_COLORMODE_SIZE                       1
#define REG_G2_BG0CNT_COLORMODE_MASK                       0x0080

#define REG_G2_BG0CNT_MOSAIC_SHIFT                         6
#define REG_G2_BG0CNT_MOSAIC_SIZE                          1
#define REG_G2_BG0CNT_MOSAIC_MASK                          0x0040

#define REG_G2_BG0CNT_CHARBASE_SHIFT                       2
#define REG_G2_BG0CNT_CHARBASE_SIZE                        4
#define REG_G2_BG0CNT_CHARBASE_MASK                        0x003c

#define REG_G2_BG0CNT_PRIORITY_SHIFT                       0
#define REG_G2_BG0CNT_PRIORITY_SIZE                        2
#define REG_G2_BG0CNT_PRIORITY_MASK                        0x0003

#ifndef SDK_ASM
#define REG_G2_BG0CNT_FIELD( screensize, bgplttslot, screenbase, colormode, mosaic, charbase, priority ) \
    (u16)( \
    ((u32)(screensize) << REG_G2_BG0CNT_SCREENSIZE_SHIFT) | \
    ((u32)(bgplttslot) << REG_G2_BG0CNT_BGPLTTSLOT_SHIFT) | \
    ((u32)(screenbase) << REG_G2_BG0CNT_SCREENBASE_SHIFT) | \
    ((u32)(colormode) << REG_G2_BG0CNT_COLORMODE_SHIFT) | \
    ((u32)(mosaic) << REG_G2_BG0CNT_MOSAIC_SHIFT) | \
    ((u32)(charbase) << REG_G2_BG0CNT_CHARBASE_SHIFT) | \
    ((u32)(priority) << REG_G2_BG0CNT_PRIORITY_SHIFT))
#endif


/* BG1CNT */

#define REG_G2_BG1CNT_SCREENSIZE_SHIFT                     14
#define REG_G2_BG1CNT_SCREENSIZE_SIZE                      2
#define REG_G2_BG1CNT_SCREENSIZE_MASK                      0xc000

#define REG_G2_BG1CNT_BGPLTTSLOT_SHIFT                     13
#define REG_G2_BG1CNT_BGPLTTSLOT_SIZE                      1
#define REG_G2_BG1CNT_BGPLTTSLOT_MASK                      0x2000

#define REG_G2_BG1CNT_SCREENBASE_SHIFT                     8
#define REG_G2_BG1CNT_SCREENBASE_SIZE                      5
#define REG_G2_BG1CNT_SCREENBASE_MASK                      0x1f00

#define REG_G2_BG1CNT_COLORMODE_SHIFT                      7
#define REG_G2_BG1CNT_COLORMODE_SIZE                       1
#define REG_G2_BG1CNT_COLORMODE_MASK                       0x0080

#define REG_G2_BG1CNT_MOSAIC_SHIFT                         6
#define REG_G2_BG1CNT_MOSAIC_SIZE                          1
#define REG_G2_BG1CNT_MOSAIC_MASK                          0x0040

#define REG_G2_BG1CNT_CHARBASE_SHIFT                       2
#define REG_G2_BG1CNT_CHARBASE_SIZE                        4
#define REG_G2_BG1CNT_CHARBASE_MASK                        0x003c

#define REG_G2_BG1CNT_PRIORITY_SHIFT                       0
#define REG_G2_BG1CNT_PRIORITY_SIZE                        2
#define REG_G2_BG1CNT_PRIORITY_MASK                        0x0003

#ifndef SDK_ASM
#define REG_G2_BG1CNT_FIELD( screensize, bgplttslot, screenbase, colormode, mosaic, charbase, priority ) \
    (u16)( \
    ((u32)(screensize) << REG_G2_BG1CNT_SCREENSIZE_SHIFT) | \
    ((u32)(bgplttslot) << REG_G2_BG1CNT_BGPLTTSLOT_SHIFT) | \
    ((u32)(screenbase) << REG_G2_BG1CNT_SCREENBASE_SHIFT) | \
    ((u32)(colormode) << REG_G2_BG1CNT_COLORMODE_SHIFT) | \
    ((u32)(mosaic) << REG_G2_BG1CNT_MOSAIC_SHIFT) | \
    ((u32)(charbase) << REG_G2_BG1CNT_CHARBASE_SHIFT) | \
    ((u32)(priority) << REG_G2_BG1CNT_PRIORITY_SHIFT))
#endif


/* BG2CNT */

#define REG_G2_BG2CNT_SCREENSIZE_SHIFT                     14
#define REG_G2_BG2CNT_SCREENSIZE_SIZE                      2
#define REG_G2_BG2CNT_SCREENSIZE_MASK                      0xc000

#define REG_G2_BG2CNT_AREAOVER_SHIFT                       13
#define REG_G2_BG2CNT_AREAOVER_SIZE                        1
#define REG_G2_BG2CNT_AREAOVER_MASK                        0x2000

#define REG_G2_BG2CNT_SCREENBASE_SHIFT                     8
#define REG_G2_BG2CNT_SCREENBASE_SIZE                      5
#define REG_G2_BG2CNT_SCREENBASE_MASK                      0x1f00

#define REG_G2_BG2CNT_COLORMODE_SHIFT                      7
#define REG_G2_BG2CNT_COLORMODE_SIZE                       1
#define REG_G2_BG2CNT_COLORMODE_MASK                       0x0080

#define REG_G2_BG2CNT_MOSAIC_SHIFT                         6
#define REG_G2_BG2CNT_MOSAIC_SIZE                          1
#define REG_G2_BG2CNT_MOSAIC_MASK                          0x0040

#define REG_G2_BG2CNT_CHARBASE_SHIFT                       2
#define REG_G2_BG2CNT_CHARBASE_SIZE                        4
#define REG_G2_BG2CNT_CHARBASE_MASK                        0x003c

#define REG_G2_BG2CNT_PRIORITY_SHIFT                       0
#define REG_G2_BG2CNT_PRIORITY_SIZE                        2
#define REG_G2_BG2CNT_PRIORITY_MASK                        0x0003

#ifndef SDK_ASM
#define REG_G2_BG2CNT_FIELD( screensize, areaover, screenbase, colormode, mosaic, charbase, priority ) \
    (u16)( \
    ((u32)(screensize) << REG_G2_BG2CNT_SCREENSIZE_SHIFT) | \
    ((u32)(areaover) << REG_G2_BG2CNT_AREAOVER_SHIFT) | \
    ((u32)(screenbase) << REG_G2_BG2CNT_SCREENBASE_SHIFT) | \
    ((u32)(colormode) << REG_G2_BG2CNT_COLORMODE_SHIFT) | \
    ((u32)(mosaic) << REG_G2_BG2CNT_MOSAIC_SHIFT) | \
    ((u32)(charbase) << REG_G2_BG2CNT_CHARBASE_SHIFT) | \
    ((u32)(priority) << REG_G2_BG2CNT_PRIORITY_SHIFT))
#endif


/* BG3CNT */

#define REG_G2_BG3CNT_SCREENSIZE_SHIFT                     14
#define REG_G2_BG3CNT_SCREENSIZE_SIZE                      2
#define REG_G2_BG3CNT_SCREENSIZE_MASK                      0xc000

#define REG_G2_BG3CNT_AREAOVER_SHIFT                       13
#define REG_G2_BG3CNT_AREAOVER_SIZE                        1
#define REG_G2_BG3CNT_AREAOVER_MASK                        0x2000

#define REG_G2_BG3CNT_SCREENBASE_SHIFT                     8
#define REG_G2_BG3CNT_SCREENBASE_SIZE                      5
#define REG_G2_BG3CNT_SCREENBASE_MASK                      0x1f00

#define REG_G2_BG3CNT_COLORMODE_SHIFT                      7
#define REG_G2_BG3CNT_COLORMODE_SIZE                       1
#define REG_G2_BG3CNT_COLORMODE_MASK                       0x0080

#define REG_G2_BG3CNT_MOSAIC_SHIFT                         6
#define REG_G2_BG3CNT_MOSAIC_SIZE                          1
#define REG_G2_BG3CNT_MOSAIC_MASK                          0x0040

#define REG_G2_BG3CNT_CHARBASE_SHIFT                       2
#define REG_G2_BG3CNT_CHARBASE_SIZE                        4
#define REG_G2_BG3CNT_CHARBASE_MASK                        0x003c

#define REG_G2_BG3CNT_PRIORITY_SHIFT                       0
#define REG_G2_BG3CNT_PRIORITY_SIZE                        2
#define REG_G2_BG3CNT_PRIORITY_MASK                        0x0003

#ifndef SDK_ASM
#define REG_G2_BG3CNT_FIELD( screensize, areaover, screenbase, colormode, mosaic, charbase, priority ) \
    (u16)( \
    ((u32)(screensize) << REG_G2_BG3CNT_SCREENSIZE_SHIFT) | \
    ((u32)(areaover) << REG_G2_BG3CNT_AREAOVER_SHIFT) | \
    ((u32)(screenbase) << REG_G2_BG3CNT_SCREENBASE_SHIFT) | \
    ((u32)(colormode) << REG_G2_BG3CNT_COLORMODE_SHIFT) | \
    ((u32)(mosaic) << REG_G2_BG3CNT_MOSAIC_SHIFT) | \
    ((u32)(charbase) << REG_G2_BG3CNT_CHARBASE_SHIFT) | \
    ((u32)(priority) << REG_G2_BG3CNT_PRIORITY_SHIFT))
#endif


/* BG0OFS */

#define REG_G2_BG0OFS_VOFFSET_SHIFT                        16
#define REG_G2_BG0OFS_VOFFSET_SIZE                         9
#define REG_G2_BG0OFS_VOFFSET_MASK                         0x01ff0000

#define REG_G2_BG0OFS_HOFFSET_SHIFT                        0
#define REG_G2_BG0OFS_HOFFSET_SIZE                         9
#define REG_G2_BG0OFS_HOFFSET_MASK                         0x000001ff

#ifndef SDK_ASM
#define REG_G2_BG0OFS_FIELD( voffset, hoffset ) \
    (u32)( \
    ((u32)(voffset) << REG_G2_BG0OFS_VOFFSET_SHIFT) | \
    ((u32)(hoffset) << REG_G2_BG0OFS_HOFFSET_SHIFT))
#endif


/* BG0HOFS */

#define REG_G2_BG0HOFS_OFFSET_SHIFT                        0
#define REG_G2_BG0HOFS_OFFSET_SIZE                         9
#define REG_G2_BG0HOFS_OFFSET_MASK                         0x01ff

#ifndef SDK_ASM
#define REG_G2_BG0HOFS_FIELD( offset ) \
    (u16)( \
    ((u32)(offset) << REG_G2_BG0HOFS_OFFSET_SHIFT))
#endif


/* BG0VOFS */

#define REG_G2_BG0VOFS_OFFSET_SHIFT                        0
#define REG_G2_BG0VOFS_OFFSET_SIZE                         9
#define REG_G2_BG0VOFS_OFFSET_MASK                         0x01ff

#ifndef SDK_ASM
#define REG_G2_BG0VOFS_FIELD( offset ) \
    (u16)( \
    ((u32)(offset) << REG_G2_BG0VOFS_OFFSET_SHIFT))
#endif


/* BG1OFS */

#define REG_G2_BG1OFS_VOFFSET_SHIFT                        16
#define REG_G2_BG1OFS_VOFFSET_SIZE                         9
#define REG_G2_BG1OFS_VOFFSET_MASK                         0x01ff0000

#define REG_G2_BG1OFS_HOFFSET_SHIFT                        0
#define REG_G2_BG1OFS_HOFFSET_SIZE                         9
#define REG_G2_BG1OFS_HOFFSET_MASK                         0x000001ff

#ifndef SDK_ASM
#define REG_G2_BG1OFS_FIELD( voffset, hoffset ) \
    (u32)( \
    ((u32)(voffset) << REG_G2_BG1OFS_VOFFSET_SHIFT) | \
    ((u32)(hoffset) << REG_G2_BG1OFS_HOFFSET_SHIFT))
#endif


/* BG1HOFS */

#define REG_G2_BG1HOFS_OFFSET_SHIFT                        0
#define REG_G2_BG1HOFS_OFFSET_SIZE                         9
#define REG_G2_BG1HOFS_OFFSET_MASK                         0x01ff

#ifndef SDK_ASM
#define REG_G2_BG1HOFS_FIELD( offset ) \
    (u16)( \
    ((u32)(offset) << REG_G2_BG1HOFS_OFFSET_SHIFT))
#endif


/* BG1VOFS */

#define REG_G2_BG1VOFS_OFFSET_SHIFT                        0
#define REG_G2_BG1VOFS_OFFSET_SIZE                         9
#define REG_G2_BG1VOFS_OFFSET_MASK                         0x01ff

#ifndef SDK_ASM
#define REG_G2_BG1VOFS_FIELD( offset ) \
    (u16)( \
    ((u32)(offset) << REG_G2_BG1VOFS_OFFSET_SHIFT))
#endif


/* BG2OFS */

#define REG_G2_BG2OFS_VOFFSET_SHIFT                        16
#define REG_G2_BG2OFS_VOFFSET_SIZE                         9
#define REG_G2_BG2OFS_VOFFSET_MASK                         0x01ff0000

#define REG_G2_BG2OFS_HOFFSET_SHIFT                        0
#define REG_G2_BG2OFS_HOFFSET_SIZE                         9
#define REG_G2_BG2OFS_HOFFSET_MASK                         0x000001ff

#ifndef SDK_ASM
#define REG_G2_BG2OFS_FIELD( voffset, hoffset ) \
    (u32)( \
    ((u32)(voffset) << REG_G2_BG2OFS_VOFFSET_SHIFT) | \
    ((u32)(hoffset) << REG_G2_BG2OFS_HOFFSET_SHIFT))
#endif


/* BG2HOFS */

#define REG_G2_BG2HOFS_OFFSET_SHIFT                        0
#define REG_G2_BG2HOFS_OFFSET_SIZE                         9
#define REG_G2_BG2HOFS_OFFSET_MASK                         0x01ff

#ifndef SDK_ASM
#define REG_G2_BG2HOFS_FIELD( offset ) \
    (u16)( \
    ((u32)(offset) << REG_G2_BG2HOFS_OFFSET_SHIFT))
#endif


/* BG2VOFS */

#define REG_G2_BG2VOFS_OFFSET_SHIFT                        0
#define REG_G2_BG2VOFS_OFFSET_SIZE                         9
#define REG_G2_BG2VOFS_OFFSET_MASK                         0x01ff

#ifndef SDK_ASM
#define REG_G2_BG2VOFS_FIELD( offset ) \
    (u16)( \
    ((u32)(offset) << REG_G2_BG2VOFS_OFFSET_SHIFT))
#endif


/* BG3OFS */

#define REG_G2_BG3OFS_VOFFSET_SHIFT                        16
#define REG_G2_BG3OFS_VOFFSET_SIZE                         9
#define REG_G2_BG3OFS_VOFFSET_MASK                         0x01ff0000

#define REG_G2_BG3OFS_HOFFSET_SHIFT                        0
#define REG_G2_BG3OFS_HOFFSET_SIZE                         9
#define REG_G2_BG3OFS_HOFFSET_MASK                         0x000001ff

#ifndef SDK_ASM
#define REG_G2_BG3OFS_FIELD( voffset, hoffset ) \
    (u32)( \
    ((u32)(voffset) << REG_G2_BG3OFS_VOFFSET_SHIFT) | \
    ((u32)(hoffset) << REG_G2_BG3OFS_HOFFSET_SHIFT))
#endif


/* BG3HOFS */

#define REG_G2_BG3HOFS_OFFSET_SHIFT                        0
#define REG_G2_BG3HOFS_OFFSET_SIZE                         9
#define REG_G2_BG3HOFS_OFFSET_MASK                         0x01ff

#ifndef SDK_ASM
#define REG_G2_BG3HOFS_FIELD( offset ) \
    (u16)( \
    ((u32)(offset) << REG_G2_BG3HOFS_OFFSET_SHIFT))
#endif


/* BG3VOFS */

#define REG_G2_BG3VOFS_OFFSET_SHIFT                        0
#define REG_G2_BG3VOFS_OFFSET_SIZE                         9
#define REG_G2_BG3VOFS_OFFSET_MASK                         0x01ff

#ifndef SDK_ASM
#define REG_G2_BG3VOFS_FIELD( offset ) \
    (u16)( \
    ((u32)(offset) << REG_G2_BG3VOFS_OFFSET_SHIFT))
#endif


/* BG2PA */

#define REG_G2_BG2PA_S_SHIFT                               15
#define REG_G2_BG2PA_S_SIZE                                1
#define REG_G2_BG2PA_S_MASK                                0x8000

#define REG_G2_BG2PA_INTEGER_DX_SHIFT                      8
#define REG_G2_BG2PA_INTEGER_DX_SIZE                       7
#define REG_G2_BG2PA_INTEGER_DX_MASK                       0x7f00

#define REG_G2_BG2PA_DECIMAL_DX_SHIFT                      0
#define REG_G2_BG2PA_DECIMAL_DX_SIZE                       8
#define REG_G2_BG2PA_DECIMAL_DX_MASK                       0x00ff

#ifndef SDK_ASM
#define REG_G2_BG2PA_FIELD( s, integer_dx, decimal_dx ) \
    (u16)( \
    ((u32)(s) << REG_G2_BG2PA_S_SHIFT) | \
    ((u32)(integer_dx) << REG_G2_BG2PA_INTEGER_DX_SHIFT) | \
    ((u32)(decimal_dx) << REG_G2_BG2PA_DECIMAL_DX_SHIFT))
#endif


/* BG2PB */

#define REG_G2_BG2PB_S_SHIFT                               15
#define REG_G2_BG2PB_S_SIZE                                1
#define REG_G2_BG2PB_S_MASK                                0x8000

#define REG_G2_BG2PB_INTEGER_DMX_SHIFT                     8
#define REG_G2_BG2PB_INTEGER_DMX_SIZE                      7
#define REG_G2_BG2PB_INTEGER_DMX_MASK                      0x7f00

#define REG_G2_BG2PB_DECIMAL_DMX_SHIFT                     0
#define REG_G2_BG2PB_DECIMAL_DMX_SIZE                      8
#define REG_G2_BG2PB_DECIMAL_DMX_MASK                      0x00ff

#ifndef SDK_ASM
#define REG_G2_BG2PB_FIELD( s, integer_dmx, decimal_dmx ) \
    (u16)( \
    ((u32)(s) << REG_G2_BG2PB_S_SHIFT) | \
    ((u32)(integer_dmx) << REG_G2_BG2PB_INTEGER_DMX_SHIFT) | \
    ((u32)(decimal_dmx) << REG_G2_BG2PB_DECIMAL_DMX_SHIFT))
#endif


/* BG2PC */

#define REG_G2_BG2PC_S_SHIFT                               15
#define REG_G2_BG2PC_S_SIZE                                1
#define REG_G2_BG2PC_S_MASK                                0x8000

#define REG_G2_BG2PC_INTEGER_DY_SHIFT                      8
#define REG_G2_BG2PC_INTEGER_DY_SIZE                       7
#define REG_G2_BG2PC_INTEGER_DY_MASK                       0x7f00

#define REG_G2_BG2PC_DECIMAL_DY_SHIFT                      0
#define REG_G2_BG2PC_DECIMAL_DY_SIZE                       8
#define REG_G2_BG2PC_DECIMAL_DY_MASK                       0x00ff

#ifndef SDK_ASM
#define REG_G2_BG2PC_FIELD( s, integer_dy, decimal_dy ) \
    (u16)( \
    ((u32)(s) << REG_G2_BG2PC_S_SHIFT) | \
    ((u32)(integer_dy) << REG_G2_BG2PC_INTEGER_DY_SHIFT) | \
    ((u32)(decimal_dy) << REG_G2_BG2PC_DECIMAL_DY_SHIFT))
#endif


/* BG2PD */

#define REG_G2_BG2PD_S_SHIFT                               15
#define REG_G2_BG2PD_S_SIZE                                1
#define REG_G2_BG2PD_S_MASK                                0x8000

#define REG_G2_BG2PD_INTEGER_DMY_SHIFT                     8
#define REG_G2_BG2PD_INTEGER_DMY_SIZE                      7
#define REG_G2_BG2PD_INTEGER_DMY_MASK                      0x7f00

#define REG_G2_BG2PD_DECIMAL_DMY_SHIFT                     0
#define REG_G2_BG2PD_DECIMAL_DMY_SIZE                      8
#define REG_G2_BG2PD_DECIMAL_DMY_MASK                      0x00ff

#ifndef SDK_ASM
#define REG_G2_BG2PD_FIELD( s, integer_dmy, decimal_dmy ) \
    (u16)( \
    ((u32)(s) << REG_G2_BG2PD_S_SHIFT) | \
    ((u32)(integer_dmy) << REG_G2_BG2PD_INTEGER_DMY_SHIFT) | \
    ((u32)(decimal_dmy) << REG_G2_BG2PD_DECIMAL_DMY_SHIFT))
#endif


/* BG2X */

#define REG_G2_BG2X_S_SHIFT                                27
#define REG_G2_BG2X_S_SIZE                                 1
#define REG_G2_BG2X_S_MASK                                 0x08000000

#define REG_G2_BG2X_INTEGER_SX_SHIFT                       8
#define REG_G2_BG2X_INTEGER_SX_SIZE                        19
#define REG_G2_BG2X_INTEGER_SX_MASK                        0x07ffff00

#define REG_G2_BG2X_DECIMAL_SX_SHIFT                       0
#define REG_G2_BG2X_DECIMAL_SX_SIZE                        8
#define REG_G2_BG2X_DECIMAL_SX_MASK                        0x000000ff

#ifndef SDK_ASM
#define REG_G2_BG2X_FIELD( s, integer_sx, decimal_sx ) \
    (u32)( \
    ((u32)(s) << REG_G2_BG2X_S_SHIFT) | \
    ((u32)(integer_sx) << REG_G2_BG2X_INTEGER_SX_SHIFT) | \
    ((u32)(decimal_sx) << REG_G2_BG2X_DECIMAL_SX_SHIFT))
#endif


/* BG2Y */

#define REG_G2_BG2Y_S_SHIFT                                27
#define REG_G2_BG2Y_S_SIZE                                 1
#define REG_G2_BG2Y_S_MASK                                 0x08000000

#define REG_G2_BG2Y_INTEGER_SY_SHIFT                       8
#define REG_G2_BG2Y_INTEGER_SY_SIZE                        19
#define REG_G2_BG2Y_INTEGER_SY_MASK                        0x07ffff00

#define REG_G2_BG2Y_DECIMAL_SY_SHIFT                       0
#define REG_G2_BG2Y_DECIMAL_SY_SIZE                        8
#define REG_G2_BG2Y_DECIMAL_SY_MASK                        0x000000ff

#ifndef SDK_ASM
#define REG_G2_BG2Y_FIELD( s, integer_sy, decimal_sy ) \
    (u32)( \
    ((u32)(s) << REG_G2_BG2Y_S_SHIFT) | \
    ((u32)(integer_sy) << REG_G2_BG2Y_INTEGER_SY_SHIFT) | \
    ((u32)(decimal_sy) << REG_G2_BG2Y_DECIMAL_SY_SHIFT))
#endif


/* BG3PA */

#define REG_G2_BG3PA_S_SHIFT                               15
#define REG_G2_BG3PA_S_SIZE                                1
#define REG_G2_BG3PA_S_MASK                                0x8000

#define REG_G2_BG3PA_INTEGER_DX_SHIFT                      8
#define REG_G2_BG3PA_INTEGER_DX_SIZE                       7
#define REG_G2_BG3PA_INTEGER_DX_MASK                       0x7f00

#define REG_G2_BG3PA_DECIMAL_DX_SHIFT                      0
#define REG_G2_BG3PA_DECIMAL_DX_SIZE                       8
#define REG_G2_BG3PA_DECIMAL_DX_MASK                       0x00ff

#ifndef SDK_ASM
#define REG_G2_BG3PA_FIELD( s, integer_dx, decimal_dx ) \
    (u16)( \
    ((u32)(s) << REG_G2_BG3PA_S_SHIFT) | \
    ((u32)(integer_dx) << REG_G2_BG3PA_INTEGER_DX_SHIFT) | \
    ((u32)(decimal_dx) << REG_G2_BG3PA_DECIMAL_DX_SHIFT))
#endif


/* BG3PB */

#define REG_G2_BG3PB_S_SHIFT                               15
#define REG_G2_BG3PB_S_SIZE                                1
#define REG_G2_BG3PB_S_MASK                                0x8000

#define REG_G2_BG3PB_INTEGER_DMX_SHIFT                     8
#define REG_G2_BG3PB_INTEGER_DMX_SIZE                      7
#define REG_G2_BG3PB_INTEGER_DMX_MASK                      0x7f00

#define REG_G2_BG3PB_DECIMAL_DMX_SHIFT                     0
#define REG_G2_BG3PB_DECIMAL_DMX_SIZE                      8
#define REG_G2_BG3PB_DECIMAL_DMX_MASK                      0x00ff

#ifndef SDK_ASM
#define REG_G2_BG3PB_FIELD( s, integer_dmx, decimal_dmx ) \
    (u16)( \
    ((u32)(s) << REG_G2_BG3PB_S_SHIFT) | \
    ((u32)(integer_dmx) << REG_G2_BG3PB_INTEGER_DMX_SHIFT) | \
    ((u32)(decimal_dmx) << REG_G2_BG3PB_DECIMAL_DMX_SHIFT))
#endif


/* BG3PC */

#define REG_G2_BG3PC_S_SHIFT                               15
#define REG_G2_BG3PC_S_SIZE                                1
#define REG_G2_BG3PC_S_MASK                                0x8000

#define REG_G2_BG3PC_INTEGER_DY_SHIFT                      8
#define REG_G2_BG3PC_INTEGER_DY_SIZE                       7
#define REG_G2_BG3PC_INTEGER_DY_MASK                       0x7f00

#define REG_G2_BG3PC_DECIMAL_DY_SHIFT                      0
#define REG_G2_BG3PC_DECIMAL_DY_SIZE                       8
#define REG_G2_BG3PC_DECIMAL_DY_MASK                       0x00ff

#ifndef SDK_ASM
#define REG_G2_BG3PC_FIELD( s, integer_dy, decimal_dy ) \
    (u16)( \
    ((u32)(s) << REG_G2_BG3PC_S_SHIFT) | \
    ((u32)(integer_dy) << REG_G2_BG3PC_INTEGER_DY_SHIFT) | \
    ((u32)(decimal_dy) << REG_G2_BG3PC_DECIMAL_DY_SHIFT))
#endif


/* BG3PD */

#define REG_G2_BG3PD_S_SHIFT                               15
#define REG_G2_BG3PD_S_SIZE                                1
#define REG_G2_BG3PD_S_MASK                                0x8000

#define REG_G2_BG3PD_INTEGER_DMY_SHIFT                     8
#define REG_G2_BG3PD_INTEGER_DMY_SIZE                      7
#define REG_G2_BG3PD_INTEGER_DMY_MASK                      0x7f00

#define REG_G2_BG3PD_DECIMAL_DMY_SHIFT                     0
#define REG_G2_BG3PD_DECIMAL_DMY_SIZE                      8
#define REG_G2_BG3PD_DECIMAL_DMY_MASK                      0x00ff

#ifndef SDK_ASM
#define REG_G2_BG3PD_FIELD( s, integer_dmy, decimal_dmy ) \
    (u16)( \
    ((u32)(s) << REG_G2_BG3PD_S_SHIFT) | \
    ((u32)(integer_dmy) << REG_G2_BG3PD_INTEGER_DMY_SHIFT) | \
    ((u32)(decimal_dmy) << REG_G2_BG3PD_DECIMAL_DMY_SHIFT))
#endif


/* BG3X */

#define REG_G2_BG3X_S_SHIFT                                27
#define REG_G2_BG3X_S_SIZE                                 1
#define REG_G2_BG3X_S_MASK                                 0x08000000

#define REG_G2_BG3X_INTEGER_SX_SHIFT                       8
#define REG_G2_BG3X_INTEGER_SX_SIZE                        19
#define REG_G2_BG3X_INTEGER_SX_MASK                        0x07ffff00

#define REG_G2_BG3X_DECIMAL_SX_SHIFT                       0
#define REG_G2_BG3X_DECIMAL_SX_SIZE                        8
#define REG_G2_BG3X_DECIMAL_SX_MASK                        0x000000ff

#ifndef SDK_ASM
#define REG_G2_BG3X_FIELD( s, integer_sx, decimal_sx ) \
    (u32)( \
    ((u32)(s) << REG_G2_BG3X_S_SHIFT) | \
    ((u32)(integer_sx) << REG_G2_BG3X_INTEGER_SX_SHIFT) | \
    ((u32)(decimal_sx) << REG_G2_BG3X_DECIMAL_SX_SHIFT))
#endif


/* BG3Y */

#define REG_G2_BG3Y_S_SHIFT                                27
#define REG_G2_BG3Y_S_SIZE                                 1
#define REG_G2_BG3Y_S_MASK                                 0x08000000

#define REG_G2_BG3Y_INTEGER_SY_SHIFT                       8
#define REG_G2_BG3Y_INTEGER_SY_SIZE                        19
#define REG_G2_BG3Y_INTEGER_SY_MASK                        0x07ffff00

#define REG_G2_BG3Y_DECIMAL_SY_SHIFT                       0
#define REG_G2_BG3Y_DECIMAL_SY_SIZE                        8
#define REG_G2_BG3Y_DECIMAL_SY_MASK                        0x000000ff

#ifndef SDK_ASM
#define REG_G2_BG3Y_FIELD( s, integer_sy, decimal_sy ) \
    (u32)( \
    ((u32)(s) << REG_G2_BG3Y_S_SHIFT) | \
    ((u32)(integer_sy) << REG_G2_BG3Y_INTEGER_SY_SHIFT) | \
    ((u32)(decimal_sy) << REG_G2_BG3Y_DECIMAL_SY_SHIFT))
#endif


/* WIN0H */

#define REG_G2_WIN0H_LEFTX_SHIFT                           8
#define REG_G2_WIN0H_LEFTX_SIZE                            8
#define REG_G2_WIN0H_LEFTX_MASK                            0xff00

#define REG_G2_WIN0H_RIGHTX_SHIFT                          0
#define REG_G2_WIN0H_RIGHTX_SIZE                           8
#define REG_G2_WIN0H_RIGHTX_MASK                           0x00ff

#ifndef SDK_ASM
#define REG_G2_WIN0H_FIELD( leftx, rightx ) \
    (u16)( \
    ((u32)(leftx) << REG_G2_WIN0H_LEFTX_SHIFT) | \
    ((u32)(rightx) << REG_G2_WIN0H_RIGHTX_SHIFT))
#endif


/* WIN1H */

#define REG_G2_WIN1H_LEFTX_SHIFT                           8
#define REG_G2_WIN1H_LEFTX_SIZE                            8
#define REG_G2_WIN1H_LEFTX_MASK                            0xff00

#define REG_G2_WIN1H_RIGHTX_SHIFT                          0
#define REG_G2_WIN1H_RIGHTX_SIZE                           8
#define REG_G2_WIN1H_RIGHTX_MASK                           0x00ff

#ifndef SDK_ASM
#define REG_G2_WIN1H_FIELD( leftx, rightx ) \
    (u16)( \
    ((u32)(leftx) << REG_G2_WIN1H_LEFTX_SHIFT) | \
    ((u32)(rightx) << REG_G2_WIN1H_RIGHTX_SHIFT))
#endif


/* WIN0V */

#define REG_G2_WIN0V_UPY_SHIFT                             8
#define REG_G2_WIN0V_UPY_SIZE                              8
#define REG_G2_WIN0V_UPY_MASK                              0xff00

#define REG_G2_WIN0V_DOWNY_SHIFT                           0
#define REG_G2_WIN0V_DOWNY_SIZE                            8
#define REG_G2_WIN0V_DOWNY_MASK                            0x00ff

#ifndef SDK_ASM
#define REG_G2_WIN0V_FIELD( upy, downy ) \
    (u16)( \
    ((u32)(upy) << REG_G2_WIN0V_UPY_SHIFT) | \
    ((u32)(downy) << REG_G2_WIN0V_DOWNY_SHIFT))
#endif


/* WIN1V */

#define REG_G2_WIN1V_UPY_SHIFT                             8
#define REG_G2_WIN1V_UPY_SIZE                              8
#define REG_G2_WIN1V_UPY_MASK                              0xff00

#define REG_G2_WIN1V_DOWNY_SHIFT                           0
#define REG_G2_WIN1V_DOWNY_SIZE                            8
#define REG_G2_WIN1V_DOWNY_MASK                            0x00ff

#ifndef SDK_ASM
#define REG_G2_WIN1V_FIELD( upy, downy ) \
    (u16)( \
    ((u32)(upy) << REG_G2_WIN1V_UPY_SHIFT) | \
    ((u32)(downy) << REG_G2_WIN1V_DOWNY_SHIFT))
#endif


/* WININ */

#define REG_G2_WININ_WIN1IN_SHIFT                          8
#define REG_G2_WININ_WIN1IN_SIZE                           6
#define REG_G2_WININ_WIN1IN_MASK                           0x3f00

#define REG_G2_WININ_WIN0IN_SHIFT                          0
#define REG_G2_WININ_WIN0IN_SIZE                           6
#define REG_G2_WININ_WIN0IN_MASK                           0x003f

#ifndef SDK_ASM
#define REG_G2_WININ_FIELD( win1in, win0in ) \
    (u16)( \
    ((u32)(win1in) << REG_G2_WININ_WIN1IN_SHIFT) | \
    ((u32)(win0in) << REG_G2_WININ_WIN0IN_SHIFT))
#endif


/* WINOUT */

#define REG_G2_WINOUT_OBJWININ_SHIFT                       8
#define REG_G2_WINOUT_OBJWININ_SIZE                        6
#define REG_G2_WINOUT_OBJWININ_MASK                        0x3f00

#define REG_G2_WINOUT_WINOUT_SHIFT                         0
#define REG_G2_WINOUT_WINOUT_SIZE                          6
#define REG_G2_WINOUT_WINOUT_MASK                          0x003f

#ifndef SDK_ASM
#define REG_G2_WINOUT_FIELD( objwinin, winout ) \
    (u16)( \
    ((u32)(objwinin) << REG_G2_WINOUT_OBJWININ_SHIFT) | \
    ((u32)(winout) << REG_G2_WINOUT_WINOUT_SHIFT))
#endif


/* MOSAIC */

#define REG_G2_MOSAIC_OBJVSIZE_SHIFT                       12
#define REG_G2_MOSAIC_OBJVSIZE_SIZE                        4
#define REG_G2_MOSAIC_OBJVSIZE_MASK                        0xf000

#define REG_G2_MOSAIC_OBJHSIZE_SHIFT                       8
#define REG_G2_MOSAIC_OBJHSIZE_SIZE                        4
#define REG_G2_MOSAIC_OBJHSIZE_MASK                        0x0f00

#define REG_G2_MOSAIC_BGVSIZE_SHIFT                        4
#define REG_G2_MOSAIC_BGVSIZE_SIZE                         4
#define REG_G2_MOSAIC_BGVSIZE_MASK                         0x00f0

#define REG_G2_MOSAIC_BGHSIZE_SHIFT                        0
#define REG_G2_MOSAIC_BGHSIZE_SIZE                         4
#define REG_G2_MOSAIC_BGHSIZE_MASK                         0x000f

#ifndef SDK_ASM
#define REG_G2_MOSAIC_FIELD( objvsize, objhsize, bgvsize, bghsize ) \
    (u16)( \
    ((u32)(objvsize) << REG_G2_MOSAIC_OBJVSIZE_SHIFT) | \
    ((u32)(objhsize) << REG_G2_MOSAIC_OBJHSIZE_SHIFT) | \
    ((u32)(bgvsize) << REG_G2_MOSAIC_BGVSIZE_SHIFT) | \
    ((u32)(bghsize) << REG_G2_MOSAIC_BGHSIZE_SHIFT))
#endif


/* BLDCNT */

#define REG_G2_BLDCNT_PLANE2_SHIFT                         8
#define REG_G2_BLDCNT_PLANE2_SIZE                          6
#define REG_G2_BLDCNT_PLANE2_MASK                          0x3f00

#define REG_G2_BLDCNT_EFFECT_SHIFT                         6
#define REG_G2_BLDCNT_EFFECT_SIZE                          2
#define REG_G2_BLDCNT_EFFECT_MASK                          0x00c0

#define REG_G2_BLDCNT_PLANE1_SHIFT                         0
#define REG_G2_BLDCNT_PLANE1_SIZE                          6
#define REG_G2_BLDCNT_PLANE1_MASK                          0x003f

#ifndef SDK_ASM
#define REG_G2_BLDCNT_FIELD( plane2, effect, plane1 ) \
    (u16)( \
    ((u32)(plane2) << REG_G2_BLDCNT_PLANE2_SHIFT) | \
    ((u32)(effect) << REG_G2_BLDCNT_EFFECT_SHIFT) | \
    ((u32)(plane1) << REG_G2_BLDCNT_PLANE1_SHIFT))
#endif


/* BLDALPHA */

#define REG_G2_BLDALPHA_EVB_SHIFT                          8
#define REG_G2_BLDALPHA_EVB_SIZE                           5
#define REG_G2_BLDALPHA_EVB_MASK                           0x1f00

#define REG_G2_BLDALPHA_EVA_SHIFT                          0
#define REG_G2_BLDALPHA_EVA_SIZE                           5
#define REG_G2_BLDALPHA_EVA_MASK                           0x001f

#ifndef SDK_ASM
#define REG_G2_BLDALPHA_FIELD( evb, eva ) \
    (u16)( \
    ((u32)(evb) << REG_G2_BLDALPHA_EVB_SHIFT) | \
    ((u32)(eva) << REG_G2_BLDALPHA_EVA_SHIFT))
#endif


/* BLDY */

#define REG_G2_BLDY_EVY_SHIFT                              0
#define REG_G2_BLDY_EVY_SIZE                               5
#define REG_G2_BLDY_EVY_MASK                               0x001f

#ifndef SDK_ASM
#define REG_G2_BLDY_FIELD( evy ) \
    (u16)( \
    ((u32)(evy) << REG_G2_BLDY_EVY_SHIFT))
#endif


#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_HW_ARM9_IOREG_G2_H_ */
#endif
