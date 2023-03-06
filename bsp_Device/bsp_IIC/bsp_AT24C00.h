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
 * @file		bsp_AT24C00.h
 * @brief		����ʵ��AT24C00��ͨѶ
 * @mainpage	��Ҫ��Ϣ
 * @author		Yuankang Liang(XerolySkinner)
 * @email		zabbcccbbaz@163.com
 * @version		V1.0.0
 * @date		2022-11-07 14:09
 */

#ifdef __cplusplus
#pragma once
#include "varint.h"
#include "bsp_IIC_STM32.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	��Ŀ
/**
 * @brief			һ��AT24�豸,����STM32��IIC����
 */ 
class bsp_STM32_AT24C00:public bsp_IIC_STM32{
	public:
		bsp_STM32_AT24C00(bsp_IIC_STM32& _bsp_IIC_STM32) :
			bsp_IIC_STM32(_bsp_IIC_STM32.GPIOx_SCK, _bsp_IIC_STM32.GPIO_Pin_SCK,_bsp_IIC_STM32.GPIOx_SDA,_bsp_IIC_STM32.GPIO_Pin_SDA) {
				bsp_STM32_AT24C00::Address	= 0x50;
				bsp_STM32_AT24C00::Page		= 8;};
		bsp_STM32_AT24C00(u8 Address, u8 Page, bsp_IIC_STM32& _bsp_IIC_STM32) :
			bsp_IIC_STM32(_bsp_IIC_STM32.GPIOx_SCK, _bsp_IIC_STM32.GPIO_Pin_SCK,_bsp_IIC_STM32.GPIOx_SDA,_bsp_IIC_STM32.GPIO_Pin_SDA) {
				bsp_STM32_AT24C00::Address = Address;
				bsp_STM32_AT24C00::Page = Page;};
		bsp_STM32_AT24C00(u8 Address, u8 Page,GPIO_TypeDef *GPIOx_SCK,uint16_t GPIO_Pin_SCK,GPIO_TypeDef *GPIOx_SDA,uint16_t GPIO_Pin_SDA) :
			bsp_IIC_STM32(GPIOx_SCK,GPIO_Pin_SCK,GPIOx_SDA,GPIO_Pin_SDA) {
				bsp_STM32_AT24C00::Address = Address;
				bsp_STM32_AT24C00::Page = Page;};
	public:
		void WriteOneByte(u8 addr,u8 dat);
		u8 ReadOneByte(u8 addr);
		void WriteByte(u8 addr,u8 *dat,u8 len);
		void AT_ReadByte(u8 addr,u8 *dat,u8 len);
	private:
		u8		Address = 0x50;
		u8		Page	= 8;
		void IIC_Delay(void);
	};
//////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

