#include "gdllib.h"

void FreeMemery(void* elem){
}

void CharOpe(){
	int iopt = -2;
	DList* list = CreateDList();
	show = show_str;
	if(list == NULL)
		printf("List is not created!\n");
	else
		printf("List is created!\n");

	while(iopt != -1){
		printf("Input iopt: ");
		scanf("%d", &iopt);

		Compare = compare_str;	
		if(iopt == 0){
			char* val = (char*)malloc(sizeof(char));
			printf("InsertElemHead.Input val: ");
			scanf("%s", val);
			printf("val = %s\n", (char*)val);
			InsertElemHead(list, val);  
		}else if(iopt == 1){
			char* val = (char*)malloc(sizeof(char));
			printf("InsertElemTail.Input val: ");
			scanf("%s", val);
			printf("val = %s\n", (char*)val);
			InsertElemTail(list, val);  //尾插法插入数据
		}else if(iopt == 2){
			char* val = (char*)malloc(sizeof(char));
			char* key = (char*)malloc(sizeof(char));
			printf("InsertElemKey.Input val and key:\n");
			scanf("%s", val);
			scanf("%s", key);
			InsertElemKey(list, val, key, Compare);
		}else if(iopt == 3){
			char* val = (char*)malloc(sizeof(char));
			char* key = (char*)malloc(sizeof(char));
			printf("ExchangeElemKey.Input val and key:\n");
			scanf("%s", val);
			scanf("%s", key);
			ExchangeElemKey(list, val, key, Compare);
		}else if(iopt == 4){
			printf("DeleteElemHead!\n");
			DeleteElemHead(list);  
		}else if(iopt == 5){
			printf("DeleteElemTail!\n");
			DeleteElemTail(list); 
		}else if(iopt == 6){
			char* key = (char*)malloc(sizeof(char));
			printf("DeleteElemKey!\nInput the key: ");
			scanf("%s", key);
			DeleteElemKey(list, key, Compare);
		}else if(iopt == 7){
			printf("QuickSort!\n");
			Sort(list->first, list->first, list->last, Compare);
		}else if(iopt == 8){
			char* key = (char*)malloc(sizeof(char));
			printf("Search!\nInput the key: ");
			scanf("%s", key);
			printf("index = %p\n",Search(list, key, Compare));
		}else if(iopt == 9){
			printf("Destory the list!\n");
			Destory(list, FreeMemery);
		}

		else if(iopt == 100){
			printf("Display the elem!\n");
//			Display(list, show);
			DNode* this = list->first;
			printf("elemTotal: %d\n", list->elemTotal);
			while(this != NULL){
				printf("add: %p\tthis->data = %s\n", this, (char*)this->data);
				this = this->next;
			}
		}
	}
}


void IntOpe(){
	int iopt = -2;
	DList* list = CreateDList();
	show = show_int;
	if(list == NULL)
		printf("List is not created!\n");
	else
		printf("List is created!\n");

	while(iopt != -1){
		printf("Input iopt: ");
		scanf("%d", &iopt);

		Compare = compare_int;	
		if(iopt == 0){
			int* val = (int*)malloc(sizeof(int));
			printf("InsertElemHead.Input val: ");
			scanf("%d", val);
			printf("val = %d\n", *(int*)val);
			InsertElemHead(list, val);  
		}else if(iopt == 1){
			int* val = (int*)malloc(sizeof(int));
			printf("InsertElemTail.Input val: ");
			scanf("%d", val);
			printf("val = %d\n", *(int*)val);
			InsertElemTail(list, val);  //尾插法插入数据
		}else if(iopt == 2){
			int* val = (int*)malloc(sizeof(int));
			int* key = (int*)malloc(sizeof(int));
			printf("InsertElemKey.Input val and key:\n");
			scanf("%d", val);
			scanf("%d", key);
			InsertElemKey(list, val, key, Compare);
		}else if(iopt == 3){
			int* val = (int*)malloc(sizeof(int));
			int* key = (int*)malloc(sizeof(int));
			printf("ExchangeElemKey.Input val and key:\n");
			scanf("%d", val);
			scanf("%d", key);
			ExchangeElemKey(list, val, key, Compare);
		}else if(iopt == 4){
			printf("DeleteElemHead!\n");
			DeleteElemHead(list);  
		}else if(iopt == 5){
			printf("DeleteElemTail!\n");
			DeleteElemTail(list); 
		}else if(iopt == 6){
			int* key = (int*)malloc(sizeof(int));
			printf("DeleteElemKey!\nInput the key: ");
			scanf("%d", key);
			DeleteElemKey(list, key, Compare);
		}else if(iopt ==7){
			printf("QuickSort!\n");
			Sort(list->first, list->first, list->last, Compare);
		}else if(iopt == 8){
			int* key = (int*)malloc(sizeof(int));
			printf("Search!\nInput the key: ");
			scanf("%d", key);
			printf("index = %p\n",Search(list, key, Compare));
		}else if(iopt == 9){
			printf("Destory the list!\n");
			Destory(list, FreeMemery);
		}

		else if(iopt == 100){
			printf("Display the elem!\n");
			DNode* this = list->first;
			printf("elemTotal: %d\n", list->elemTotal);
			while(this != NULL){
				printf("add: %p\tthis->data = %d\n", this, *(int*)this->data);
				this = this->next;
			}
		}
	}
}


int main(){
	int chooseOpe = -1;
	printf("Input Operate Data Type(0.int, 1.string): ");
	scanf("%d", &chooseOpe);

	if(chooseOpe == 0)
		IntOpe();
	else if(chooseOpe == 1)
		CharOpe();

	return 0;
}
