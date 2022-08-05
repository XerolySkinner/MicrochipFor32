/*----------------------------------------------------------------------------------------------------
#	THIS FILE IS A PART OF XerolySkinner's PROJECT
#
#	THIS PROGRAM IS FREE SOFTWARE
#
#	E-mail:ZABBCCCBBAZ@163.com
#	QQ:2715099320
#
#	Copyright (c) 2022 XerolySkinner
#	All rights reserved.
*/

/*----------------------------------------------------------------------------------------------------
	����:bsp_Queue
	ʱ��:20220806-0226
	����Ա:��Դ��
	˵��:������FIFO����
*/
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
////////////////////////////////////////////////////////////////////////////////////////////////////
//	����
struct _Queue {
	struct _Queue* front;
	void* member;
	struct _Queue* rear;
};
////////////////////////////////////////////////////////////////////////////////////////////////////
//	������
struct _Queue* bsp_QueueInit(void) {
	struct _Queue* list = malloc(sizeof(struct _Queue));
	if (list == NULL)return NULL;
	list->front =	NULL;
	list->rear =	NULL;
	list->member =	NULL;
	return list;}
////////////////////////////////////////////////////////////////////////////////////////////////////
//	���пռ��
char bsp_QueueEmpty(struct _Queue *list) {
	return (list->front == NULL && list->rear == NULL);}
////////////////////////////////////////////////////////////////////////////////////////////////////
//	����β�ʹ�ѹ���Ա
char bsp_QueuePush(struct _Queue *list,void* member) {
	struct _Queue* listAdd = malloc(sizeof(struct _Queue));
	struct _Queue* listFront = list->front;
	struct _Queue* listRear = list->rear;
	if (list == NULL)return 1;				//��ֹ��ը
	if (listAdd == NULL)return 1;			//��ֹ��ը

	listAdd->member = member;				//���������

	//	�յ�λ��ʼ��
	if (bsp_QueueEmpty(list)) {
		list->front = list->rear = listAdd;
		listAdd->front = listAdd->rear = listAdd;}
	//	����λ����
	else {
		listAdd->front	= listRear;			//�½ڵ�����β��
		listRear->rear	= listAdd;			//β�ͽ����½ڵ�
		listAdd->rear	= listAdd;			//β���Խ�
		list->rear		= listAdd;			//��β��
		}
	return 0;}
//--------------------------------------------------------------------------------------------------
char bsp_QueuePushCharPtr(struct _Queue* list, char* member, unsigned int len) {
	char* enter = malloc(len+1);
	if (enter == NULL)return 1;
	enter[len] = '\0';
	strcpy_s(enter,len+1, member);
	bsp_QueuePush(list,enter);}

void bsp_QueuePushCharPtrFree(char* member) {
	free(member);}
////////////////////////////////////////////////////////////////////////////////////////////////////
//	����ͷ��������Ա
void* bsp_QueuePop(struct _Queue* list) {
	struct _Queue* listFront = list->front;
	struct _Queue* listRear = list->rear;
	void* result=NULL;
	if (list == NULL)return NULL;			//��ֹ��ը
	if (bsp_QueueEmpty(list))return NULL;	//�Ѹ�����

	//	�Ѹ��ڵ�
	if (listFront== listRear) {
		list->front = list->rear = NULL;
		result= listFront->member;}
	else {
		list->front = listFront->rear;
		result= listFront->member;}
	free(listFront);						//Ĩ����
	return result;}
////////////////////////////////////////////////////////////////////////////////////////////////////
