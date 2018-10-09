#ifndef _WORDCOUNT_H
#define _WORDCOUNT_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <sys/time.h>
#include "gdllib.h"

#define WORD_SIZE 32 

typedef struct _ListArray{
	char bigCh;
	char smallCh;
	DList* listHead;
}ListArray;

typedef struct _Word{
	char* word;
	int count;
	int pos;
}Word;


int Compare_Word(void* elem1, void* elem2);
int Compare_CaseWord(void* elem1, void* elem2);
int Compare_Count(void* elem1, void* elem2);
int Compare_Pos(void* elem1, void* elem2);

int Compare_InList_W(void* elem1, void* elem2);
int Compare_InList_w(void* elem1, void* elem2);


FILE* ReadFile(char* readOpt);
int PrintData(DList* list);

int GetArrayIndex(char* wordStr);
int GetWordList_NoUL(ListArray hashArray[], FILE* fp);
int GetWordList_UL(ListArray hashArray[], FILE* fp);

int DListSort(DNode* head, DNode* left, DNode* right, char cFlag);
void FreeMemery(Elemtype elem);


#endif
