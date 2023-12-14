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
  * @file		bsp_PrintArt.h
  * @brief		print重定向的艺术
  * @mainpage	主要信息
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		2022-11-27 02:15
  */
#pragma once
#ifdef __cplusplus
#include "User.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include "varint.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	类声明
/**
 * @brief			创造一个print的重定向对象
 */
class bsp_PrintArt{
	public:
		bsp_PrintArt(void);
		bsp_PrintArt(u32 len);
		int print(const char* format, ...);
	private:
		u32 Bufflen;
		virtual void Transmit(u8* dat, u32 len) = 0;};

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	bsp适配
#ifdef _STM32_HAL_
#include "usart.h"
/**
 * @brief			创造一个print的重定向对象
 */
class bsp_PrintArt_STM32:public bsp_PrintArt{
	public:
		bsp_PrintArt_STM32(UART_HandleTypeDef *huart,u32 Bufflen);
		bsp_PrintArt_STM32(UART_HandleTypeDef *huart);
	private:
		UART_HandleTypeDef *huart;
		virtual void Transmit(u8* dat, u32 len){
			HAL_UART_Transmit(huart,dat,len,0xFF);
	}};
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
