#ifndef _LS_H
#define _LS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <termios.h>

#include "gdllib.h"

#define PAGE_SIZE 4096

typedef struct _Info{
	char infoName[256];      //文件名
	int  infoNameLen;        //文件名长度
	char infoPerm[11];       //文件权限
	char infoTime[25];		 //文件修改时间
	char infoUname[16];      //用户名
	char infoGname[16];      //组用户名
	long infoLink;           //连接数
	long long infoSize;      //文件大小
}Info;

int Compare_Name(Elemtype elem1, Elemtype elem2);
int Compare_Time(Elemtype elem1, Elemtype elem2);


long TimeToFigure( Info* data);
int TransformMonth(char* yearArray);


void FreeMemery(Elemtype elem);

long long GetTotal(DList* fileList, int aFlag);
int  PrintData(DList* fileList, char* filePath, int aFlag, int lFlag, int tFlag);

void PrintFileName(struct stat statInfo, char* fileName);
void Display_lFileInfo(struct stat statInfo);
void Display_Info(DList* fileList);
void Display_lInfo(DList* fileList);
void Display_aInfo(DList* fileList);
void Display_alInfo(DList* fileList);

int GetInfoListNoHide(DList* fileList, char* dirPath);
int GetInfoList(DList* fileList, char* dirPath);

#endif
