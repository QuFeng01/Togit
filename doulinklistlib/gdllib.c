#include "gdllib.h"


int 
compare_int(void* elem1, void* elem2){
	if(*(int*)elem1 - *(int*)elem2 < 0)
		return -1;
	else if(*(int*)elem1 - *(int*)elem2 == 0)
		return 0;
	else
		return 1;
}

int 
compare_str(void* elem1, void* elem2){
	if( strcmp((char*)elem1, (char*)elem2) < 0)
		return -1;
	else if( strcmp((char*)elem1, (char*)elem2) == 0)
		return 0;
	else
		return -1;
}


void 
show_int(DNode* node){
	printf("add: %p\tnode->data = %d\t\n", node, *(int*)node->data);
}


void 
show_str(DNode* node){
	printf("add: %p\tnode->data = %s\n", node, (char*)node->data);
}


DList* 
CreateDList(){
	//创建双链表
	DList* list = (DList*)malloc(sizeof(DList));
	
	if(list == NULL){
//		printf("Create List Failed!\n");
		return NULL;
	}

	list->elemTotal = 0;
	list->first = NULL;
	list->last = NULL;
//	printf("Create List Success!\n");
	return list;
}


int 
Destory(DList* list, void (*FreeData)(Elemtype elem)){
	//销毁链表
	while(list->first != NULL){
		FreeData(list->last);
		DeleteElemTail(list);
	}
	free(list);

	return 0;
}

int 
Display(DList* list, void (*show)(DNode* node)){
	//显示数据
	DNode* this = list->first;

	if(this == NULL){
		printf("List is empty!\n");
		return 0;
	}
	else{
		while(this != NULL){
			printf("add: %p\t", this);
			show(this);
			this = this->next;
		}
		printf("All elem has shown!\n");
		return 10;
	}
}


DList*  
MergeList(DList* list1, DList* list2){
	//链表拼接
	if(list1->first != NULL && list2->first != NULL){
		list1->last->next = list2->first;
		list2->first->prev = list1->last;
		list1->last = list2->last;
	}else if(list1->first == NULL && list2->first != NULL){
		list1->first = list2->first;
		list1->last = list2->last;
	}
	
	list1->elemTotal = list1->elemTotal + list2->elemTotal;
	free(list2);
	return list1;
}


DNode* 
NewDNode(Elemtype val){
	DNode* node = (DNode*)malloc(sizeof(DNode));

	if(node == NULL){
//		printf("Create NewDNode Failed!\n");
		return NULL;
	}else{
		node->data = val;
		node->next = NULL;
		node->prev = NULL;
//		printf("Create NewDNode Success!\n");
		return node;
	}
}	


int 
InsertElemHead(DList* list,Elemtype val){
	//头插法插入数据
	DNode* node = NewDNode(val);

	if(node == NULL){
//		printf("Create node failed!\n");
		return -1;
	}else if(list->first == NULL){
		list->first = node;
		list->last = node;
		list->elemTotal++;
//		printf("Insert the first elem of list!\n");
		return 1;
	}else{
		node->next = list->first;
		node->prev = NULL;
		list->first->prev = node;
		list->first = node;
		list->elemTotal++;
//		printf("Insert elem to list head success!\n");
		return 2;
	}
}


int 
InsertElemTail(DList* list,Elemtype val){
	//尾插法插入数据
	DNode* node = NewDNode(val);

	if(node == NULL){
//		printf("Create node failed!\n");
		return -1;
	}else if(list->last == NULL){
		list->first = node;
		list->last = node;
		list->elemTotal++;

//		printf("Insert the first elem of list!\n");
		return 1;
	}else{
//		printf("GO\n");
		node->next = NULL;
		node->prev = list->last;
		list->last->next = node;
		list->last = node;
//		printf("node add: %p\tnode->data%p\n", node, node->data);
		list->elemTotal++;
//		printf("Insert elem to list tail success!\n");
		return 3;
	}
}


int 
InsertElemKey(DList* list, Elemtype val, Elemtype key, int (*Compare)(Elemtype elem1, Elemtype elem2)){
	DNode* node = NewDNode(val);

	if(node == NULL){
//		printf("Create node failed!\n");
		return -1;
	}else if(list->last == NULL){
		printf("List is empty!\n");
		list->first = node;
		list->last = node;
		list->elemTotal++;
//		printf("Insert the first elem of list!\n");
		return 1;
	}else{
		DNode* this = list->first;

		while(this != NULL){
			if(Compare(this->data, key) == 0 ){
				if(this->prev == NULL){
					node->prev = NULL;
					node->next = list->first;
					list->first->prev = node;
					list->first = node;
					list->elemTotal++;
//					printf("Insert elem to the first!\n");
					return 2;
				}else{
					node->prev = this->prev;
					node->next = this;
					this->prev->next = node;
					this->prev = node;
					list->elemTotal++;
//					printf("Insert elem to the normal pos!\n");
					return 4;
				}
			}
			this = this->next;
		}
	}
}


int 
ExchangeElemKey(DList* list, Elemtype val, Elemtype key, int (*Compare)(Elemtype elem1, Elemtype elem2)){
	//将key的值修改为val
	if(list->last == NULL){
		printf("List is empty!\n");
		return 0;
	}else{
		DNode* this = list->first;
		while(this != NULL){
			if(Compare(this->data, key) == 0 )
				this->data = val;
			this = this->next;
		}
		printf("The key has changed!\n");
		return 5;
	}
}


int 
DeleteElemHead(DList* list){
	//头部删除
	DNode* this = list->first;

	if(this == NULL){
//		printf("List is empty!\n");
		return 0;
	}else if(this->next == NULL){
//		printf("List has one elem!\n");
		list->first = NULL;
		list->last = NULL;
		free(this);
		list->elemTotal--;
//		printf("Delete the one elem!\n");
		return 6;
	}else{
		list->first = this->next;
		this->next->prev = NULL;
		free(this);
		list->elemTotal--;
//		printf("Delete the head elem!\n");
		return 7;
	}
}


int 
DeleteElemTail(DList* list){
	//尾部删除
	DNode* this = list->last;

	if(this == NULL){
//		printf("List is empty!\n");
		return 0;
	}else if(this->prev == NULL){
//		printf("List had one elem!\n");
		list->last = NULL;
		list->first = NULL;
		free(this);
		list->elemTotal--;
//		printf("Delete the one elem!\n");
		return 6;
	}else{
		list->last = this->prev;
		this->prev->next = NULL;
		free(this);
		list->elemTotal--;
//		printf("Delete the last elem!\n");
		return 8;
	}
}


int 
DeleteElemKey(DList* list, Elemtype key, int (*Compare)(Elemtype elem1, Elemtype elem2)){
	//删除指定值
	DNode* this = list->first;

	if(this == NULL){
		printf("List is empty!\n");
		return 0;
	}

	while(this != NULL){
		if(this->prev == NULL && this->next == NULL && Compare(this->data, key) == 0){
			list->first = NULL;
			list->last = NULL;
			free(this);
			list->elemTotal--;
			printf("The only one elem has deleted!\n");
		}else if(this->prev == NULL && Compare(this->data, key) == 0){
			list->first = this->next;
			this->next->prev = NULL;
			free(this);
			list->elemTotal--;
			printf("Delete the first elem!\n");
		}else if(this->next == NULL && Compare(this->data, key) == 0){
			list->last = this->prev;
			this->prev->next = NULL;
			free(this);
			list->elemTotal--;
			printf("Delete the last elem!\n");
		}else if(Compare(this->data, key) == 0){
			this->prev->next = this->next;
			this->next->prev = this->prev;
			free(this);
			list->elemTotal--;
			printf("Delete the elem!\n");
		}
		this = this->next;
	}
	return 9;
}


int 
DeleteElemPtr(DList* list, DNode* goal){
	//根据指针删除元素
	if(list->first == NULL){
		return -1;
	}else if( list->first == goal ){
		DeleteElemHead(list);
	}else if( list->last == goal ){
		DeleteElemTail(list);
	}else{
		goal->prev->next = goal->next;
		goal->next->prev = goal->prev;
		free(goal);
	}

	return 0;
}


DNode* 
Search(DList* list, Elemtype key, int (*Compare)(Elemtype elem1, Elemtype elem2)){
	//查找元素并返回该元素指针
	DNode* this = list->first;

	while(this != NULL){
		if(Compare(this->data, key) != 0){
			this = this->next;
		}else{
			return this;
		}
	}

	return this;
}


DNode* 
PartionDList(DNode* head, DNode* left, DNode* right, int (*Compare)(Elemtype elem1, Elemtype elem2)){
	//划分
	Elemtype key = NULL;
	Elemtype temp = NULL;

	if(head == NULL){
		return NULL;
	}
	else if(head->next == NULL){
		return head;
	}

	key = left->data;

	while(left != right){
		while(left != right && (Compare(key, right->data) < 0 || Compare(key, right->data) == 0)){
		right = right->prev;
		}

		temp = left->data;
		left->data = right->data;
		right->data = temp;

		while(left != right && (Compare(left->data, key) < 0 || Compare(left->data, key) == 0)){
			left = left->next;
		}

		temp = left->data;
		left->data = right->data;
		right->data = temp;
	}

	return left;
}


int
Sort(DNode* head, DNode* left, DNode* right, int (*Compare)(Elemtype elem1, Elemtype elem2)){
	//快速排序
	if(head == NULL){
//		printf("List is empty!\n");
		return 0;
	}
	
	DNode* partion = NULL;

	partion = PartionDList(head, left, right, Compare);
	if( left != partion )
		Sort(head, left, partion->prev, Compare);
	if( partion != right )
		Sort(head, partion->next, right, Compare);

}
