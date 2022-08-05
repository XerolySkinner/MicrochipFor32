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
#ifndef	_BSP_QUEUE
#define	_BSP_QUEUE
////////////////////////////////////////////////////////////////////////////////////////////////////
//	��������
//	ѭ��ֱ��ִ����ȫ����
#define bsp_QueuePopRunLoopVoid(Queue)					\
	do{													\
		while(!bsp_QueueEmpty(Queue))					\
			((void (*)(void))bsp_QueuePop(Queue))();	\
	}while(0)
//	������ִ�е�������
#define bsp_QueuePopRunIfVoid(Queue)					\
	do{													\
		if(!bsp_QueueEmpty(Queue))						\
			((void (*)(void))bsp_QueuePop(Queue))();	\
	}while(0)
//	���ö��д�����
struct _Queue* bsp_QueueInit(void);
char bsp_QueueEmpty(struct _Queue* list);
char bsp_QueuePush(struct _Queue* list, void* member);
void* bsp_QueuePop(struct _Queue* list);
void bsp_QueuePushCharPtrFree(char* member);
char bsp_QueuePushCharPtr(struct _Queue* list, char* member, unsigned int len);
////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
