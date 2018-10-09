#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){
	FILE* fp = fopen(argv[argc-1], "r");
	if(fp == NULL){
		printf("Open file failed!\n");
		return -1;
	}

	char* strBuffer = (char*)malloc(1000 * sizeof(char));
	if( strBuffer == NULL ){
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
	while( fgets(strBuffer, 2048, fp) ){
		pos = 0;
		int length = strlen(strBuffer);
//		printf("str length = %d\n", length);
		*(strBuffer + length - 1) = '\0';
//		printf("strBuffer : %s\n", strBuffer);
		
		while( !isalpha(*(strBuffer+pos)) ){
			pos++;
		}
//		printf("Init pos = %d\n", pos);
//		printf("first char : %c\n", *(strBuffer + pos));

		while( *(strBuffer + pos) != '\0' ){
			int wPos = 0;
			int lenTime = 1;

			if( *(strBuffer+pos) == '\'')
				pos++;

			while( isalpha( *(strBuffer+pos) ) || *(strBuffer+pos) == '\''){
				if(wPos <  (24 * lenTime) ){
					*(word + wPos) = *(strBuffer + pos);
					wPos++;
				}else{
					lenTime++;
					word = realloc(word, 24*lenTime);
					if(word == NULL)
						return -1;
				}
				pos++;
			}
//			printf("pos = %d\t%c\n", pos, *(strBuffer + pos));
//			printf("wPos = %d\t%c\n", wPos, *(word + wPos));

			if( *(word + wPos - 1) == '\''){
				*(word + wPos - 1) = '\0';
			}else{
				*(word + wPos) = '\0';
			}
//			printf("%s\n", word);

			while( !isalpha(*(strBuffer+pos)) && *(strBuffer+pos) != '\'' && *(strBuffer+pos) != '\0' ){
				pos++;
			}
			wordCount++;
		}
	}
	printf("wordCount = %d\n", wordCount);

	free(word);
	free(strBuffer);
	fclose(fp);

	return 0;
}
