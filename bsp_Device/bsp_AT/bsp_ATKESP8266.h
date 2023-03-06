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
  * @file		bsp_ATKESP8266.h
  * @brief		ATK-ESP8266ģ��
  * @mainpage	��Ҫ��Ϣ
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		2022-11-25 00:18
  */
#pragma once
#ifdef __cplusplus
#include "bsp_AT.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	ͷ�ļ�
/**
 * @brief			ʵ������ATKESP8266����
 */
class bsp_ATKESP8266 :public bsp_AT{
	public:
		void TCP_Service_T(u8 cha, u32 len);
		void TCP_Client_T(void);
		void UDP_Service_T(u32 len);
	public:
		void AP_TCP_Service(
			const char* SSID,
			const char* PIN,
			const char* port);
		void AP_TCP_Client(
			const char* SSID,
			const char* PIN,
			const char* IP,
			const char* port);
		void AP_UDP(
			const char* SSID,
			const char* PIN,
			const char* IP,
			const char* port);	
	public:
		void STA_TCP_Service(
			const char* WIFISSID,
			const char* WIFIPIN,
			const char* port);
		void STA_TCP_Client(
			const char* WIFISSID,
			const char* WIFIPIN,
			const char* IP,
			const char* port);
		void STA_UDP(
			const char* WIFISSID,
			const char* WIFIPIN,
			const char* IP,
			const char* port);
	public:
		void APSTA_TCP_Service(
			const char* SSID,
			const char* PIN,
			const char* WIFISSID,
			const char* WIFIPIN,
			const char* port);
		void APSTA_TCP_Client(
			const char* SSID,
			const char* PIN,
			const char* WIFISSID,
			const char* WIFIPIN,
			const char* IP,
			const char* port);
		void APSTA_UDP(
			const char* SSID,
			const char* PIN,
			const char* WIFISSID,
			const char* WIFIPIN,
			const char* IP,
			const char* port);
	public:
		virtual void Transmit(u8* dat, u16 len);
	};
//////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
