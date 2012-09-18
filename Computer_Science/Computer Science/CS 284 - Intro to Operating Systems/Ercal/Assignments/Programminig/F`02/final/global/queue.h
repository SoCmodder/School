
#ifndef QUEUE_H
#define QUEUE_H

typedef struct {
	void *data;
	void *next;
} QueueNode;

typedef struct {
	QueueNode *head;
	QueueNode *tail;
} QueueType;

void CreateQueue(QueueType **node);
void Enqueue(QueueType **node, void *data);
void *Dequeue(QueueType **node);

#endif

