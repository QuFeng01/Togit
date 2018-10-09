#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>


typedef struct _Info{
	char infoName[256];      //文件名
	int  infoNameLen;        //文件名长度
	char infoPerm[10];       //文件权限
	char infoTime[25];		 //文件修改时间
	char infoUname[16];      //用户名
	char infoGname[16];      //组用户名
	long infoLink;           //连接数
	long long infoSize;      //文件大小
}Info;



int main(int argc, char* argv[]){
	int oc = -1;
	int aFlag = 0;
	int lFlag = 0;

	while( (oc = getopt(argc, argv, "al")) != -1){
		switch(oc){
			case 'a':
				aFlag = 1;
				break;
			case 'l':
				lFlag = 1;
				break;
			default:
				return -1;
		}
	}


	while( argc != optind){
		struct stat statInfo;
		if(stat(argv[optind], &statInfo) == -1){
			perror("");
			return 0;
		}

		optind++;
	}

	return 0;
}
