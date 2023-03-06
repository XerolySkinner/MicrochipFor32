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
  * @file		bsp_PID.cpp
  * @brief		ʵ����PID�㷨
  * @mainpage	��Ҫ��Ϣ
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		2022-11-09 03:12
  */

//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	ͷ�ļ�
//	
#include "bsp_PID.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	�ຯ��
//	
/**
 * @brief				PID�㷨
 * @param	temp 		Ŀǰ����
 * @return				���ص�����
 */
float bsp_Position_PID::PID(float temp) {
	float thisError;
	thisError = target - temp;		//��ǰ�������趨ֵ��ȥ��ǰֵ
	integral += thisError;			//�����֣�����������ۼ�����
	result = 
		Kp * thisError + 
		Ki * integral + 
		Kd * (thisError - lasterror);
	lasterror = thisError;

	if (result_H == result_L)return result;
	if (result >= result_H)result == result_H;
	else if (result <= result_L)result == result_L;
	return result;
}
//----------------------------------------------------------------------------------------------------
/**
 * @brief				PID�㷨
 * @param	temp		Ŀǰ����
 * @return				���ص�����
 */
float bsp_Increment_PID::PID(float temp) {
	float thisError=target - temp;	//��ǰ�������趨ֵ��ȥ��ǰֵ
	float increment;
	float pError, dError, iError;

	pError = thisError - lasterror;
	iError = thisError;
	dError = thisError - 2 * lasterror + preerror;

	increment = 
		Kp * pError + 
		Ki * iError + 
		Kd * dError;				//��������
	preerror = lasterror;			//���ƫ�������´�����
	lasterror = thisError;			//���ƫ�������´�����
	result += increment;			//�ϴν����������

	if (result_H == result_L)return result;
	if (result >= result_H)result == result_H;
	else if (result <= result_L)result == result_L;
	return result;}
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
/**
 * @brief			������ʷ����
 * @return			���PID��������
 */
void bsp_Position_PID::clean(void) {
	integral = 0;		//����ֵ
	lasterror = 0;		//ǰһ��ƫ��
	result = 0;			//���ֵ
	}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			������ʷ����
 * @return			���PID��������
 */
void bsp_Increment_PID::clean(void) {
	lasterror = 0;		//ǰһ��ƫ��   
	preerror = 0;		//ǰ����ƫ��
	result = 0;			//���ֵ
	}
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
/**
 * @brief			PID��������
 * @param	P	 	P����
 * @param	I	 	I����
 * @param	D	 	D����
 */
void bsp_Position_PID::set(float P, float I, float D) {
	Kp = P; Ki = I; Kd = D;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			PID��������
 * @param	P	 	P����
 * @param	I	 	I����
 * @param	D	 	D����
 */
void bsp_Increment_PID::set(float P, float I, float D) {
	Kp = P; Ki = I; Kd = D;}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	���캯��
//	
bsp_Position_PID::bsp_Position_PID(void) {
	bsp_Position_PID::target = 0;
	bsp_Position_PID::lasterror = 0;
	bsp_Position_PID::Kp = 0;
	bsp_Position_PID::Ki = 0;
	bsp_Position_PID::Kd = 0;
	bsp_Position_PID::integral = 0;
	bsp_Position_PID::result = 0;
	bsp_Position_PID::result_H = 0;
	bsp_Position_PID::result_L = 0;
}
//----------------------------------------------------------------------------------------------------
/**
 * @brief				PID�㷨
 * @param	Kp			P����
 * @param	Ki			I����
 * @param	Kd			D����
 * @param	target		Ŀ��ֵ
 * @param	result_H	������ֵ
 * @param	result_L	�����Сֵ
 */
bsp_Position_PID::bsp_Position_PID(
		float Kp, float Ki, float Kd, float target,
		float result_H, float result_L) {
	bsp_Position_PID::target = target;
	bsp_Position_PID::lasterror = 0;
	bsp_Position_PID::Kp = Kp;
	bsp_Position_PID::Ki = Ki;
	bsp_Position_PID::Kd = Kd;
	bsp_Position_PID::integral = 0;
	bsp_Position_PID::result = 0;
	bsp_Position_PID::result_H = 0;
	bsp_Position_PID::result_L = 0;
}
//----------------------------------------------------------------------------------------------------
bsp_Position_PID::~bsp_Position_PID(void) {}
//----------------------------------------------------------------------------------------------------
bsp_Increment_PID::bsp_Increment_PID(void) {
	bsp_Increment_PID::target = 0;
	bsp_Increment_PID::lasterror = 0;
	bsp_Increment_PID::preerror = 0;
	bsp_Increment_PID::Kp = 0;
	bsp_Increment_PID::Ki = 0;
	bsp_Increment_PID::Kd = 0;
	bsp_Increment_PID::result = 0;
	bsp_Increment_PID::result_H = 0;
	bsp_Increment_PID::result_L = 0;
}
//----------------------------------------------------------------------------------------------------
/**
 * @brief				PID�㷨
 * @param	Kp			P����
 * @param	Ki			I����
 * @param	Kd			D����
 * @param	target		Ŀ��ֵ
 * @param	result_H	������ֵ
 * @param	result_L	�����Сֵ
 */
bsp_Increment_PID::bsp_Increment_PID(
		float Kp, float Ki, float Kd, float target,
	float result_H, float result_L) {
	bsp_Increment_PID::target = target;
	bsp_Increment_PID::lasterror = 0;
	bsp_Increment_PID::preerror = 0;
	bsp_Increment_PID::Kp = Kp;
	bsp_Increment_PID::Ki = Ki;
	bsp_Increment_PID::Kd = Kd;
	bsp_Increment_PID::result = 0;
	bsp_Increment_PID::result_H = 0;
	bsp_Increment_PID::result_L = 0;
}
//----------------------------------------------------------------------------------------------------
bsp_Increment_PID::~bsp_Increment_PID(void) {}
//////////////////////////////////////////////////////////////////////////////////////////////////////
