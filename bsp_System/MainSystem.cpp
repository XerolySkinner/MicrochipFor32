/*----------------------------------------------------------------------------------------------------
 #
 #	Copyright (c) 2022 Yuankang Liang(XerolySkinner)
 #
 #	�������ԭ���ṩ,���κ���ʾ��ʾ
 #	���κ������,���߶����е��κ����⳥����
 #
 #	ʹ�õ��������:
 #	1.	�����������������Դ,�������������д��ԭʼ���.
 #	2.	��Ȩ�������������и�����,���Ұ�Ȩ�������������ͬʱ����.
 #	3.	��ȷ������ʹ��,����,�޸�,�ַ�,�����۱���������.
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
 * @file		MainSystem.cpp
 * @brief		ʵ����һ��C++����Ե�Ƭ������
 * @mainpage	��Ҫ��Ϣ
 * @author		Yuankang Liang(XerolySkinner)
 * @email		zabbcccbbaz@163.com
 * @version		V1.0.0
 * @date		2022-11-07 18:50
 */

//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	ͷ�ļ�
#include "vartable.h"
//----------------------------------------------------------------------------------------------------
bsp_PrintArt_STM32 com(&huart1);
bsp_IDLEUART RS485_Arm(&huart2,&htim5);
bsp_IDLEUART RS485_Ear(&huart3,&htim6);
bsp_IDLEUART RS485_Eye(&huart4,&htim7);
_mb_master wire_Arm;
_mb_master wire_Ear;
_mb_master wire_Eye;
//----------------------------------------------------------------------------------------------------
u8 transmit_RS485_Arm(u8* buff,u32 len){
	HAL_UART_Transmit_DMA(RS485_Arm.huart,buff,len);
	return 0;}

u8 transmit_RS485_Ear(u8* buff,u32 len){
	HAL_UART_Transmit_DMA(RS485_Ear.huart,buff,len);
	return 0;}

u8 transmit_RS485_Eye(u8* buff,u32 len){
	HAL_UART_Transmit_DMA(RS485_Eye.huart,buff,len);
	return 0;}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	����
//	
/**
 * @brief			��ʼ��������ײ�
 * @note			��MX���ɵ�main��,����ѭ��ǰ���ñ�����
 *
 */
void MainInit(void){
	/// @todo		�ڴ˴���д��ʼ������
	rt_kprintf("MainThread\r\n");
	RS485_Arm.init();
	RS485_Eye.init();
	RS485_Ear.init();
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_Base_Start_IT(&htim3);
	
	wire_Arm=mb_Master_create_F(transmit_RS485_Arm);
	wire_Ear=mb_Master_create_F(transmit_RS485_Ear);
	wire_Eye=mb_Master_create_F(transmit_RS485_Eye);
	
	Val_Init();
	bsp_rtThread_Init();
	while(1)osDelay(1000);
	return;}
//////////////////////////////////////////////////////////////////////////////////////////////////////

