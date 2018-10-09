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

	if( 1 == argc ){	
		printf("total = \n");
		char* fileName = (char*)malloc(sizeof(char)*255);
		strcpy(fileName, ".");
//		printf("%s\n", fileName);
	
		DIR* dir;
		dir = opendir(fileName);
		if(dir == NULL){
			printf("Open Dir Failed!\n");
			return -1;
		}
	
		struct dirent* ent = NULL;
		char* file = (char*)malloc(sizeof(char)*255);
		strcpy(file, fileName);
		strcat(file, "/");
//		printf("%s\n", file);
		while( (ent = readdir(dir)) != NULL){
			strcat(file, ent->d_name);
		
			char str[10] = "----------";
			if( 4 == ent->d_type )  str[0] = 'd';
			if( 10 == ent->d_type ) str[0] = 'l';

			struct stat fileInfo;
			if( stat(file, &fileInfo) == -1){
				perror("stat");
				return -1;
			}
		
			if(fileInfo.st_mode & S_IRUSR )	 str[1] = 'r';
			if(fileInfo.st_mode & S_IWUSR )	 str[2] = 'w';
			if(fileInfo.st_mode & S_IXUSR )	 str[3] = 'x';
		
			if(fileInfo.st_mode & S_IRGRP )	 str[4] = 'r';
			if(fileInfo.st_mode & S_IWGRP )	 str[5] = 'w';
			if(fileInfo.st_mode & S_IXGRP )	 str[6] = 'x';
			
			if(fileInfo.st_mode & S_IROTH )	 str[7] = 'r';
			if(fileInfo.st_mode & S_IWOTH )	 str[8] = 'w';
			if(fileInfo.st_mode & S_IXOTH )	 str[9] = 'x';
			printf("%s %4ld ", str, (long)fileInfo.st_nlink);
		
			struct passwd* pwd;
			struct group* grp;
			pwd = getpwuid(fileInfo.st_uid);
			grp = getgrgid(fileInfo.st_gid);
			printf("%s %s ", pwd->pw_name, grp->gr_name);
//			printf("%3d %1d %s\n", ent->d_reclen, ent->d_type, ent->d_name);
			printf("%8lld ", (long long)fileInfo.st_size);
		
			char time[25];
			strncpy(time, ctime(&fileInfo.st_mtime), 25);
			time[24] = '\0';
			printf("%s ", time);

			if( 4 == ent->d_type)
				printf("\033[1;34;40m%s\033[0m\n", ent->d_name);
			else if( 10 == ent->d_type)	
				printf("\033[1;36;40m%s\033[0m\n", ent->d_name);
			else
				printf("%s\n", ent->d_name);

			strcpy(file, fileName);
			strcat(file, "/");
		}

		free(file);
		closedir(dir);
		free(fileName);
		printf("\n");
	}


	while( argc != optind){
		printf("total = \n");
		char* fileName = (char*)malloc(sizeof(char)*255);
		strcpy(fileName, argv[optind]);
//		printf("%s\n", fileName);
	
		DIR* dir;
		dir = opendir(fileName);
		if(dir == NULL){
			printf("Open Dir Failed!\n");
			return -1;
		}
	
		struct dirent* ent = NULL;
		char* file = (char*)malloc(sizeof(char)*255);
		strcpy(file, fileName);
		strcat(file, "/");
//		printf("%s\n", file);
		while( (ent = readdir(dir)) != NULL){
			strcat(file, ent->d_name);
		
			char str[10] = "----------";
			if( 4 == ent->d_type )  str[0] = 'd';
			if( 10 == ent->d_type ) str[0] = 'l';

			struct stat fileInfo;
			if( stat(file, &fileInfo) == -1){
				perror("stat");
				return -1;
			}
		
			if(fileInfo.st_mode & S_IRUSR )	 str[1] = 'r';
			if(fileInfo.st_mode & S_IWUSR )	 str[2] = 'w';
			if(fileInfo.st_mode & S_IXUSR )	 str[3] = 'x';
		
			if(fileInfo.st_mode & S_IRGRP )	 str[4] = 'r';
			if(fileInfo.st_mode & S_IWGRP )	 str[5] = 'w';
			if(fileInfo.st_mode & S_IXGRP )	 str[6] = 'x';
			
			if(fileInfo.st_mode & S_IROTH )	 str[7] = 'r';
			if(fileInfo.st_mode & S_IWOTH )	 str[8] = 'w';
			if(fileInfo.st_mode & S_IXOTH )	 str[9] = 'x';
			printf("%s %4ld ", str, (long)fileInfo.st_nlink);
		
			struct passwd* pwd;
			struct group* grp;
			pwd = getpwuid(fileInfo.st_uid);
			grp = getgrgid(fileInfo.st_gid);
			printf("%s %s ", pwd->pw_name, grp->gr_name);
//			printf("%3d %1d %s\n", ent->d_reclen, ent->d_type, ent->d_name);
			printf("%8lld ", (long long)fileInfo.st_size);
		
			char time[25];
			strncpy(time, ctime(&fileInfo.st_mtime), 25);
			time[24] = '\0';
			printf("%s ", time);

			if( 4 == ent->d_type)
				printf("\033[1;34;40m%s\033[0m\n", ent->d_name);
			else if( 10 == ent->d_type)	
				printf("\033[1;36;40m%s\033[0m\n", ent->d_name);
			else
				printf("%s\n", ent->d_name);

			strcpy(file, fileName);
			strcat(file, "/");
		}

		free(file);
		closedir(dir);
		free(fileName);
		optind++;
		printf("\n");
	}

	return 0;
}
