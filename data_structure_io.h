#ifndef 	DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

#include "data_structure_types.h"
#include "linux_file_test.h"


void timeStamp(char* stamp);
int checkFileOpen(char* fileName);


int initBlockInfo(BlockInfo **newBlock, FileInfo *thisFile);
int updateTimeOnBlockInfo(BlockInfo *thisBlock);
int removeBlockInfo(BlockInfo *thisBlock);
int checkLimitBlockSize(BlockInfo *thisBlock);
int readBlock(BlockInfo* thisBlock, char* buffer);
int writeBlock(BlockInfo* thisBlock, char* buffer);



int initFileInfo(FileInfo **newFile, char* fileName);
int updateTimeOnFileInfo(FileInfo *thisFile);
int removeFileInfo(FileInfo *thisFile);
int readFile(FileInfo* thisFile);
int addBlockInfoOnFileInfo(FileInfo* thisFile, BlockInfo* newBlockInfo);


int initBlockNode(BlockNode **blockNode, FileNode *thisFile);
int updateTimeOnBlockNode(BlockNode *blockNode);
int removeBlockNode(BlockNode *blockNode);
int printBlockNode(BlockNode *thisBlock);


int initFileNode(FileNode **fileNode, char* fileName);
int updateTimeOnFileNode(FileNode *fileNode);
int removeFileNode(FileNode *fileNode);
int printFileNode(FileNode *thisFile);



int initUserInfo(UserInfo **newUserInfo, char* id, char* pw);
int printUserInfo(UserInfo *thisUserInfo);
int addLogicalFile(UserInfo *thisUser, char *userFileName);
int copyFileToUserFile(UserInfo *thisUser, FileController *fileController , char *filePath);


int initFileController(FileController **newFileController);
BlockInfo* getBlockInfo(FileController *thisFileController);
bool checkAvailableBlockInLinuxFile(FileInfo *thisFile);


#endif
