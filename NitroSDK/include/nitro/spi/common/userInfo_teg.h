/*---------------------------------------------------------------------------*
  Project:  NitroSDK - SPI - include
  File:     userInfo_teg.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: userInfo_teg.h,v $
  Revision 1.5  01/18/2006 02:12:38  kitase_hirotake
  do-indent

  Revision 1.4  02/28/2005 05:26:03  yosizaki
  do-indent.

  Revision 1.3  09/03/2004 13:03:11  takano_makoto
  Corrected spelling:  NitroConfigData -> NVRAMConfigData.

  Revision 1.2  09/03/2004 04:29:15  terui
  Revised according to structure definition adjustments relating to user information in NVRAM.

  Revision 1.1  08/25/2004 09:20:43  terui
  Initial upload.

  $NoKeywords: $
 *---------------------------------------------------------------------------*/
#ifndef NITRO_SPI_COMMON_USERINFO_TEG_H_
#define NITRO_SPI_COMMON_USERINFO_TEG_H_

#ifdef __cplusplus
extern "C" {
#endif

/*===========================================================================*/

/*---------------------------------------------------------------------------*
    constant definitions
 *---------------------------------------------------------------------------*/
// config setting data format version
#define NVRAM_CONFIG_DATA_VERSION           0

// various setting values in config
#define NVRAM_CONFIG_BOOT_GAME_LOG_NUM      8   // number of stored boot game logs
#define NVRAM_CONFIG_NICKNAME_LENGTH        8   // Nickname Length

// language setting codes
#define NVRAM_CONFIG_LANG_JAPANESE          0   // Japanese
#define NVRAM_CONFIG_LANG_ENGLISH           1   // English
#define NVRAM_CONFIG_LANG_FRENCH            2   // France
#define NVRAM_CONFIG_LANG_GERMAN            3   // German
#define NVRAM_CONFIG_LANG_ITALIAN           4   // Italian
#define NVRAM_CONFIG_LANG_SPANISH           5   // Spanish
#define NVRAM_CONFIG_LANG_CODE_MAX          6   // number of types of language setting codes

/*---------------------------------------------------------------------------*
    structure definitions
 *---------------------------------------------------------------------------*/
// Nickname (20byte)
typedef struct NVRAMConfigNickname
{
    u16     name[NVRAM_CONFIG_NICKNAME_LENGTH]; // Nickname (Maximum of 8 characters in UNICODE, No terminal code)
    u16     length;                    // Number of characters
    u16     padding;

}
NVRAMConfigNickname;

// Sex Code (4byte)
typedef enum NVRAMConfigSexCode
{
    NVRAM_CONFIG_SEX_MALE = 0,         // Male
    NVRAM_CONFIG_SEX_FEMALE,           // Female
    NVRAM_CONFIG_SEX_CODE_MAX
}
NVRAMConfigSexCode;

// Blood type code (4byte)
typedef enum NVRAMConfigBloodType
{
    NVRAM_CONFIG_BLOOD_A = 0,          // Type A
    NVRAM_CONFIG_BLOOD_B,              // Type B
    NVRAM_CONFIG_BLOOD_AB,             // Type AB
    NVRAM_CONFIG_BLOOD_O,              // Type O
    NVRAM_CONFIG_BLOOD_TYPE_MAX
}
NVRAMConfigBloodType;

// Date data (4byte)
typedef struct NVRAMConfigDate
{
    u16     year;                      //Year:1800 - 2100
    u8      month;                     //Month:01 - 12
    u8      day;                       //Day:01 - 31

}
NVRAMConfigDate;

// Owner Information (32byte)
typedef struct NVRAMConfigOwnerInfo
{
    NVRAMConfigNickname nickname;      // Nickname
    NVRAMConfigSexCode sex;            // Sex
    NVRAMConfigBloodType bloodType;    // Blood type
    NVRAMConfigDate birthday;          // Birthdate

}
NVRAMConfigOwnerInfo;


// Boot game log data (36byte)
typedef struct NVRAMConfigBootGameLog
{
    u32     gameCode[NVRAM_CONFIG_BOOT_GAME_LOG_NUM];   // The list of game brevity codes for the games started up in the past (Ring Buffer)
    u16     top;                       // Index number of the last log
    u16     num;                       // Number of logs

}
NVRAMConfigBootGameLog;                // 36 byte

// Touch Panel Calibration Data (12byte)  xyxyxy
typedef struct NVRAMConfigTpCData
{
    u16     calib_data[6];             // Calibration Information

}
NVRAMConfigTpCData;


// Each type of configuration data for NITRO (96byte)  xyxyxy
typedef struct NVRAMConfigData
{
    u8      version;                   // Flash storage data format version
    u8      timezone;                  // Time zone
    u16     agbLcd;                    // Start up on which LCD when booting in AGB mode? (0:TOP,1:BOTTOM)
    u32     rtcOffset;                 // Offset value when configuring the RTC (Each time the user changes the configuration of the RTC, this fluctuates in response to its value.)&#x81;j
    u32     language;                  // Language code
    NVRAMConfigOwnerInfo owner;        // Owner Information
    NVRAMConfigTpCData tp;             // Touch Panel Calibration Data
    NVRAMConfigBootGameLog bootGameLog; // Boot Game Log

}
NVRAMConfigData;

// Format when saving NVRAM for each type of configuration data for NITRO (100byte)   xyxyxy
typedef struct NVRAMConfig
{
    NVRAMConfigData ncd;               // Each type of configuration data for NITRO  xyxyxy
    u16     saveCount;                 // Loop and count 0x00-0x7f. The data is valid where the count value is new.  xyxyxy
    u16     crc16;                     // 16bitCRC for each type of configuration data for NITRO  xyxyxy

}
NVRAMConfig;


/*===========================================================================*/

#ifdef  __cplusplus
}       /* extern "C"*/
#endif

#endif /* NITRO_SPI_COMMON_USERINFO_TEG_H_ */

/*---------------------------------------------------------------------------*
  End of file
 *---------------------------------------------------------------------------*/
