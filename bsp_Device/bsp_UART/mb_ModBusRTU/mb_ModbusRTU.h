/*----------------------------------------------------------------------------------------------------
 #
 #	Copyright (c) 2022 Yuankang Liang(XerolySkinner)
 #
 #	本软件按原样提供,无任何明示或暗示
 #	在任何情况下,作者都不承担任何损害赔偿责任
 #
 #	使用的许可声明:
 #	1.	不得歪曲本软件的来源,你不能声称你编写了原始软件.
 #	2.	免费授予以任何目的,前提是版权声明出现在所有副本中.
 #		并且版权声明和许可声明同时出现.
 #	3.	你有使用,复制,修改,分发,和销售本软件的许可.
 #	4.	如果你在产品中使用,产品文档中的声明是赞赏的但不是必须的.
 #	5.	本通知不得从任何来源删除或更改.
 #
 #	Yuankang Liang(XerolySkinner)
 #		E-mail:zabbcccbbaz@163.com
 #		QQ:2715099320
 #		Mobile Phone:13005636215
 #
 #	All rights reserved.
 */

 /**
  * @file		mb_ModbusRTU.h
  * @brief		ModbusRTU库
  * @mainpage	主要信息
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		Thu Sep 21 11:24:43 2023

  */
#ifndef _mb_ModbusRTU_H
#define _mb_ModbusRTU_H
#ifdef __cplusplus
extern "C"{
#endif
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdarg.h"
#include "varint.h"
#include "bsp_CRC.h"
#include <rtthread.h>
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	定义
/**
 * @brief			开关预定义
 */
#define mb_malloc	malloc
#define mb_crc		CRC16_MODBUS
typedef u8 (*mb_transmit)(u8*,u32);
//----------------------------------------------------------------------------------------------------	
#define Default_Buff 64
//----------------------------------------------------------------------------------------------------
#define CRC_Endian	0
#define Dat_Endian	1
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	宏函数
#define CRC_CHECK
#define ModBus_ACK
#define ModBus_RADIO
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	宏函数
#define MODBUS_GET_BIT(ptr,offset) (((ptr)[(offset) / 8] >> ((offset) % 8)) & 1)
#define MODBUS_SET_BIT(ptr,offset,val) (*(ptr + (offset) / 8) = (*(ptr + (offset) / 8) & ~(1 << ((offset) % 8))) | (!!((val)) << ((offset) % 8)))
#define ceil_div(x,y) (((x)/(y))+!!((x)%(y)))
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	定义
/**
 * @brief			ModBus功能码
 */
typedef enum{
	MB_FUNC_RD_OUT_COIL				=0x01,			///	读线圈寄存器
	MB_FUNC_RD_IN_COIL				=0x02,			///	读状态寄存器
	MB_FUNC_RD_HOLD_REG				=0x03,			///	读保持寄存器
	MB_FUNC_RD_IN_REG				=0x04,			///	读输入寄存器
	MB_FUNC_WR_COIL					=0x05,			///	写单线圈寄存器
	MB_FUNC_WR_REG					=0x06,			///	写单保持寄存器
	MB_FUNC_WR_COILS				=0x0F,			///	写多线圈寄存器
	MB_FUNC_WR_REGS					=0x10,			///	写多保持寄存器
}MB_FUNC_ENUM;
//////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
#endif
