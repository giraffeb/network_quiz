#ifndef 	DATA_STRUCTURE_TYPES_H
#define DATA_STRUCTURE_TYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>//O_RDWD
#include <unistd.h>//write(), open();b

#include <stdbool.h>
#include <string.h>

#include <time.h>


#define maxBlocksInFile 6

#define timeStampLength 256
#define fileNameLength 1024

#define userIdLength 256
#define userPwLength 256
#define maxUserFileSize 10


struct physical_block_info;
struct physical_file_info;

struct logical_block_info;
struct logical_file_info;

struct user_info;

struct physical_file_controller;



typedef struct physical_block_info{

	struct physical_file_info *file; // 현재 이 물리 블록 정보가 소속되 있는 물리 파일을 가리키는 포인터가 필요하다 고 생각함.
	//char file_name[fileNameLength]; //위 포인터를 못쓸때 필요했던 거고, 이제는 필요가 없어요 ㅎㅎㅎㅎㅎ

	int block_index;
	int start_point_in_block;//블록의 시작지점
	int end_point_in_block;//블록의 끝지점

	char create_time[timeStampLength];
	char update_time[timeStampLength];

}BlockInfo;



typedef struct physical_file_info{
	char file_name[fileNameLength];

	int current_file_size;
	int last_block_index;

	struct physical_block_info *blocks[maxBlocksInFile];

	char create_time[timeStampLength];
	char update_time[timeStampLength];

}FileInfo;



typedef struct logical_block_info{


	struct logical_file_info *file;

	int logical_block_index;
	struct physical_block_info* thisBlock;

	//프로그램 실행시 논리적파일과 물리적 파일을 연결하기 위한 고리
	// unique block Id = fileName + blockIndex
	//관리는 아직 모르겠다.
	char physical_file_name[fileNameLength];
	int physical_block_index;

	struct logical_block_info* next;//DEPRECATED : 의미가 없는 듯.

	char create_time[timeStampLength];
	char update_time[timeStampLength];


}BlockNode;



typedef struct logical_file_info{

	int logicla_file_index;
	char file_name[fileNameLength];
	int last_block_index;

	struct logical_block_info* block_list[maxBlocksInFile];
//	struct logical_block_info* head;
//	struct logical_block_info* tail;

	char create_time[timeStampLength];
	char update_time[timeStampLength];

}FileNode;

typedef struct user_info{

	char user_id[userIdLength];
	char user_pw[userPwLength];

	FileNode *file_list[maxUserFileSize];
	int last_file_index;

}UserInfo;

typedef struct phyisical_file_controller{

	//물리파일의 생성 크기는 차후 변경할 수 있습니다.
	//이 개수로 인해서 최대개수의 논리적인 파일의 생성에 제한이 있을 수 있습니다.
	FileInfo *file_list[maxUserFileSize];
	int last_file_index;

}FileController;



//void myTimeStamp(char* stamp);

#endif DATA_STRUCTURE_TYPES_H
