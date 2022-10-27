#ifndef _include_h
#define _include_h

#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "delay.h"
#include "modbus_slave.h"

#include "proc.h"
#include "init.h"
#include "flash.h"
#include "n32g031.h"
#include "n32g031_conf.h"
		
#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t

#define s8 int8_t
#define s16 int16_t
#define s32 int32_t


#ifdef __GLOBALS__
#define EXT
#else
#define EXT extern
#endif



typedef struct
{
	uint8_t Rxlen;
	char RxBuf[S_RX_BUF_SIZE];
	uint8_t Txlen;
	char TxBuf[S_TX_BUF_SIZE];
}PRINT_MODS_T;

EXT PRINT_MODS_T g_tPrint;
EXT u8 EVENODD,tim_flag;
EXT u8 ModelID;
EXT u16 ModelBaud;

#endif

