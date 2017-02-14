#include "record_io.h"

/*
 * TODO : FileNode, BlockNode, FileInfo, BlockInfo, UserInfo
 * 같은 구조체 정보를 파일로 저장하는 API
 *
 *
 *
 * */

/*
 *  어차피 read(), write()는
 *  메모리 시작위치, 읽거나 쓸 크기 가 전부임.
 *  파일 명이 문제가 될텐데.
 *
 * */



int writeUserInfoToFile(UserInfo* thisUser){
	int fd, structSize;
	char *fileName = "userInfo";

	fd = checkFileOpen(fileName);

	if(fd <= 0){
		createLinuxFile(fileName);
	}

	fd = openLinuxFile(fileName);
	if(fd <= 0){
		return -1;
	}

	structSize = sizeof(UserInfo);

	write(fd, thisUser, structSize);
	close(fd);

	return 1;
}



int writeFileNodeToFile(FileNode *thisFile){
	int fd, structSize;
	char *fileName = "fileNode";

	fd = checkFileOpen(fileName);

	if(fd <= 0){
		createLinuxFile(fileName);
	}

	fd = open(fileName, O_RDWR);

	structSize = sizeof(FileNode);

	write(fd, thisFile, structSize);
	close(fd);

	return 1;
}


int writeBlockNodeToFile(BlockNode *thisBlock){
	int fd, structSize;
	char *fileName = "blockNode";

	fd = checkFileOpen(fileName);

	if(fd <= 0){
		createLinuxFile(fileName);
	}

	fd = open(fileName, O_RDWR);

	structSize = sizeof(BlockNode);

	write(fd, thisBlock, structSize);
	close(fd);

	return 1;

}


int writeFileNodeListToFile(FileNode **fileNodeList){

	return 1;
}


int writeBlockNodeListToFile(BlockNode **blockNodeList){

	return 1;
}
//###### writeAPI END ######

//###### readAPI ######
int readUserInfoFromFile(){
	int fd, structSize;
	char *fileName = "userInfo";
	UserInfo *thisUser;
	thisUser = (UserInfo*)calloc(1, sizeof(UserInfo));

	fd = checkFileOpen(fileName);

	if(fd<=0){
		return -1;
	}
	fd = openLinuxFile(fileName);

	structSize = sizeof(UserInfo);
	read(fd, thisUser, structSize+1);

	printUserInfo(thisUser);
	close(fd);

	return 1;
}


int readFileNodeFromFile(){
	int fd, structSize;
	char *fileName = "fileNode";
	FileNode* thisFileNode;
	thisFileNode = (FileNode*)calloc(1, sizeof(FileNode));


	fd = checkFileOpen(fileName);

	if(fd<=0){
		return -1;
	}
	fd = openLinuxFile(fileName);

	structSize = sizeof(FileNode);
	read(fd, thisFileNode, structSize);
	close(fd);
	printFileNode(thisFileNode);


	return 1;
}

int readBlockNodeFromFile(){
	int fd, structSize;
	char *fileName = "blockNode";
	BlockNode* thisBlockNode;
	thisBlockNode = (BlockNode*)calloc(1, sizeof(BlockNode));


	fd = checkFileOpen(fileName);

	if(fd<=0){
		return -1;
	}
	fd = openLinuxFile(fileName);

	structSize = sizeof(BlockNode);
	read(fd, thisBlockNode, structSize);
	close(fd);

	printBlockNode(thisBlockNode);

	return 1;
}

//###### read API END ######

//
//
//int main(){
//
//	UserInfo* newUser;
//	FileNode* newFileNode;
//	BlockNode* newBlockNode;
//	FileController* fileController;
//
//	initFileController(&fileController);
//
//
//	initUserInfo(&newUser,"pp","ww");
//	initFileNode(&newFileNode, "newFile");
//	initBlockNode(&newBlockNode,newFileNode);
//
//	newBlockNode->thisBlock = getBlockInfo(fileController);
//	sprintf(newBlockNode->physical_file_name , "%s",newBlockNode->file->file_name);
//	newBlockNode->physical_block_index = newBlockNode->thisBlock->block_index;
//
//
//	printUserInfo(newUser);
//	printFileNode(newFileNode);
//	printBlockNode(newBlockNode);
//
//	printf("##############################\n");
//
//	writeUserInfoToFile(newUser);
//	writeFileNodeToFile(newFileNode);
//	writeBlockNodeToFile(newBlockNode);
//
//	readUserInfoFromFile();
//	printf("------------------------------------\n");
//	readFileNodeFromFile();
//	printf("------------------------------------\n");
//	readBlockNodeFromFile();
//
//	return 0;
//}

