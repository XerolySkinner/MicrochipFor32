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
  * @file		bsp_ATKESP8266.cpp
  * @brief		ATK-ESP8266ģ��
  * @mainpage	��Ҫ��Ϣ
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		2022-11-25 00:18
  */
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	ͷ�ļ�
#include "bsp_ATKESP8266.h"
#include <stdio.h>
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	�ຯ��
/**
 * @brief			����ΪAP,TCP������ģʽ
 * @param	SSID 	������������
 * @param	PIN 	������������
 * @param	port 	���ÿ��Ŷ˿�
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
 * @brief			����ΪAP,TCP�ͻ���ģʽ
 * @param	SSID 	������������
 * @param	PIN 	������������
 * @param	IP 		�������ӵ�IP
 * @param	port 	���ÿ��Ŷ˿�
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
 * @brief			����ΪAP,UDPģʽ
 * @param	SSID 	������������
 * @param	PIN 	������������
 * @param	IP 		�������ӵ�IP
 * @param	port 	���ÿ��Ŷ˿�
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
 * @brief				����ΪSTA,TCP�ͻ���ģʽ
 * @param	WIFISSID 	����������������
 * @param	WIFIPIN 	����������������
 * @param	port 		�������Ӷ˿�
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
 * @brief				����ΪSTA,TCP�ͻ���ģʽ
 * @param	WIFISSID 	����������������
 * @param	WIFIPIN 	����������������
 * @param	IP 			��������IP
 * @param	port 		�������Ӷ˿�
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
 * @brief				����ΪSTA,UDPģʽ
 * @param	WIFISSID 	����������������
 * @param	WIFIPIN 	����������������
 * @param	IP 			��������IP
 * @param	port 		�������Ӷ˿�
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
 * @brief				����ΪAP&STA,TCP������ģʽ
 * @param	SSID	 	������������
 * @param	PIN			������������
 * @param	WIFISSID 	����������������
 * @param	WIFIPIN 	����������������
 * @param	port 		���ÿ��Ŷ˿�
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
 * @brief				����ΪAP&STA,TCP�ͻ���ģʽ
 * @param	SSID	 	������������
 * @param	PIN			������������
 * @param	WIFISSID 	����������������
 * @param	WIFIPIN 	����������������
 * @param	IP			��������IP
 * @param	port 		�������Ӷ˿�
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
 * @brief				����ΪAP&STA,UDPģʽ
 * @param	SSID	 	������������
 * @param	PIN			������������
 * @param	WIFISSID 	����������������
 * @param	WIFIPIN 	����������������
 * @param	IP			��������IP
 * @param	port 		�������Ӷ˿�
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
 * @brief				׼����������
 * @param	cha		 	���Ͷ˿�
 * @param	len			���ݳ���
 */
void bsp_ATKESP8266::TCP_Service_T(u8 cha, u32 len) {
	char dat[50] = { "" };
	sprintf(dat, "CIPSEND=%d,%d", cha,len); com(dat);}
//----------------------------------------------------------------------------------------------------
/**
 * @brief				׼����������
 */
void bsp_ATKESP8266::TCP_Client_T(void) {
	com("CIPSEND");}
//----------------------------------------------------------------------------------------------------
/**
 * @brief				׼����������
 * @param	len			���ݳ���
 */
void bsp_ATKESP8266::UDP_Service_T(u32 len) {
	char dat[50] = { "" };
	sprintf(dat, "CIPSEND=%d",len); com(dat);}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	���캯��
void bsp_ATKESP8266::Transmit(u8* dat, u16 len) {
	for (u32 i = 0; i < len; i++)
		printf("%c", dat[i]);}
//////////////////////////////////////////////////////////////////////////////////////////////////////
