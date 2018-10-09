#ifndef _GDLLIB_H
#define _GDLLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>




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

int (*Compare)(Elemtype elem1, Elemtype elem2);
void (*FreeData)(Elemtype elem);

void show_int(DNode* node);
void show_str(DNode* node);

void (*show)(DNode* node);

DList* CreateDList();   //创建双链表
int Destory(DList* list, void (*FreeMem)(Elemtype elem));  //销毁链表
int Display(DList* list, void (*show)(DNode* node));   //显示数据
DList* MergeList(DList* list1, DList* list2);   //链表拼接


DNode* NewDNode(Elemtype val);
int InsertElemHead(DList* list,Elemtype val);  //头插法插入数据
int InsertElemTail(DList* list,Elemtype val);  //尾插法插入数据
int InsertElemKey(DList* list, Elemtype val, Elemtype key, int (*Compare)(Elemtype elem1, Elemtype elem2));   //将val插入到key之前

int ExchangeElemKey(DList* list, Elemtype val, Elemtype key, int (*Compare)(Elemtype elem1, Elemtype elem2));  //将key的值修改为val

int DeleteElemHead(DList* list);  //头部删除
int DeleteElemTail(DList* list);  //尾部删除
int DeleteElemKey(DList* list, Elemtype key, int (*Compare)(Elemtype elem1, Elemtype elem2)); //删除指定值
int DeleteElemPtr(DList* list, DNode* goal); //根据指针删除元素

DNode* Search(DList* list, Elemtype key, int (*Compare)(Elemtype elem1, Elemtype elem2));  //查找元素并返回位序

DNode* PartionDList(DNode* head, DNode* left, DNode* right, int (*Compare)(Elemtype elem1, Elemtype elem2));  //划分
int Sort(DNode* head, DNode* left, DNode* right, int (*Compare)(Elemtype elem1, Elemtype elem2));  //快速排序


#endif
