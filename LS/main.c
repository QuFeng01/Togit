#include "ls.h"


int main(int argc, char* argv[]){
	int oc = -1;
	int aFlag = 0;
	int lFlag = 0;
	int tFlag = 0;

	while( (oc = getopt(argc, argv, "alt")) != -1 ){
		switch(oc){
			case 'a':
				aFlag = 1;
				break;
			case 'l':
				lFlag = 1;
				break;
			case 't':
				tFlag = 1;
				break;
			default:
				return -1;
		}
	}

	if( optind == argc ){
		char* dirPath = (char*)malloc(sizeof(char)*256);
		strcpy(dirPath, ".");
		
		DList* fileList = CreateDList();
		if( fileList == NULL ){
			printf("Create List Failed!\n");
			free(dirPath);
			return -1;
		}

		PrintData(fileList, dirPath, aFlag, lFlag, tFlag);
		
		free(dirPath);
		Destory(fileList, FreeMemery);
	}

	
	while( argc != optind ){
		struct stat statInfo;
		if( stat(argv[optind], &statInfo) == -1){
			perror("ls: ");
			optind++;
			printf("\n");
			continue;
		}
		if( (statInfo.st_mode & S_IFMT) != S_IFDIR ){
			if( 1 == lFlag ){
				Display_lFileInfo(statInfo);
			}
			PrintFileName( statInfo, argv[optind]);
			printf("\n");
			return 0;
		}
		
		printf("%s:\n", argv[optind]);
		char* dirPath = (char*)malloc(sizeof(char)*256);
		strcpy(dirPath, argv[optind]);
		
		DList* fileList = CreateDList();
		if( fileList == NULL ){
			printf("Create List Failed!\n");
			free(dirPath);
			return -1;
		}
		
		PrintData(fileList, dirPath, aFlag, lFlag, tFlag);
		printf("\n");

		free(dirPath);
		Destory(fileList, FreeMemery);
		optind++;
	}

	return 0;
}
