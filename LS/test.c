#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>


void PrintData(struct stat* sb, const char* str);


int main(int argc, char* argv[]){
	struct stat sb;
	int oc;
	
	while( (oc = getopt(argc, argv, "a")) != -1 ){
		switch(oc){
			case 'a':
				printf("-a option\n");
				break;
			default:
				return -1;
		}
	}
	
	char* path = ".";
	if( optind == argc ){
		if( stat( path, &sb) == -1){
			perror("stat");
			return -1;
		}

		char str[10] = "----------";
		printf("File type :				");
		switch( sb.st_mode & S_IFMT ){
			case S_IFBLK:
				printf("block device\n");
				str[0] = 'b';
				break;
			case S_IFCHR:
				printf("character device\n");
				str[0] = 'c';
				break;
			case S_IFDIR:
				printf("directory\n");
				str[0] = 'd';
				break;
			case S_IFIFO:
				printf("FIFO/pipe\n");
				str[0] = 'f';
				break;
			case S_IFLNK:
				printf("symlink\n");
				str[0] = 'l';
				break;
			case S_IFREG:
				printf("regular file\n");
				str[0] = '-';
				break;
			case S_IFSOCK:
				printf("socket\n");
				str[0] = 's';
				break;
			default:
				printf("unknown?\n");
				str[0] = '?';
				break;
		}

		PrintData(&sb, str);
	}

	while(optind != argc){
		path = argv[optind];
		if( stat(path, &sb) == -1){
			perror("stat");
			return -1;
		}

		char str[10] = "----------";
		printf("File type :				");
		switch( sb.st_mode & S_IFMT ){
			case S_IFBLK:
				printf("block device\n");
				*str = 'b';
				break;
			case S_IFCHR:
				printf("character device\n");
				*str = 'c';
				break;
			case S_IFDIR:
				printf("directory\n");
				*str = 'd';
				break;
			case S_IFIFO:
				printf("FIFO/pipe\n");
				*str = 'f';
				break;
			case S_IFLNK:
				printf("symlink\n");
				*str = 'l';
				break;
			case S_IFREG:
				printf("regular file\n");
				*str = '-';
				break;
			case S_IFSOCK:
				printf("socket\n");
				*str = 's';
				break;
			default:
				printf("unknown?\n");
				*str = '?';
				break;
		}

		PrintData(&sb, str);
		optind++;
	}

	return 0;
}



void 
PrintData(struct stat* sb, const char* str){
		printf("%s\n", str);
		printf("I-node number:				%ld\n", (long)sb->st_ino);
		printf("Mode					%lo(octal)\n", (unsigned long)sb->st_mode);
		printf("Link count:				%ld\n", (long)sb->st_nlink);
		printf("Owership:				UID=%ld GID=%ld\n", (long)sb->st_uid, (long)sb->st_gid);
		struct passwd* pwd;
		struct group* grp;
		pwd = getpwuid(getuid());
		grp = getgrgid(pwd->pw_gid);
		printf("OwershipName:				UID=%s GID=%s\n", pwd->pw_name, grp->gr_name);
		printf("Preferred I/O block size:		%ld bytes\n", (long)sb->st_blksize);
		printf("File size:				%lld bytes\n", (long long)sb->st_size);
		printf("Blocks allocated:			%lld\n", (long long)sb->st_blocks);
		printf("Last status change:			%s", ctime(&sb->st_ctime));
		printf("&sb->st_ctime = %d\n", &sb->st_ctime);
		printf("Last file access:			%s", ctime(&sb->st_atime));
		printf("Last file modification:			%s", ctime(&sb->st_mtime));
}
