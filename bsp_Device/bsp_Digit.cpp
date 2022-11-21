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
  * @file		bsp_Digit.cpp
  * @brief		数码管显示类
  * @mainpage	主要信息
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		2022-11-16 19:24
  */
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	头文件
#include "bsp_Digit.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	成员函数
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
//	构造函数
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
