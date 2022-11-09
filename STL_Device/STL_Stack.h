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
  * @file		STL_Stack.h
  * @brief		ʵ����STL���е�Stack
  * @mainpage	��Ҫ��Ϣ
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		2022-11-08 16:41
  */

#ifdef __cplusplus
#pragma once
#include "varint.h"
#include <stdlib.h>
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	����ֵö��
//	
/**
 * @brief 					ջ�ķ���ֵ
 */
enum STACKS_RES{
	STACKS_OK,				///< �ɹ�
	STACKS_EMPTY,			///< ջ�ǿյ�
	STACKS_REAL_ERROR,		///< �ط������realloc
	STACKS_MALL_ERROR		///< �ط������malloc
	};
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	��Ŀ
/**
 * @brief 					һ��ջ����
 * @note					ʹ��realloc���·��䷽ʽ��֯
 *							ջ���ڴ�ռ��������,�ʺ�С���ݳ����ٶȽ�������
 */
class STL_rStack
{
	public:
		STL_rStack(void);
		~STL_rStack(void);
	public:
		u8		push		(u8 var);
		u8		pop			(void);
		u8		top			(u8& var);
		u32		The_size	(void);
		u32		The_room	(void);
		u8		clean		(void);

		u8		poptop		(void);

		u8		push32		(u32 var);
		u32		poptop32	(void);

		void	pushfun(void(*fun)(void));
		void	(*poptopfun(void))(void);
	private:
		u32		room;		//	����ռ�
		u32		size;		//	���г�Ա
		u8*		dat;		//	����ͷ
};
//----------------------------------------------------------------------------------------------------
/**
 * @brief 					����ʽջ�Ľڵ�
 */
struct _lStack {
	struct _lStack*	front;		///< ǰһ���ڵ��ָ��
	void*			dat;		///< ���ݵ�ָ��
	u32				size;		///< �����ݵĴ�С
	};
typedef struct _lStacks _lStacks;
/**
 * @brief 					һ��ջ����
 * @note					ʹ���������·��䷽ʽ��֯
 *							ջ���ڴ�ռ��Ƿ�������,�ʺϿ��ٽ�������
 */
class STL_lStack{
	public:
		STL_lStack(void);
		~STL_lStack(void);
	public:
		u8		push(void* &var, u32 size);
		u8		pop(void);
		u8		top(void* &var, u32& size);

		u8		push8(u8 var);
		u8		top8(u8& var);
		u8		poptop8(void);

		u8		push32(u32 var);
		u8		top32(u32& var);
		u32		poptop32(void);

		u8		pushfun(void(*fun)(void));
		void	(*poptopfun(void))(void);
	private:
		u32			mem;		//	���г�Ա
		_lStack*	dat;		//	ջ����Ա
};
//////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
