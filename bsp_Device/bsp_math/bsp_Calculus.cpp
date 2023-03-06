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
  * @file		bsp_Calculus.cpp
  * @brief		��ɢ΢����
  * @mainpage	��Ҫ��Ϣ
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		2022-11-23 02:46
  */

//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	ͷ�ļ�
#include "bsp_Calculus.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	�ຯ��
/**
 * @brief			������΢��
 * @param	var 	�˴����븡������
 * @return			��ʱ��΢��ֵ
 */
float bsp_Differential::Differential(float var) {
	static float old=var;
	float result= (var - old) / dt;
	old = var;
	return result;}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	�ຯ��
/**
 * @brief			�����ݻ���
 * @param	var 	�˴����븡������
 * @return			�ӿ�ʼ�����ڵ��ܻ���ֵ
 */
float bsp_Integral::Integral(float var) {
	results += var * dt;
	return results;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			���赱ǰ����ֵ
 * @param	var 	Ҫ���õĻ���ֵ
 */
void bsp_Integral::Integral_set(float results) {
	bsp_Integral::results = results;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			������ʷ���泤��
 * @param	var 	����Ļ��泤��
 * @return			���ط�����ڴ�λ��,0Ϊ����ʧ��
 */
u32 bsp_Integral::Integral_makelist(u32 len) {
	result_list = (float*)malloc(sizeof(float)* len);
	result_len = len;
	Integral_clslist();
	return (u32)result_list;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			���д��л������Ļ���
 * @param	var 	��Ҫ���ֵ���ֵ
 * @return			���ػ���ֵ
 */
float bsp_Integral::Integral_list(float var) {
	static u32 len=0;
	results += var * dt;
	//	������ʷ
	result_list[len] = var * dt;
	//	����ת
	++len;
	if (len == result_len)len = 0;
	//	ȥ��βֵ
	if (len < result_len - 1)
		results -= result_list[len + 1];
	else
		results -= result_list[0];
	//	
	return results;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			ɾ�����ͷ���ʷ������
 */
void bsp_Integral::Integral_dellist(void) {
	free(result_list);
	result_len = 0;
	result_list = NULL;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			�����ʷ������
 */
void bsp_Integral::Integral_clslist(void) {
	if (result_list == NULL)return;
	for (u32 i = 0; i < result_len; i++)
		result_list[i] = 0;}
//////////////////////////////////////////////////////////////////////////////////////////////////////
