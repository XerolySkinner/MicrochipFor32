/*----------------------------------------------------------------------------------------------------
#	THIS FILE IS PART OF XEROLYSKINNER'S PROJECT
#
#	THIS PROGRAM IS FREE SOFTWARE
#
#	E-mail:ZABBCCCBBAZ@163.com
#	QQ:2715099320
#
#	Copyright (c) 2022 XerolySkinner
#	All rights reserved.
*/

/*----------------------------------------------------------------------------------------------------
	名字:MainSystem
	时间:20220713-2238
	程序员:梁源康
	说明:主程序
*/
#ifndef _XEROLYSKINNER_BSP_FLASH_H
#define _XEROLYSKINNER_BSP_FLASH_H
#include "main.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	程序
//	
uint32_t bsp_WriteFlashOnePage(uint32_t *dat,uint32_t num);
void bsp_ReadFlash(uint32_t *dat,uint32_t num);
void bsp_WriteFlash_Pack(void);
void bsp_ReadFlash_Pack(void);
//////////////////////////////////////////////////////////////////////////////////////////////////////
#endif