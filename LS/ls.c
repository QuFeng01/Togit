#include "ls.h"

int 
Compare_Name(Elemtype elem1, Elemtype elem2){
	if( strcasecmp(((Info*)elem1)->infoName, ((Info*)elem2)->infoName ) > 0)
		return 1;
	else if(strcasecmp(((Info*)elem1)->infoName, ((Info*)elem2)->infoName) == 0)
		return 0;
	else 
		return -1;
}


int 
Compare_Time(Elemtype elem1, Elemtype elem2){
	long time1 = TimeToFigure( (Info*)elem1 );
	long time2 = TimeToFigure( (Info*)elem2 );

	if( time1 > time2)
		return 1;
	else if( time1 == time2 )
		return 0;
	else 
		return -1;
}


int 
TransformMonth(char* yearArray){
	if( strcmp(yearArray, "Jan") == 0 ){
		return 1;
	}else if( strcmp(yearArray, "Feb") == 0 ){
		return 2;
	}else if( strcmp(yearArray, "Mar") == 0 ){
		return 3;
	}else if( strcmp(yearArray, "Apr") == 0 ){
		return 4;
	}else if( strcmp(yearArray, "May") == 0 ){
		return 5;
	}else if( strcmp(yearArray, "Jun") == 0 ){
		return 6;
	}else if( strcmp(yearArray, "Jul") == 0 ){
		return 7;
	}else if( strcmp(yearArray, "Aug") == 0 ){
		return 8;
	}else if( strcmp(yearArray, "Sep") == 0 ){
		return 9;
	}else if( strcmp(yearArray, "Oct") == 0 ){
		return 10;
	}else if( strcmp(yearArray, "Nov") == 0 ){
		return 11;
	}else
		return 12;
}


long
TimeToFigure( Info* data){
		long reTime = 0;

		char year[5] = {0};
		int i = 0;
		while(i < 4){
			year[i] = *(data->infoTime + 20 + i);
			i++;
		}
		year[4] = '\0';
		int yearInt = atoi(year);
		reTime = yearInt * 10000000000;

		char month[4] = {0};
		i = 0;
		while(i < 3){
			month[i] = *(data->infoTime + 4 + i);
			i++;
		}
		month[3] = '\0';
		int monthInt = TransformMonth(month);
		reTime = reTime + monthInt * 100000000;

		char day[3] = {0};
		i = 0;
		while(i < 2){
			day[i] = *(data->infoTime + 8 + i);
			i++;
		}
		day[2] = '\0';
		int dayInt = atoi(day);
		reTime = reTime + dayInt * 1000000;
		
		char hour[3] = {0};
		i = 0;
		while(i < 2){
			hour[i] = *(data->infoTime + 11 + i);
			i++;
		}
		hour[2] = '\0';
		int hourInt = atoi(hour);
		reTime = reTime + hourInt * 10000;

		char mim[3] = {0};
		i = 0;
		while(i < 2){
			mim[i] = *(data->infoTime + 14 + i);
			i++;
		}
		mim[2] = '\0';
		int mimInt = atoi(mim);
		reTime = reTime + mimInt * 100;

		char sec[3] = {0};
		i = 0;
		while(i < 2){
			sec[i] = *(data->infoTime + 17 + i);
			i++;
		}
		sec[2] = '\0';
		int secInt = atoi(sec);	

		return (reTime + secInt);
}



void 
FreeMemery(Elemtype elem){
	Info* info = (Info*)(((DNode*)elem)->data);
	free(info);
}


long long 
GetTotal(DList* fileList, int aFlag){
	DNode* this = fileList->first;

	if(this == NULL)
		return 0;

	long long total = 0;
	if( 1 == aFlag){
		while(this != NULL){
			if( 0 == ((((Info*)this->data)->infoSize) % PAGE_SIZE) ){
				total += ( (((Info*)this->data)->infoSize) / PAGE_SIZE );
			}else{
				total += ( (((Info*)this->data)->infoSize) / PAGE_SIZE  + 1 );
			}

			this = this->next;
		}
	}else{
		while(this != NULL){
			if( *(((Info*)this->data)->infoName) != '.' ){
				if( 0 == ((((Info*)this->data)->infoSize) % PAGE_SIZE) ){
					total += ( (((Info*)this->data)->infoSize) / PAGE_SIZE );
				}else{
					total += ( (((Info*)this->data)->infoSize) / PAGE_SIZE  + 1 );
				}	
			}	

			this = this->next;
		}
	}

	return total * 4;
}


int
PrintData(DList* fileList, char* dirPath, int aFlag, int lFlag, int tFlag){
	if( 0 == aFlag && 0 == lFlag ){	
		GetInfoListNoHide(fileList, dirPath);
		if(fileList->first == NULL){
			free(dirPath);
			Destory(fileList, FreeMemery);
			return -1;
		}
		if( 1 == tFlag ){
			Sort(fileList->first, fileList->first, fileList->last, Compare_Time);
		}else{
			Sort(fileList->first, fileList->first, fileList->last, Compare_Name);
		}
		Display_Info(fileList);
	}

	else if( 0 == aFlag && 1 == lFlag){
		GetInfoList(fileList, dirPath);		
		printf("total %lld\n", GetTotal(fileList, aFlag));
		if(fileList->first == NULL){
			free(dirPath);
			Destory(fileList, FreeMemery);
			return -1;
		}
		if( 1 == tFlag ){
			Sort(fileList->first, fileList->first, fileList->last, Compare_Time);
		}else{
			Sort(fileList->first, fileList->first, fileList->last, Compare_Name);
		}
		Display_lInfo(fileList);
	}

	else if( 1 == aFlag && 0 == lFlag ){
		GetInfoList(fileList, dirPath);		
		if( 1 == tFlag ){
			Sort(fileList->first, fileList->first, fileList->last, Compare_Time);
		}else{
			Sort(fileList->first, fileList->first, fileList->last, Compare_Name);
		}
		Display_aInfo(fileList);
	}

	else if( 1 == aFlag && 1 == lFlag ){
		GetInfoList(fileList, dirPath);		
		printf("total %lld\n", GetTotal(fileList, aFlag));
		if( 1 == tFlag ){
			Sort(fileList->first, fileList->first, fileList->last, Compare_Time);
		}else{
			Sort(fileList->first, fileList->first, fileList->last, Compare_Name);
		}
		Display_alInfo(fileList);
	}

	return 0;
}




int 
GetInfoListNoHide(DList* fileList, char* dirPath){
	DIR* dir;
	dir = opendir(dirPath);
	if( dir == NULL ){
		printf("Open Dir Failed!\n");
		free(dirPath);
		Destory(fileList, FreeMemery);
		return -1;
	}

	struct dirent* ent = NULL;
	strcat(dirPath, "/");
	while( (ent = readdir(dir)) != NULL){
		if( *(ent->d_name) == '.' )
			continue;

		Info* fileInfo = (Info*)malloc(sizeof(Info));
		char* filePath = (char*)malloc(sizeof(char)*256);
		strcpy(filePath, dirPath);

		strcpy(fileInfo->infoName, ent->d_name);
		fileInfo->infoNameLen = strlen(ent->d_name);
			
		char str[11] = "----------";
		if( ent->d_type == 4 )
			str[0] = 'd';
		else if( ent->d_type == 10 )
			str[0] = 'l';
			
		struct stat statInfo;
		strcat(filePath, fileInfo->infoName);
		if( stat(filePath, &statInfo) == -1 ){
			perror("stat");
			free(filePath);
			free(fileInfo);
			free(dirPath);
			Destory(fileList, FreeMemery);
			return -1;
		}
			
		if(statInfo.st_mode & S_IRUSR )	 str[1] = 'r';
		if(statInfo.st_mode & S_IWUSR )	 str[2] = 'w';
		if(statInfo.st_mode & S_IXUSR )	 str[3] = 'x';
		
		if(statInfo.st_mode & S_IRGRP )	 str[4] = 'r';
		if(statInfo.st_mode & S_IWGRP )	 str[5] = 'w';
		if(statInfo.st_mode & S_IXGRP )	 str[6] = 'x';
			
		if(statInfo.st_mode & S_IROTH )	 str[7] = 'r';
		if(statInfo.st_mode & S_IWOTH )	 str[8] = 'w';
		if(statInfo.st_mode & S_IXOTH )	 str[9] = 'x';
			
		strcpy(fileInfo->infoPerm, str);
		*((fileInfo->infoPerm)+10) = '\0';
		fileInfo->infoLink = statInfo.st_nlink;

		struct passwd* pwd;
		struct group* grp;
		pwd = getpwuid(statInfo.st_uid);
		grp = getgrgid(statInfo.st_gid);
		strcpy(fileInfo->infoUname, pwd->pw_name);
		strcpy(fileInfo->infoGname, grp->gr_name);

		fileInfo->infoSize = statInfo.st_size;
		

		strncpy(fileInfo->infoTime, ctime(&statInfo.st_mtime), 25);
		fileInfo->infoTime[24] = '\0';
		InsertElemTail(fileList, fileInfo);
			
		free(filePath);	
	}

	return 0;
}



int
GetInfoList(DList* fileList, char* dirPath){
	DIR* dir = opendir(dirPath);
	if( dir == NULL ){
		printf("Open Dir Failed!\n");
		free(dirPath);
		Destory(fileList, FreeMemery);
		return -1;
	}

	struct dirent* ent = NULL;
	strcat(dirPath, "/");
	while( (ent = readdir(dir)) != NULL){
		Info* fileInfo = (Info*)malloc(sizeof(Info));
		char* filePath = (char*)malloc(sizeof(char)*256);
		memset(fileInfo, 0, sizeof(Info));
		memset(filePath, 0, sizeof(char)*256);

		strcpy(filePath, dirPath);

		strcpy(fileInfo->infoName, ent->d_name);
		fileInfo->infoNameLen = strlen(ent->d_name);
			
		char str[11] = "-----------";
		if( ent->d_type == 4 )
			str[0] = 'd';
		else if( ent->d_type == 10 )
			str[0] = 'l';
			
		struct stat statInfo;
		strcat(filePath, fileInfo->infoName);
		if( stat(filePath, &statInfo) == -1 ){
			perror("stat");
			free(filePath);
			free(fileInfo);
			free(dirPath);
			Destory(fileList, FreeMemery);
			return -1;
		}
			
		if(statInfo.st_mode & S_IRUSR )	 str[1] = 'r';
		if(statInfo.st_mode & S_IWUSR )	 str[2] = 'w';
		if(statInfo.st_mode & S_IXUSR )	 str[3] = 'x';
		
		if(statInfo.st_mode & S_IRGRP )	 str[4] = 'r';
		if(statInfo.st_mode & S_IWGRP )	 str[5] = 'w';
		if(statInfo.st_mode & S_IXGRP )	 str[6] = 'x';
			
		if(statInfo.st_mode & S_IROTH )	 str[7] = 'r';
		if(statInfo.st_mode & S_IWOTH )	 str[8] = 'w';
		if(statInfo.st_mode & S_IXOTH )	 str[9] = 'x';
			
		strcpy(fileInfo->infoPerm, str);
		*((fileInfo->infoPerm)+10) = '\0';
		fileInfo->infoLink = statInfo.st_nlink;

		struct passwd* pwd;
		struct group* grp;
		pwd = getpwuid(statInfo.st_uid);
		grp = getgrgid(statInfo.st_gid);
		strcpy(fileInfo->infoUname, pwd->pw_name);
		strcpy(fileInfo->infoGname, grp->gr_name);

		fileInfo->infoSize = statInfo.st_size;

		strncpy(fileInfo->infoTime, ctime(&statInfo.st_mtime), 25);
		fileInfo->infoTime[24] = '\0';
		InsertElemTail(fileList, fileInfo);
			
		free(filePath);	
	}

	return 0;
}


void 
PrintFileName(struct stat statInfo, char* fileName){
		switch( statInfo.st_mode & S_IFMT ){
			case S_IFDIR:
				printf("\033[1;34;40m%s\033[0m", fileName);
				break;
			case S_IFLNK:  
				printf("\033[1;36;40m%s\033[0m", fileName);		
				break;
		}
		if(statInfo.st_mode & S_IXUSR || statInfo.st_mode & S_IXGRP || statInfo.st_mode & S_IXOTH )	 
			printf("\033[1;32;40m%s\033[0m", fileName);
		else
			printf("%s", fileName);			
}


void 
Display_lFileInfo(struct stat statInfo){
		char str[11] = "-----------";
		switch( statInfo.st_mode & S_IFMT ){
			case S_IFBLK:  str[0] = 'b';  break;
			case S_IFCHR:  str[0] = 'c';  break;
			case S_IFLNK:  str[0] = 'l';  break;
			case S_IFSOCK: str[0] = 's';  break;
		}		
			
		if(statInfo.st_mode & S_IRUSR )	 str[1] = 'r';
		if(statInfo.st_mode & S_IWUSR )	 str[2] = 'w';
		if(statInfo.st_mode & S_IXUSR )	 str[3] = 'x';
		
		if(statInfo.st_mode & S_IRGRP )	 str[4] = 'r';
		if(statInfo.st_mode & S_IWGRP )	 str[5] = 'w';
		if(statInfo.st_mode & S_IXGRP )	 str[6] = 'x';
			
		if(statInfo.st_mode & S_IROTH )	 str[7] = 'r';
		if(statInfo.st_mode & S_IWOTH )	 str[8] = 'w';
		if(statInfo.st_mode & S_IXOTH )	 str[9] = 'x';
		
		str[10] = '\0';
		printf("%s  %3ld  ", str, statInfo.st_nlink);
		struct passwd* pwd;
		struct group* grp;
		pwd = getpwuid(statInfo.st_uid);
		grp = getgrgid(statInfo.st_gid);
		printf("%8s  %8s  %8ld  ", pwd->pw_name, grp->gr_name, statInfo.st_size);
		
		char infoTime[25];
		strncpy(infoTime, ctime(&statInfo.st_mtime), 25);
		infoTime[24] = '\0';
		printf("%s  ", infoTime );
}


void 
Display_Info(DList* fileList){
	Display_aInfo(fileList);
}


void 
Display_aInfo(DList* fileList){
	struct winsize size;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &size);
	int col = size.ws_col;

	if(col < 30){
		col -= 10;
	}else if(col < 100 && col > 30){
		col -= 25;
	}else{
		col -= 40;
	}
	
	int nameLen = 0;
	DNode* this = fileList->first;
	while( this != NULL){
		nameLen = strlen(((Info*)(this->data))->infoName) + nameLen + 2;
		this = this->next;
	}
	
	int line = 0;
	if( 0 == (nameLen % col) ){
		line = nameLen / col;
	}else{
		line = nameLen / col + 1;
	}
	
	int rowDif = 0;
	if( 0 == (fileList->elemTotal % line) ){
		rowDif = fileList->elemTotal / line;
	}else{
		rowDif = fileList->elemTotal / line + 1;
	}

	int widthSum = 0;
	this = fileList->first;
	int iFlag = 0;
	for(iFlag = 0; iFlag < rowDif; iFlag++){
		int tempLen = 0;
		DNode* find = this;
		while( find != NULL){
			int difFlag = 0;
			if( tempLen < strlen(((Info*)(find->data))->infoName) )	
				tempLen = strlen(((Info*)(find->data))->infoName);
			while(find != NULL && difFlag < rowDif){
				find = find->next;
				difFlag++;
			}
		}
		widthSum += tempLen;
		this = this->next;
	}

	
	if( widthSum > col){
		line += 1;

		if( 0 == (fileList->elemTotal % line) ){
			rowDif = fileList->elemTotal / line;
		}else{
			rowDif = fileList->elemTotal / line + 1;
		}
	}	


	this = fileList->first;
	DNode* find = NULL;
	int lineCount = 0;
	int setWidth = 0;
	int colWidth[rowDif];
	for(iFlag = 0; iFlag < rowDif; iFlag++){
		colWidth[iFlag] = 0;
	}
	while(lineCount < line && this != NULL){
		find = this;
		while(find != NULL){
			int getWidth = strlen(((Info*)find->data)->infoName);
			if(getWidth > colWidth[setWidth]){
				colWidth[setWidth] = getWidth;
			}
			
			iFlag = 0;
			while(iFlag < line && find != NULL){
				find = find->next;
				iFlag++;
			}
			setWidth++;
		}
		
		setWidth = 0;
		this = this->next;
		lineCount++;
	}
	
	this = fileList->first;
	find = NULL;
	lineCount = 0;
	setWidth = 0;
	while(lineCount < line && this != NULL){
		find = this;
		while(find != NULL){
			if( *(((Info*)find->data)->infoPerm) == 'd' )
				printf("\033[1;34;40m%-*s\033[0m  ", colWidth[setWidth], ((Info*)find->data)->infoName);
			else if( *(((Info*)find->data)->infoPerm) == 'l' )
				printf("\033[1;36;40m%-*s\033[0m  ", colWidth[setWidth], ((Info*)find->data)->infoName);		
			else if( *((((Info*)find->data)->infoPerm) + 3) == 'x' || *((((Info*)find->data)->infoPerm) + 6) == 'x' || *((((Info*)find->data)->infoPerm) + 9) == 'x' )
				printf("\033[1;32;40m%-*s\033[0m  ", colWidth[setWidth], ((Info*)find->data)->infoName);
			else
				printf("%-*s  ", colWidth[setWidth], ((Info*)find->data)->infoName);			

			
			iFlag = 0;
			while(iFlag < line && find != NULL){
				find = find->next;
				iFlag++;
			}
			setWidth++;
		}
		
		setWidth = 0;
		this = this->next;
		printf("\n");	
		lineCount++;
	}

}


void 
Display_lInfo(DList* fileList){
	DNode* this = fileList->first;

	while(this != NULL){
		if( *(((Info*)this->data)->infoName) != '.' ){
			printf("%s ", ((Info*)this->data)->infoPerm);
			printf("%3ld ", ((Info*)this->data)->infoLink);
			printf("%8s %8s ", ((Info*)this->data)->infoUname, ((Info*)this->data)->infoGname);
			printf("%8lld %s ", ((Info*)this->data)->infoSize, ((Info*)this->data)->infoTime);
			
			if( *(((Info*)this->data)->infoPerm) == 'd' )
				printf("\033[1;34;40m%s\033[0m\n", ((Info*)this->data)->infoName);
			else if( *(((Info*)this->data)->infoPerm) == 'l' )
				printf("\033[1;36;40m%s\033[0m\n", ((Info*)this->data)->infoName);		
			else if( *((((Info*)this->data)->infoPerm) + 3) == 'x' || *((((Info*)this->data)->infoPerm) + 6) == 'x' || *((((Info*)this->data)->infoPerm) + 9) == 'x' )
				printf("\033[1;32;40m%s\033[0m\n", ((Info*)this->data)->infoName);
			else
				printf("%s\n", ((Info*)this->data)->infoName);
		}

		this = this->next;
	}
}



void
Display_alInfo(DList* fileList){
	DNode* this = fileList->first;

	while(this != NULL){
		printf("%s ", ((Info*)this->data)->infoPerm);
		printf("%3ld ", ((Info*)this->data)->infoLink);
		printf("%8s %8s ", ((Info*)this->data)->infoUname, ((Info*)this->data)->infoGname);
		printf("%8lld %s ", ((Info*)this->data)->infoSize, ((Info*)this->data)->infoTime);
			
		if( *(((Info*)this->data)->infoPerm) == 'd' )
			printf("\033[1;34;40m%s\033[0m\n", ((Info*)this->data)->infoName);
		else if( *(((Info*)this->data)->infoPerm) == 'l' )
			printf("\033[1;36;40m%s\033[0m\n", ((Info*)this->data)->infoName);		
		else if( *((((Info*)this->data)->infoPerm) + 3) == 'x' || *((((Info*)this->data)->infoPerm) + 6) == 'x' || *((((Info*)this->data)->infoPerm) + 9) == 'x' )
			printf("\033[1;32;40m%s\033[0m\n", ((Info*)this->data)->infoName);
		else
			printf("%s\n", ((Info*)this->data)->infoName);

		this = this->next;
	}
}
