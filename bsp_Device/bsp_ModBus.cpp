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
  * @file		bsp_ModBus.cpp
  * @brief		ModBusͨ�ź���
  * @mainpage	��Ҫ��Ϣ
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		2022-11-21 17:09
  */
#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	ͷ�ļ�
#include "bsp_ModBus.h"
#include "bsp_CRC.h"
#include <stdio.h>
#include <stdlib.h>
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	�ຯ��
/**
 * @brief			���Ͷ�ȡ����Ĵ�����ָ��
 * @param	address	��ȡ�ĵ�ַ
 * @param	mem		��ȡ�ĸ���
 * @return			�޷���ֵ
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
 * @brief			���Ͷ�ȡ����Ĵ�����ָ��
 * @param	address	��ȡ�ĵ�ַ
 * @param	mem		��ȡ�ĸ���
 * @return			�޷���ֵ
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
 * @brief			����дһ���Ĵ�����ָ��
 * @param	address	д��ĵ�ַ
 * @param	var		д���ֵ
 * @return			�޷���ֵ
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
 * @brief			����д����Ĵ�����ָ��
 * @param	address	д��ĵ�ַ
 * @param	mem		д��ĸ���
 * @param	*var	��д�����ݵĻ�����
 * @return			�޷���ֵ
 * @note			��ͨ�Ž���ʹ��WriteRegsVar
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
	//	��������
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
 * @brief			����д����Ĵ�����ָ��
 * @param	address	д��ĵ�ַ
 * @param	mem		д��ĸ���
 * @param	var		д�������
 *					����mem�����������˴�����
 * @return			�޷���ֵ
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
	//	��������
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
 * @brief			���Ͷ������Ȧ��ָ��
 * @param	address	��ȡ�ĵ�ַ
 * @param	mem		��ȡ�ĸ���
 * @return			�޷���ֵ
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
 * @brief			���Ͷ�������Ȧ��ָ��
 * @param	address	��ȡ�ĵ�ַ
 * @param	mem		��ȡ�ĸ���
 * @return			�޷���ֵ
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
 * @brief			����д��һ����Ȧ��ָ��
 * @param	address	д��ĵ�ַ
 * @param	state	д���״̬
 *					0:��λ
 *					����:��λ
 * @return			�޷���ֵ
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
 * @brief			����д�����Ȧ��ָ��
 * @param	address	д��ĵ�ַ
 * @param	mem		д��ĸ���
 * @param	*var	��д�����ݵĻ�����
 * @return			�޷���ֵ
 * @note			��ͨ�Ž���ʹ��WriteCoilsVar
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
	//	��������
	for (u8 i = 0; i < bytes - 9; i++)dat[7 + i] = var[i];
	crc = CRC16_MODBUS(dat, bytes - 2);
	dat[bytes - 2] = ((u8*)(&crc))[0];
	dat[bytes - 1] = ((u8*)(&crc))[1];
	Transmit(dat, bytes);
	free(dat);}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			����д�����Ȧ��ָ��
 * @param	address	д��ĵ�ַ
 * @param	mem		д��ĸ���
 * @param	var		д�������
 *					����mem�����������˴�����
 * @return			�޷���ֵ
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
	//	����ܽ���Ϣ
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
//	�ຯ��
/**
 * @brief			��ModBusЭ�����������������
 * @param	*dat	�������Ļ�����
 * @return			�޷���ֵ
 */
void bsp_ModBus_Rx::analysis(u8* dat) {
	u16 crc = 0;
	ID = dat[0];
	Func = dat[1];
	//	�ͷŻ����ڴ�
	free(OutCoilDat);
	free(InCoilDat);
	free(KeepRegDat);
	free(InRegDat);
	//	CRC����
	if (Func == Fun_R_OutCoil ||
		Func == Fun_R_InCoil ||
		Func == Fun_R_KeepReg ||
		Func == Fun_R_InReg) {
		crc = CRC16_MODBUS(dat, dat[2] + 3);
		crcts = (	((u8*)(&crc))[1] == dat[dat[2] + 3] &&
					((u8*)(&crc))[0] == dat[dat[2] + 4]);}
	switch (Func) {
		case Fun_R_OutCoil:
			//	�����Ȧ
			OutCoilMem = dat[2];
			OutCoilDat = (u8*)malloc(OutCoilMem);
			if (OutCoilDat == NULL)break;
			for (u8 i = 0; i < OutCoilMem; i++)
				OutCoilDat[i] = dat[3 + i];
			break;
		case Fun_R_InCoil:
			//	������Ȧ
			InCoilMem = dat[2];
			InCoilDat = (u8*)malloc(InCoilMem);
			if (InCoilDat == NULL)break;
			for (u8 i = 0; i < InCoilMem; i++)
				InCoilDat[i] = dat[3 + i];
			break;
		case Fun_R_KeepReg:
			//	���ּĴ���
			KeepRegMem = dat[2] / 2;
			KeepRegDat = (u16*)malloc(KeepRegMem * 2);
			if (KeepRegDat == NULL)break;
			for (u8 i = 0; i < KeepRegMem; i++) {
				((u8*)KeepRegDat)[1 + i * 2] = dat[3 + i * 2];
				((u8*)KeepRegDat)[0 + i * 2] = dat[4 + i * 2];}
				break;
		case Fun_R_InReg:
			//	����Ĵ���
			InRegMem = dat[2] / 2;
			InRegDat = (u16*)malloc(InRegMem * 2);
			if (InRegDat == NULL)break;
			for (u8 i = 0; i < InRegMem; i++) {
				((u8*)InRegDat)[1 + i * 2] = dat[3 + i * 2];
				((u8*)InRegDat)[0 + i * 2] = dat[4 + i * 2];}
			break;
		default:
			//	д����������
			break;}}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	���캯��
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
