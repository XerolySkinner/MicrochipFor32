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
  * @file		mbs_ModBusRTU.h
  * @brief		从机ModBusRTU
  * @mainpage	主要信息
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		Thu Sep 21 17:08:59 2023

  */
#ifndef _mbs_ModBusRTU_H
#define _mbs_ModBusRTU_H
#ifdef __cplusplus
extern "C"{
#endif
#include "mb_ModbusRTU.h"
#include "varint.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	类型
/**
 * @brief			ModBusRTU_Slave结构体
 */
typedef struct{
	//	本征数据
	u8 				ID;								//	从机结构体
	u8				mask_id;						//	掩码ID
	u8				mask;							//	掩码
	//	发送接口
	mb_transmit 	tramsmit;						//	发送函数
	u8*				TxBuff;							//	接受缓冲区
	u32				TxLen;							//	长度
	u32				TxMaxLen;						//	分配长度
	//	数据池
	u8			 	Func;							//	接受功能码
	u16				Addr;							//	地址头部
	u16				Mem;							//	数量头部
	u8				Byte;							//	字节数
	u16				Data;							//	单个字节
	
	u8*				RxBuff;							//	接受缓冲区
	u32				RxMaxLen;						//	分配长度
	
	
	//	池数据
	u8*				InCoilPool;						//	离散输入线圈池
	u8*				OutCoilPool;					//	离散输出线圈池
	u16*			InRegPool;						//	输入寄存器池
	u16*			HoldRegPool;					//	保持寄存器池
	//	池大小
	u32				InCoilPoolSize;					//	离散输入线圈池
	u32				OutCoilPoolSize;				//	离散输出线圈池
	u32				InRegPoolSize;					//	输入寄存器池
	u32				HoldRegPoolSize;				//	保持寄存器池
}_mb_struct_slave;
typedef _mb_struct_slave* _mb_slave;
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	定义
/**
 * @brief			TODO
 */
#define mb_Slave_create_IFOH(I,F,O,H) mb_Slave_create("-ID-TxBuffSize-RxBuffSize-transmit-OutCoil-HoldRegPool",I,Default_Buff,Default_Buff,F,O,H)
#define mb_Slave_create_IFCR(I,F,C,R) mb_Slave_create("-ID-TxBuffSize-RxBuffSize-transmit-OutCoil-HoldRegPool-InCoil-InRegPool",I,Default_Buff,Default_Buff,F,C,R,C,R)

_mb_slave mb_Slave_create(const char* str,...);
//----------------------------------------------------------------------------------------------------
u8 mb_Slave_WR_COIL_Ack(_mb_slave obj,u16 Addr,u16 Data);
u8 mb_Slave_WR_REG_Ack(_mb_slave obj,u16 Addr,u16 Data);
u8 mb_Slave_WR_REGS_Ack(_mb_slave obj,u16 Addr,u16 Mem);
u8 mb_Slave_WR_COILS_Ack(_mb_slave obj,u16 Addr,u16 Mem);

u8 mb_Slave_RD_OUT_COIL_Ack(_mb_slave obj,u16 Mem,u8* Data);
u8 mb_Slave_RD_IN_COIL_Ack(_mb_slave obj,u16 Mem,u8* Data);
u8 mb_Slave_RD_HOLD_REG_Ack(_mb_slave obj,u8 Mem,u16* Data);
u8 mb_Slave_RD_IN_REG_Ack(_mb_slave obj,u8 Mem,u16* Data);
//----------------------------------------------------------------------------------------------------
u8 yr_Slave_WR_In_REGS_Ask(_mb_slave obj,u8 ID,u16 Addr,u16 Mem,u16* Data);
u8 yr_Slave_WR_Hold_REGS_Ask(_mb_slave obj,u8 ID,u16 Addr,u16 Mem,u16* Data);
u8 yr_Slave_WR_In_COILS_Ask(_mb_slave obj,u8 ID,u16 Addr,u16 Mem,u8* Data);
u8 yr_Slave_WR_Out_COILS_Ask(_mb_slave obj,u8 ID,u16 Addr,u16 Mem,u8* Data);
//----------------------------------------------------------------------------------------------------
#define mb_Slave_get(x,y) mb_Slave_Unpack(x,y,mb_Slave_Lencount(y))
u8 mb_Slave_Unpack(_mb_slave obj,u8* Buff,u32 len);
u8 mb_Slave_Ack(_mb_slave obj);
u8 mb_Slave_Pool(_mb_slave obj);
u8 mb_Slave_Lencount(u8* Buff);
//////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
#endif
