/*----------------------------------------------------------------------------------------------------
 #
 #	Copyright (c) 2022 Yuankang Liang(XerolySkinner)
 #
 #	�������ԭ���ṩ,���κ���ʾ��ʾ
 #	���κ������,���߶����е��κ����⳥����
 #
 #	ʹ�õ��������:
 #	1.	�����������������Դ,�㲻���������д��ԭʼ���.
 #	2.	����������κ�Ŀ��,ǰ���ǰ�Ȩ�������������и�����.
 #		���Ұ�Ȩ�������������ͬʱ����.
 #	3.	����ʹ��,����,�޸�,�ַ�,�����۱���������.
 #	4.	������ڲ�Ʒ��ʹ��,��Ʒ�ĵ��е����������͵ĵ����Ǳ����.
 #	5.	��֪ͨ���ô��κ���Դɾ�������.
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
  * @brief		print�ض��������
  * @mainpage	��Ҫ��Ϣ
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
//	������
/**
 * @brief			����һ��print���ض������
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
//	bsp����
#ifdef _STM32_HAL_
#include "usart.h"
/**
 * @brief			����һ��print���ض������
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
