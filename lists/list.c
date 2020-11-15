#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include "list.h"
#include "../SEThread.h"

extern struct programData data;
pthread_mutex_t list_lock;

struct LinkedList *createLinkedList()
{
	struct LinkedList *list = malloc(sizeof(struct LinkedList));
	list->head = NULL;
	list->tail = NULL;
    if(pthread_mutex_init(&list_lock, NULL) != 0){
        printf("Mutex lock has failed in createLinkedList()!\n");
        return NULL;
    }
	return list;
}

struct BurstNode* FCFS(struct LinkedList* list, int* flag){
    pthread_mutex_lock(&list_lock);
    if(list->head == NULL){
        pthread_mutex_unlock(&list_lock);
        return NULL;
    }
    struct BurstNode* temp = list->head;
    list->head = list->head->next;
    if(temp == list->tail)
        list->tail = NULL;
    pthread_mutex_unlock(&list_lock);
    temp->next= NULL;
    temp->last = 1;
    return temp;
} 

struct BurstNode* SJF(struct LinkedList* list, int* flag){
    pthread_mutex_lock(&list_lock);
    if(list->head == NULL){
        pthread_mutex_unlock(&list_lock);
        return NULL;
    }
    if(list->head == list->tail){
        struct BurstNode* temp = list->head;
        list->head = NULL;
        list->tail = NULL;
        pthread_mutex_unlock(&list_lock);
        temp->last = 1;
        return temp;
    }
    struct BurstNode* prevMinNode = NULL;
    struct BurstNode* minNode = list->head;
    struct BurstNode* cur = list->head->next;
    struct BurstNode* prev = list->head;
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
    pthread_mutex_unlock(&list_lock);
    minNode->next = NULL;
    minNode->last = 1;
    return minNode;
}

struct BurstNode* RR(struct LinkedList* list, int* flag){
    pthread_mutex_lock(&list_lock);
	int quantum = data.quantum;
    if(list->head == NULL){
        pthread_mutex_unlock(&list_lock);
        return NULL;
    }
    if(list->head == list->tail){
        if(list->head->burstTime <= quantum){
            struct BurstNode* temp = list->head;
            list->head = NULL;
            list->tail = NULL;
            pthread_mutex_unlock(&list_lock);
            temp->last = 1;
            return temp;
        }
        struct BurstNode* returnNode = (struct BurstNode*)malloc(sizeof(struct BurstNode));
        returnNode->next = NULL;
        returnNode->id = list->head->id;
        returnNode->burstTime = quantum;
        returnNode->last = 0;
        returnNode->first = list->head->first;
        returnNode->entryTime = list->head->entryTime;
        list->head->first = 0;
        list->head->burstTime = list->head->burstTime - quantum;
        pthread_mutex_unlock(&list_lock);
        return returnNode;
    }
    struct BurstNode* temp = list->head;
    temp->last = 1;
    list->head = list->head->next;
    if(temp->burstTime > quantum){
        *flag = 1;
        struct BurstNode* newNode = (struct BurstNode*)malloc(sizeof(struct BurstNode));
        newNode->id = temp->id;
        newNode->burstTime = temp->burstTime - quantum;
        newNode->next = NULL;
        newNode->entryTime = temp->entryTime;
        newNode->first = 0;
        newNode->initialBurstTime = temp->initialBurstTime;
        list->tail->next = newNode;
        list->tail = newNode;
        temp->burstTime = quantum;
        temp->last = 0;
    }
    pthread_mutex_unlock(&list_lock);
    temp->next = NULL;
    return temp;
}

void addNode(struct LinkedList *list, int id, int burstTime)
{
    pthread_mutex_lock(&list_lock);
    struct timeval entryTime;
    struct BurstNode* newNode = malloc(sizeof(struct BurstNode));
    newNode->id = id;
    newNode->burstTime = burstTime;
    newNode->initialBurstTime = burstTime;
    newNode->first = 1;
    newNode->last = 0;
    newNode->next = NULL;
	if (list->head == NULL)
	{
		list->head = newNode;
		list->tail = list->head;
	}
	else
	{
		list->tail->next = newNode;
		list->tail = list->tail->next;
	}
    gettimeofday(&entryTime, NULL);
    list->tail->entryTime = entryTime;
    pthread_mutex_unlock(&list_lock);
}