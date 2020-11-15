#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"
#include "../SEThread.h"

extern struct programData data;

struct LinkedList *createLinkedList()
{
	struct LinkedList *list = malloc(sizeof(struct LinkedList));
	list->head = NULL;
	list->tail = NULL;

	return list;
}

struct Node* FCFS(struct LinkedList* list){
    if(list->head == NULL)
        return NULL;
    struct Node* temp = list->head;
    list->head = list->head->next;
    if(temp == list->tail)
        list->tail = NULL;
    return temp;
} 

struct Node* SJF(struct LinkedList* list){
    if(list->head == NULL)
        return NULL;
    if(list->head == list->tail){
        struct BurstNode* temp = list->head;
        list->head = NULL;
        list->tail = NULL;
        return temp;
    }
    struct Node* prevMinNode = NULL;
    struct Node* minNode = list->head;
    struct Node* cur = list->head->next;
    struct Node* prev = list->head;
    while(cur != NULL){
        if(cur->burstTime < minNode->burstTime){
            minNode = cur;
            prevMinNode = prev;
        }
        prev = cur;
        cur = cur->next;
    }

    if(minNode == list->head)
        list->head = list->head->next;

    else if(minNode == list->tail){
        list->tail = prevMinNode;
        list->tail->next = NULL;
    }

    else
        prevMinNode->next = minNode->next;

    return minNode;
}

struct Node* RR(struct LinkedList* list){
	int quantum = data.quantum;
    if(list->head == NULL)
        return NULL;
    if(list->head == list->tail){
        if(list->head->burstTime <= quantum){
            struct Node* temp = list->head;
            list->head = NULL;
            list->tail = NULL;
            return temp;
        }
        struct Node* returnNode = (struct Node*)malloc(sizeof(struct Node));
        returnNode->next = NULL;
        returnNode->id = list->head->id;
        returnNode->burstTime = quantum;
        list->head->burstTime = list->head->burstTime - quantum;
        return returnNode;
    }
    struct Node* temp = list->head;
    list->head = list->head->next;
    if(temp->burstTime > quantum){
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->id = temp->id;
        newNode->burstTime = temp->burstTime - quantum;
        newNode->next = NULL;
        list->tail->next = newNode;
        list->tail = newNode;
        temp->burstTime = quantum;
    }
    return temp;
}

void addNode(struct LinkedList *list, int id, int burstTime)
{
	if (list->head == NULL)
	{
		list->head = malloc(sizeof(struct Node));
		list->tail = list->head;

		list->head->id = id;
        list->head->burstTime = burstTime;
		list->head->next = NULL;
	}
	else
	{
		list->tail->next = malloc(sizeof(struct Node));
		list->tail = list->tail->next;

		list->tail->next = NULL;
		list->tail->id = id;
		list->tail->burstTime = burstTime;
	}
}