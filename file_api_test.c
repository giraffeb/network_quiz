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
//
//
//
//int main(){
//
//	FileNode *newFile;
//	BlockNode *newBlock;
//	UserInfo *newUser;
//
//	char idBuffer[256];
//	char pwBuffer[256];
//
//	initFileNode(&newFile, "02");
//	//dataStructure들을 체크하려면  printObject 형태가 필요하겠다.
//
//	printFileNode(newFile);
//
//	printf("########################################\n");
//
//	initBlockNode(&newBlock, newFile);
//
//	printBlockNode(newBlock);
//
//
//	printf("### ### ### ### ### ###\n");
//	printf("maybe interface part\n");
//	memset(idBuffer, 0, sizeof(idBuffer));
//	memset(pwBuffer, 0, sizeof(pwBuffer));
//
//
//	printf("INPUT YOUR ID : ");
//	fgets(idBuffer, sizeof(idBuffer), stdin);
//
//	printf("INPUT YOUR PW : ");
//	fgets(pwBuffer, sizeof(pwBuffer), stdin);
//
//	initUserInfo(&newUser, idBuffer, pwBuffer);
//	printUserInfo(newUser);
//
//	return 0;
//}
