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
 * @file		bsp_IIC.h
 * @brief		����ʵ�����IIC����
 *				�������������������IIC����
 * @mainpage	��Ҫ��Ϣ
 * @author		Yuankang Liang(XerolySkinner)
 * @email		zabbcccbbaz@163.com
 * @version		V1.0.0
 * @date		2022-11-07 00:56
 */

#ifdef __cplusplus
#pragma once
#include "User.h"
#include "varint.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	ö��ͷ
/**
 * @brief 		���ƹܽŵ�����״̬(��λ,��λ,��ȡ)
 */
enum {
	IIC_RESET,			///< �ܽŸ�λ״̬
	IIC_SET,			///< �ܽ���λ״̬
	IIC_READ			///< ��ȡ�ܽ�״̬
};
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	��Ŀ
/**
 * @brief 		IIC�Ļ���ʵ�ַ���
 * 				�������������Խӿ���Ҫʵ��,�ֱ��ǿ���ʱ��,��������,��ʱ����
 */
class bsp_IIC{
	public:
		void	IIC_WriteOneByte(u8 id, u8 addr, u8 dat);
		u8		IIC_ReadOneByte(u8 id, u8 addr);
		void	IIC_Write(u8 id,u8 addr,u8* dat,u32 len);
		void	IIC_Read(u8 id,u8 addr,u8* dat,u32 len);
	public:
		void	IIC_Start(void);
		void	IIC_Stop(void);
		void	IIC_SendAck(u8 ackbit);
		u8		IIC_WaitAck(void);
		void	IIC_SendByte(u8 byt);
		u8		IIC_RecByte(void);
	protected:
		/**
		 * @brief			����SCK�ܽſ�
		 * 
		 * @param	var		�˴�������״̬,IIC_SET��λ�ܽ�,IIC_RESET��λ�ܽ�
		 * @return			��varΪIIC_READʱ���عܽ�״̬
		 * @todo			��ҪΪ��ʵ�ֲſ�ʹ�����IIC
		 */ 
		virtual u8 IIC_SCK(u8 var) = 0;
		/**
		 * @brief			����SDA�ܽſ�
		 * 
		 * @param	var		�˴�������״̬,IIC_SET��λ�ܽ�,IIC_RESET��λ�ܽ�
		 * @return			��varΪIIC_READʱ���عܽ�״̬
		 * @todo			��ҪΪ��ʵ�ֲſ�ʹ�����IIC
		 */ 
		virtual u8 IIC_SDA(u8 var) = 0;
		/**
		 * @brief			ʱ���е���ʱ
		 * 					�ڴ˴�������ʱ
		 * @todo			��ҪΪ��ʵ�ֲſ�ʹ�����IIC
		 */ 
		virtual void IIC_Delay(void) = 0;
	};
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	bsp����
#ifdef _STM32_HAL_
#include "gpio.h"
/**
 * @brief 		STM32�汾�����IIC
 * 				��Ҫʹ�ù��캯����ʼ��
 */
class bsp_IIC_STM32 :public bsp_IIC{
	public:
		bsp_IIC_STM32(GPIO_TypeDef *GPIOx_SCK,uint16_t GPIO_Pin_SCK,GPIO_TypeDef *GPIOx_SDA,uint16_t GPIO_Pin_SDA);
	protected:
		virtual u8 IIC_SCK(u8 var);
		virtual u8 IIC_SDA(u8 var);
		virtual void IIC_Delay(void);
	public:
		GPIO_TypeDef		*GPIOx_SCK;
		uint16_t			GPIO_Pin_SCK;
		GPIO_TypeDef		*GPIOx_SDA;
		uint16_t			GPIO_Pin_SDA;
	};
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

