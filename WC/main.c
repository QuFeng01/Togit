#include <unistd.h>
#include "wordcount.h"


int main(int argc, char* argv[]){
	struct timeval tStart;
	struct timeval tEnd;
	
	if(argc == 1){
		printf("argument is too little\n");
		return 0;
	}

	gettimeofday(&tStart, NULL);

	if( strcmp(argv[1], "--help") == 0 ){
		printf("wordcount --help\n\t-c Create list with upper and lower not being considering\n\t   In default, there will consider upper and lower without -c option\n\t-s [argument] Sort the list\n\t\t[D] directionnary sort\n\t\t[M] counting sort\n\t\t[L] Location sort\n\t-p Print the data of list\n");
		return 0;
	}

	int iCount = 0;

	int oc;
	int cOptFlag = 0;
	int pOptFlag = 0;
	int sOptFlag = 0;
	char sOpt;

	while( (oc = getopt(argc, argv, "cps:")) != -1){
		switch(oc){
			case 'c':
				cOptFlag = 1;
				break;
			case 'p':
				if( 1 == pOptFlag ){
					break;
				}
				pOptFlag = 1;
				break;
			case 's':
				if( 1 == sOptFlag){
					break;
				}
				sOptFlag = 1;
				sOpt = optarg[0];
				break;
			default:
				printf("Please input option like : -c -p -s\n");
				return -1;
		}
	}


	ListArray hashArray[26];
	int i = 0;
	for(i = 0; i < 26; i++){
		hashArray[i].bigCh = 65+i;
		hashArray[i].smallCh = 97+i;
		hashArray[i].listHead = CreateDList();
		if( hashArray[i].listHead == NULL ){
			printf("Create DList Failed!\n");
			return -1;
		}
	}
	
/*	for(i = 0; i < 26; i++){
		printf("bigCh = %c\tsmallCh = %c\tadd : %p\n", hashArray[i].bigCh, hashArray[i].smallCh, hashArray[i].listHead);
	}
*/
	int num = argc - optind;
	int tempOptind = optind;
	int wordTotal[num];
	int wordCount[num];
	int total = 0;
	num = 0;
	while( optind != argc ){
		FILE* fp = fopen(argv[optind], "r");
		if(fp == NULL ){
			printf("Open file failed!\n");
			return -1;
		}
		printf("Open file success!\n");

		total = 0;
		for(i = 0; i < 26; i++){
			total = (hashArray[i].listHead)->elemTotal + total;
		}
		wordTotal[num] = total;	

		if( 1 != cOptFlag){
			wordCount[num] = GetWordList_UL(hashArray, fp);
			iCount = wordCount[num] + iCount;
		}else{
			wordCount[num] = GetWordList_NoUL(hashArray, fp);
			iCount = wordCount[num] + iCount;
		}
		
		total = 0;
		for(i = 0; i < 26; i++){
			total = (hashArray[i].listHead)->elemTotal + total;
		}
		wordTotal[num] = total - wordTotal[num];
		
		fclose(fp);
		optind++;
		num++;
	}
	
	total = 0;
	if( 1 == sOptFlag || 1 == pOptFlag){
		for( i = 1; i < 26; i++){
			MergeList(hashArray[0].listHead, hashArray[i].listHead);
		}
		DList* list = hashArray[0].listHead;
		
		if(1 == sOptFlag)
			DListSort(list->first, list->first, list->last, sOpt);

		if(1 == pOptFlag)
			PrintData(list);

		total = list->elemTotal;
		Destory(list, FreeMemery);
	}else{
		for(i = 0; i < 26; i++){
			total = (hashArray[i].listHead)->elemTotal + total;
			Destory(hashArray[i].listHead, FreeMemery);
		}
	}


	
	gettimeofday(&tEnd, NULL);
	printf("All time: %ldms\n", tEnd.tv_sec*1000 + tEnd.tv_usec/1000 - tStart.tv_sec*1000 - tStart.tv_usec/1000);
	
	num = 0;
	while( num < argc - tempOptind ){
		printf("wordTotal = %4d\twordCount = %4d\tFileName : %s\n", wordTotal[num], wordCount[num], argv[tempOptind+num]);
		num++;
	}
	printf("All words is not repeated in all file : %d\n", total);
	printf("The number of word is : %d\n", iCount);
	return 0;
}

