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
#ifndef	_BSP_QUEUE
#define	_BSP_QUEUE
////////////////////////////////////////////////////////////////////////////////////////////////////
//	函数声明
//	循环直到执行完全函数
#define bsp_QueuePopRunLoopVoid(Queue)					\
	do{													\
		while(!bsp_QueueEmpty(Queue))					\
			((void (*)(void))bsp_QueuePop(Queue))();	\
	}while(0)
//	弹出并执行单个函数
#define bsp_QueuePopRunIfVoid(Queue)					\
	do{													\
		if(!bsp_QueueEmpty(Queue))						\
			((void (*)(void))bsp_QueuePop(Queue))();	\
	}while(0)
//	常用队列处理函数
struct _Queue* bsp_QueueInit(void);
char bsp_QueueEmpty(struct _Queue* list);
char bsp_QueuePush(struct _Queue* list, void* member);
void* bsp_QueuePop(struct _Queue* list);
void bsp_QueuePushCharPtrFree(char* member);
char bsp_QueuePushCharPtr(struct _Queue* list, char* member, unsigned int len);
////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
