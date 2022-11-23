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
  * @file		bsp_Calculus.h
  * @brief		��ɢ΢����
  * @mainpage	��Ҫ��Ϣ
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		2022-11-23 02:46
  */
#pragma once
#include <stdlib.h>
#include "varint.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	��Ŀ
/**
 * @brief 					һ��΢�ֶ���
 */
class bsp_Differential{
	public:
		bsp_Differential(float dt) {
			bsp_Differential::dt = dt;}
	public:
		float Differential(float var);
	public:
		float dt;			///< ʱ�����
	};
//----------------------------------------------------------------------------------------------------
/**
 * @brief 					һ�����ֶ���
 * @note					��Ӧ������Integral��Integral_list
 * @note					ѡ��һ�ַ�ʽ(�����������߲���)��,�Ͳ�Ӧ�ø���ʹ�÷�ʽ
 * @note					��Ȼ����������ʽ���㷨ʱ��Ӱ�첻��,����Ϊ�˱����˷ѿռ�,������ʹ�ù���Ļ�����
 */
class bsp_Integral {
	public:
		bsp_Integral(float dt) {
			bsp_Integral::result_list = NULL;
			bsp_Integral::dt = dt;
			bsp_Integral::results = 0;}
		~bsp_Integral(void) {
			free(result_list);
			result_list = NULL;}
	public:
		float Integral(float var);
		void Integral_set(float results);

		float Integral_list(float var);
		u32 Integral_makelist(u32 len);
		void Integral_dellist(void);
		void Integral_clslist(void);
	public:
		float	*result_list;	///< ������ʷ
		u32		result_len;		///< ��ʷ����������
		float	results;		///< ���ֻ���
		float	dt;				///< ʱ�����
	};
//////////////////////////////////////////////////////////////////////////////////////////////////////
