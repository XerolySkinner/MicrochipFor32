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
  * @file		bsp_ATKESP8266.cpp
  * @brief		ATK-ESP8266模块
  * @mainpage	主要信息
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		2022-11-25 00:18
  */
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	头文件
#include "bsp_ATKESP8266.h"
#include <stdio.h>
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	类函数
/**
 * @brief			设置为AP,TCP服务器模式
 * @param	SSID 	设置网络名称
 * @param	PIN 	设置网络密码
 * @param	port 	设置开放端口
 */
void bsp_ATKESP8266::AP_TCP_Service(
	const char* SSID,
	const char* PIN,
	const char* port){
	char dat[100] = { "" };
	com("CWMODE=2");
	com("RST");
	sprintf(dat, "CWSAP=\"%s\",\"%s\",1,4", SSID, PIN); com(dat);
	com("CIPMUX=1");
	sprintf(dat, "CIPSERVER=1,%s", port); com(dat);}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			设置为AP,TCP客户端模式
 * @param	SSID 	设置网络名称
 * @param	PIN 	设置网络密码
 * @param	IP 		设置连接的IP
 * @param	port 	设置开放端口
 */
void bsp_ATKESP8266::AP_TCP_Client(
	const char* SSID,
	const char* PIN,
	const char* IP,
	const char* port) {
	char dat[100] = { "" };
	com("CWMODE=2");
	com("RST");
	sprintf(dat, "CWSAP=\"%s\",\"%s\",1,4", SSID, PIN); com(dat);
	com("CIPMUX=0");
	sprintf(dat, "CIPSTART=\"TCP\",\"%s\",%s", IP, port); com(dat);
	com("CIPMODE=1");}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			设置为AP,UDP模式
 * @param	SSID 	设置网络名称
 * @param	PIN 	设置网络密码
 * @param	IP 		设置连接的IP
 * @param	port 	设置开放端口
 */
void bsp_ATKESP8266::AP_UDP(
	const char* SSID,
	const char* PIN,
	const char* IP,
	const char* port) {
	char dat[100] = { "" };
	com("CWMODE=2");
	com("RST");
	sprintf(dat, "CWSAP=\"%s\",\"%s\",1,4",SSID,PIN);com(dat);
	com("CIPMUX=0");
	sprintf(dat, "CIPSTART=\"UDP\",\"%s\",%s", IP, port);com(dat);}
//////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief				设置为STA,TCP客户端模式
 * @param	WIFISSID 	设置连接网络名称
 * @param	WIFIPIN 	设置连接网络密码
 * @param	port 		设置连接端口
 */
void bsp_ATKESP8266::STA_TCP_Service(
	const char* WIFISSID, 
	const char* WIFIPIN,
	const char* port) {
	char dat[100] = { "" };
	com("CWMODE=1");
	com("RST");
	sprintf(dat, "CWJAP=\"%s\",\"%s\"", WIFISSID, WIFIPIN); com(dat);
	com("CIPMUX=1");
	sprintf(dat, "CIPSERVER=1,%s", port); com(dat);}
//----------------------------------------------------------------------------------------------------
/**
 * @brief				设置为STA,TCP客户端模式
 * @param	WIFISSID 	设置连接网络名称
 * @param	WIFIPIN 	设置连接网络密码
 * @param	IP 			设置连接IP
 * @param	port 		设置连接端口
 */
void bsp_ATKESP8266::STA_TCP_Client(
	const char* WIFISSID,
	const char* WIFIPIN,
	const char* IP,
	const char* port) {
	char dat[100] = { "" };
	com("CWMODE=1");
	com("RST");
	sprintf(dat, "CWJAP=\"%s\",\"%s\"", WIFISSID, WIFIPIN); com(dat);
	com("CIPMUX=0");
	sprintf(dat, "CIPSTART=\"TCP\",\"%s\",%s", IP, port); com(dat);
	com("CIPMODE=1");}
//----------------------------------------------------------------------------------------------------
/**
 * @brief				设置为STA,UDP模式
 * @param	WIFISSID 	设置连接网络名称
 * @param	WIFIPIN 	设置连接网络密码
 * @param	IP 			设置连接IP
 * @param	port 		设置连接端口
 */
void bsp_ATKESP8266::STA_UDP(
	const char* WIFISSID,
	const char* WIFIPIN,
	const char* IP,
	const char* port) {
	char dat[100] = { "" };
	com("CWMODE=1");
	com("RST");
	sprintf(dat, "CWJAP=\"%s\",\"%s\"", WIFISSID, WIFIPIN); com(dat);
	com("CIPMUX=0");
	sprintf(dat, "CIPSTART=\"UDP\",\"%s\",%s", IP, port); com(dat);}
//////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief				设置为AP&STA,TCP服务器模式
 * @param	SSID	 	设置网络名称
 * @param	PIN			设置网络密码
 * @param	WIFISSID 	设置连接网络名称
 * @param	WIFIPIN 	设置连接网络密码
 * @param	port 		设置开放端口
 */
void bsp_ATKESP8266::APSTA_TCP_Service(
	const char* SSID,
	const char* PIN,
	const char* WIFISSID,
	const char* WIFIPIN,
	const char* port) {
	char dat[100] = { "" };
	com("CWMODE=3");
	com("RST");
	sprintf(dat, "CWSAP=\"%s\",\"%s\",1,4", SSID, PIN); com(dat);
	sprintf(dat, "CWJAP=\"%s\",\"%s\"", WIFISSID, WIFIPIN); com(dat);
	com("CIPMUX=1");
	sprintf(dat, "CIPSERVER=1,%s", port); com(dat);
	com("CIPSTO=1200");}
//----------------------------------------------------------------------------------------------------
/**
 * @brief				设置为AP&STA,TCP客户端模式
 * @param	SSID	 	设置网络名称
 * @param	PIN			设置网络密码
 * @param	WIFISSID 	设置连接网络名称
 * @param	WIFIPIN 	设置连接网络密码
 * @param	IP			设置连接IP
 * @param	port 		设置连接端口
 */
void bsp_ATKESP8266::APSTA_TCP_Client(
	const char* SSID,
	const char* PIN,
	const char* WIFISSID,
	const char* WIFIPIN,
	const char* IP,
	const char* port) {
	char dat[100] = { "" };
	com("CWMODE=3");
	com("RST");
	sprintf(dat, "CWSAP=\"%s\",\"%s\",1,4", SSID, PIN); com(dat);
	sprintf(dat, "CWJAP=\"%s\",\"%s\"", WIFISSID, WIFIPIN); com(dat);
	com("CIPMUX=1");
	sprintf(dat, "CIPSERVER=1,%s", port); com(dat);
	com("CIPSTO=1200");
	sprintf(dat, "CIPSTART=0,\"TCP\",\"%s\",%s", IP, port); com(dat);}
//----------------------------------------------------------------------------------------------------
/**
 * @brief				设置为AP&STA,UDP模式
 * @param	SSID	 	设置网络名称
 * @param	PIN			设置网络密码
 * @param	WIFISSID 	设置连接网络名称
 * @param	WIFIPIN 	设置连接网络密码
 * @param	IP			设置连接IP
 * @param	port 		设置连接端口
 */
void bsp_ATKESP8266::APSTA_UDP(
	const char* SSID,
	const char* PIN,
	const char* WIFISSID,
	const char* WIFIPIN,
	const char* IP,
	const char* port) {
	char dat[100] = { "" };
	com("CWMODE=3");
	com("RST");
	sprintf(dat, "CWSAP=\"%s\",\"%s\",1,4", SSID, PIN); com(dat);
	sprintf(dat, "CWJAP=\"%s\",\"%s\"", WIFISSID, WIFIPIN); com(dat);
	com("CIPMUX=1");
	sprintf(dat, "CIPSERVER=1,%s", port); com(dat);
	com("CIPSTO=1200");
	sprintf(dat, "CIPSTART=0,\"UDP\",\"%s\",%s", IP, port); com(dat);}
//////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief				准备发送数据
 * @param	cha		 	发送端口
 * @param	len			数据长度
 */
void bsp_ATKESP8266::TCP_Service_T(u8 cha, u32 len) {
	char dat[50] = { "" };
	sprintf(dat, "CIPSEND=%d,%d", cha,len); com(dat);}
//----------------------------------------------------------------------------------------------------
/**
 * @brief				准备发送数据
 */
void bsp_ATKESP8266::TCP_Client_T(void) {
	com("CIPSEND");}
//----------------------------------------------------------------------------------------------------
/**
 * @brief				准备发送数据
 * @param	len			数据长度
 */
void bsp_ATKESP8266::UDP_Service_T(u32 len) {
	char dat[50] = { "" };
	sprintf(dat, "CIPSEND=%d",len); com(dat);}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	构造函数
void bsp_ATKESP8266::Transmit(u8* dat, u16 len) {
	for (u32 i = 0; i < len; i++)
		printf("%c", dat[i]);}
//////////////////////////////////////////////////////////////////////////////////////////////////////
