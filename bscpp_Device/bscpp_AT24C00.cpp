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
 * @file		bscpp_AT24C00.cpp
 * @brief		本类实现AT24C00的通讯
 * @mainpage	主要信息
 * @author		Yuankang Liang(XerolySkinner)
 * @email		zabbcccbbaz@163.com
 * @version		V1.0.0
 * @date		2022-11-07 14:09
 */

//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	头文件
#include "varint.h"
#include "main.h"
#include "bscpp_AT24C00.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	程序
//	
/**
 * @brief			实现AT定制的IIC延时时间
 */ 
void bscpp_STM32_AT24C00::IIC_Delay(void){
	HAL_Delay(5);}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			储存一个字节
 * @param	addr 	储存的位置
 * @param	dat 	储存的字节
 */ 
void bscpp_STM32_AT24C00::WriteOneByte(u8 addr,u8 dat){
	IIC_WriteOneByte(Address,addr,dat);}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			读取一个字节
 * @param	addr 	读取的位置
 * @return			返回读取的字节
 */ 
u8 bscpp_STM32_AT24C00::ReadOneByte(u8 addr){
	return IIC_ReadOneByte(Address,addr);}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			写入定长度的字节
 * @param	addr 	写入的位置
 * @param	*dat 	写入的数据头
 * @param	len 	写入的数据长度
 */ 
void bscpp_STM32_AT24C00::WriteByte(u8 addr,u8 *dat,u8 len){
	unsigned int member=0;
	IIC_Start();
	IIC_SendByte(Address<<1);
	IIC_WaitAck();
	IIC_SendByte(addr);
	IIC_WaitAck();
	do{
		IIC_SendByte(dat[member]);
		IIC_WaitAck();
		member++;
		if(((member+addr)%Page)==0){
			IIC_Stop();
			IIC_Delay();
			IIC_Start();
			IIC_SendByte(Address<<1);
			IIC_WaitAck();
			IIC_SendByte(addr+member);
			IIC_WaitAck();}
		}while(member!=len);
	IIC_Stop();
	IIC_Delay();}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			读取定长度的字节
 * @param	addr 	读取的位置
 * @param	*dat 	读取到的数据头
 * @param	len 	读取的数据长度
 */ 
void bscpp_STM32_AT24C00::AT_ReadByte(u8 addr,u8 *dat,u8 len){
	IIC_Read(Address,addr,dat,len);}
//////////////////////////////////////////////////////////////////////////////////////////////////////

