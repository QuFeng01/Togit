#ifndef _GDLLIB_H
#define _GDLLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/**
 ***************************************************************
 * return val         indicated
 *    -1              Create node failed 
 *     0              List is empty,  No Key 
 *     1              Insert the first elem of list
 *     2              Insert elem to list head success
 *     3              Insert elem to list tail success
 *     4              Insert elem to the normal pos
 *     5              The key has changed
 *     6              Delete the one elem
 *     7              Delete the head elem
 *     8              Delete the last elem
 *     9              Delete the elme form the key
 *     10             ALL elem has shown
 *     11             List has been destoryed
 *     13             Sort completed
 ****************************************************************
 */



typedef void* Elemtype;

typedef struct _DNode{
	Elemtype data;
	struct _DNode* next;
	struct _DNode* prev;
}DNode;

typedef struct _DList{
	int elemTotal;
	struct _DNode* first;
	struct _DNode* last;
}DList;

int compare_int(Elemtype elem1, Elemtype elem2);
int compare_str(Elemtype elem1, Elemtype elem2);

int (*compare)(Elemtype elem1, Elemtype elem2);

void show_int(DNode* node);
void show_str(DNode* node);

void (*show)(DNode* node);

DList* CreateDList();   //创建双链表
int Destory(DList* list);  //销毁链表
int Display(DList* list, void (*show)(DNode* node));   //显示数据

DNode* NewDNode(Elemtype val);
int InsertElemHead(DList* list,Elemtype val);  //头插法插入数据
int InsertElemTail(DList* list,Elemtype val);  //尾插法插入数据
int InsertElemKey(DList* list, Elemtype val, Elemtype key, int (*compare)(Elemtype elem1, Elemtype elem2));   //将val插入到key之前

int ExchangeElemKey(DList* list, Elemtype val, Elemtype key, int (*compare)(Elemtype elem1, Elemtype elem2));  //将key的值修改为val

int DeleteElemHead(DList* list);  //头部删除
int DeleteElemTail(DList* list);  //尾部删除
int DeleteElemKey(DList* list, Elemtype key, int (*compare)(Elemtype elem1, Elemtype elem2)); //删除指定值

int Search(DList* list, Elemtype key, int (*compare)(Elemtype elem1, Elemtype elem2));  //查找元素并返回位序

DNode* PartionDList(DNode* head, DNode* left, DNode* right, int (*compare)(Elemtype elem1, Elemtype elem2));  //划分
int Sort(DNode* head, DNode* left, DNode* right, int (*compare)(Elemtype elem1, Elemtype elem2));  //快速排序


#endif
