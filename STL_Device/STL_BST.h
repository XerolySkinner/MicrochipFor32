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
  * @file		STL_BST.h
  * @brief		ʵ�ֶ���������
  * @mainpage	��Ҫ��Ϣ
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		2022-12-09 20:30
  */
#pragma once
#ifdef __cplusplus
#include "varint.h"
#include <stdlib.h>
#include <stdio.h>
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	�ṹ����
enum BST_RES{
	BST_OK,
	BST_NULL,
};

enum {
	BST_L,
	BST_R,
};
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	�ṹ����
typedef struct STL_BST_Node STL_BST_Node;
struct STL_BST_Node {
	STL_BST_Node*	Father;					//	���ڵ�
	u32				val;					//	ֵ
	u32				heigh;					//	�߶�
	STL_BST_Node*	Lkid;					//	��ڵ�
	STL_BST_Node*	Rkid;					//	�ҽڵ�
	};
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	��Ŀ
/**
 * @brief			������������
 */
class STL_BST{
	public:
		STL_BST(void);
		~STL_BST(void);
	public:
		u32				Insert(u32 num);			//	����ֵ
		u32				Remove(u32 num);			//	ɾ��ֵ
		STL_BST_Node*	Find(u32 num);				//	Ѱ��ֵ
		u32				ergodic(STL_BST_Node* p);	//	�����ڵ�

		u32				Min(u32& num_save);			//	������Сֵ
		u32				Max(u32& num_save);			//	�������ֵ
	public:
		STL_BST_Node*	root;						//	���ڵ�
		u32				depth;						//	�����
	private:
		u32				tsRL(STL_BST_Node* p);		//	�����Ǹ��ڵ��������
		STL_BST_Node*	make(u32 num);				//	����һ���ڵ�
		
		u32				Llink(						//	��֫����
			STL_BST_Node* F, STL_BST_Node* L);
		u32				Rlink(						//	��֫����
			STL_BST_Node* F, STL_BST_Node* R);
		
		STL_BST_Node*	Min(STL_BST_Node* p);		//	������Сֵ�ڵ�
		STL_BST_Node*	Max(STL_BST_Node* p);		//	�������ֵ�ڵ�
};
//////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
