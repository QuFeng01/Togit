#include "wordcount.h"


int 
Compare_Word(void* elem1, void* elem2){
	if( strcmp( (((Word*)elem1)->word), (((Word*)elem2)->word) ) > 0)
		return 1;
	else if( strcmp( (((Word*)elem1)->word), (((Word*)elem2)->word) ) == 0 )
		return 0;
	else
		return -1;
}


int 
Compare_CaseWord(void* elem1, void* elem2){
	if( strcasecmp((((Word*)elem1)->word), ((Word*)elem2)->word) > 0)
		return 1;
	else if( strcasecmp((((Word*)elem1)->word), ((Word*)elem2)->word) == 0 )
		return 0;
	else
		return -1;
}


int 
Compare_Count(void* elem1, void* elem2){
	if( (((Word*)elem1)->count) > (((Word*)elem2)->count) )
		return 1;
	else if( (((Word*)elem1)->count) == (((Word*)elem2)->count) )
		return 0;
	else 
		return -1;
}


int 
Compare_Pos(void* elem1, void* elem2){
	if( (((Word*)elem1)->pos) > (((Word*)elem2)->pos) )
		return 1;
	else if( (((Word*)elem1)->pos) == (((Word*)elem2)->pos) )
		return 0;
	else 
		return -1;
}


int 
Compare_InList_W(void* elem1, void* elem2){
	if( strcasecmp( ((Word*)elem1)->word, (char*)elem2) != 0 )
		return 1;
	else 
		return strcasecmp( ((Word*)elem1)->word, (char*)elem2);
}


int 
Compare_InList_w(void* elem1, void* elem2){
	if( strcmp( ((Word*)elem1)->word, (char*)elem2) != 0 )
		return 1;
	else
		return  strcmp( ((Word*)elem1)->word, (char*)elem2); 
}


FILE* 
ReadFile(char* readOpt){
	FILE* fp = fopen(readOpt, "r");
	if(fp == NULL){
		printf("Open file failed!\n");
		return NULL;
	}
	printf("Open file success!\n");
	return fp;
}


int 
PrintData(DList* list){	
	DNode* pWord = list->first;	
	while(pWord != NULL){
		printf("pWord->add: %p\tWord: %-10s\tpWord->count: %-5d\t\tpWord->pos : %d\n", pWord, ((Word*)pWord->data)->word, ((Word*)pWord->data)->count, ((Word*)pWord->data)->pos);
		pWord = pWord->next;
	}
	return 0;
}



int 
GetWordList_UL(ListArray hashArray[], FILE* fp){	
	int iCount = 0;
	int pos = 0;

	char* strBuffer = (char*)malloc(2048 * sizeof(char));
	if(strBuffer == NULL)
		return -1;
	
	char* wordStr = (char*)malloc(sizeof(char)*WORD_SIZE);
	if(wordStr == NULL)
		return -1;

	while( fgets(strBuffer, 2048, fp) ){
		int length = strlen(strBuffer);
		*(strBuffer + length - 1) = '\0';

		pos = 0;
		while( !isalpha(*(strBuffer+pos)) ){
			pos++;
		}

		while( *(strBuffer + pos) != '\0' ){
			int wPos = 0;
			
			if( *(strBuffer + pos) == '\'' )
				pos++;

			while( isalpha( *(strBuffer+pos)) || *(strBuffer+pos) == '\''){
				if(wPos < WORD_SIZE ){
					*(wordStr + wPos) = *(strBuffer + pos);
					wPos++;
				}else{
					*(wordStr + wPos - 1)= '\0';
					wPos--;
					pos--;
					break;
				}
				pos++;
			}

			if( *(wordStr + wPos - 1) == '\''){
				*(wordStr + wPos - 1) = '\0';
			}else{
				*(wordStr + wPos) = '\0';
			}
			
			int arrIndex = GetArrayIndex(wordStr) - 1;
			DNode* find = (hashArray[arrIndex].listHead)->first;
			find = Search(hashArray[arrIndex].listHead, wordStr, Compare_InList_w);
			if( find != NULL ){
				(((Word*)find->data)->count)++;
			}else{
				Word* wNode = (Word*)malloc(sizeof(Word));
				if(wNode == NULL)
					return -1;

				wNode->word = (char*)malloc(sizeof(char)*WORD_SIZE);
				if((wNode->word) == NULL)
					return -1;
				strcpy(wNode->word, wordStr);
				wNode->count = 1;
				wNode->pos = iCount + 1;
				InsertElemTail(hashArray[arrIndex].listHead, wNode);
			}
			

			while(!isalpha(*(strBuffer+pos)) && *(strBuffer+pos) != '\0')
				pos++;

			iCount++;
		}
	}
	
	free(wordStr);
	free(strBuffer);
	return iCount;
}

int 
GetWordList_NoUL(ListArray hashArray[], FILE* fp){	
	int iCount = 0;
	int pos = 0;

	char* strBuffer = (char*)malloc(2048 * sizeof(char));
	if(strBuffer == NULL)
		return -1;
	
	char* wordStr = (char*)malloc(sizeof(char)*WORD_SIZE);
	if(wordStr == NULL)
		return -1;

	while( fgets(strBuffer, 2048, fp) ){
		int length = strlen(strBuffer);
		*(strBuffer + length - 1) = '\0';

		pos = 0;
		while( !isalpha(*(strBuffer+pos)) ){
			pos++;
		}

		while( *(strBuffer + pos) != '\0' ){
			int wPos = 0;
			
			if( *(strBuffer + pos) == '\'' )
				pos++;

			while( isalpha( *(strBuffer+pos)) || *(strBuffer+pos) == '\''){
				if(wPos < WORD_SIZE ){
					*(wordStr + wPos) = *(strBuffer + pos);
					wPos++;
				}else{
					*(wordStr + wPos - 1) = '\0';
					wPos--;
					pos--;
					break;
				}
				pos++;
			}

			if( *(wordStr + wPos - 1) == '\''){
				*(wordStr + wPos - 1) = '\0';
			}else{
				*(wordStr + wPos) = '\0';
			}
			

			int arrIndex = GetArrayIndex(wordStr) - 1;
			DNode* find = (hashArray[arrIndex].listHead)->first;
			find = Search(hashArray[arrIndex].listHead, wordStr, Compare_InList_W);
			if( find != NULL ){
				(((Word*)find->data)->count)++;
			}else{
				Word* wNode = (Word*)malloc(sizeof(Word));
				if(wNode == NULL)
					return -1;

				wNode->word = (char*)malloc(sizeof(char)*WORD_SIZE);
				if((wNode->word) == NULL)
					return -1;
				strcpy(wNode->word, wordStr);
				wNode->count = 1;
				wNode->pos = iCount + 1;
				InsertElemTail(hashArray[arrIndex].listHead, wNode);
			}
			

			while(!isalpha(*(strBuffer+pos)) && *(strBuffer+pos) != '\0')
				pos++;

			iCount++;
		}
	}
	
	free(wordStr);
	free(strBuffer);
	return iCount;
}


int 
DListSort(DNode* head, DNode* left, DNode* right, char cFlag){
	if( cFlag == 'D'){
		 Sort(head, left, right, Compare_Word); 
		 return 1;
	}
	else if( cFlag == 'M' ){
		Sort(head, left, right, Compare_Count); 
		return 2;
	}
	else if( cFlag == 'L' ){
		Sort(head, left, right, Compare_Pos); 
		return 3;
	}
	else{
		printf("command s requires arguments like:\n D(Directionnary), M(Number), L(Location)\n");
		return -1;
	}
		  
}


void
FreeMemery(Elemtype elem){	
	Word* pWord = ((DNode*)elem)->data;
	free(pWord->word);
//	printf("Free pWord\n");
	free(((DNode*)elem)->data);
//	printf("Free data\n");
}


int 
GetArrayIndex(char* wordStr){
	int val = *(wordStr);
	switch(val){
		case 'A':
			return 1;
		case 'a':
			return 1;
		case 'B':
			return 2;
		case 'b':
			return 2;
		case 'C':
			return 3;
		case 'c':
			return 3;
		case 'D':
			return 4;
		case 'd':
			return 4;
		case 'E':
			return 5;
		case 'e':
			return 5;
		case 'F':
			return 6;
		case 'f':
			return 6;
		case 'G':
			return 7;
		case 'g':
			return 7;
		case 'H':
			return 8;
		case 'h':
			return 8;
		case 'I':
			return 9;
		case 'i':
			return 9;
		case 'J':
			return 10;
		case 'j':
			return 10;
		case 'K':
			return 11;
		case 'k':
			return 11;
		case 'L':
			return 12;
		case 'l':
			return 12;
		case 'M':
			return 13;
		case 'm':
			return 13;
		case 'N':
			return 14;
		case 'n':
			return 14;
		case 'O':
			return 15;
		case 'o':
			return 15;
		case 'P':
			return 16;
		case 'p':
			return 16;
		case 'Q':
			return 17;
		case 'q':
			return 17;
		case 'R':
			return 18;
		case 'r':
			return 18;
		case 'S':
			return 19;
		case 's':
			return 19;
		case 'T':
			return 20;
		case 't':
			return 20;
		case 'U':
			return 21;
		case 'u':
			return 21;
		case 'V':
			return 22;
		case 'v':
			return 22;
		case 'W':
			return 23;
		case 'w':
			return 23;
		case 'X':
			return 24;
		case 'x':
			return 24;
		case 'Y':
			return 25;
		case 'y':
			return 25;
		case 'Z':
			return 26;
		case 'z':
			return 26;
	}
	return -1;
}
