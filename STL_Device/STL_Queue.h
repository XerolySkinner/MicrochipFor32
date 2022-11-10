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
  * @file		STL_Queue.h
  * @brief		ʵ����STL���е�Queue
  * @mainpage	��Ҫ��Ϣ
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		2022-11-09 01:03
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
  * @brief 					���еķ���ֵ
  */
enum QUEUES_RES {
	QUEUES_OK,				///< �ɹ�
	QUEUES_EMPTY,			///< �����ǿյ�
	QUEUES_REAL_ERROR,		///< �ط������realloc
	QUEUES_MALL_ERROR		///< �ط������malloc
};
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	��Ŀ
/**
 * @brief 					һ�����е���
 */
class STL_rQueue{
public:
	STL_rQueue(void);
	~STL_rQueue(void);
public:
	u8		push(u8 var);
	u8		pop(void);
	u8		top(u8& var);
	u32		The_size(void);
	u32		The_room(void);
	u8		clean(void);

	u8		poptop(void);

	u8		push32(u32 var);
	u32		poptop32(void);

	void	pushfun(void(*fun)(void));
	void	(*poptopfun(void))(void);
private:
	u32		room;		//	����ռ�
	u32		size;		//	���г�Ա
	u8*		dat;		//	����ͷ
};
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	��Ŀ
/**
 * @brief 					����ʽ���еĽڵ�
 */
struct _lQueue {
	struct _lQueue* back;		///< ��һ���ڵ��ָ��
	void*			dat;		///< ���ݵ�ָ��
	u32				size;		///< �����ݵĴ�С
};
typedef struct _lQueues _lQueues;
/**
 * @brief 					һ�����е���
 * @note					ʹ���������·��䷽ʽ��֯
 *							���е��ڴ�ռ��Ƿ�������,�ʺϿ��ٽ�������
 */
class STL_lQueue {
public:
	STL_lQueue(void);
	~STL_lQueue(void);
public:
	u8		push(void*& var, u32 size);
	u8		pop(void);
	u8		top(void*& var, u32& size);

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
	_lQueue*	Hdat;		//	���н���
	_lQueue*	Tdat;		//	���е���
};
//////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
