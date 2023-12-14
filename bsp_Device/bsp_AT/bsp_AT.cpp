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
  * @file		bsp_AT.cpp
  * @brief		ATָ�
  * @mainpage	��Ҫ��Ϣ
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		2022-11-25 00:00
  */
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	ͷ�ļ�
#include "bsp_AT.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	�ຯ��
/**
 * @brief			����һ��ATָ��,�Ѽ�AT+��\r\nβ
 * @param	dat 	����������
 */
void bsp_AT::com(const char* dat) {
	Transmit((u8*)"AT+", 3);
	Transmit((u8*)dat, strlen(dat));
	Transmit((u8*)"\r\n", 2);}
//////////////////////////////////////////////////////////////////////////////////////////////////////