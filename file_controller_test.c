#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <unistd.h>

#include <string.h>
#include <stdbool.h>

#include <time.h>

#include "linux_file_test.h"
#include "data_structure_io.h"
#include "record_io.h"


/*
 * TODO : #1작업해야할 부분
 *
 * 1)
 * 여기서 read
 * 그리고 버전관리
 * 사용자 관리까지 붙이고
 *
 * 흐름을 매끄럽게 하는 함수들을 추가해서
 * 명확하게 정리해 놓는 것이 목표.
 *
 * 2) 특정 파일을 복사하는 형태로
 * 이 파일 시스템이 붙이는것이 목표
 *
 * 복사를 진행하면서, update time을 만들고
 * 파일 크기를 업데이트 하는 부분 완성하기
 *
 *:: 복사까지는 완료 시간에 대한것과 매끄러운 처리를 할것
 *
 * 3) 그 다음 목표는 서버에서 socket을 이용한 동기화 형태
 * */

int main(){

	char buffer[blockSize];

	FileController *fileController;
	initFileController(&fileController);


	UserInfo* newUser;
	initUserInfo(&newUser,"hello", "itsme");

	copyFileToUserFile(newUser, fileController, "./test02");

	printf("##########\n");
	FileNode* tempFileNode = newUser->file_list[0];
	printf("%d\n", tempFileNode->last_block_index);

	BlockInfo *tempBlockInfo;

	int i;
	for(i =0;i<=tempFileNode->last_block_index; i++){
		tempBlockInfo = tempFileNode->block_list[i]->thisBlock;

		memset(buffer, 0, bufferSize);
		readBlock(tempBlockInfo, buffer);

	}


	/*TODO : #지금해야할일!!!!
	 * 이제 할일은?
	 * 데이터 스트럭쳐 저장하기
	 * 논리파일, 블럭
	 * 물리파일, 블럭
	 *
	 * 프로그램을 다시 올렸을때 어떻게 서로 연결할 것인가?!
	 *
	 *구현하기
	 *
	 *
	 *NEXT는 서버와 통신하기!
	 *Mutex controll
	 * */
	writeUserInfoToFile(newUser);
	writeFileNodeToFile(newUser->file_list[0]);
	writeBlockNodeToFile(newUser->file_list[0]->block_list[0]);

	readUserInfoFromFile();
	printf("###");
	readFileNodeFromFile();
	printf("###");
	readBlockNodeFromFile();
	printf("###");
	return 0;
}
