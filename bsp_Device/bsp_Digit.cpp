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
  * @file		bsp_Digit.cpp
  * @brief		�������ʾ��
  * @mainpage	��Ҫ��Ϣ
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		2022-11-16 19:24
  */
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	ͷ�ļ�
#include "bsp_Digit.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	��Ա����
//----------------------------------------------------------------------------------------------------
void bsp_Digit::dat(u8 SendVal) {
	for (u8 i = 0; i < 8; i++) {
		HAL_GPIO_WritePin(GPIOx_MOSIO,GPIO_Pin_MOSIO,((SendVal << i) & 0x80)?GPIO_PIN_SET: GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOx_S_CLK,GPIO_Pin_S_CLK,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOx_S_CLK, GPIO_Pin_S_CLK, GPIO_PIN_SET);}}
//----------------------------------------------------------------------------------------------------
void bsp_Digit::com(void) {
	HAL_GPIO_WritePin(GPIOx_R_CLK, GPIO_Pin_R_CLK, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOx_R_CLK, GPIO_Pin_R_CLK, GPIO_PIN_SET);}
//----------------------------------------------------------------------------------------------------
void bsp_Digit::DatCom(u8 SendVal,u8 cha){
	u16 i=0xFFFF/division;
	dat(Polarity?~digit_ca[SendVal]:digit_ca[SendVal]);
	dat(1<<cha);
	com();
	while(++i);}
//----------------------------------------------------------------------------------------------------
void bsp_Digit::num(u16 num){
	DatCom(num%10,0);num/=10;
	DatCom(num%10,1);num/=10;
	DatCom(num%10,2);num/=10;
	DatCom(num%10,3);num/=10;}
//----------------------------------------------------------------------------------------------------
void bsp_Digit::dop(u8 cha){
	u16 i=0xFFFF/division;
	dat(Polarity?0x80:0x7E);
	dat(1<<cha);
	com();
	while(++i);}
//----------------------------------------------------------------------------------------------------
void bsp_Digit::numdop(u16 num,u8 cha){
	bsp_Digit::num(num);
	bsp_Digit::dop(cha);}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	���캯��
bsp_Digit::bsp_Digit(
	GPIO_TypeDef* GPIOx_MOSIO, uint16_t GPIO_Pin_MOSIO,
	GPIO_TypeDef* GPIOx_S_CLK, uint16_t GPIO_Pin_S_CLK,
	GPIO_TypeDef* GPIOx_R_CLK, uint16_t GPIO_Pin_R_CLK,
	bool Polarity){
	bsp_Digit::division=2;
	bsp_Digit::Polarity = Polarity;
	bsp_Digit::GPIOx_MOSIO = GPIOx_MOSIO;
	bsp_Digit::GPIO_Pin_MOSIO = GPIO_Pin_MOSIO;
	bsp_Digit::GPIOx_S_CLK = GPIOx_S_CLK;
	bsp_Digit::GPIO_Pin_S_CLK = GPIO_Pin_S_CLK;
	bsp_Digit::GPIOx_R_CLK = GPIOx_R_CLK;
	bsp_Digit::GPIO_Pin_R_CLK = GPIO_Pin_R_CLK;}
//////////////////////////////////////////////////////////////////////////////////////////////////////
