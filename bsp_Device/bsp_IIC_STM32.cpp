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
  * @file		 bsp_IIC_STM32.cpp
  * @brief		 ʵ�����STM32�����IIC��
  * @mainpage	 ��Ҫ��Ϣ
  * @author 	 Yuankang Liang(XerolySkinner)
  * @email		 zabbcccbbaz@163.com
  * @version	 V1.0.0
  * @date		 2022-11-07 00:56
  */

//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	ͷ�ļ�
#include "bsp_IIC_STM32.h"
#include "gpio.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	���캯��
//	
/**
 * @brief					����STM32��IIC���������
 * 
 * @param	*GPIOx_SCK		SCK�Ķ˿�
 * @param	GPIO_Pin_SCK	SCK�Ĺܿں�
 * @param	*GPIOx_SDA		SDA�Ķ˿�
 * @param	GPIO_Pin_SDA	SDA�Ĺܿں�
 */
bsp_IIC_STM32::bsp_IIC_STM32(GPIO_TypeDef *GPIOx_SCK,uint16_t GPIO_Pin_SCK,GPIO_TypeDef *GPIOx_SDA,uint16_t GPIO_Pin_SDA){
	bsp_IIC_STM32::GPIOx_SCK=GPIOx_SCK;
	bsp_IIC_STM32::GPIO_Pin_SCK=GPIO_Pin_SCK;
	bsp_IIC_STM32::GPIOx_SDA=GPIOx_SDA;
	bsp_IIC_STM32::GPIO_Pin_SDA=GPIO_Pin_SDA;}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	�������
//	
/**
 * @brief			ʱ���е���ʱ
 *					�ڴ˴�������ʱ
 */ 
void bsp_IIC_STM32::IIC_Delay(void) {
	u8 i = 0;
	while (++i);}
/**
 * @brief			����SCK�ܽſ�
 * 
 * @param	var 	�˴�������״̬,IIC_SET��λ�ܽ�,IIC_RESET��λ�ܽ�
 * @return			��varΪIIC_READʱ���عܽ�״̬
 */ 
u8 bsp_IIC_STM32::IIC_SCK(u8 var) {
	if (var == IIC_RESET) {
		HAL_GPIO_WritePin(GPIOx_SCK, GPIO_Pin_SCK, GPIO_PIN_RESET);
		return 2;}
	else if (var == IIC_SET) {
		HAL_GPIO_WritePin(GPIOx_SCK, GPIO_Pin_SCK, GPIO_PIN_SET);
		return 2;}
	else {
		return HAL_GPIO_ReadPin(GPIOx_SCK, GPIO_Pin_SCK);
	}}
/**
 * @brief			����SDA�ܽſ�
 * @param	var 	�˴�������״̬,IIC_SET��λ�ܽ�,IIC_RESET��λ�ܽ�
 * @return			��varΪIIC_READʱ���عܽ�״̬
 */ 
u8 bsp_IIC_STM32::IIC_SDA(u8 var) {
	if (var == IIC_RESET) {
		HAL_GPIO_WritePin(GPIOx_SDA, GPIO_Pin_SDA, GPIO_PIN_RESET);
		return 2;}
	else if (var == IIC_SET) {
		HAL_GPIO_WritePin(GPIOx_SDA, GPIO_Pin_SDA, GPIO_PIN_SET);
		return 2;}
	else {
		return HAL_GPIO_ReadPin(GPIOx_SDA, GPIO_Pin_SDA);
		}}
//////////////////////////////////////////////////////////////////////////////////////////////////////

