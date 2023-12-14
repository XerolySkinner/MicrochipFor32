/*----------------------------------------------------------------------------------------------------
 #
 #	Copyright (c) 2022 Yuankang Liang(XerolySkinner)
 #
 #	��������ԭ���ṩ,���κ���ʾ��ʾ
 #	���κ������,���߶����е��κ����⳥����
 #
 #	ʹ�õ���������:
 #	1.	������������������Դ,�㲻���������д��ԭʼ����.
 #	2.	����������κ�Ŀ��,ǰ���ǰ�Ȩ�������������и�����.
 #		���Ұ�Ȩ��������������ͬʱ����.
 #	3.	����ʹ��,����,�޸�,�ַ�,�����۱�����������.
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
  * @file		bsp_AT.h
  * @brief		ATָ�
  * @mainpage	��Ҫ��Ϣ
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		2022-11-25 00:00
  */
#pragma once
#ifdef __cplusplus
#include <string.h>
#include "varint.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	ͷ�ļ�
/**
 * @brief			ATЭ��Ļ���
 */
class bsp_AT{
	public:
		void com(const char* dat);
	protected:
		/**
		 * @brief			�������ݵ��˿�
		 * @param	dat 	����ͷ
		 * @param	len 	���ݳ���
		 */
		virtual void Transmit(u8* dat, u16 len) = 0;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////
#endif