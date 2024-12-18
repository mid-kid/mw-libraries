/*---------------------------------------------------------------------------*
  Project:  NitroSDK - OS - include
  File:     spinLock.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: spinLock.h,v $
  Revision 1.31  01/18/2006 02:12:28  kitase_hirotake
  do-indent

  Revision 1.30  03/01/2005 01:57:00  yosizaki
  Revised copyright year

  Revision 1.29  02/28/2005 05:26:01  yosizaki
  do-indent.

  Revision 1.28  09/02/2004 06:28:15  yada
  only change comment

  Revision 1.27  07/23/2004 04:28:23  yada
  OS_UnLock* restored for compatibility

  Revision 1.26  07/23/2004 01:52:32  yada
  inline -> static inline

  Revision 1.25  07/23/2004 00:58:43  yada
  rename OS_UnLock* -> OS_Unlock*

  Revision 1.24  07/22/2004 08:21:41  yada
  change some lockID's type u32->u16

  Revision 1.23  06/21/2004 11:02:32  yada
  fix comment. incorrect about return value.

  Revision 1.22  04/07/2004 02:03:17  yada
  fix header comment

  Revision 1.21  03/26/2004 10:37:49  yada
  Added OS_GetLockID(), OS_ReleaseLockID()

  Revision 1.20  03/25/2004 07:25:21  yada
  Added concerning OS_LockCard(), and other card lock

  Revision 1.19  03/04/2004 09:48:59  yada
  Prohibited IRQ/FIQ for cartridge lock only.

  Revision 1.18  02/05/2004 07:27:19  yada
  historic IRIS character string returned from NITRO to IRIS. xyxyxy

  Revision 1.17  2004/02/05 07:09:03  yasu
  change SDK prefix iris -> nitro

  Revision 1.16  01/14/2004 01:43:41  yada
  Made it possible to configure execution functions during 'lock' and 'unlock'

  Revision 1.15  12/25/2003 07:29:56  yada
  Changes as per unified type rules

  Revision 1.14  2003/12/22 13:42:13  yasu
  Added 'struct'" tag to OS_LockWord/LockByte

  Revision 1.13  12/18/2003 07:25:26  yada
  Deleted unnecessary comments

  Revision 1.12  12/18/2003 07:18:59  yada
  Deleted MAINP, SUBP priority define

  Revision 1.11  2003/12/17 06:08:12  yasu
  Minor corrections

  Revision 1.10  2003/12/11 00:35:38  yasu
  Commented out target.h

  Revision 1.9  2003/12/10 10:56:18  yasu
  Transplanted only those SpinLock functions essential to ISDPrint
  OS_LockWord() -> OS_LockByWord()
  Changes such as volatile LockWord -> OS_LockWord

  Revision 1.8  12/08/2003 12:21:03  yada
  Support for changes to 12/3 REDSDK

  Revision 1.7  11/28/2003 01:54:47  yada
  Reflects REDSDK 03-11-27

  Revision 1.6  11/14/2003 06:50:13  yada
  System preparer OS_Halt() to -> OS_HaltA9()  xyxyxy

  Revision 1.5  11/06/2003 10:35:55  yada
  Separated processes for IRIS_BB and NITRO_TEG

  Revision 1.4  11/05/2003 07:29:55  yada
  Changed filename lowercase 'l' to uppercase 'L'

  Revision 1.2  11/04/2003 09:08:43  yada
  (none)

  Revision 1.1  10/31/2003 04:12:03  yada
  Created initial version


  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_OS_SPINLOCK_H_
#define NITRO_OS_SPINLOCK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <nitro/types.h>

//======================================================================
//                      Lock functions
//
//Use these functions for shared resources like work RAM, VRAM-C and xyxyxy
//  VRAM-D that are shared between Game card, Game Pak and CPU, and for xyxyxy
//  exclusive control of private resources like inter-CPU transmission FIFO. xyxyxy
//======================================================================

// Lock ID

#define OS_UNLOCK_ID            0      // ID when lock variable is not locked
#define OS_MAINP_LOCKED_FLAG    0x40   // Main processor lock-check flag
#define OS_MAINP_LOCK_ID_START  0x40   // Starting number of lock ID assigned for main processor  xyxyxy
#define OS_MAINP_LOCK_ID_END    0x6f   //                               Ending number             "       "       "  xyxyxy
#define OS_MAINP_DBG_LOCK_ID    0x70   //                               Debugger reserved number  "       "       "  xyxyxy
#define OS_MAINP_SYSTEM_LOCK_ID 0x7f   //                               System reserved number    "       "       "  xyxyxy
#define OS_SUBP_LOCKED_FLAG     0x80   //   Sub processor lock-check flag xyxyxy
#define OS_SUBP_LOCK_ID_START   0x80   //   Starting number of lock ID assigned for subprocessor  xyxyxy
#define OS_SUBP_LOCK_ID_END     0xaf   //                               Ending number             "       "       "  xyxyxy
#define OS_SUBP_DBG_LOCK_ID     0xb0   //                               Debugger reserved number  "       "       "  xyxyxy
#define OS_SUBP_SYSTEM_LOCK_ID  0xbf   //                               System reserved number    "       "       "  xyxyxy

#define OS_LOCK_SUCCESS         0      // Lock success
#define OS_LOCK_ERROR           (-1)   // Lock error

#define OS_UNLOCK_SUCCESS       0      // Unlock success
#define OS_UNLOCK_ERROR         (-2)   // Unlock error

#define OS_LOCK_FREE            0      // Unlocking

#define OS_LOCK_ID_ERROR        (-3)   // Lock ID error


//---- structure of lock variable 
typedef volatile struct OSLockWord
{
    u32     lockFlag;
    u16     ownerID;
    u16     extension;
}
OSLockWord;

/*---------------------------------------------------------------------------*
  Name:         OS_InitLock

  Description:  initialize system lock variable
                and privilege to access shared resources

                * cartridge exclusive control area is not cleared
                  because debugger uses.

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    OS_InitLock(void);

//----------------------------------------------------------------------
//          Spinlock
//
//- This conducts lock variable spinlock for exclusive control of
//  resources shared between processors and between modules.
//- Trials continue until lock succeeds.
//- Be sure to lock resources shared between processors before using them xyxyxy
//- Private processor resources do not need to be locked if use can be set xyxyxy
//  with timing. xyxyxy
//  Private resources can be locked just for debug time.
//
//Arguments:
//  lockID              Lock ID
//  lockp       Lock variable's pointer
//
//Returned value:
//  OS_LOCK_SUCCESS     Lock success
//----------------------------------------------------------------------
s32     OS_LockByWord(u16 lockID, OSLockWord *lockp, void (*ctrlFuncp) (void));
s32     OS_LockCartridge(u16 lockID);
s32     OS_LockCard(u16 lockID);

//----------------------------------------------------------------------
//          Unlock
//
//- This unlocks and passes access rights of shared resources to the subprocessor.
//- In the case of running a module that is not locked, it will not be unlocked,
//  and OS_UNLOCK_ERROR will be returned.
//
//Arguments:
//  lockID              Lock ID
//  lockp       Lock variable's pointer
//
//Returned value:
//  OS_UNLOCK_SUCCESS   Unlock success
//  OS_UNLOCK_ERROR     Unlock error
//----------------------------------------------------------------------
s32     OS_UnlockByWord(u16 lockID, OSLockWord *lockp, void (*ctrlFuncp) (void));
s32     OS_UnlockCartridge(u16 lockID);
s32     OS_UnlockCard(u16 lockID);

//---- for compatibility to old name ('UnLock' <-> 'Unlock')
//     because isd lib calls OS_UnLock*, these cannot be inline.
s32     OS_UnLockByWord(u16 lockID, OSLockWord *lockp, void (*ctrlFuncp) (void));
s32     OS_UnLockCartridge(u16 lockID);
s32     OS_UnLockCard(u16 lockID);

//----------------------------------------------------------------------
//          Lock trials
//
//- Try spinlock once only.
//- Be sure to lock resources shared between processors before using them xyxyxy
//- Private processor resources do not need to be locked if use can be set xyxyxy
//  with timing. xyxyxy
//  Private resources can be locked just for debug time.
//
//Arguments:
//  lockID              Lock ID
//  lockp       Lock variable's pointer
//  CtrlFuncp           Resource control functions pointer
//
//Returned value:
//  right                  Locking (the previously stored ID)
//  OS_LOCK_SUCCESS     Lock success
//----------------------------------------------------------------------
s32     OS_TryLockByWord(u16 lockID, OSLockWord *lockp, void (*crtlFuncp) (void));
s32     OS_TryLockCartridge(u16 lockID);
s32     OS_TryLockCard(u16 lockID);

//----------------------------------------------------------------------
//          Read the lock variable's owner module ID
//
//- This reads the lock variable's owner module ID.
//- You can check which processor has ownership rights at time when
//  module ID is non-zero.
//- For shared resources, you can maintain this by prohibiting interrupts only  
//  when "main processor has the rights."  
//  In other states, this might be changed by subprocessor.
//- Lock variables are not necessarily unlocked, even when owner module ID is 0.  xyxyxy
//
//Arguments:
//  lockp       Lock variable's pointer
//
//Returned value:    Owner module ID
//
//Note: Be aware that if the main memory is not being accessed through a cache,
//  byte access cannot be performed.
//  Thus, as a basic rule, you should use OS_ReadOwnerOfLockWord() for main memory.
//----------------------------------------------------------------------
u16     OS_ReadOwnerOfLockWord(OSLockWord *lockp);
#define OS_ReadOwnerOfLockCartridge()  OS_ReadOwnerOfLockWord( (OSLockWord *)HW_CTRDG_LOCK_BUF )
#define OS_ReadOwnerOfLockCard()       OS_ReadOwnerOfLockWord( (OSLockWord *)HW_CARD_LOCK_BUF  )



/*---------------------------------------------------------------------------*
  Name:         OS_GetLockID

  Description:  get lock ID

  Arguments:    None.

  Returns:      OS_LOCK_ID_ERROR, if fail to get ID

                if ARM9
                   0x40-0x6f       lockID
                else if ARM7
                   0x80-0xaf       lockID
                endif

                *Notice:  ID is allocated only 48 pattern at a highest.

 *---------------------------------------------------------------------------*/
s32     OS_GetLockID(void);


/*---------------------------------------------------------------------------*
  Name:         OS_ReleaseLockID

  Description:  release lock ID

  Arguments:    lockID : id to tend to release

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    OS_ReleaseLockID(u16 lockID);

#ifdef __cplusplus
} /* extern "C"*/
#endif

/* NITRO_OS_SPINLOCK_H_ */
#endif
