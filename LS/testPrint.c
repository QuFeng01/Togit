#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <termios.h>


typedef struct _Info{
	char name[256];;
	int  len;
}Info;


int main(int argc, char* argv[]){
	Info file[20];
	
	struct winsize size;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &size);
	printf("ws_col = %d\v ws_row = %-d\n", size.ws_col, size.ws_row);
	printf("haha\v gaga\n");
	
	int wide = 10;

	char* str1 = "abc";
	char* str2 = "hello world!";
	char* str3 = "short";
	char* str4 = "too longdaudahdoaidaidhaiodabdao";
	char* str5 = "stand";
	
	int width1 = strlen(str2);
	int width2 = strlen(str4);
	printf("%-*s %-*s %s\n%s %s\n", width1, str1, width2, str3, str5, str2, str4);

	char* flag = strrchr(str5, 'b');
	if(flag == NULL){
		printf("Don't find\n");
	}else{
		printf("%s\n", flag);
	}
	
	int pSize = 4097;
	int total = 0;
	if( (pSize % 4096) != 0)
		printf("total = %d\n", pSize / 4096 + 1);

	return 0;
}
