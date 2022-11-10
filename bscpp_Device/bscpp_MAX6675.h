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
  * @file		bscpp_MAX6675.h
  * @brief		ʵ����MAX6675������
  * @mainpage	��Ҫ��Ϣ
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		2022-11-11 02:01
  */

#ifdef __cplusplus
#pragma once
#include "varint.h"
#include "spi.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	��Ŀ
/**
 * @brief 		MAX6675��һ��������
 * @note		Ӳ��SPI��Ҫ��������
 *				Date Size:16 Bits
 *				MSB First
 *				��Ƶ�ٶȺ��ʼ���
 *				��Ҫ׼��һ��CS�ܽ��Կ���ѡͨ
 */
class bscpp_MAX6675{
	public:
		bscpp_MAX6675(
			SPI_HandleTypeDef* hspi,
			GPIO_TypeDef* GPIOx_CS, uint16_t GPIO_Pin_CS);
	public:
		float ReadTemperature(void);
	 protected:
		SPI_HandleTypeDef* hspi;
		GPIO_TypeDef* GPIOx_CS;
		uint16_t GPIO_Pin_CS;
	};
//////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
