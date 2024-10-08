/*---------------------------------------------------------------------------*
  Project:  NitroSDK - IO Register List - 
  File:     nitro/hw/ARM9/ioreg_GX.h

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
#ifndef NITRO_HW_ARM9_IOREG_GX_H_
#define NITRO_HW_ARM9_IOREG_GX_H_

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


/* DISPCNT */

#define REG_DISPCNT_OFFSET                                 0x000
#define REG_DISPCNT_ADDR                                   (HW_REG_BASE + REG_DISPCNT_OFFSET)
#define reg_GX_DISPCNT                                     (*( REGType32v *) REG_DISPCNT_ADDR)

/* DISPSTAT */

#define REG_DISPSTAT_OFFSET                                0x004
#define REG_DISPSTAT_ADDR                                  (HW_REG_BASE + REG_DISPSTAT_OFFSET)
#define reg_GX_DISPSTAT                                    (*( REGType16v *) REG_DISPSTAT_ADDR)

/* VCOUNT */

#define REG_VCOUNT_OFFSET                                  0x006
#define REG_VCOUNT_ADDR                                    (HW_REG_BASE + REG_VCOUNT_OFFSET)
#define reg_GX_VCOUNT                                      (*( REGType16v *) REG_VCOUNT_ADDR)

/* DISPCAPCNT */

#define REG_DISPCAPCNT_OFFSET                              0x064
#define REG_DISPCAPCNT_ADDR                                (HW_REG_BASE + REG_DISPCAPCNT_OFFSET)
#define reg_GX_DISPCAPCNT                                  (*( REGType32v *) REG_DISPCAPCNT_ADDR)

/* DISP_MMEM_FIFO */

#define REG_DISP_MMEM_FIFO_OFFSET                          0x068
#define REG_DISP_MMEM_FIFO_ADDR                            (HW_REG_BASE + REG_DISP_MMEM_FIFO_OFFSET)
#define reg_GX_DISP_MMEM_FIFO                              (*( REGType32v *) REG_DISP_MMEM_FIFO_ADDR)

/* DISP_MMEM_FIFO_L */

#define REG_DISP_MMEM_FIFO_L_OFFSET                        0x068
#define REG_DISP_MMEM_FIFO_L_ADDR                          (HW_REG_BASE + REG_DISP_MMEM_FIFO_L_OFFSET)
#define reg_GX_DISP_MMEM_FIFO_L                            (*( REGType16v *) REG_DISP_MMEM_FIFO_L_ADDR)

/* DISP_MMEM_FIFO_H */

#define REG_DISP_MMEM_FIFO_H_OFFSET                        0x06a
#define REG_DISP_MMEM_FIFO_H_ADDR                          (HW_REG_BASE + REG_DISP_MMEM_FIFO_H_OFFSET)
#define reg_GX_DISP_MMEM_FIFO_H                            (*( REGType16v *) REG_DISP_MMEM_FIFO_H_ADDR)

/* MASTER_BRIGHT */

#define REG_MASTER_BRIGHT_OFFSET                           0x06c
#define REG_MASTER_BRIGHT_ADDR                             (HW_REG_BASE + REG_MASTER_BRIGHT_OFFSET)
#define reg_GX_MASTER_BRIGHT                               (*( REGType16v *) REG_MASTER_BRIGHT_ADDR)

/* TVOUTCNT */

#define REG_TVOUTCNT_OFFSET                                0x070
#define REG_TVOUTCNT_ADDR                                  (HW_REG_BASE + REG_TVOUTCNT_OFFSET)
#define reg_GX_TVOUTCNT                                    (*( REGType16v *) REG_TVOUTCNT_ADDR)

/* VRAMCNT */

#define REG_VRAMCNT_OFFSET                                 0x240
#define REG_VRAMCNT_ADDR                                   (HW_REG_BASE + REG_VRAMCNT_OFFSET)
#define reg_GX_VRAMCNT                                     (*( REGType32v *) REG_VRAMCNT_ADDR)

/* VRAMCNT_A */

#define REG_VRAMCNT_A_OFFSET                               0x240
#define REG_VRAMCNT_A_ADDR                                 (HW_REG_BASE + REG_VRAMCNT_A_OFFSET)
#define reg_GX_VRAMCNT_A                                   (*( REGType8v *) REG_VRAMCNT_A_ADDR)

/* VRAMCNT_B */

#define REG_VRAMCNT_B_OFFSET                               0x241
#define REG_VRAMCNT_B_ADDR                                 (HW_REG_BASE + REG_VRAMCNT_B_OFFSET)
#define reg_GX_VRAMCNT_B                                   (*( REGType8v *) REG_VRAMCNT_B_ADDR)

/* VRAMCNT_C */

#define REG_VRAMCNT_C_OFFSET                               0x242
#define REG_VRAMCNT_C_ADDR                                 (HW_REG_BASE + REG_VRAMCNT_C_OFFSET)
#define reg_GX_VRAMCNT_C                                   (*( REGType8v *) REG_VRAMCNT_C_ADDR)

/* VRAMCNT_D */

#define REG_VRAMCNT_D_OFFSET                               0x243
#define REG_VRAMCNT_D_ADDR                                 (HW_REG_BASE + REG_VRAMCNT_D_OFFSET)
#define reg_GX_VRAMCNT_D                                   (*( REGType8v *) REG_VRAMCNT_D_ADDR)

/* WVRAMCNT */

#define REG_WVRAMCNT_OFFSET                                0x244
#define REG_WVRAMCNT_ADDR                                  (HW_REG_BASE + REG_WVRAMCNT_OFFSET)
#define reg_GX_WVRAMCNT                                    (*( REGType32v *) REG_WVRAMCNT_ADDR)

/* VRAMCNT_E */

#define REG_VRAMCNT_E_OFFSET                               0x244
#define REG_VRAMCNT_E_ADDR                                 (HW_REG_BASE + REG_VRAMCNT_E_OFFSET)
#define reg_GX_VRAMCNT_E                                   (*( REGType8v *) REG_VRAMCNT_E_ADDR)

/* VRAMCNT_F */

#define REG_VRAMCNT_F_OFFSET                               0x245
#define REG_VRAMCNT_F_ADDR                                 (HW_REG_BASE + REG_VRAMCNT_F_OFFSET)
#define reg_GX_VRAMCNT_F                                   (*( REGType8v *) REG_VRAMCNT_F_ADDR)

/* VRAMCNT_G */

#define REG_VRAMCNT_G_OFFSET                               0x246
#define REG_VRAMCNT_G_ADDR                                 (HW_REG_BASE + REG_VRAMCNT_G_OFFSET)
#define reg_GX_VRAMCNT_G                                   (*( REGType8v *) REG_VRAMCNT_G_ADDR)

/* VRAMCNT_WRAM */

#define REG_VRAMCNT_WRAM_OFFSET                            0x247
#define REG_VRAMCNT_WRAM_ADDR                              (HW_REG_BASE + REG_VRAMCNT_WRAM_OFFSET)
#define reg_GX_VRAMCNT_WRAM                                (*( REGType8v *) REG_VRAMCNT_WRAM_ADDR)

/* VRAM_HI_CNT */

#define REG_VRAM_HI_CNT_OFFSET                             0x248
#define REG_VRAM_HI_CNT_ADDR                               (HW_REG_BASE + REG_VRAM_HI_CNT_OFFSET)
#define reg_GX_VRAM_HI_CNT                                 (*( REGType16v *) REG_VRAM_HI_CNT_ADDR)

/* VRAMCNT_H */

#define REG_VRAMCNT_H_OFFSET                               0x248
#define REG_VRAMCNT_H_ADDR                                 (HW_REG_BASE + REG_VRAMCNT_H_OFFSET)
#define reg_GX_VRAMCNT_H                                   (*( REGType8v *) REG_VRAMCNT_H_ADDR)

/* VRAMCNT_I */

#define REG_VRAMCNT_I_OFFSET                               0x249
#define REG_VRAMCNT_I_ADDR                                 (HW_REG_BASE + REG_VRAMCNT_I_OFFSET)
#define reg_GX_VRAMCNT_I                                   (*( REGType8v *) REG_VRAMCNT_I_ADDR)

/* POWCNT */

#define REG_POWCNT_OFFSET                                  0x304
#define REG_POWCNT_ADDR                                    (HW_REG_BASE + REG_POWCNT_OFFSET)
#define reg_GX_POWCNT                                      (*( REGType16v *) REG_POWCNT_ADDR)


/*
 * Definitions of Register fields
 */


/* DISPCNT */

#define REG_GX_DISPCNT_O_SHIFT                             31
#define REG_GX_DISPCNT_O_SIZE                              1
#define REG_GX_DISPCNT_O_MASK                              0x80000000

#define REG_GX_DISPCNT_BG_SHIFT                            30
#define REG_GX_DISPCNT_BG_SIZE                             1
#define REG_GX_DISPCNT_BG_MASK                             0x40000000

#define REG_GX_DISPCNT_BGSCREENOFFSET_SHIFT                27
#define REG_GX_DISPCNT_BGSCREENOFFSET_SIZE                 3
#define REG_GX_DISPCNT_BGSCREENOFFSET_MASK                 0x38000000

#define REG_GX_DISPCNT_BGCHAROFFSET_SHIFT                  24
#define REG_GX_DISPCNT_BGCHAROFFSET_SIZE                   3
#define REG_GX_DISPCNT_BGCHAROFFSET_MASK                   0x07000000

#define REG_GX_DISPCNT_OH_SHIFT                            23
#define REG_GX_DISPCNT_OH_SIZE                             1
#define REG_GX_DISPCNT_OH_MASK                             0x00800000

#define REG_GX_DISPCNT_EXOBJ_SHIFT                         20
#define REG_GX_DISPCNT_EXOBJ_SIZE                          3
#define REG_GX_DISPCNT_EXOBJ_MASK                          0x00700000

#define REG_GX_DISPCNT_VRAM_SHIFT                          18
#define REG_GX_DISPCNT_VRAM_SIZE                           2
#define REG_GX_DISPCNT_VRAM_MASK                           0x000c0000

#define REG_GX_DISPCNT_MODE_SHIFT                          16
#define REG_GX_DISPCNT_MODE_SIZE                           2
#define REG_GX_DISPCNT_MODE_MASK                           0x00030000

#define REG_GX_DISPCNT_OW_SHIFT                            15
#define REG_GX_DISPCNT_OW_SIZE                             1
#define REG_GX_DISPCNT_OW_MASK                             0x00008000

#define REG_GX_DISPCNT_W1_SHIFT                            14
#define REG_GX_DISPCNT_W1_SIZE                             1
#define REG_GX_DISPCNT_W1_MASK                             0x00004000

#define REG_GX_DISPCNT_W0_SHIFT                            13
#define REG_GX_DISPCNT_W0_SIZE                             1
#define REG_GX_DISPCNT_W0_MASK                             0x00002000

#define REG_GX_DISPCNT_DISPLAY_SHIFT                       8
#define REG_GX_DISPCNT_DISPLAY_SIZE                        5
#define REG_GX_DISPCNT_DISPLAY_MASK                        0x00001f00

#define REG_GX_DISPCNT_BLANK_SHIFT                         7
#define REG_GX_DISPCNT_BLANK_SIZE                          1
#define REG_GX_DISPCNT_BLANK_MASK                          0x00000080

#define REG_GX_DISPCNT_OBJMAP_SHIFT                        4
#define REG_GX_DISPCNT_OBJMAP_SIZE                         3
#define REG_GX_DISPCNT_OBJMAP_MASK                         0x00000070

#define REG_GX_DISPCNT_BG02D3D_SHIFT                       3
#define REG_GX_DISPCNT_BG02D3D_SIZE                        1
#define REG_GX_DISPCNT_BG02D3D_MASK                        0x00000008

#define REG_GX_DISPCNT_BGMODE_SHIFT                        0
#define REG_GX_DISPCNT_BGMODE_SIZE                         3
#define REG_GX_DISPCNT_BGMODE_MASK                         0x00000007

#define REG_GX_DISPCNT_OBJMAP_CH_SHIFT                     4
#define REG_GX_DISPCNT_OBJMAP_CH_SIZE                      1
#define REG_GX_DISPCNT_OBJMAP_CH_MASK                      0x00000010

#define REG_GX_DISPCNT_OBJMAP_BM_SHIFT                     5
#define REG_GX_DISPCNT_OBJMAP_BM_SIZE                      2
#define REG_GX_DISPCNT_OBJMAP_BM_MASK                      0x00000060

#define REG_GX_DISPCNT_EXOBJ_CH_SHIFT                      20
#define REG_GX_DISPCNT_EXOBJ_CH_SIZE                       2
#define REG_GX_DISPCNT_EXOBJ_CH_MASK                       0x00300000

#define REG_GX_DISPCNT_EXOBJ_BM_SHIFT                      22
#define REG_GX_DISPCNT_EXOBJ_BM_SIZE                       1
#define REG_GX_DISPCNT_EXOBJ_BM_MASK                       0x00400000

#ifndef SDK_ASM
#define REG_GX_DISPCNT_FIELD( o, bg, bgscreenoffset, bgcharoffset, oh, exobj, vram, mode, ow, w1, w0, display, blank, objmap, bg02d3d, bgmode, objmap_ch, objmap_bm, exobj_ch, exobj_bm ) \
    (u32)( \
    ((u32)(o) << REG_GX_DISPCNT_O_SHIFT) | \
    ((u32)(bg) << REG_GX_DISPCNT_BG_SHIFT) | \
    ((u32)(bgscreenoffset) << REG_GX_DISPCNT_BGSCREENOFFSET_SHIFT) | \
    ((u32)(bgcharoffset) << REG_GX_DISPCNT_BGCHAROFFSET_SHIFT) | \
    ((u32)(oh) << REG_GX_DISPCNT_OH_SHIFT) | \
    ((u32)(exobj) << REG_GX_DISPCNT_EXOBJ_SHIFT) | \
    ((u32)(vram) << REG_GX_DISPCNT_VRAM_SHIFT) | \
    ((u32)(mode) << REG_GX_DISPCNT_MODE_SHIFT) | \
    ((u32)(ow) << REG_GX_DISPCNT_OW_SHIFT) | \
    ((u32)(w1) << REG_GX_DISPCNT_W1_SHIFT) | \
    ((u32)(w0) << REG_GX_DISPCNT_W0_SHIFT) | \
    ((u32)(display) << REG_GX_DISPCNT_DISPLAY_SHIFT) | \
    ((u32)(blank) << REG_GX_DISPCNT_BLANK_SHIFT) | \
    ((u32)(objmap) << REG_GX_DISPCNT_OBJMAP_SHIFT) | \
    ((u32)(bg02d3d) << REG_GX_DISPCNT_BG02D3D_SHIFT) | \
    ((u32)(bgmode) << REG_GX_DISPCNT_BGMODE_SHIFT) | \
    ((u32)(objmap_ch) << REG_GX_DISPCNT_OBJMAP_CH_SHIFT) | \
    ((u32)(objmap_bm) << REG_GX_DISPCNT_OBJMAP_BM_SHIFT) | \
    ((u32)(exobj_ch) << REG_GX_DISPCNT_EXOBJ_CH_SHIFT) | \
    ((u32)(exobj_bm) << REG_GX_DISPCNT_EXOBJ_BM_SHIFT))
#endif


/* DISPSTAT */

#define REG_GX_DISPSTAT_VCOUNTER_SHIFT                     7
#define REG_GX_DISPSTAT_VCOUNTER_SIZE                      9
#define REG_GX_DISPSTAT_VCOUNTER_MASK                      0xff80

#define REG_GX_DISPSTAT_VQI_SHIFT                          5
#define REG_GX_DISPSTAT_VQI_SIZE                           1
#define REG_GX_DISPSTAT_VQI_MASK                           0x0020

#define REG_GX_DISPSTAT_HBI_SHIFT                          4
#define REG_GX_DISPSTAT_HBI_SIZE                           1
#define REG_GX_DISPSTAT_HBI_MASK                           0x0010

#define REG_GX_DISPSTAT_VBI_SHIFT                          3
#define REG_GX_DISPSTAT_VBI_SIZE                           1
#define REG_GX_DISPSTAT_VBI_MASK                           0x0008

#define REG_GX_DISPSTAT_LYC_SHIFT                          2
#define REG_GX_DISPSTAT_LYC_SIZE                           1
#define REG_GX_DISPSTAT_LYC_MASK                           0x0004

#define REG_GX_DISPSTAT_HBLK_SHIFT                         1
#define REG_GX_DISPSTAT_HBLK_SIZE                          1
#define REG_GX_DISPSTAT_HBLK_MASK                          0x0002

#define REG_GX_DISPSTAT_VBLK_SHIFT                         0
#define REG_GX_DISPSTAT_VBLK_SIZE                          1
#define REG_GX_DISPSTAT_VBLK_MASK                          0x0001

#ifndef SDK_ASM
#define REG_GX_DISPSTAT_FIELD( vcounter, vqi, hbi, vbi, lyc, hblk, vblk ) \
    (u16)( \
    ((u32)(vcounter) << REG_GX_DISPSTAT_VCOUNTER_SHIFT) | \
    ((u32)(vqi) << REG_GX_DISPSTAT_VQI_SHIFT) | \
    ((u32)(hbi) << REG_GX_DISPSTAT_HBI_SHIFT) | \
    ((u32)(vbi) << REG_GX_DISPSTAT_VBI_SHIFT) | \
    ((u32)(lyc) << REG_GX_DISPSTAT_LYC_SHIFT) | \
    ((u32)(hblk) << REG_GX_DISPSTAT_HBLK_SHIFT) | \
    ((u32)(vblk) << REG_GX_DISPSTAT_VBLK_SHIFT))
#endif


/* VCOUNT */

#define REG_GX_VCOUNT_VCOUNTER_SHIFT                       0
#define REG_GX_VCOUNT_VCOUNTER_SIZE                        9
#define REG_GX_VCOUNT_VCOUNTER_MASK                        0x01ff

#ifndef SDK_ASM
#define REG_GX_VCOUNT_FIELD( vcounter ) \
    (u16)( \
    ((u32)(vcounter) << REG_GX_VCOUNT_VCOUNTER_SHIFT))
#endif


/* DISPCAPCNT */

#define REG_GX_DISPCAPCNT_E_SHIFT                          31
#define REG_GX_DISPCAPCNT_E_SIZE                           1
#define REG_GX_DISPCAPCNT_E_MASK                           0x80000000

#define REG_GX_DISPCAPCNT_MOD_SHIFT                        29
#define REG_GX_DISPCAPCNT_MOD_SIZE                         2
#define REG_GX_DISPCAPCNT_MOD_MASK                         0x60000000

#define REG_GX_DISPCAPCNT_COFS_SHIFT                       26
#define REG_GX_DISPCAPCNT_COFS_SIZE                        2
#define REG_GX_DISPCAPCNT_COFS_MASK                        0x0c000000

#define REG_GX_DISPCAPCNT_SRCB_SHIFT                       25
#define REG_GX_DISPCAPCNT_SRCB_SIZE                        1
#define REG_GX_DISPCAPCNT_SRCB_MASK                        0x02000000

#define REG_GX_DISPCAPCNT_SRCA_SHIFT                       24
#define REG_GX_DISPCAPCNT_SRCA_SIZE                        1
#define REG_GX_DISPCAPCNT_SRCA_MASK                        0x01000000

#define REG_GX_DISPCAPCNT_WSIZE_SHIFT                      20
#define REG_GX_DISPCAPCNT_WSIZE_SIZE                       2
#define REG_GX_DISPCAPCNT_WSIZE_MASK                       0x00300000

#define REG_GX_DISPCAPCNT_WOFS_SHIFT                       18
#define REG_GX_DISPCAPCNT_WOFS_SIZE                        2
#define REG_GX_DISPCAPCNT_WOFS_MASK                        0x000c0000

#define REG_GX_DISPCAPCNT_DEST_SHIFT                       16
#define REG_GX_DISPCAPCNT_DEST_SIZE                        2
#define REG_GX_DISPCAPCNT_DEST_MASK                        0x00030000

#define REG_GX_DISPCAPCNT_EVB_SHIFT                        8
#define REG_GX_DISPCAPCNT_EVB_SIZE                         5
#define REG_GX_DISPCAPCNT_EVB_MASK                         0x00001f00

#define REG_GX_DISPCAPCNT_EVA_SHIFT                        0
#define REG_GX_DISPCAPCNT_EVA_SIZE                         5
#define REG_GX_DISPCAPCNT_EVA_MASK                         0x0000001f

#ifndef SDK_ASM
#define REG_GX_DISPCAPCNT_FIELD( e, mod, cofs, srcb, srca, wsize, wofs, dest, evb, eva ) \
    (u32)( \
    ((u32)(e) << REG_GX_DISPCAPCNT_E_SHIFT) | \
    ((u32)(mod) << REG_GX_DISPCAPCNT_MOD_SHIFT) | \
    ((u32)(cofs) << REG_GX_DISPCAPCNT_COFS_SHIFT) | \
    ((u32)(srcb) << REG_GX_DISPCAPCNT_SRCB_SHIFT) | \
    ((u32)(srca) << REG_GX_DISPCAPCNT_SRCA_SHIFT) | \
    ((u32)(wsize) << REG_GX_DISPCAPCNT_WSIZE_SHIFT) | \
    ((u32)(wofs) << REG_GX_DISPCAPCNT_WOFS_SHIFT) | \
    ((u32)(dest) << REG_GX_DISPCAPCNT_DEST_SHIFT) | \
    ((u32)(evb) << REG_GX_DISPCAPCNT_EVB_SHIFT) | \
    ((u32)(eva) << REG_GX_DISPCAPCNT_EVA_SHIFT))
#endif


/* DISP_MMEM_FIFO */

#define REG_GX_DISP_MMEM_FIFO_EVEN_SHIFT                   0
#define REG_GX_DISP_MMEM_FIFO_EVEN_SIZE                    16
#define REG_GX_DISP_MMEM_FIFO_EVEN_MASK                    0x0000ffff

#define REG_GX_DISP_MMEM_FIFO_ODD_SHIFT                    16
#define REG_GX_DISP_MMEM_FIFO_ODD_SIZE                     16
#define REG_GX_DISP_MMEM_FIFO_ODD_MASK                     0xffff0000

#ifndef SDK_ASM
#define REG_GX_DISP_MMEM_FIFO_FIELD( even, odd ) \
    (u32)( \
    ((u32)(even) << REG_GX_DISP_MMEM_FIFO_EVEN_SHIFT) | \
    ((u32)(odd) << REG_GX_DISP_MMEM_FIFO_ODD_SHIFT))
#endif


/* DISP_MMEM_FIFO_L */

#define REG_GX_DISP_MMEM_FIFO_L_RED_SHIFT                  0
#define REG_GX_DISP_MMEM_FIFO_L_RED_SIZE                   5
#define REG_GX_DISP_MMEM_FIFO_L_RED_MASK                   0x001f

#define REG_GX_DISP_MMEM_FIFO_L_GREEN_SHIFT                5
#define REG_GX_DISP_MMEM_FIFO_L_GREEN_SIZE                 5
#define REG_GX_DISP_MMEM_FIFO_L_GREEN_MASK                 0x03e0

#define REG_GX_DISP_MMEM_FIFO_L_BLUE_SHIFT                 10
#define REG_GX_DISP_MMEM_FIFO_L_BLUE_SIZE                  5
#define REG_GX_DISP_MMEM_FIFO_L_BLUE_MASK                  0x7c00

#ifndef SDK_ASM
#define REG_GX_DISP_MMEM_FIFO_L_FIELD( red, green, blue ) \
    (u16)( \
    ((u32)(red) << REG_GX_DISP_MMEM_FIFO_L_RED_SHIFT) | \
    ((u32)(green) << REG_GX_DISP_MMEM_FIFO_L_GREEN_SHIFT) | \
    ((u32)(blue) << REG_GX_DISP_MMEM_FIFO_L_BLUE_SHIFT))
#endif


/* DISP_MMEM_FIFO_H */

#define REG_GX_DISP_MMEM_FIFO_H_RED_SHIFT                  0
#define REG_GX_DISP_MMEM_FIFO_H_RED_SIZE                   5
#define REG_GX_DISP_MMEM_FIFO_H_RED_MASK                   0x001f

#define REG_GX_DISP_MMEM_FIFO_H_GREEN_SHIFT                5
#define REG_GX_DISP_MMEM_FIFO_H_GREEN_SIZE                 5
#define REG_GX_DISP_MMEM_FIFO_H_GREEN_MASK                 0x03e0

#define REG_GX_DISP_MMEM_FIFO_H_BLUE_SHIFT                 10
#define REG_GX_DISP_MMEM_FIFO_H_BLUE_SIZE                  5
#define REG_GX_DISP_MMEM_FIFO_H_BLUE_MASK                  0x7c00

#ifndef SDK_ASM
#define REG_GX_DISP_MMEM_FIFO_H_FIELD( red, green, blue ) \
    (u16)( \
    ((u32)(red) << REG_GX_DISP_MMEM_FIFO_H_RED_SHIFT) | \
    ((u32)(green) << REG_GX_DISP_MMEM_FIFO_H_GREEN_SHIFT) | \
    ((u32)(blue) << REG_GX_DISP_MMEM_FIFO_H_BLUE_SHIFT))
#endif


/* MASTER_BRIGHT */

#define REG_GX_MASTER_BRIGHT_E_MOD_SHIFT                   14
#define REG_GX_MASTER_BRIGHT_E_MOD_SIZE                    2
#define REG_GX_MASTER_BRIGHT_E_MOD_MASK                    0xc000

#define REG_GX_MASTER_BRIGHT_E_VALUE_SHIFT                 0
#define REG_GX_MASTER_BRIGHT_E_VALUE_SIZE                  5
#define REG_GX_MASTER_BRIGHT_E_VALUE_MASK                  0x001f

#ifndef SDK_ASM
#define REG_GX_MASTER_BRIGHT_FIELD( e_mod, e_value ) \
    (u16)( \
    ((u32)(e_mod) << REG_GX_MASTER_BRIGHT_E_MOD_SHIFT) | \
    ((u32)(e_value) << REG_GX_MASTER_BRIGHT_E_VALUE_SHIFT))
#endif


/* TVOUTCNT */

#define REG_GX_TVOUTCNT_COMMAND3_SHIFT                     8
#define REG_GX_TVOUTCNT_COMMAND3_SIZE                      4
#define REG_GX_TVOUTCNT_COMMAND3_MASK                      0x0f00

#define REG_GX_TVOUTCNT_COMMAND2_SHIFT                     4
#define REG_GX_TVOUTCNT_COMMAND2_SIZE                      4
#define REG_GX_TVOUTCNT_COMMAND2_MASK                      0x00f0

#define REG_GX_TVOUTCNT_COMMAND_SHIFT                      0
#define REG_GX_TVOUTCNT_COMMAND_SIZE                       4
#define REG_GX_TVOUTCNT_COMMAND_MASK                       0x000f

#ifndef SDK_ASM
#define REG_GX_TVOUTCNT_FIELD( command3, command2, command ) \
    (u16)( \
    ((u32)(command3) << REG_GX_TVOUTCNT_COMMAND3_SHIFT) | \
    ((u32)(command2) << REG_GX_TVOUTCNT_COMMAND2_SHIFT) | \
    ((u32)(command) << REG_GX_TVOUTCNT_COMMAND_SHIFT))
#endif


/* VRAMCNT */

/* VRAMCNT_A */

#define REG_GX_VRAMCNT_A_E_SHIFT                           7
#define REG_GX_VRAMCNT_A_E_SIZE                            1
#define REG_GX_VRAMCNT_A_E_MASK                            0x80

#define REG_GX_VRAMCNT_A_OFS_SHIFT                         3
#define REG_GX_VRAMCNT_A_OFS_SIZE                          2
#define REG_GX_VRAMCNT_A_OFS_MASK                          0x18

#define REG_GX_VRAMCNT_A_MST_SHIFT                         0
#define REG_GX_VRAMCNT_A_MST_SIZE                          2
#define REG_GX_VRAMCNT_A_MST_MASK                          0x03

#ifndef SDK_ASM
#define REG_GX_VRAMCNT_A_FIELD( e, ofs, mst ) \
    (u8)( \
    ((u32)(e) << REG_GX_VRAMCNT_A_E_SHIFT) | \
    ((u32)(ofs) << REG_GX_VRAMCNT_A_OFS_SHIFT) | \
    ((u32)(mst) << REG_GX_VRAMCNT_A_MST_SHIFT))
#endif


/* VRAMCNT_B */

#define REG_GX_VRAMCNT_B_E_SHIFT                           7
#define REG_GX_VRAMCNT_B_E_SIZE                            1
#define REG_GX_VRAMCNT_B_E_MASK                            0x80

#define REG_GX_VRAMCNT_B_OFS_SHIFT                         3
#define REG_GX_VRAMCNT_B_OFS_SIZE                          2
#define REG_GX_VRAMCNT_B_OFS_MASK                          0x18

#define REG_GX_VRAMCNT_B_MST_SHIFT                         0
#define REG_GX_VRAMCNT_B_MST_SIZE                          2
#define REG_GX_VRAMCNT_B_MST_MASK                          0x03

#ifndef SDK_ASM
#define REG_GX_VRAMCNT_B_FIELD( e, ofs, mst ) \
    (u8)( \
    ((u32)(e) << REG_GX_VRAMCNT_B_E_SHIFT) | \
    ((u32)(ofs) << REG_GX_VRAMCNT_B_OFS_SHIFT) | \
    ((u32)(mst) << REG_GX_VRAMCNT_B_MST_SHIFT))
#endif


/* VRAMCNT_C */

#define REG_GX_VRAMCNT_C_E_SHIFT                           7
#define REG_GX_VRAMCNT_C_E_SIZE                            1
#define REG_GX_VRAMCNT_C_E_MASK                            0x80

#define REG_GX_VRAMCNT_C_OFS_SHIFT                         3
#define REG_GX_VRAMCNT_C_OFS_SIZE                          2
#define REG_GX_VRAMCNT_C_OFS_MASK                          0x18

#define REG_GX_VRAMCNT_C_MST_SHIFT                         0
#define REG_GX_VRAMCNT_C_MST_SIZE                          3
#define REG_GX_VRAMCNT_C_MST_MASK                          0x07

#ifndef SDK_ASM
#define REG_GX_VRAMCNT_C_FIELD( e, ofs, mst ) \
    (u8)( \
    ((u32)(e) << REG_GX_VRAMCNT_C_E_SHIFT) | \
    ((u32)(ofs) << REG_GX_VRAMCNT_C_OFS_SHIFT) | \
    ((u32)(mst) << REG_GX_VRAMCNT_C_MST_SHIFT))
#endif


/* VRAMCNT_D */

#define REG_GX_VRAMCNT_D_E_SHIFT                           7
#define REG_GX_VRAMCNT_D_E_SIZE                            1
#define REG_GX_VRAMCNT_D_E_MASK                            0x80

#define REG_GX_VRAMCNT_D_OFS_SHIFT                         3
#define REG_GX_VRAMCNT_D_OFS_SIZE                          2
#define REG_GX_VRAMCNT_D_OFS_MASK                          0x18

#define REG_GX_VRAMCNT_D_MST_SHIFT                         0
#define REG_GX_VRAMCNT_D_MST_SIZE                          3
#define REG_GX_VRAMCNT_D_MST_MASK                          0x07

#ifndef SDK_ASM
#define REG_GX_VRAMCNT_D_FIELD( e, ofs, mst ) \
    (u8)( \
    ((u32)(e) << REG_GX_VRAMCNT_D_E_SHIFT) | \
    ((u32)(ofs) << REG_GX_VRAMCNT_D_OFS_SHIFT) | \
    ((u32)(mst) << REG_GX_VRAMCNT_D_MST_SHIFT))
#endif


/* WVRAMCNT */

/* VRAMCNT_E */

#define REG_GX_VRAMCNT_E_E_SHIFT                           7
#define REG_GX_VRAMCNT_E_E_SIZE                            1
#define REG_GX_VRAMCNT_E_E_MASK                            0x80

#define REG_GX_VRAMCNT_E_MST_SHIFT                         0
#define REG_GX_VRAMCNT_E_MST_SIZE                          3
#define REG_GX_VRAMCNT_E_MST_MASK                          0x07

#ifndef SDK_ASM
#define REG_GX_VRAMCNT_E_FIELD( e, mst ) \
    (u8)( \
    ((u32)(e) << REG_GX_VRAMCNT_E_E_SHIFT) | \
    ((u32)(mst) << REG_GX_VRAMCNT_E_MST_SHIFT))
#endif


/* VRAMCNT_F */

#define REG_GX_VRAMCNT_F_E_SHIFT                           7
#define REG_GX_VRAMCNT_F_E_SIZE                            1
#define REG_GX_VRAMCNT_F_E_MASK                            0x80

#define REG_GX_VRAMCNT_F_OFS_SHIFT                         3
#define REG_GX_VRAMCNT_F_OFS_SIZE                          2
#define REG_GX_VRAMCNT_F_OFS_MASK                          0x18

#define REG_GX_VRAMCNT_F_MST_SHIFT                         0
#define REG_GX_VRAMCNT_F_MST_SIZE                          3
#define REG_GX_VRAMCNT_F_MST_MASK                          0x07

#ifndef SDK_ASM
#define REG_GX_VRAMCNT_F_FIELD( e, ofs, mst ) \
    (u8)( \
    ((u32)(e) << REG_GX_VRAMCNT_F_E_SHIFT) | \
    ((u32)(ofs) << REG_GX_VRAMCNT_F_OFS_SHIFT) | \
    ((u32)(mst) << REG_GX_VRAMCNT_F_MST_SHIFT))
#endif


/* VRAMCNT_G */

#define REG_GX_VRAMCNT_G_E_SHIFT                           7
#define REG_GX_VRAMCNT_G_E_SIZE                            1
#define REG_GX_VRAMCNT_G_E_MASK                            0x80

#define REG_GX_VRAMCNT_G_OFS_SHIFT                         3
#define REG_GX_VRAMCNT_G_OFS_SIZE                          2
#define REG_GX_VRAMCNT_G_OFS_MASK                          0x18

#define REG_GX_VRAMCNT_G_MST_SHIFT                         0
#define REG_GX_VRAMCNT_G_MST_SIZE                          3
#define REG_GX_VRAMCNT_G_MST_MASK                          0x07

#ifndef SDK_ASM
#define REG_GX_VRAMCNT_G_FIELD( e, ofs, mst ) \
    (u8)( \
    ((u32)(e) << REG_GX_VRAMCNT_G_E_SHIFT) | \
    ((u32)(ofs) << REG_GX_VRAMCNT_G_OFS_SHIFT) | \
    ((u32)(mst) << REG_GX_VRAMCNT_G_MST_SHIFT))
#endif


/* VRAMCNT_WRAM */

#define REG_GX_VRAMCNT_WRAM_BANK_SHIFT                     0
#define REG_GX_VRAMCNT_WRAM_BANK_SIZE                      2
#define REG_GX_VRAMCNT_WRAM_BANK_MASK                      0x03

#ifndef SDK_ASM
#define REG_GX_VRAMCNT_WRAM_FIELD( bank ) \
    (u8)( \
    ((u32)(bank) << REG_GX_VRAMCNT_WRAM_BANK_SHIFT))
#endif


/* VRAM_HI_CNT */

/* VRAMCNT_H */

#define REG_GX_VRAMCNT_H_E_SHIFT                           7
#define REG_GX_VRAMCNT_H_E_SIZE                            1
#define REG_GX_VRAMCNT_H_E_MASK                            0x80

#define REG_GX_VRAMCNT_H_MST_SHIFT                         0
#define REG_GX_VRAMCNT_H_MST_SIZE                          2
#define REG_GX_VRAMCNT_H_MST_MASK                          0x03

#ifndef SDK_ASM
#define REG_GX_VRAMCNT_H_FIELD( e, mst ) \
    (u8)( \
    ((u32)(e) << REG_GX_VRAMCNT_H_E_SHIFT) | \
    ((u32)(mst) << REG_GX_VRAMCNT_H_MST_SHIFT))
#endif


/* VRAMCNT_I */

#define REG_GX_VRAMCNT_I_E_SHIFT                           7
#define REG_GX_VRAMCNT_I_E_SIZE                            1
#define REG_GX_VRAMCNT_I_E_MASK                            0x80

#define REG_GX_VRAMCNT_I_MST_SHIFT                         0
#define REG_GX_VRAMCNT_I_MST_SIZE                          2
#define REG_GX_VRAMCNT_I_MST_MASK                          0x03

#ifndef SDK_ASM
#define REG_GX_VRAMCNT_I_FIELD( e, mst ) \
    (u8)( \
    ((u32)(e) << REG_GX_VRAMCNT_I_E_SHIFT) | \
    ((u32)(mst) << REG_GX_VRAMCNT_I_MST_SHIFT))
#endif


/* POWCNT */

#define REG_GX_POWCNT_GE_SHIFT                             3
#define REG_GX_POWCNT_GE_SIZE                              1
#define REG_GX_POWCNT_GE_MASK                              0x0008

#define REG_GX_POWCNT_RE_SHIFT                             2
#define REG_GX_POWCNT_RE_SIZE                              1
#define REG_GX_POWCNT_RE_MASK                              0x0004

#define REG_GX_POWCNT_E2DG_SHIFT                           1
#define REG_GX_POWCNT_E2DG_SIZE                            1
#define REG_GX_POWCNT_E2DG_MASK                            0x0002

#define REG_GX_POWCNT_LCD_SHIFT                            0
#define REG_GX_POWCNT_LCD_SIZE                             1
#define REG_GX_POWCNT_LCD_MASK                             0x0001

#define REG_GX_POWCNT_LCDB_SHIFT                           8
#define REG_GX_POWCNT_LCDB_SIZE                            1
#define REG_GX_POWCNT_LCDB_MASK                            0x0100

#define REG_GX_POWCNT_E2DGB_SHIFT                          9
#define REG_GX_POWCNT_E2DGB_SIZE                           1
#define REG_GX_POWCNT_E2DGB_MASK                           0x0200

#define REG_GX_POWCNT_DSEL_SHIFT                           15
#define REG_GX_POWCNT_DSEL_SIZE                            1
#define REG_GX_POWCNT_DSEL_MASK                            0x8000

#ifndef SDK_ASM
#define REG_GX_POWCNT_FIELD( ge, re, e2dg, lcd, lcdb, e2dgb, dsel ) \
    (u16)( \
    ((u32)(ge) << REG_GX_POWCNT_GE_SHIFT) | \
    ((u32)(re) << REG_GX_POWCNT_RE_SHIFT) | \
    ((u32)(e2dg) << REG_GX_POWCNT_E2DG_SHIFT) | \
    ((u32)(lcd) << REG_GX_POWCNT_LCD_SHIFT) | \
    ((u32)(lcdb) << REG_GX_POWCNT_LCDB_SHIFT) | \
    ((u32)(e2dgb) << REG_GX_POWCNT_E2DGB_SHIFT) | \
    ((u32)(dsel) << REG_GX_POWCNT_DSEL_SHIFT))
#endif


#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_HW_ARM9_IOREG_GX_H_ */
#endif
