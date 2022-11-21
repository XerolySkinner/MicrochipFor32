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
  * @file		bsp_ModBus.h
  * @brief		ModBus通信函数
  * @mainpage	主要信息
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		2022-11-21 17:09
  */
#pragma once
#include "varint.h"
#include "usart.h"
#include <stdarg.h>
#ifdef __cplusplus
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	数据码
enum Fun_ModBus {
	Fun_R_OutCoil	= 0x01,				///< 读取输出线圈
	Fun_R_InCoil	= 0x02,				///< 读取输入线圈
	Fun_R_KeepReg	= 0x03,				///< 读取保持寄存
	Fun_R_InReg		= 0x04,				///< 读取输入寄存

	Fun_W_OneCoil	= 0x05,				///< 写入单线圈
	Fun_W_OneReg	= 0x06,				///< 写入单寄存
	Fun_W_Coils		= 0x0F,				///< 写入多线圈
	Fun_W_Regs		= 0x10,				///< 写入多寄存
};
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	类目
/**
 * @brief			ModBus发送器
 */
class bsp_ModBus_Tx{
	public:
		bsp_ModBus_Tx(u8 ID);
	public:
		void ReadKeepReg(u16 address,u16 mem);
		void ReadInReg(u16 address, u16 mem);
		void WriteOneReg(u16 address, u16 var);
		void WriteRegs(u16 address, u16 mem, u16* var);
		void WriteRegsVar(u16 address, u16 mem,...);

		void ReadOutCoil(u16 address,u16 mem);
		void ReadInCoil(u16 address, u16 mem);
		void WriteOneCoil(u16 address, u16 state);
		void WriteCoils(u16 address, u16 mem, u8* var);
		void WriteCoilsVar(u16 address, u16 mem,...);
	protected:
		virtual void Transmit(u8 *dat, u16 len)=0;
	protected:
		u8		ID;						///< 器件ID
	};
//----------------------------------------------------------------------------------------------------
/**
 * @brief			ModBus协议分析器
 */
class bsp_ModBus_Rx{
	public:
		bsp_ModBus_Rx(void);
		~bsp_ModBus_Rx(void);
	public:
		void analysis(u8* dat);
		//		共有变量
		u8		ID;						///< 器件ID
		u8		Func;					///< 功能号
		u8		crcts;					///< CRC测试
		//		保持寄存器特有
		u16		*KeepRegDat;
		u8		KeepRegMem;
		//		输入寄存器特有
		u16*	InRegDat;
		u8		InRegMem;
		//		输出线圈特有
		u8*		OutCoilDat;
		u8		OutCoilMem;
		//		输入线圈特有
		u8*		InCoilDat;
		u8		InCoilMem;};
//////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
