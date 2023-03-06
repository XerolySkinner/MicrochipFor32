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
 * @file		bsp_IIC.cpp
 * @brief		����ʵ�����IIC����
 *				�������������������IIC����
 * @mainpage	��Ҫ��Ϣ
 * @author		Yuankang Liang(XerolySkinner)
 * @email		zabbcccbbaz@163.com
 * @version		V1.0.0
 * @date		2022-11-07 00:56
 *
 */

//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	ͷ�ļ�
#include "bsp_IIC.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	�ײ����
//	
/**
 * @brief			����IIC��ʼ�ź�
 */
void bsp_IIC::IIC_Start(void) {
	IIC_SDA(IIC_SET);
	IIC_SDA(IIC_SET);
	IIC_SCK(IIC_SET);
	IIC_Delay();
	IIC_SDA(IIC_RESET);
	IIC_Delay();
	IIC_SCK(IIC_RESET);}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			����IICֹͣ�ź�
 */
void bsp_IIC::IIC_Stop(void) {
	IIC_SDA(IIC_RESET);
	IIC_SCK(IIC_SET);
	IIC_Delay();
	IIC_SDA(IIC_SET);
	IIC_Delay();}
//----------------------------------------------------------------------------------------------------
//����Ӧ����Ӧ���ź�
/**
 * @brief			����IICӦ���ź�
 * @param	ackbit	0ΪӦ��,1λ��Ӧ��
 */
void bsp_IIC::IIC_SendAck(u8 ackbit) {
	IIC_SCK(IIC_RESET);
	IIC_SDA(ackbit);
	IIC_Delay();
	IIC_SCK(IIC_SET);
	IIC_Delay();
	IIC_SCK(IIC_RESET);
	IIC_SDA(IIC_SET);
	IIC_Delay();}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			�ȴ�Ӧ���ź�
 * @return			�����Ƿ��л�Ӧ
 */
u8 bsp_IIC::IIC_WaitAck(void) {
	u8 ackbit;
	IIC_SCK(IIC_SET);
	IIC_Delay();
	ackbit = IIC_SDA(IIC_READ);
	IIC_SCK(IIC_RESET);
	IIC_Delay();
	return ackbit;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			����IICһ���ֽ��ź�
 * @param	byt		���͵��ֽ�
 */
void bsp_IIC::IIC_SendByte(u8 byt) {
	u8 i;
	for (i = 0; i < 8; i++) {
		IIC_SCK(IIC_RESET);
		IIC_Delay();
		IIC_SDA((byt & 0x80) != 0);
		IIC_Delay();
		IIC_SCK(IIC_SET);
		byt <<= 1;
		IIC_Delay();}
	IIC_SCK(IIC_RESET);}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			����IICһ���ֽ��ź�
 * @return			���յ���һ���ֽ��ź�
 */
u8 bsp_IIC::IIC_RecByte(void) {
	u8 i=0, da=0;
	for (i = 0; i < 8; i++) {
		IIC_SCK(IIC_SET);
		IIC_Delay();
		da <<= 1;
		if (IIC_SDA(IIC_READ))da |= 1;
		IIC_SCK(IIC_RESET);
		IIC_Delay();}
	return da;}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	��װ����
//	
/**
 * @brief			ʹ�����߷���һ���ֽ�����
 * 
 * @param	id		���͵�������ַ,��0x68(MPU6050)
 * @param	addr	��Ҫ��д�ļĴ�����ַ
 * @param	dat 	��д������
 * @return			�޷���ֵ
 */ 
void bsp_IIC::IIC_WriteOneByte(u8 id, u8 addr, u8 dat) {
	IIC_Start();
	IIC_SendByte(id << 1);
	IIC_WaitAck();
	IIC_SendByte(addr);
	IIC_WaitAck();
	IIC_SendByte(dat);
	IIC_WaitAck();
	IIC_Stop();}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			ʹ�����߽���һ���ֽ�����
 * 
 * @param	id		���յ�������ַ,��0x68(MPU6050)
 * @param	addr	��Ҫ��ȡ���ݵļĴ�����ַ
 * @return			���ظüĴ����ڵ�����
 */
u8 bsp_IIC::IIC_ReadOneByte(u8 id, u8 addr) {
	u8 temp = 0;
	IIC_Start();
	IIC_SendByte(id << 1);
	IIC_WaitAck();
	IIC_SendByte(addr);
	IIC_SendAck(0);
	IIC_Start();
	IIC_SendByte((id << 1) | 0x01);
	IIC_SendAck(0);
	temp = IIC_RecByte();
	IIC_SendAck(1);
	IIC_Stop();
	return temp;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			ʹ�����߷��Ͷ�������
 * 
 * @param	id		���͵�������ַ,��0x68(MPU6050)
 * @param	addr	��Ҫ��д�ļĴ�����ַ��ʼ
 * @param	dat 	��д������ָ��
 * @param	len		������Ŀ
 * @return			�޷���ֵ
 */
void bsp_IIC::IIC_Write(u8 id,u8 addr,u8* dat,u32 len){
	IIC_Start();
	IIC_SendByte(id<<1);
	IIC_WaitAck();
	IIC_SendByte(addr);
	IIC_WaitAck();
	for(int i=0;i<len;i++){
		IIC_SendByte(dat[i]);
		IIC_WaitAck();}
	IIC_Stop();
	return;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			ʹ�����߽��ն�������
 * 
 * @param	id		���յ�������ַ,��0x68(MPU6050)
 * @param	addr	��Ҫ���յļĴ�����ַ��ʼ
 * @param	dat 	��д������ָ��
 * @param	len		������Ŀ
 * @return			�޷���ֵ
 */
void bsp_IIC::IIC_Read(u8 id,u8 addr,u8* dat,u32 len){
	IIC_Start();
	IIC_SendByte(id<<1);
	IIC_WaitAck();
	IIC_SendByte(addr);
	IIC_SendAck(0);
	IIC_Start();
	IIC_SendByte((id<<1)|0x01);
	IIC_SendAck(0);
	for(int i=0;i<len;i++){
		dat[i]=IIC_RecByte();
		IIC_SendAck(i==(len-1));}
	IIC_Stop();
	return;}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	bsp����
#ifdef _STM32_HAL_
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
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////

