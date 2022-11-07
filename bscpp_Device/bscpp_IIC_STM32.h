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
  * @file		 bscpp_IIC_STM32.h
  * @brief		 实现针对STM32的软件IIC类
  * @mainpage	 主要信息
  * @author 	 Yuankang Liang(XerolySkinner)
  * @email		 zabbcccbbaz@163.com
  * @version	 V1.0.0
  * @date		 2022-11-07 00:56
  */

 /*----------------------------------------------------------------------------------------------------
	  名字:bscpp_IIC_STM32
	  时间:20221107-0056
	  程序员:梁源康
	  说明:主程序
  */
#pragma once
#ifdef __cplusplus
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	头文件
#include "gpio.h"
#include "varint.h"
#include "bscpp_IIC.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	类目
/**
 * @brief 		STM32版本的软件IIC
 * 				需要使用构造函数初始化
 */
class bscpp_IIC_STM32 :public bscpp_IIC{
	public:
		bscpp_IIC_STM32(GPIO_TypeDef *GPIOx_SCK,uint16_t GPIO_Pin_SCK,GPIO_TypeDef *GPIOx_SDA,uint16_t GPIO_Pin_SDA);
	protected:
		u8 IIC_SCK(u8 var);
		u8 IIC_SDA(u8 var);
		virtual void IIC_Delay(void);
	public:
		GPIO_TypeDef		*GPIOx_SCK;
		uint16_t			GPIO_Pin_SCK;
		GPIO_TypeDef		*GPIOx_SDA;
		uint16_t			GPIO_Pin_SDA;
	};
//////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
	
