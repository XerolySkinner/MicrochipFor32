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
 * @file		bscpp_IIC.h
 * @brief		本类实现软件IIC功能
 *				依此类派生出其他软件IIC功能
 * @mainpage	主要信息
 * @author		Yuankang Liang(XerolySkinner)
 * @email		zabbcccbbaz@163.com
 * @version		V1.0.0
 * @date		2022-11-07 00:56
 */

#ifdef __cplusplus
#pragma once
#include "varint.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	枚举头
/**
 * @brief 		控制管脚的三种状态(置位,复位,读取)
 */
enum {
	IIC_RESET,			///< 管脚复位状态
	IIC_SET,			///< 管脚置位状态
	IIC_READ			///< 读取管脚状态
};
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	类目
/**
 * @brief 		IIC的基础实现方法
 * 				留下三个保护性接口需要实现,分别是控制时钟,控制数据,延时函数
 */
class bscpp_IIC{
	public:
		void	IIC_WriteOneByte(u8 id, u8 addr, u8 dat);
		u8		IIC_ReadOneByte(u8 id, u8 addr);
		void	IIC_Write(u8 id,u8 addr,u8* dat,u32 len);
		void	IIC_Read(u8 id,u8 addr,u8* dat,u32 len);
	public:
		void	IIC_Start(void);
		void	IIC_Stop(void);
		void	IIC_SendAck(u8 ackbit);
		u8		IIC_WaitAck(void);
		void	IIC_SendByte(u8 byt);
		u8		IIC_RecByte(void);
	protected:
		/**
		 * @brief			控制SCK管脚口
		 * 
		 * @param	var		此处有三个状态,IIC_SET置位管脚,IIC_RESET复位管脚
		 * @return			当var为IIC_READ时返回管脚状态
		 * @todo			需要为其实现才可使用软件IIC
		 */ 
		virtual u8 IIC_SCK(u8 var) = 0;
		/**
		 * @brief			控制SDA管脚口
		 * 
		 * @param	var		此处有三个状态,IIC_SET置位管脚,IIC_RESET复位管脚
		 * @return			当var为IIC_READ时返回管脚状态
		 * @todo			需要为其实现才可使用软件IIC
		 */ 
		virtual u8 IIC_SDA(u8 var) = 0;
		/**
		 * @brief			时序中的延时
		 * 					在此处短暂延时
		 * @todo			需要为其实现才可使用软件IIC
		 */ 
		virtual void IIC_Delay(void) = 0;
	};
//////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

