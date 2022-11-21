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
 * @file		bsp_AT24C00.h
 * @brief		本类实现AT24C00的通讯
 * @mainpage	主要信息
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
//	类目
/**
 * @brief			一个AT24设备,基于STM32的IIC总线
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

