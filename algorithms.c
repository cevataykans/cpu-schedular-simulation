#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "algorithms.h"
#include "SEThread.h"

struct BurstNode* FCFS(){
    if(head == NULL)
        return NULL;
    struct BurstNode* temp = head;
    head = head->next;
    if(temp == tail)
        tail = NULL;
    return temp;
} 

struct BurstNode* SJF(){
    if(head == NULL)
        return NULL;
    if(head == tail){
        struct BurstNode* temp = head;
        head = NULL;
        tail = NULL;
        return temp;
    }
    struct BurstNode* prevMinNode = NULL;
    struct BurstNode* minNode = head;
    struct BurstNode* cur = head->next;
    struct BurstNode* prev = head;
    while(cur != NULL){
        if(cur->burstTime < minNode->burstTime){
            minNode = cur;
            prevMinNode = prev;
        }
        prev = cur;
        cur = cur->next;
    }

    if(minNode == head)
        head = head->next;

    else if(minNode == tail){
        tail = prevMinNode;
        tail->next = NULL;
    }

    else
        prevMinNode->next = minNode->next;

    return minNode;
}

struct BurstNode* RR(){
    if(head == NULL)
        return NULL;
    if(head == tail){
        if(head->burstTime <= q){
            struct BurstNode* temp = head;
            head = NULL;
            tail = NULL;
            return temp;
        }
        struct BurstNode* returnNode = (struct BurstNode*)malloc(sizeof(struct BurstNode));
        returnNode->next = NULL;
        returnNode->id = head->id;
        returnNode->burstTime = q;
        head->burstTime = head->burstTime - q;
        return returnNode;
    }
    struct BurstNode* temp = head;
    head = head->next;
    if(temp->burstTime > q){
        struct BurstNode* newNode = (struct BurstNode*)malloc(sizeof(struct BurstNode));
        newNode->id = temp->id;
        newNode->burstTime = temp->burstTime - q;
        newNode->next = NULL;
        tail->next = newNode;
        tail = newNode;
        temp->burstTime = q;
    }
    return temp;
}