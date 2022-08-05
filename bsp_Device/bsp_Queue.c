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
	名字:bsp_Queue
	时间:20220806-0226
	程序员:梁源康
	说明:队列与FIFO函数
*/
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
////////////////////////////////////////////////////////////////////////////////////////////////////
//	声明
struct _Queue {
	struct _Queue* front;
	void* member;
	struct _Queue* rear;
};
////////////////////////////////////////////////////////////////////////////////////////////////////
//	主程序
struct _Queue* bsp_QueueInit(void) {
	struct _Queue* list = malloc(sizeof(struct _Queue));
	if (list == NULL)return NULL;
	list->front =	NULL;
	list->rear =	NULL;
	list->member =	NULL;
	return list;}
////////////////////////////////////////////////////////////////////////////////////////////////////
//	队列空检测
char bsp_QueueEmpty(struct _Queue *list) {
	return (list->front == NULL && list->rear == NULL);}
////////////////////////////////////////////////////////////////////////////////////////////////////
//	队列尾巴处压入成员
char bsp_QueuePush(struct _Queue *list,void* member) {
	struct _Queue* listAdd = malloc(sizeof(struct _Queue));
	struct _Queue* listFront = list->front;
	struct _Queue* listRear = list->rear;
	if (list == NULL)return 1;				//防止爆炸
	if (listAdd == NULL)return 1;			//防止爆炸

	listAdd->member = member;				//加入聪明仔

	//	空单位初始化
	if (bsp_QueueEmpty(list)) {
		list->front = list->rear = listAdd;
		listAdd->front = listAdd->rear = listAdd;}
	//	常单位续编
	else {
		listAdd->front	= listRear;			//新节点连接尾巴
		listRear->rear	= listAdd;			//尾巴交接新节点
		listAdd->rear	= listAdd;			//尾巴自交
		list->rear		= listAdd;			//新尾巴
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
//	队列头部弹出成员
void* bsp_QueuePop(struct _Queue* list) {
	struct _Queue* listFront = list->front;
	struct _Queue* listRear = list->rear;
	void* result=NULL;
	if (list == NULL)return NULL;			//防止爆炸
	if (bsp_QueueEmpty(list))return NULL;	//寡妇函数

	//	寡妇节点
	if (listFront== listRear) {
		list->front = list->rear = NULL;
		result= listFront->member;}
	else {
		list->front = listFront->rear;
		result= listFront->member;}
	free(listFront);						//抹脖子
	return result;}
////////////////////////////////////////////////////////////////////////////////////////////////////
