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
  * @file		bsp_CRC.h
  * @brief		CRC16У��
  * @mainpage	��Ҫ��Ϣ
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		2022-11-21 04:10
  */
#ifndef _BSP_CRC_H
#define _BSP_CRC_H
#ifdef __cplusplus
extern "C"{
#endif
#include "varint.h"
////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------
//	����
u16 CRC16_MODBUS(u8 *pucFrame,u16 usLen);
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
#endif