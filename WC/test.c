#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>


int main(int argc, char* *argv){
	char* valStr = "abc";
	int val = *valStr;
	printf("val = %d\n", val);
	switch(val){
		case 'a':
			printf("valCh = %c\n", val);
			break;
	}

	struct timeval tStart;
	struct timeval tEnd;
	struct timeval tGetline;
	struct timeval tGetword;

	gettimeofday(&tStart, NULL);
	
	FILE* fp = fopen(argv[argc-1], "r");
	if(fp == NULL){
		printf("Open file failed!\n");
		return -1;
	}

	int line = 0;
	char* strBuffer = (char*)malloc(2048*sizeof(char));
	if(strBuffer == NULL)
		return -1;
	while( fgets(strBuffer, 2048, fp) ){
		line++;
	}
	free(strBuffer);
	fclose(fp);
	printf("line = %d\n", line);

	gettimeofday(&tGetline, NULL);


	FILE* fpW = fopen(argv[argc-1], "r");
	if(fpW == NULL){
		printf("Open file failed!\n");
		return -1;
	}

	char* strBufferW = (char*)malloc(2048 * sizeof(char));
	if( strBufferW == NULL ){
		printf("Allocate strBuffer failed!\n");
		return -1;
	}
	
	char* word = (char*)malloc(24*sizeof(char));
	if( word == NULL ){
		printf("Allocate word failed!\n");
		return -1;
	}

	int wordCount = 0;
	int pos = 0;
	while( fgets(strBufferW, 2048, fp) ){
		pos = 0;
		int length = strlen(strBufferW);
		*(strBufferW + length - 1) = '\0';
		
		while( !isalpha(*(strBufferW+pos)) ){
			pos++;
		}

		while( *(strBufferW + pos) != '\0' ){
			int wPos = 0;

			if( *(strBufferW+pos) == '\'')
				pos++;

			while( isalpha( *(strBufferW+pos) ) || *(strBufferW+pos) == '\''){
				if(wPos <  24  ){
					*(word + wPos) = *(strBufferW + pos);
					wPos++;
				}else{
				}
				pos++;
			}

			if( *(word + wPos - 1) == '\''){
				*(word + wPos - 1) = '\0';
			}else{
				*(word + wPos) = '\0';
			}

			while( !isalpha(*(strBufferW+pos)) && *(strBufferW+pos) != '\0' ){
				pos++;
			}
			wordCount++;
		}
	}
	printf("WordCount = %d\n", wordCount);
	gettimeofday(&tGetword, NULL);


	gettimeofday(&tEnd, NULL);

	printf("GetLine time = %ldms\n", tGetline.tv_sec*1000 + tGetline.tv_usec/1000 - tStart.tv_sec*1000 - tStart.tv_usec/1000);
	printf("GetWord time = %ldms\n", tGetword.tv_sec*1000 + tGetword.tv_usec/1000 - tGetline.tv_sec*1000 - tGetline.tv_usec/1000);


	return 0;
}
