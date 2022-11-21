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
  * @file		bsp_ModBus_STM32.h
  * @brief		ModBus通信基于STM32
  * @mainpage	主要信息
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		2022-11-22 01:28
  */

#pragma once
#include "bsp_ModBus.h"
#include "usart.h"
#include "varint.h"
#ifdef __cplusplus
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	类目
/**
 * @brief			STM32用串口的ModBus发送器
 */
class bsp_ModBus_STM32:public bsp_ModBus_Tx {
	public:
		bsp_ModBus_STM32(UART_HandleTypeDef* huart,u8 ID,uint32_t Timeout):bsp_ModBus_Tx(ID){
			bsp_ModBus_STM32::huart = huart;
			bsp_ModBus_STM32::Timeout = Timeout;}
	protected:
		virtual void Transmit(u8 *dat, u16 len){
			HAL_UART_Transmit(huart,dat,len,0xFF);}
	private:
		UART_HandleTypeDef* huart;
		uint32_t Timeout;};
//////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
