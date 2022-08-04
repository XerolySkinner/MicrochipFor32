/*----------------------------------------------------------------------------------------------------
#	THIS FILE IS A PART OF XerolySkinner's PROJECT
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
	����:bsp_Console
	ʱ��:20220805-0424
	����Ա:��Դ��
	˵��:���λ������
*/
#ifndef _XEROLYSKINNER_BSP_CONSOLE_H
#define _XEROLYSKINNER_BSP_CONSOLE_H
#include "usart.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	ȫ������
//	
#pragma pack(1)
struct console_pack{
	uint8_t		var0;
	uint16_t	var1;
	uint32_t	var2;
};
#pragma pack()
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	����
//	
void bsp_ConsoleInit(UART_HandleTypeDef *huart);
void bsp_ConsoleJump(UART_HandleTypeDef *huart);
void HAL_UART_IdleCpltCallback(UART_HandleTypeDef *huart);
//////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
