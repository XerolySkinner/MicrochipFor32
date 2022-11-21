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
  * @file		bsp_ModBus.cpp
  * @brief		ModBus通信函数
  * @mainpage	主要信息
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		2022-11-21 17:09
  */
#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	头文件
#include "bsp_ModBus.h"
#include "bsp_CRC.h"
#include <stdio.h>
#include <stdlib.h>
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	类函数
/**
 * @brief			发送读取保存寄存器的指令
 * @param	address	读取的地址
 * @param	mem		读取的个数
 * @return			无返回值
 */
void bsp_ModBus_Tx::ReadKeepReg(u16 address, u16 mem) {
	u8 dat[8];
	u16 crc;
	dat[0] = ID;
	dat[1] = Fun_R_KeepReg;
	dat[2] = ((u8*)(&address))[1];
	dat[3] = ((u8*)(&address))[0];
	dat[4] = ((u8*)(&mem))[1];
	dat[5] = ((u8*)(&mem))[0];
	crc = CRC16_MODBUS(dat, 6);
	dat[6] = ((u8*)(&crc))[0];
	dat[7] = ((u8*)(&crc))[1];
	Transmit(dat,8);}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			发送读取输入寄存器的指令
 * @param	address	读取的地址
 * @param	mem		读取的个数
 * @return			无返回值
 */
void bsp_ModBus_Tx::ReadInReg(u16 address, u16 mem) {
	u8 dat[8];
	u16 crc;
	dat[0] = ID;
	dat[1] = Fun_R_InReg;
	dat[2] = ((u8*)(&address))[1];
	dat[3] = ((u8*)(&address))[0];
	dat[4] = ((u8*)(&mem))[1];
	dat[5] = ((u8*)(&mem))[0];
	crc = CRC16_MODBUS(dat,6);
	dat[6] = ((u8*)(&crc))[0];
	dat[7] = ((u8*)(&crc))[1];
	Transmit(dat, 8);}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			发送写一个寄存器的指令
 * @param	address	写入的地址
 * @param	var		写入的值
 * @return			无返回值
 */
void bsp_ModBus_Tx::WriteOneReg(u16 address, u16 var) {
	u8 dat[8];
	u16 crc;
	dat[0] = ID;
	dat[1] = Fun_W_OneReg;
	dat[2] = ((u8*)(&address))[1];
	dat[3] = ((u8*)(&address))[0];
	dat[4] = ((u8*)(&var))[1];
	dat[5] = ((u8*)(&var))[0];
	crc = CRC16_MODBUS(dat, 6);
	dat[6] = ((u8*)(&crc))[0];
	dat[7] = ((u8*)(&crc))[1];
	Transmit(dat, 8);}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			发送写多个寄存器的指令
 * @param	address	写入的地址
 * @param	mem		写入的个数
 * @param	*var	待写入数据的缓冲区
 * @return			无返回值
 * @note			简单通信建议使用WriteRegsVar
 */
void bsp_ModBus_Tx::WriteRegs(u16 address,u16 mem,u16* var) {
	u8 bytes = 9 + mem * 2;
	u8* dat = (u8*)malloc(bytes);
	if (dat == NULL)return;
	u16 crc;
	dat[0] = ID;
	dat[1] = Fun_W_Regs;
	dat[2] = ((u8*)(&address))[1];
	dat[3] = ((u8*)(&address))[0];
	dat[4] = ((u8*)(&mem))[1];
	dat[5] = ((u8*)(&mem))[0];
	dat[6] = mem*2;
	//	填入数据
	for (u8 i = 0; i < mem; i++){
		dat[7 + i*2] = ((u8*)var)[1+i*2];
		dat[8 + i*2] = ((u8*)var)[0+i*2];}
	crc = CRC16_MODBUS(dat, bytes - 2);
	dat[bytes - 2] = ((u8*)(&crc))[0];
	dat[bytes - 1] = ((u8*)(&crc))[1];
	Transmit(dat, bytes);
	free(dat);}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			发送写多个寄存器的指令
 * @param	address	写入的地址
 * @param	mem		写入的个数
 * @param	var		写入的数据
 *					根据mem的数量决定此处数量
 * @return			无返回值
 */
void bsp_ModBus_Tx::WriteRegsVar(u16 address, u16 mem,...) {
	va_list table;
	va_start(table,mem);
	u16 vars;
	u8 bytes = 9 + mem * 2;
	u8* dat = (u8*)malloc(bytes);
	if (dat == NULL)return;
	u16 crc;
	dat[0] = ID;
	dat[1] = Fun_W_Regs;
	dat[2] = ((u8*)(&address))[1];
	dat[3] = ((u8*)(&address))[0];
	dat[4] = ((u8*)(&mem))[1];
	dat[5] = ((u8*)(&mem))[0];
	dat[6] = mem*2;
	//	填入数据
	for (u8 i = 0; i < mem; i++){
		vars=va_arg(table, u32);
		dat[7 + i*2] = ((u8*)(&vars))[1];
		dat[8 + i*2] = ((u8*)(&vars))[0];}
	crc = CRC16_MODBUS(dat, bytes - 2);
	dat[bytes - 2] = ((u8*)(&crc))[0];
	dat[bytes - 1] = ((u8*)(&crc))[1];
	Transmit(dat, bytes);
	free(dat);
	va_end(table);}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			发送读输出线圈的指令
 * @param	address	读取的地址
 * @param	mem		读取的个数
 * @return			无返回值
 */
void bsp_ModBus_Tx::ReadOutCoil(u16 address, u16 mem) {
	u8 dat[8];
	u16 crc;
	dat[0] = ID;
	dat[1] = Fun_R_OutCoil;
	dat[2] = ((u8*)(&address))[1];
	dat[3] = ((u8*)(&address))[0];
	dat[4] = ((u8*)(&mem))[1];
	dat[5] = ((u8*)(&mem))[0];
	crc = CRC16_MODBUS(dat, 6);
	dat[6] = ((u8*)(&crc))[0];
	dat[7] = ((u8*)(&crc))[1];
	Transmit(dat, 8);}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			发送读输入线圈的指令
 * @param	address	读取的地址
 * @param	mem		读取的个数
 * @return			无返回值
 */
void bsp_ModBus_Tx::ReadInCoil(u16 address, u16 mem) {
	u8 dat[8];
	u16 crc;
	dat[0] = ID;
	dat[1] = Fun_R_InCoil;
	dat[2] = ((u8*)(&address))[1];
	dat[3] = ((u8*)(&address))[0];
	dat[4] = ((u8*)(&mem))[1];
	dat[5] = ((u8*)(&mem))[0];
	crc = CRC16_MODBUS(dat, 6);
	dat[6] = ((u8*)(&crc))[0];
	dat[7] = ((u8*)(&crc))[1];
	Transmit(dat, 8);}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			发送写入一个线圈的指令
 * @param	address	写入的地址
 * @param	state	写入的状态
 *					0:复位
 *					其他:置位
 * @return			无返回值
 */
void bsp_ModBus_Tx::WriteOneCoil(u16 address, u16 state){
	u8 dat[8];
	u16 var = state ? 0xFF00 : 0x0000;
	u16 crc;
	dat[0] = ID;
	dat[1] = Fun_W_OneCoil;
	dat[2] = ((u8*)(&address))[1];
	dat[3] = ((u8*)(&address))[0];
	dat[4] = ((u8*)(&var))[1];
	dat[5] = ((u8*)(&var))[0];
	crc = CRC16_MODBUS(dat, 6);
	dat[6] = ((u8*)(&crc))[0];
	dat[7] = ((u8*)(&crc))[1];
	Transmit(dat, 8);}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			发送写多个线圈的指令
 * @param	address	写入的地址
 * @param	mem		写入的个数
 * @param	*var	待写入数据的缓冲区
 * @return			无返回值
 * @note			简单通信建议使用WriteCoilsVar
 */
void bsp_ModBus_Tx::WriteCoils(u16 address, u16 mem, u8* var) {
	u8 bytes = (mem / 8) + (mem % 8 != 0) + 9;
	u8* dat = (u8*)malloc(bytes);
	if (dat == NULL)return;
	u16 crc;
	dat[0] = ID;
	dat[1] = Fun_W_Coils;
	dat[2] = ((u8*)(&address))[1];
	dat[3] = ((u8*)(&address))[0];
	dat[4] = ((u8*)(&mem))[1];
	dat[5] = ((u8*)(&mem))[0];
	dat[6] = bytes - 9;
	//	填入数据
	for (u8 i = 0; i < bytes - 9; i++)dat[7 + i] = var[i];
	crc = CRC16_MODBUS(dat, bytes - 2);
	dat[bytes - 2] = ((u8*)(&crc))[0];
	dat[bytes - 1] = ((u8*)(&crc))[1];
	Transmit(dat, bytes);
	free(dat);}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			发送写多个线圈的指令
 * @param	address	写入的地址
 * @param	mem		写入的个数
 * @param	var		写入的数据
 *					根据mem的数量决定此处数量
 * @return			无返回值
 */
void bsp_ModBus_Tx::WriteCoilsVar(u16 address, u16 mem,...) {
	va_list table;
	va_start(table,mem);
	u8 var=0;
	u16 crc;
	u8 bytes = (mem / 8) + (mem % 8 != 0) + 9;
	u8* dat = (u8*)malloc(bytes);
	if (dat == NULL)return;
	dat[0] = ID;
	dat[1] = Fun_W_Coils;
	dat[2] = ((u8*)(&address))[1];
	dat[3] = ((u8*)(&address))[0];
	dat[4] = ((u8*)(&mem))[1];
	dat[5] = ((u8*)(&mem))[0];
	dat[6] = bytes - 9;
	//	填入管脚信息
	for(u16 i=0;i<mem;i++){
		var=va_arg(table,u32);
		if(var)
			dat[7 + (i/8)]|=1<<(i%8);
		else
			dat[7 + (i/8)]&=~(1<<(i%8));}
	crc = CRC16_MODBUS(dat, bytes - 2);
	dat[bytes - 2] = ((u8*)(&crc))[0];
	dat[bytes - 1] = ((u8*)(&crc))[1];
	Transmit(dat, bytes);
	free(dat);
	va_end(table);}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	类函数
/**
 * @brief			以ModBus协议分析缓冲区内数据
 * @param	*dat	待分析的缓冲区
 * @return			无返回值
 */
void bsp_ModBus_Rx::analysis(u8* dat) {
	u16 crc = 0;
	ID = dat[0];
	Func = dat[1];
	//	释放缓存内存
	free(OutCoilDat);
	free(InCoilDat);
	free(KeepRegDat);
	free(InRegDat);
	//	CRC检验
	if (Func == Fun_R_OutCoil ||
		Func == Fun_R_InCoil ||
		Func == Fun_R_KeepReg ||
		Func == Fun_R_InReg) {
		crc = CRC16_MODBUS(dat, dat[2] + 3);
		crcts = (	((u8*)(&crc))[1] == dat[dat[2] + 3] &&
					((u8*)(&crc))[0] == dat[dat[2] + 4]);}
	switch (Func) {
		case Fun_R_OutCoil:
			//	输出线圈
			OutCoilMem = dat[2];
			OutCoilDat = (u8*)malloc(OutCoilMem);
			if (OutCoilDat == NULL)break;
			for (u8 i = 0; i < OutCoilMem; i++)
				OutCoilDat[i] = dat[3 + i];
			break;
		case Fun_R_InCoil:
			//	输入线圈
			InCoilMem = dat[2];
			InCoilDat = (u8*)malloc(InCoilMem);
			if (InCoilDat == NULL)break;
			for (u8 i = 0; i < InCoilMem; i++)
				InCoilDat[i] = dat[3 + i];
			break;
		case Fun_R_KeepReg:
			//	保持寄存器
			KeepRegMem = dat[2] / 2;
			KeepRegDat = (u16*)malloc(KeepRegMem * 2);
			if (KeepRegDat == NULL)break;
			for (u8 i = 0; i < KeepRegMem; i++) {
				((u8*)KeepRegDat)[1 + i * 2] = dat[3 + i * 2];
				((u8*)KeepRegDat)[0 + i * 2] = dat[4 + i * 2];}
				break;
		case Fun_R_InReg:
			//	输入寄存器
			InRegMem = dat[2] / 2;
			InRegDat = (u16*)malloc(InRegMem * 2);
			if (InRegDat == NULL)break;
			for (u8 i = 0; i < InRegMem; i++) {
				((u8*)InRegDat)[1 + i * 2] = dat[3 + i * 2];
				((u8*)InRegDat)[0 + i * 2] = dat[4 + i * 2];}
			break;
		default:
			//	写回显与其他
			break;}}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	构造函数
bsp_ModBus_Tx::bsp_ModBus_Tx(u8 ID) {
	bsp_ModBus_Tx::ID = ID;}
//----------------------------------------------------------------------------------------------------
bsp_ModBus_Rx::bsp_ModBus_Rx(void) {
	KeepRegDat = NULL;
	InRegDat = NULL;
	OutCoilDat = NULL;
	InCoilDat = NULL;}
//----------------------------------------------------------------------------------------------------
bsp_ModBus_Rx::~bsp_ModBus_Rx(void){
	free(OutCoilDat);
	free(InCoilDat);
	free(KeepRegDat);
	free(InRegDat);}
//////////////////////////////////////////////////////////////////////////////////////////////////////
