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
#include "STL_BST.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	类函数
/**
 * @brief			插入成员
 * @param	num		成员值
 * @return			见BST_RES
 */
u32 STL_BST::Insert(u32 num) {
	STL_BST_Node* now=root;
	STL_BST_Node* new_Node= make(num);
	u32 count = 1;
	if (new_Node == NULL)return BST_NULL;
	//	空树
	if (root == NULL) {
		depth = 0;
		root = new_Node;
		return BST_OK;}
	//	非空树
	while (1) {
		//	填入左肢
		if (now->val > num) {
			if (now->Lkid == NULL) {	//	左肢为空,直接填入
				Llink(now, new_Node);
				break;}
			else {						//	左肢非空,继续迭代
				++count;				//	高度自增
				now = now->Lkid;}		//	下一层
		}
		//	填入右肢
		else {
			if (now->Rkid == NULL) {	//	右肢为空,直接填入
				Rlink(now, new_Node);
				break;}
			else{						//	右肢非空,继续迭代
				++count;				//	高度自增
				now = now->Rkid;}		//	下一层
		}
	}
	new_Node->heigh = count;			//	填入树高
	if (depth < count)depth = count;	//	更新深度
	return BST_OK;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			寻找成员
 * @param	num		寻找成员值
 * @return			找到的节点的指针
 */
STL_BST_Node* STL_BST::Find(u32 num) {
	STL_BST_Node* now = root;
	//	空树
	if (root == NULL)return NULL;		//	找不到元素
	//	非空树
	while (1) {
		if (now->val == num)
			return now;
		else if (now->val > num) {
			if (now->Lkid == NULL)		//	左肢为空,不会再找到了
				return NULL;
			else
				now = now->Lkid;}
		else {
			if (now->Rkid == NULL)		//	右肢为空,不会再找到了
				return NULL;
			else
				now = now->Rkid;}
	}
	return now;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			删除成员
 * @param	num		删除成员值
 * @return			见BST_RES
 */
u32 STL_BST::Remove(u32 num) {
	STL_BST_Node* now = Find(num);
	STL_BST_Node* Lmax = NULL;
	if (now == NULL)return BST_NULL;
	//	无子代
	if (now->Lkid == NULL && now->Rkid == NULL) {
		if (tsRL(now)==BST_NULL) {
			//	父节点
			root = NULL;
			depth = 0;
			free(now);}
		else if (tsRL(now) == BST_L) {
			//	父左节点
			Llink(now->Father, NULL);
			free(now);
			}
		else if (tsRL(now) == BST_R) {
			//	父右节点
			Rlink(now->Father, NULL);
			free(now);}
		}
	//	左单
	else if (now->Lkid != NULL && now->Rkid == NULL) {
		if (tsRL(now) == BST_NULL) {
			//	父节点
			root = root->Lkid;
			--depth;
			free(now);}
		else if (tsRL(now) == BST_L) {
			//	父左节点
			Llink(now->Father, now->Lkid);
			free(now);}
		else if (tsRL(now) == BST_R) {
			//	父右节点
			Rlink(now->Father, now->Lkid);
			free(now);}
		}
	//	右单
	else if (now->Lkid == NULL && now->Rkid != NULL) {
		if (tsRL(now) == BST_NULL) {
			//	父节点
			root = root->Rkid;
			--depth;
			free(now);}
		else if (tsRL(now) == BST_L) {
			//	父左节点
			Llink(now->Father, now->Rkid);
			free(now);}
		else if (tsRL(now) == BST_R) {
			//	父右节点
			Rlink(now->Father, now->Rkid);
			free(now);}
		}
	//	双系
	else {
		Lmax = Max(now->Lkid);
		now->val = Lmax->val;
		//	善后
		if (tsRL(Lmax) == BST_L)
			Llink(Lmax->Father, Lmax->Lkid == NULL ? NULL : Lmax->Lkid);
		if (tsRL(Lmax) == BST_R)
			Rlink(Lmax->Father, Lmax->Lkid == NULL ? NULL : Lmax->Lkid);
		free(Lmax);
		}
	//	收尾
	return BST_OK;
	}
//----------------------------------------------------------------------------------------------------
/**
 * @brief				最大成员
 * @param	num_save	将找到的值填入该变量
 * @return				见BST_RES
 */
u32 STL_BST::Max(u32& num_save) {
	num_save = Max(root)->val;
	return BST_OK;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief				最小成员
 * @param	num_save	将找到的值填入该变量
 * @return				见BST_RES
 */
u32 STL_BST::Min(u32& num_save) {
	num_save = Min(root)->val;
	return BST_OK;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief				从小到大迭代节点
 * @param	p			从该节点及其下的遍历
 * @return				见BST_RES
 */
u32 STL_BST::ergodic(STL_BST_Node* p) {
	if (p == NULL)return BST_NULL;
	//	左迭代
	if (p == NULL)return BST_NULL;
	else(ergodic(p->Lkid));
	//	中迭代
	printf("%3d ", p->val);
	//	右迭代
	if (p->Rkid == NULL)return BST_NULL;
	else(ergodic(p->Rkid));
	return BST_NULL;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	私有函数
/**
 * @brief				生成一个空的节点
 * @param	num			节点初始化值
 * @return				见BST_RES
 */
STL_BST_Node* STL_BST::make(u32 num) {
	STL_BST_Node* res=(STL_BST_Node*)malloc(sizeof(STL_BST_Node));
	if (res == NULL)return NULL;
	res->Father = NULL;
	res->Lkid = NULL;
	res->Rkid = NULL;
	res->val = num;
	res->heigh = 0;
	return res;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief				节点的左孩子连接到节点
 * @param	F			操作的父节点
 * @param	L			连接的左节点
 * @return				见BST_RES
 */
u32 STL_BST::Llink(STL_BST_Node* F, STL_BST_Node* L) {
	if (F == NULL || L == NULL)return BST_NULL;
	F->Lkid = L;
	L->Father = F;
	return BST_OK;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief				节点的左孩子连接到节点
 * @param	F			操作的父节点
 * @param	R			连接的右节点
 * @return				见BST_RES
 */
u32 STL_BST::Rlink(STL_BST_Node* F, STL_BST_Node* R) {
	if (F == NULL || R == NULL)return BST_NULL;
	F->Rkid = R;
	R->Father = F;
	return BST_OK;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief				寻找最大的节点
 * @param	p			从此节点及其下为搜索域
 * @return				最大节点的指针
 */
STL_BST_Node* STL_BST::Max(STL_BST_Node* p) {
	if (p->Rkid == NULL)return p;
	else return Max(p->Rkid);}
//----------------------------------------------------------------------------------------------------
/**
 * @brief				寻找最小的节点
 * @param	p			从此节点及其下为搜索域
 * @return				最小节点的指针
 */
STL_BST_Node* STL_BST::Min(STL_BST_Node* p) {
	if (p->Lkid == NULL)return p;
	else return Min(p->Lkid);}
//----------------------------------------------------------------------------------------------------
/**
 * @brief				测试该节点为其父节点的左节点还是右节点
 * @param	p			被测试节点
 * @return				测试为BST_L或BST_R,或者无父节点BST_NULL
 */
u32	STL_BST::tsRL(STL_BST_Node* p) {
	if (p->Father == NULL)return BST_NULL;
	else if (p->Father->Lkid == p)return BST_L;
	else if (p->Father->Rkid == p)return BST_R;
	else return BST_NULL;}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	结构函数
STL_BST::STL_BST(void) {
	root = NULL;
	depth = 0;}
//----------------------------------------------------------------------------------------------------
STL_BST::~STL_BST(void) {
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////
