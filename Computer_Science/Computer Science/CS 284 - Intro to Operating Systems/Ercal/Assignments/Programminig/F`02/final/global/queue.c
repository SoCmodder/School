
#include <stdlib.h>
#include "queue.h"

void CreateQueue(QueueType **node) {
	*node = malloc(sizeof(QueueNode));
	(*node)->head = NULL;
	(*node)->tail = NULL;
}

void Enqueue(QueueType **node, void *data) {
	QueueNode *newNode;

	newNode = (QueueNode*)malloc(sizeof(QueueNode));
	newNode->data = data;
	newNode->next = NULL;

	if(*node && (*node)->tail) {
		(*node)->tail->next = newNode;
		(*node)->tail = newNode;
	} else {
		(*node)->head = newNode;
		(*node)->tail = newNode;
	}

}

void *Dequeue(QueueType **node) {
	QueueNode *temp;
	void *data;

	data = (*node)->head->data;
	temp = (*node)->head->next;
	free((*node)->head);
	(*node)->head = temp;
	if(!(*node)->head) {
		free(*node);
		*node = NULL;
	}

	return data;

}

