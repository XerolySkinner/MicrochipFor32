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
  * @file		bsp_ModBus.h
  * @brief		ModBusͨ�ź���
  * @mainpage	��Ҫ��Ϣ
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
//	������
enum Fun_ModBus {
	Fun_R_OutCoil	= 0x01,				///< ��ȡ�����Ȧ
	Fun_R_InCoil	= 0x02,				///< ��ȡ������Ȧ
	Fun_R_KeepReg	= 0x03,				///< ��ȡ���ּĴ�
	Fun_R_InReg		= 0x04,				///< ��ȡ����Ĵ�

	Fun_W_OneCoil	= 0x05,				///< д�뵥��Ȧ
	Fun_W_OneReg	= 0x06,				///< д�뵥�Ĵ�
	Fun_W_Coils		= 0x0F,				///< д�����Ȧ
	Fun_W_Regs		= 0x10,				///< д���Ĵ�
};
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	��Ŀ
/**
 * @brief			ModBus������
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
		u8		ID;						///< ����ID
	};
//----------------------------------------------------------------------------------------------------
/**
 * @brief			ModBusЭ�������
 */
class bsp_ModBus_Rx{
	public:
		bsp_ModBus_Rx(void);
		~bsp_ModBus_Rx(void);
	public:
		void analysis(u8* dat);
		//		���б���
		u8		ID;						///< ����ID
		u8		Func;					///< ���ܺ�
		u8		crcts;					///< CRC����
		//		���ּĴ�������
		u16		*KeepRegDat;
		u8		KeepRegMem;
		//		����Ĵ�������
		u16*	InRegDat;
		u8		InRegMem;
		//		�����Ȧ����
		u8*		OutCoilDat;
		u8		OutCoilMem;
		//		������Ȧ����
		u8*		InCoilDat;
		u8		InCoilMem;};
//////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
