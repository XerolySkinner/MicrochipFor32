/*----------------------------------------------------------------------------------------------------
 #
 #	Copyright (c) 2022 Yuankang Liang(XerolySkinner)
 #
 #	本软件按原样提供,无任何明示或暗示
 #	在任何情况下,作者都不承担任何损害赔偿责任
 #
 #	使用的许可声明:
 #	1.	不得歪曲本软件的来源,你不能声称你编写了原始软件.
 #	2.	免费授予以任何目的,前提是版权声明出现在所有副本中.
 #		并且版权声明和许可声明同时出现.
 #	3.	你有使用,复制,修改,分发,和销售本软件的许可.
 #	4.	如果你在产品中使用,产品文档中的声明是赞赏的但不是必须的.
 #	5.	本通知不得从任何来源删除或更改.
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
  * @brief		实现二叉搜索树
  * @mainpage	主要信息
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
//	结构类型
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
//	结构类型
typedef struct STL_BST_Node STL_BST_Node;
struct STL_BST_Node {
	STL_BST_Node*	Father;					//	父节点
	u32				val;					//	值
	u32				heigh;					//	高度
	STL_BST_Node*	Lkid;					//	左节点
	STL_BST_Node*	Rkid;					//	右节点
	};
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	类目
/**
 * @brief			二叉搜索树类
 */
class STL_BST{
	public:
		STL_BST(void);
		~STL_BST(void);
	public:
		u32				Insert(u32 num);			//	插入值
		u32				Remove(u32 num);			//	删除值
		STL_BST_Node*	Find(u32 num);				//	寻找值
		u32				ergodic(STL_BST_Node* p);	//	遍历节点

		u32				Min(u32& num_save);			//	返回最小值
		u32				Max(u32& num_save);			//	返回最大值
	public:
		STL_BST_Node*	root;						//	根节点
		u32				depth;						//	树深度
	private:
		u32				tsRL(STL_BST_Node* p);		//	测试是父节点的左还是右
		STL_BST_Node*	make(u32 num);				//	创造一个节点
		
		u32				Llink(						//	左肢链接
			STL_BST_Node* F, STL_BST_Node* L);
		u32				Rlink(						//	右肢链接
			STL_BST_Node* F, STL_BST_Node* R);
		
		STL_BST_Node*	Min(STL_BST_Node* p);		//	返回最小值节点
		STL_BST_Node*	Max(STL_BST_Node* p);		//	返回最大值节点
};
//////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
