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
  * @file		bsp_ATKESP8266.h
  * @brief		ATK-ESP8266模块
  * @mainpage	主要信息
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
//	头文件
/**
 * @brief			实现驱动ATKESP8266的类
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
