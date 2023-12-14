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
  * @file		mbm_ModBusRTU.h
  * @brief		主机ModBusRTU
  * @mainpage	主要信息
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V2.0.0
  * @date		Thu Sep 21 17:08:36 2023

  */
#ifndef _mbm_ModBusRTU_H
#define _mbm_ModBusRTU_H
#ifdef __cplusplus
extern "C"{
#endif
#include "varint.h"
#include "mb_ModbusRTU.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	定义
/**
 * @brief			ModBusRTU_Master结构体
 */
typedef struct{
	//	发送接口
	mb_transmit 	tramsmit;						//	发送函数
	u8*				TxBuff;							//	接受缓冲区
	u32				TxLen;							//	长度
	u32				TxMaxLen;						//	分配长度
	//	数据池
	u8 				RxID;							//	从机结构体
	u8			 	RxFunc;							//	接受功能码
	u16				RxAddr;							//	地址头部
	
	u8				RxByte;							//	字节数
	//	数据池
	u8 				TxID;							//	从机结构体
	u8			 	TxFunc;							//	接受功能码
	u16				TxAddr;							//	地址头部
	//	数据池
	u16				Mem;							//	数量头部
	
	u8*				RxCoilBuff;						//	接受缓冲区
	u32				RxCoilMaxLen;					//	分配长度
	u16*			RxRegBuff;						//	接受缓冲区
	u32				RxRegMaxLen;					//	分配长度
	//	数据池
	u32				VarNum;
	void**			VarBuff;
}_mb_struct_master;
typedef _mb_struct_master* _mb_master;
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	定义
/**
 * @brief			TODO
 */
#define mb_Master_create_F(F) mb_Master_create("-transmit-TxBuffSize-RxCoilBuff-RxRegBuff",F,Default_Buff,Default_Buff,Default_Buff)
_mb_master mb_Master_create(const char* str,...);
//----------------------------------------------------------------------------------------------------
//	应用函数
u8 mb_Master_WR_COIL_Ask(_mb_master obj,u8 ID,u16 Addr,u16 Data);
u8 mb_Master_WR_REG_Ask(_mb_master obj,u8 ID,u16 Addr,u16 Data);
u8 mb_Master_WR_REGS_Ask(_mb_master obj,u8 ID,u16 Addr,u16 Mem,u16* Data);
u8 mb_Master_WR_COILS_Ask(_mb_master obj,u8 ID,u16 Addr,u16 Mem,u8* Data);
#define mb_Master_WR_REGS_ADDR_Ask(obj,ID,Addr,Mem,Data) mb_Master_WR_REGS_Ask(obj,ID,Addr,Mem,(Data)+(Addr))
#define mb_Master_WR_COILS_ADDR_Ask(obj,ID,Addr,Mem,Data) mb_Master_WR_COILS_Ask(obj,ID,Addr,Mem,(Data)+(Addr))
u8 mb_Master_WR_REGS_Var_Ask(_mb_master obj,u8 ID,u16 Addr,u16 Mem,...);
u8 mb_Master_WR_COILS_Var_Ask(_mb_master obj,u8 ID,u16 Addr,u16 Mem,...);
//----------------------------------------------------------------------------------------------------
//	基矢
u8 mb_Master_RD_OUT_COIL_Ask(_mb_master obj,u8 ID,u16 Addr,u16 Mem);
u8 mb_Master_RD_IN_COIL_Ask(_mb_master obj,u8 ID,u16 Addr,u16 Mem);
u8 mb_Master_RD_HOLD_REG_Ask(_mb_master obj,u8 ID,u16 Addr,u16 Mem);
u8 mb_Master_RD_IN_REG_Ask(_mb_master obj,u8 ID,u16 Addr,u16 Mem);
//	应用函数
u8 mb_Master_RD_OUT_COIL_Var_Ask(_mb_master obj,u8 ID,u16 Addr,u16 Mem,...);
u8 mb_Master_RD_IN_COIL_Var_Ask(_mb_master obj,u8 ID,u16 Addr,u16 Mem,...);
u8 mb_Master_RD_HOLD_REG_Var_Ask(_mb_master obj,u8 ID,u16 Addr,u16 Mem,...);
u8 mb_Master_RD_IN_REG_Var_Ask(_mb_master obj,u8 ID,u16 Addr,u16 Mem,...);

u8 mb_Master_RD_OUT_COILS_Ask(_mb_master obj,u8 ID,u16 Addr,u16 Mem,u8* Data);
u8 mb_Master_RD_IN_COILS_Ask(_mb_master obj,u8 ID,u16 Addr,u16 Mem,u8* Data);
u8 mb_Master_RD_HOLD_REGS_Ask(_mb_master obj,u8 ID,u16 Addr,u16 Mem,u16* Data);
u8 mb_Master_RD_IN_REGS_Ask(_mb_master obj,u8 ID,u16 Addr,u16 Mem,u16* Data);
#define mb_Master_RD_HOLD_REGS_ADDR_Ask(obj,ID,Addr,Mem,Data) mb_Master_RD_HOLD_REGS_Ask(obj,ID,Addr,Mem,(Data)+(Addr))
#define mb_Master_RD_IN_REGS_ADDR_Ask(obj,ID,Addr,Mem,Data) mb_Master_RD_IN_REGS_Ask(obj,ID,Addr,Mem,(Data)+(Addr))
#define mb_Master_RD_OUT_COILS_ADDR_Ask(obj,ID,Addr,Mem,Data)	mb_Master_RD_OUT_COILS_Ask(obj,ID,Addr,Mem,(Data)+(Addr))
#define mb_Master_RD_IN_COILS_ADDR_Ask(obj,ID,Addr,Mem,Data)	mb_Master_RD_IN_COILS_Ask(obj,ID,Addr,Mem,(Data)+(Addr))
//----------------------------------------------------------------------------------------------------
#define mb_Master_get(x,y) mb_Master_Unpack(x,y,mb_Master_Lencount(y))
u8 mb_Master_Unpack(_mb_master obj,u8* Buff,u32 len);
u8 mb_Master_Lencount(u8* Buff);
//////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
#endif
