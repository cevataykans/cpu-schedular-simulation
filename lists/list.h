#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <stdlib.h>

struct LinkedList *createLinkedList();
void addNode(struct LinkedList *list, int id, int burstTime);
void traverseList(struct LinkedList *list);
struct Node* FCFS(struct LinkedList* list);
struct Node* SJF(struct LinkedList* list);
struct Node* RR(struct LinkedList* list);

struct LinkedList
{
	struct Node *head;
	struct Node *tail;
};

struct Node
{
	struct Node *next;
	int id;
	int burstTime;
};