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
 * @file		varint.h
 * @brief		ȫ�ֹ��õı�׼���ͱ�
 * @mainpage	��Ҫ��Ϣ
 * @author		Yuankang Liang(XerolySkinner)
 * @email		zabbcccbbaz@163.com
 * @version		V1.0.0
 * @date		2022-11-07 18:50
 */

#pragma once
#include "stdint.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	����
//	
typedef uint8_t			u8;		///< 8λ�޷���������
typedef uint16_t		u16;	///< 16λ�޷���������
typedef uint32_t		u32;	///< 32λ�޷���������
typedef uint64_t		u64;	///< 64λ�޷���������

typedef int8_t			i8;		///< 8λ�з���������
typedef int16_t			i16;	///< 16λ�з���������
typedef int32_t			i32;	///< 32λ�з���������
typedef int64_t			i64;	///< 64λ�з���������

typedef volatile u8		vu8;	///< 8λ�޷����ױ�����
typedef volatile u16 	vu16;	///< 16λ�޷����ױ�����
typedef volatile u32 	vu32;	///< 32λ�޷����ױ�����
typedef volatile u64 	vu64;	///< 64λ�޷����ױ�����

typedef volatile i8		vi8;	///< 8λ�з����ױ�����
typedef volatile i16 	vi16;	///< 16λ�з����ױ�����
typedef volatile i32 	vi32;	///< 32λ�з����ױ�����
typedef volatile i64 	vi64;	///< 64λ�з����ױ�����
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	λ��
#define P8(x)		((u8*)(&(x)))				///< ǿ��ת�����u8��ָ��
#define Pn8(x,y)	(((u8*)(&(x)))[y])			///< ǿ��ת�����u8������
#define P16(x)		((u16*)(&(x)))				///< ǿ��ת�����u16��ָ��
#define Pn16(x,y)	(((u16*)(&(x)))[y])			///< ǿ��ת�����u16������
#define P32(x)		((u32*)(&(x)))				///< ǿ��ת�����u32��ָ��
#define Pn32(x,y)	(((u32*)(&(x)))[y])			///< ǿ��ת�����u32������

#define L8(x)		((u8*)((x)))				///< ǿ��ת�����u8��ָ��
#define Ln8(x,y)	(((u8*)((x)))[y])			///< ǿ��ת�����u8������
#define L16(x)		((u16*)((x)))				///< ǿ��ת�����u16��ָ��
#define Ln16(x,y)	(((u16*)((x)))[y])			///< ǿ��ת�����u16������
#define L32(x)		((u32*)((x)))				///< ǿ��ת�����u32��ָ��
#define Ln32(x,y)	(((u32*)((x)))[y])			///< ǿ��ת�����u32������

#define DelLb(x)	(x & (x - 1))				///< �Ƴ����λ��1
#define qDelLb(x)	(x=(x & (x - 1)))			///< �Ƴ����������λ��1

#define toBool(x)	(x!=0)						///< ��������
#define uBit(x,y)	(x&(1<<y))					///< ��ѡĳһλ
#define tBit(x,y)	(toBool(uBit(x,y)))			///< ��ѡĳһλ���Ҳ�����

#define sBit(x,y)	(x|(1<<y))					///< �ø�ĳһλ
#define rBit(x,y)	(x&(~(1<<y)))				///< ����ĳһλ
#define mBit(x,y,z)	((z)?sBit(x,y):rBit(x,y))	///< ѡ������������ĳһλ

#define LoopAdd(var,min,step,max)	(var<max?var+step:min)
#define qLoopAdd(var,min,step,max)	(var=var<max?var+step:min)
#define LoopDec(var,min,step,max)	(var>min?var-step:max)
#define qLoopDec(var,min,step,max)	(var=var>min?var-step:max)

#define nabs(x) ((x)>0?(x):-(x))

#define bsp_GET_BIT(ptr,offset) (((ptr)[(offset) / 8] >> ((offset) % 8)) & 1)
#define bsp_SET_BIT(ptr,offset,val) (*(ptr + (offset) / 8) = (*(ptr + (offset) / 8) & ~(1 << ((offset) % 8))) | (!!((val)) << ((offset) % 8)))
//////////////////////////////////////////////////////////////////////////////////////////////////////

