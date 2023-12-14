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
  * @file		bsp_Sigcom.h
  * @brief		实时控制台
  * @mainpage	主要信息
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		Wed Mar  1 16:44:13 2023

  */

#pragma once
#ifdef __cplusplus
#include "varint.h"
#include "bsp_PrintArt.h"
#include "stdlib.h"
#include "usart.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	错误码
enum{
	bsp_Sigcom_OK,
	bsp_Sigcom_FULL,
	bsp_Sigcom_CODE,
	};
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	类目
/**
 * @brief			TODO
 */
 class bsp_Sigcom:public bsp_PrintArt_STM32{
	 public:
	 bsp_Sigcom(UART_HandleTypeDef *huart);
	 bsp_Sigcom(UART_HandleTypeDef *huart,u32 len);
	 public:
		void init(void);
		void clean(void);
		u32 callback_UART(void);
	 public:
		UART_HandleTypeDef *huart;
		u8* buff;
		u8* buffhead;
		u32 len;
		u32 lenmax;
	 private:
		u8 temp;
	 public:
		 struct{
			 u8 echo		:1;		//	回显标志位
			 u8 code		:1;		//	功能码标志位
			}seting;
	};
//////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
