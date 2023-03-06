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
  * @file		bsp_PID.h
  * @brief		ʵ����PID�㷨
  * @mainpage	��Ҫ��Ϣ
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		2022-11-09 03:12
  */

#ifdef __cplusplus
#pragma once
#include "varint.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	��Ŀ
/**
 * @brief 					λ�÷�Ϊ������PID�㷨
 */
class bsp_Position_PID{
	public:
		bsp_Position_PID(void);
		bsp_Position_PID(
			float Kp, float Ki, float Kd, float target,
			float result_H, float result_L);
		~bsp_Position_PID(void);
	public:
		float	PID(float temp);
		void	clean(void);
		void	set(float P, float I, float D);
	public:
		float target;		///< �趨ֵ
		float Kp;			///< ����ϵ��
		float Kd;			///< ����ϵ��
		float Ki;			///< ΢��ϵ��
		float result;		///< ���ֵ
	private:
		float integral;		///< ����ֵ
		float lasterror;	///< ǰһ��ƫ��

		float result_H;		///< ������ֵ
		float result_L;		///< ������ֵ
	};
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	��Ŀ
/**
 * @brief 					������Ϊ������PID�㷨
 */
class bsp_Increment_PID {
	public:
		bsp_Increment_PID(void);
		bsp_Increment_PID(
			float Kp, float Ki, float Kd, float target,
			float result_H, float result_L);
		~bsp_Increment_PID(void);
	public:
		float	PID(float temp);
		void	clean(void);
		void	set(float P, float I, float D);
	public:
		float target;		///< �趨ֵ
		float Kp;			///< ����ϵ��
		float Kd;			///< ����ϵ��
		float Ki;			///< ΢��ϵ��
		float result;		///< ���ֵ
	private:
		float lasterror;	///< ǰһ��ƫ��
		float preerror;		///< ǰ����ƫ��

		float result_H;		///< ������ֵ
		float result_L;		///< ������ֵ
	};
//////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
