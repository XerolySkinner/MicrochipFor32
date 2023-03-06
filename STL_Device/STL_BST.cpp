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
#include "STL_BST.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	�ຯ��
/**
 * @brief			�����Ա
 * @param	num		��Աֵ
 * @return			��BST_RES
 */
u32 STL_BST::Insert(u32 num) {
	STL_BST_Node* now=root;
	STL_BST_Node* new_Node= make(num);
	u32 count = 1;
	if (new_Node == NULL)return BST_NULL;
	//	����
	if (root == NULL) {
		depth = 0;
		root = new_Node;
		return BST_OK;}
	//	�ǿ���
	while (1) {
		//	������֫
		if (now->val > num) {
			if (now->Lkid == NULL) {	//	��֫Ϊ��,ֱ������
				Llink(now, new_Node);
				break;}
			else {						//	��֫�ǿ�,��������
				++count;				//	�߶�����
				now = now->Lkid;}		//	��һ��
		}
		//	������֫
		else {
			if (now->Rkid == NULL) {	//	��֫Ϊ��,ֱ������
				Rlink(now, new_Node);
				break;}
			else{						//	��֫�ǿ�,��������
				++count;				//	�߶�����
				now = now->Rkid;}		//	��һ��
		}
	}
	new_Node->heigh = count;			//	��������
	if (depth < count)depth = count;	//	�������
	return BST_OK;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			Ѱ�ҳ�Ա
 * @param	num		Ѱ�ҳ�Աֵ
 * @return			�ҵ��Ľڵ��ָ��
 */
STL_BST_Node* STL_BST::Find(u32 num) {
	STL_BST_Node* now = root;
	//	����
	if (root == NULL)return NULL;		//	�Ҳ���Ԫ��
	//	�ǿ���
	while (1) {
		if (now->val == num)
			return now;
		else if (now->val > num) {
			if (now->Lkid == NULL)		//	��֫Ϊ��,�������ҵ���
				return NULL;
			else
				now = now->Lkid;}
		else {
			if (now->Rkid == NULL)		//	��֫Ϊ��,�������ҵ���
				return NULL;
			else
				now = now->Rkid;}
	}
	return now;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			ɾ����Ա
 * @param	num		ɾ����Աֵ
 * @return			��BST_RES
 */
u32 STL_BST::Remove(u32 num) {
	STL_BST_Node* now = Find(num);
	STL_BST_Node* Lmax = NULL;
	if (now == NULL)return BST_NULL;
	//	���Ӵ�
	if (now->Lkid == NULL && now->Rkid == NULL) {
		if (tsRL(now)==BST_NULL) {
			//	���ڵ�
			root = NULL;
			depth = 0;
			free(now);}
		else if (tsRL(now) == BST_L) {
			//	����ڵ�
			Llink(now->Father, NULL);
			free(now);
			}
		else if (tsRL(now) == BST_R) {
			//	���ҽڵ�
			Rlink(now->Father, NULL);
			free(now);}
		}
	//	��
	else if (now->Lkid != NULL && now->Rkid == NULL) {
		if (tsRL(now) == BST_NULL) {
			//	���ڵ�
			root = root->Lkid;
			--depth;
			free(now);}
		else if (tsRL(now) == BST_L) {
			//	����ڵ�
			Llink(now->Father, now->Lkid);
			free(now);}
		else if (tsRL(now) == BST_R) {
			//	���ҽڵ�
			Rlink(now->Father, now->Lkid);
			free(now);}
		}
	//	�ҵ�
	else if (now->Lkid == NULL && now->Rkid != NULL) {
		if (tsRL(now) == BST_NULL) {
			//	���ڵ�
			root = root->Rkid;
			--depth;
			free(now);}
		else if (tsRL(now) == BST_L) {
			//	����ڵ�
			Llink(now->Father, now->Rkid);
			free(now);}
		else if (tsRL(now) == BST_R) {
			//	���ҽڵ�
			Rlink(now->Father, now->Rkid);
			free(now);}
		}
	//	˫ϵ
	else {
		Lmax = Max(now->Lkid);
		now->val = Lmax->val;
		//	�ƺ�
		if (tsRL(Lmax) == BST_L)
			Llink(Lmax->Father, Lmax->Lkid == NULL ? NULL : Lmax->Lkid);
		if (tsRL(Lmax) == BST_R)
			Rlink(Lmax->Father, Lmax->Lkid == NULL ? NULL : Lmax->Lkid);
		free(Lmax);
		}
	//	��β
	return BST_OK;
	}
//----------------------------------------------------------------------------------------------------
/**
 * @brief				����Ա
 * @param	num_save	���ҵ���ֵ����ñ���
 * @return				��BST_RES
 */
u32 STL_BST::Max(u32& num_save) {
	num_save = Max(root)->val;
	return BST_OK;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief				��С��Ա
 * @param	num_save	���ҵ���ֵ����ñ���
 * @return				��BST_RES
 */
u32 STL_BST::Min(u32& num_save) {
	num_save = Min(root)->val;
	return BST_OK;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief				��С��������ڵ�
 * @param	p			�Ӹýڵ㼰���µı���
 * @return				��BST_RES
 */
u32 STL_BST::ergodic(STL_BST_Node* p) {
	if (p == NULL)return BST_NULL;
	//	�����
	if (p == NULL)return BST_NULL;
	else(ergodic(p->Lkid));
	//	�е���
	printf("%3d ", p->val);
	//	�ҵ���
	if (p->Rkid == NULL)return BST_NULL;
	else(ergodic(p->Rkid));
	return BST_NULL;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	˽�к���
/**
 * @brief				����һ���յĽڵ�
 * @param	num			�ڵ��ʼ��ֵ
 * @return				��BST_RES
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
 * @brief				�ڵ���������ӵ��ڵ�
 * @param	F			�����ĸ��ڵ�
 * @param	L			���ӵ���ڵ�
 * @return				��BST_RES
 */
u32 STL_BST::Llink(STL_BST_Node* F, STL_BST_Node* L) {
	if (F == NULL || L == NULL)return BST_NULL;
	F->Lkid = L;
	L->Father = F;
	return BST_OK;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief				�ڵ���������ӵ��ڵ�
 * @param	F			�����ĸ��ڵ�
 * @param	R			���ӵ��ҽڵ�
 * @return				��BST_RES
 */
u32 STL_BST::Rlink(STL_BST_Node* F, STL_BST_Node* R) {
	if (F == NULL || R == NULL)return BST_NULL;
	F->Rkid = R;
	R->Father = F;
	return BST_OK;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief				Ѱ�����Ľڵ�
 * @param	p			�Ӵ˽ڵ㼰����Ϊ������
 * @return				���ڵ��ָ��
 */
STL_BST_Node* STL_BST::Max(STL_BST_Node* p) {
	if (p->Rkid == NULL)return p;
	else return Max(p->Rkid);}
//----------------------------------------------------------------------------------------------------
/**
 * @brief				Ѱ����С�Ľڵ�
 * @param	p			�Ӵ˽ڵ㼰����Ϊ������
 * @return				��С�ڵ��ָ��
 */
STL_BST_Node* STL_BST::Min(STL_BST_Node* p) {
	if (p->Lkid == NULL)return p;
	else return Min(p->Lkid);}
//----------------------------------------------------------------------------------------------------
/**
 * @brief				���Ըýڵ�Ϊ�丸�ڵ����ڵ㻹���ҽڵ�
 * @param	p			�����Խڵ�
 * @return				����ΪBST_L��BST_R,�����޸��ڵ�BST_NULL
 */
u32	STL_BST::tsRL(STL_BST_Node* p) {
	if (p->Father == NULL)return BST_NULL;
	else if (p->Father->Lkid == p)return BST_L;
	else if (p->Father->Rkid == p)return BST_R;
	else return BST_NULL;}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	�ṹ����
STL_BST::STL_BST(void) {
	root = NULL;
	depth = 0;}
//----------------------------------------------------------------------------------------------------
STL_BST::~STL_BST(void) {
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////
