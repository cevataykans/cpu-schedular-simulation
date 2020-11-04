#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"

// struct LinkedList *createLinkedList();
// void destroyLinkedList( struct LinkedList *list);
// void addNode( struct LinkedList *list, char *data);
// void traverseList( struct LinkedList *list);
// void sortByInsertion(struct LinkedList *list );
// //int compareNodes( char word[], struct Node *to);
// //void swapNodes( struct Node *from, struct Node *to);
// int getRandomNumber( int lowerBound, int upperBound);
// struct Node *getHead( struct LinkedList *list);

// struct LinkedList
// {
// 	struct Node *head;
// 	struct Node *tail;
// };

// struct Node
// {
// 	struct Node *next;
// 	char word[1024];
// 	int count;
// };

//int NUM_COUNT = 10000;

// int main( int argc. char *argv[])
// {
// 	// This is my first C program!
// 	printf( "Hello World!\n");
// 	struct LinkedList *myList = createLinkedList();

// 	// Set random seed
// 	srand( time( 0));

// 	struct timeval startTime;
// 	struct timeval finishTime;

// 	gettimeofday( &startTime, NULL);
// 	for ( int i = 0; i < NUM_COUNT; i++)
// 	{
// 		int ranNum = getRandomNumber( 0, NUM_COUNT);
// 		addNode( myList, ranNum);
// 	}
// 	gettimeofday( &finishTime, NULL);

// 	printf( "Time of execution to add 10,000 numbers:\n");
// 	printf( "\tIn seconds: %d\n", finishTime.tv_sec - startTime.tv_sec);
// 	printf( "\tIn microseconds: %ld\n",
// 		(finishTime.tv_sec * 1000000 + finishTime.tv_usec) -
// 		 (startTime.tv_sec * 1000000 + startTime.tv_usec) );

// 	destroyLinkedList( myList);

// 	return 0;
// }

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

struct Node* RR(){
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

		strcpy(list->head->word, data);
		list->head->count = 1;
		list->head->next = NULL;
	}
	else
	{
		list->tail->next = malloc(sizeof(struct Node));
		list->tail = list->tail->next;

		list->tail->next = NULL;
		strcpy(list->tail->word, data); // list->tail->word = data;
		list->tail->count = 1;
	}
}

void traverseList(struct LinkedList *list)
{
	struct Node *cur = list->head;
	while (cur != NULL)
	{
		printf("Data is: %s\t\t\tNumber is: %d\n", cur->word, cur->count);
		cur = cur->next;
	}
}