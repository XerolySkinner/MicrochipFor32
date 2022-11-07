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
 * @file		bscpp_AT24C00.cpp
 * @brief		����ʵ��AT24C00��ͨѶ
 * @mainpage	��Ҫ��Ϣ
 * @author		Yuankang Liang(XerolySkinner)
 * @email		zabbcccbbaz@163.com
 * @version		V1.0.0
 * @date		2022-11-07 14:09
 */

//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	ͷ�ļ�
#include "varint.h"
#include "main.h"
#include "bscpp_AT24C00.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	����
//	
/**
 * @brief			ʵ��AT���Ƶ�IIC��ʱʱ��
 */ 
void bscpp_STM32_AT24C00::IIC_Delay(void){
	HAL_Delay(5);}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			����һ���ֽ�
 * @param	addr 	�����λ��
 * @param	dat 	������ֽ�
 */ 
void bscpp_STM32_AT24C00::WriteOneByte(u8 addr,u8 dat){
	IIC_WriteOneByte(Address,addr,dat);}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			��ȡһ���ֽ�
 * @param	addr 	��ȡ��λ��
 * @return			���ض�ȡ���ֽ�
 */ 
u8 bscpp_STM32_AT24C00::ReadOneByte(u8 addr){
	return IIC_ReadOneByte(Address,addr);}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			д�붨���ȵ��ֽ�
 * @param	addr 	д���λ��
 * @param	*dat 	д�������ͷ
 * @param	len 	д������ݳ���
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
 * @brief			��ȡ�����ȵ��ֽ�
 * @param	addr 	��ȡ��λ��
 * @param	*dat 	��ȡ��������ͷ
 * @param	len 	��ȡ�����ݳ���
 */ 
void bscpp_STM32_AT24C00::AT_ReadByte(u8 addr,u8 *dat,u8 len){
	IIC_Read(Address,addr,dat,len);}
//////////////////////////////////////////////////////////////////////////////////////////////////////

