#include <stdio.h>
#include "main.h"

#define MAXQSIZE 100

typedef struct {
	QElemType* base;
	int front;
	int rear;
}SqQueue;

Status InitQueue(SqQueue* Q);
int QueueLength(SqQueue Q);
Status EnQueue(SqQueue* Q, QElemType x);
Status DeQueue(SqQueue* Q, QElemType* x);
QElemType GetHead(SqQueue Q);
void PrintQueue(SqQueue Q);

void main() {
	SqQueue Q;
	QElemType x;
	int i, i_en;
	InitQueue(&Q);
	printf("请输入要入队多少个的数据：");
	scanf("%d", &i_en);
	for (i = 1; i <= i_en; i++)
	{
		printf("第%d个元素：", i);
		scanf("%d", &x);
		EnQueue(&Q, x);
	}
	printf("长度为：%d\n", QueueLength(Q));
	PrintQueue(Q);
	while (Q.front != Q.rear)
	{
		printf("是否出队一个元素（Y--1，N--0）：");
		scanf("%d", &x);
		if (x)
		{
			DeQueue(&Q, &x);
			printf("出队元素为：%d\n", x);
			PrintQueue(Q);
			continue;
		}
		break;
	}
	x = GetHead(Q);
	printf("展示栈顶元素：%d\n", x);
}

Status InitQueue(SqQueue* Q) {
	Q->base = (QElemType*)malloc(MAXQSIZE * sizeof(QElemType));
	if (!Q->base)
	{
		exit(OVERFLOW);
	}
	Q->front = Q->rear = 0;
	return OK;
}

int QueueLength(SqQueue Q) {
	return ((Q.rear - Q.front + MAXQSIZE) % MAXQSIZE);
}

Status EnQueue(SqQueue* Q, QElemType x) {
	if ((Q->rear + 1) % MAXQSIZE == Q->front) {
		return ERROR;
	}
	Q->base[Q->rear] = x;
	Q->rear = (Q->rear + 1) % MAXQSIZE;
	return OK;
}

Status DeQueue(SqQueue* Q, QElemType* x) {
	if (Q->rear == Q->front)
	{
		return ERROR;
	}
	*x = Q->base[Q->front];
	Q->front = (Q->front + 1) % MAXQSIZE;
	return OK;
}

QElemType GetHead(SqQueue Q) {
	if (Q.rear != Q.front)
	{
		return Q.base[Q.front];
	}
	return ERROR;
}

void PrintQueue(SqQueue Q) {
	int i, i_head;
	i_head = Q.front;
	for (i = 1; i <= QueueLength(Q); i++)
	{
		printf("第%d个元素：%d\n", i, Q.base[i_head]);
		i_head++;
	}
}