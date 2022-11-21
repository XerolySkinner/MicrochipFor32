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
  * @file		bsp_ModBus_STM32.h
  * @brief		ModBusͨ�Ż���STM32
  * @mainpage	��Ҫ��Ϣ
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
//	��Ŀ
/**
 * @brief			STM32�ô��ڵ�ModBus������
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
