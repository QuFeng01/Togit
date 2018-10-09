#include <stdio.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char* argv[]){
	int aflag = 0;
	int bflag = 0;
	int cflag = 0;
	int dflag = 0;
	int count = 0;
	int oc;

	char* cOpt;
	char* dOpt;
	
	while((oc = getopt(argc, argv, "abc:d::")) != -1){
		switch(oc){
			case 'a':
				printf("optind = %d\n", optind);
				break;
			case 'b':
				printf("optind = %d\n", optind);
				break;
			case 'c':
				printf("optind = %d\n", optind);
				break;
			case 'd':
				printf("optind = %d\n", optind);
				break;
			default:
			printf("option is error!\n");
				break;
		}
	}
	printf("optind = %d\n", optind);
	
/*	int num = argc - 1 - optind;
	while(0 != num ){
		printf("num%s\n", argv[optind + num]);
		num--;
	}
	printf("%s\n", argv[optind + num]);
*/
	return 0;
}
