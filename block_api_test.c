//#include <stdio.h>
//#include <stdlib.h>
//
//#include <fcntl.h>
//#include <unistd.h>
//
//#include <string.h>
//#include <stdbool.h>
//
//#include <time.h>
//
//#include "linux_file_test.h"
//#include "data_structure_io.h"
//#include "record_io.h"
//
///*
// * TODO : 현재 작업 영역입니다.
// *  BlockLevel API를 작성 중입니다.
// * */
//int main(){
//	FileInfo *newFile;
//	BlockInfo *newBlock;
//
//	char readBuffer[blockSize];
//	char writeBuffer[blockSize];
//
//	initFileInfo(&newFile, "01");
//	addBlockInfoOnFileInfo(newFile);
//	addBlockInfoOnFileInfo(newFile);
//
//
//	memset(writeBuffer, 0, bufferSize);
//	memset(readBuffer, 0, bufferSize);
//
//	sprintf(writeBuffer, "%s", "NEWTHING!@@@@@");
//
//	printf("newFileName : %s\n", newFile->file_name);
//	printf("newFile block id : %d\n", newFile->blocks[0]->block_id);
//
//	writeBlock(newFile->blocks[0], writeBuffer);
//	writeBlock(newFile->blocks[1], writeBuffer);
//
//	printf("0: %d\n", newFile->blocks[0]->end_point_in_block);
//	printf("1: %d\n", newFile->blocks[1]->end_point_in_block);
//
//	//writeBlockOnLinuxFile(newFile->file_name, 0, writeBuffer);
//	//readBlockOnLinuxFile(newFile->file_name, 0, readBuffer);
//	readFile(newFile);
//
//
//
//	return 0;
//}
//
