#include "data_structure_io.h"


//###### common function ######
/*
 * 파일과 블록의 생성시간, 수정시간을 기록하기 위한 시간 값을 기록한다.
 * 해당 블록이나 파일 구조체의 문자열 멤버변수에 값을 기록한다.
 * 예) 20170107 16:24:02
 *
 * */
void timeStamp(char* stamp){

	time_t timer;
	struct tm *t;

	timer = time(NULL);

	t = localtime(&timer);

	memset(stamp, 0, sizeof(stamp));
	//printf("this point\n");
	sprintf(stamp, "%04d%02d%02d %02d:%02d:%02d", t->tm_year+1900, t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);

}

//곧 사라질 아이로 생각됨.
int checkFileOpen(char *fileName){

	int fd;

	fd = open(fileName, O_RDWR );


	//fd < 0 file not exist
	if(fd < 0 ){
		printf("file not exist\n");
	}


	return fd;
}
//###### common function END ######



//######BLOCK INFO API #########

/*
 * physical file = FileInfo에 소속된 블록을 초기화한다.
 * 초기화되는 블록은 소속된 파일의 이름을 복사해사 가지고,
 * 파일이 가진 블록 수에 맞춰서 block_id를 가진다.
 *
 * */
int initBlockInfo(BlockInfo **newBlock, FileInfo *thisFile){

	(*newBlock) = (BlockInfo*)calloc(1, sizeof(BlockInfo));

	(*newBlock)->file = thisFile;
	(*newBlock)->block_index = 0; //초기화 이후에 파일아래 상대적인 번호 부여 받아야함.

	(*newBlock)->start_point_in_block = blockSize * (*newBlock)->block_index;
	(*newBlock)->end_point_in_block = blockSize * (*newBlock)->block_index;

	timeStamp( (*newBlock)->create_time);
	sprintf( (*newBlock)->update_time,"%s", (*newBlock)->create_time);

	return 1;
}


// DEPRECATED: 안써요

int updateTimeOnBlockInfo(BlockInfo* block){
	if(block == NULL){
		return -1;
	}

	timeStamp(block->update_time);

	return 1;
}


int removeBlockInfo(BlockInfo *thisBlock){
	if(thisBlock == NULL){
		return -1;
	}

	free(thisBlock);

	return 1;
}


//DEPRECATED : 아직 활용 방안을 모릅니다.
int checkLimitBlockSize(BlockInfo *thisBlockd){
	int count;


	return 1;
}



int readBlock(BlockInfo* thisBlock, char* buffer){

	return readBlockOnLinuxFile(thisBlock->file->file_name, thisBlock->block_index, buffer);
};



int writeBlock(BlockInfo* thisBlock, char* buffer){
	int writeAmount;

	//BlockInfo print
	//	printf("**block_index : %d\n", thisBlock->block_index);
	//	printf("**write buffer : %s\n", buffer );
	//

	writeAmount = writeBlockOnLinuxFile(thisBlock->file->file_name
			, thisBlock->block_index
			, buffer);
	thisBlock->end_point_in_block = thisBlock->start_point_in_block + writeAmount;
	/*매번 블록의 크기와 같은 양을 덮어쓴다고 정했으므로,
		start_point_in_block + writeAmount가
		end_point_in_block이 된다.
		Append해서 작성하는 형태가 아니기 때문에 이렇다.

	*/

	return writeAmount;
};



/*
 *
typedef struct physical_block_info{

	struct physical_file_info *file; // 현재 이 물리 블록 정보가 소속되 있는 물리 파일을 가리키는 포인터가 필요하다 고 생각함.
	//char file_name[fileNameLength]; //위 포인터를 못쓸때 필요했던 거고, 이제는 필요가 없어요 ㅎㅎㅎㅎㅎ

	int block_index;
	int start_point_in_block;//블록의 시작지점
	int end_point_in_block;//블록의 끝지점

	char create_time[timeStampLength];
	char update_time[timeStampLength];

}BlockInfo;
 * */
int printBlockInfo(BlockInfo* thisBlock){

	printf("block_index : %d\n", thisBlock->block_index);
	printf("start_point_in_block : %d\n", thisBlock->start_point_in_block);
	printf("end_point_in_block : %d\n", thisBlock->end_point_in_block);

	printf("create_time : %s\n", thisBlock->create_time);
	printf("update_time : %s\n", thisBlock->update_time);


	return 0;
}



//######BLOCKINFO API END ######




//###### FILEINFO API ######

int initFileInfo(FileInfo **newFile, char* fileName){

	int fd;

	(*newFile) = (FileInfo*)calloc(1, sizeof(FileInfo));
	fd = checkFileOpen(fileName);

	if( fd < 0){
			printf("file not exist. make file :D\n ");
			createLinuxFile(fileName);
	}

	sprintf((*newFile)->file_name,"%s", fileName);
	(*newFile)->current_file_size = 0;
	(*newFile)->last_block_index = -1;

	timeStamp( (*newFile)->create_time);
	sprintf( (*newFile)->update_time, "%s", (*newFile)->create_time );

	return 1;
}

//DEPRECATED : 안씁니다 아직은.
int updateTimeOnFileInfo(FileInfo *thisFile){
	if(thisFile == NULL ){
		return -1;
	}

	timeStamp( thisFile->update_time);

return 1;
}


int removeFileInfo(FileInfo *thisFile){
	if(thisFile == NULL){
		return -1;
	}

	free(thisFile);

	return 1;
}


//DEPRECATED : 파일 단위로 읽을 필요가 없습니다.
int readFile(FileInfo* thisFile){
	int readAmount = 0;
	int blockIndex;
	char* buffer[bufferSize];

	for(blockIndex =0; blockIndex <= thisFile->last_block_index; blockIndex++){
		readAmount += readBlockOnLinuxFile(thisFile->file_name
																						, thisFile->blocks[blockIndex]
																						,buffer);
	}

	return readAmount;
}


//FIXME : 플로우를 확인해야합니다.
//FileCotroller에서 받아오는 형태로 변경했습니다.
int addBlockInfoOnFileInfo(FileInfo* thisFile, BlockInfo* newBlockInfo){

	int blockId;

	//file pointer 널 체크
	if(thisFile == NULL){
		printf("fileInfo null pointer error\n");
		return -1;
	}

	//FileInfo 최대 블록 수 체크
	if( thisFile->last_block_index+1 >= maxBlocksInFile ){
		printf("file can't have more blocks\n");
		return -1;
	}


	blockId = ++thisFile->last_block_index;
	newBlockInfo->block_index = blockId;
	newBlockInfo->start_point_in_block = blockId * blockSize;
	newBlockInfo->end_point_in_block = blockId * blockSize;

	thisFile->blocks[thisFile->last_block_index] = newBlockInfo;


	return 1;
}
//###### FILEINFO API END ######





//###### BLOCKNODE API ######
int initBlockNode(BlockNode **blockNode, FileNode *thisFile){

	(*blockNode) = (BlockNode*)calloc(1, sizeof(BlockNode));

	(*blockNode)->file = thisFile;
	(*blockNode)->logical_block_index = -1; //유저가 가진 파일별로 유니크하게 할당 되어야 합니다.

	sprintf((*blockNode)->physical_file_name, "%s", "");
	(*blockNode)->physical_block_index= -1;

	(*blockNode)->thisBlock = NULL;
	//(*blockNode)->next = NULL;
	timeStamp((*blockNode)->create_time);
	sprintf((*blockNode)->update_time,"%s", (*blockNode)->create_time);

	return 1;
}


int updateTimeOnBlockNode(BlockNode *blockNode){
	if(blockNode == NULL){
		return -1;
	}

	timeStamp(blockNode->update_time);

	return 1;
}


int removeBlockNode(BlockNode *blockNode){

	if(blockNode == NULL){
		return -1;
	}

	free(blockNode);

	return 1;
}

/*
 * typedef struct logical_block_info{


	struct logical_file_info *file;

	int logical_block_index;
	struct physical_block_info* thisBlock;

	struct logical_block_info* next;

	char create_time[timeStampLength];
	char update_time[timeStampLength];


}BlockNode;
 * */
int printBlockNode(BlockNode *thisBlock){

	char *flag;

	if(thisBlock->file == NULL){
		flag = "NULL";
	}else{
		flag = "NOT NULL";
	}
	printf("logical_file_info : %s\n", flag);
	printf("logical_block_index : %d\n", thisBlock->logical_block_index);

	if(thisBlock->thisBlock == NULL){
		flag = "NULL";
	}else{
		flag = "NOT NULL";
	}
	printf("physical_block_info : %s\n", flag);

	if(thisBlock->next== NULL){
		flag = "NULL";
	}else{
		flag = "NOT NULL";
	}
	printf("logical_block_index : %s\n", flag);

	printf("physical_fileName : %s \n", thisBlock->physical_file_name);
	printf("physical_block_index : %d \n", thisBlock->physical_block_index);

	printf("create_time : %s\n", thisBlock->create_time);
	printf("update_time : %s\n", thisBlock->update_time);

	return 0;
}

//######BLOCKNODE API END ######






//###### FILENODE API ######

int initFileNode(FileNode **fileNode, char* fileName){

	(*fileNode) = (FileNode*)calloc(1, sizeof(FileNode));

	(*fileNode)->last_block_index = -1;
	(*fileNode)->logicla_file_index = 0;
	sprintf((*fileNode)->file_name, "%s", fileName);

	memset((*fileNode)->block_list, 0, sizeof(FileNode)* maxBlocksInFile);

	timeStamp((*fileNode)->create_time);
	sprintf((*fileNode)->update_time,"%s", (*fileNode)->create_time);


	return 1;
}


int updateTimeOnFileNode(FileNode *fileNode){
	if(fileNode == NULL){
		return -1;
	}

	timeStamp(fileNode->update_time);

	return 1;
}


int removeFileNode(FileNode *fileNode){
	if(fileNode == NULL){
		return -1;
	}

	free(fileNode);

	return 1;
}


/*
 *
 *

typedef struct logical_file_info{

	int logicla_file_index;
	char file_name[fileNameLength];

	struct logical_block_info* head;
	struct logical_block_info* tail;


	char create_time[timeStampLength];
	char update_time[timeStampLength];

}FileNode;
 *
 * */

int printFileNode(FileNode *thisFile){

	char *flag;

	printf("logical_file_index : %d\n",thisFile->logicla_file_index);
	printf("file_name : %s\n", thisFile->file_name);

	printf("create_time : %s\n", thisFile->create_time);
	printf("update_time : %s\n", thisFile->update_time);

	return 0;
}
//###### FILENODE API END ######



//###### USERINFO API ######

int initUserInfo(UserInfo **newUserInfo, char* id, char* pw){

	(*newUserInfo) = (UserInfo*) calloc(1, sizeof(UserInfo));

	(*newUserInfo)->last_file_index = -1;

	/*
	 * client에서 받아서 넘겨야 겠지.
	 * */
	sprintf((*newUserInfo)->user_id, "%s", id );
	sprintf((*newUserInfo)->user_pw, "%s", pw);

	return 0;
}

/*
 *
 * typedef struct user_info{

	char user_id[userIdLength];
	char user_pw[userPwLength];

	FileNode file_list[maxUserFileSize];
	int last_file_index;

}UserInfo;
 * */
int printUserInfo(UserInfo *thisUserInfo){

	char *flag;

	printf("user_id : %s\n", thisUserInfo->user_id );
	printf("user_pw : %s\n", thisUserInfo->user_pw );

	printf("last_file_index : %d\n", thisUserInfo->last_file_index );

	if(thisUserInfo->file_list[0] == NULL){
		flag = "NULL";
	}else{
		flag = "NOT NULL";
	}
	printf("file_list is %s\n", flag);


	return 0;
}

/*
 * TODO : 파일 생성시의 로직 생각 정리.
 * 작석중
 * 파일 생성시의 로직을 생각하면서 완성해보자.
 *
 * 파일 생성시
 * 상황,
 * 목적,
 * 블록 생성과의 관계.
 *
 *
 * PhysicalFile과 LogicalFile의 관리가 독립적으로 될 수 있을까?
 * 마치 데이터 베이스 처럼.
 * 누가 logicalFile 관리에 대한 책임을 질 수 있지?
 *
 *
 * #로직을 생각해보자.
 * 1)LocalFileController가 물리적인 파일을 관리한다.
 *  2) 로직컬 파일에서 블록을 요청 하면 넘겨준다.
 *  3) 이걸 프로그램이 종료시에도 파일러 정보를 기록하고 있어서,
 *  재 기동시에도 사용가능해야 한다.
 *  4) 서버와의 동기화에 이 파일이 사용될 것으로 판단된다.
 *  5) struct serialize 를 어떻게 해서 파일에 저장해야 하는지도 모릅니다.
 *
 *
 * */
int addLogicalFile(UserInfo *thisUser, char* userFileName){

	FileNode *newFileNode;
	char fileInfoName[fileNameLength];


	if(thisUser == NULL){
		printf("thisUser is NULL pointer error\n");
		return -1;
	}

	if(thisUser->last_file_index+1 >= maxBlocksInFile){
		printf("Can't make more block in This File\n");
		return -1;
	}

	/*
	 *  FileNode에서의 파일이름은 사용자가 지정하는 이름이다.
	 * */

	initFileNode(&newFileNode, userFileName);
	thisUser->last_file_index++;
	thisUser->file_list[thisUser->last_file_index] = newFileNode;
//
//	memset(fileInfoName, 0, sizeof(fileInfoName));
//	sprintf(fileInfoName, "%d", thisUser->last_file_index);
//


	return 0;
}

/*TODO : copyFileToUserFile(): 작성 중.
 1) 코드의 가독성 개선
 2) 하나의 논리 파일은, 다수의 물리파일로 구성될 수 있다.

 복사가능한 파일 크기를 제한하는 방법으로 구현
 차후 방향
 논리파일이 가질수 있는 블록의 개수제한을 늘림,
 물리파일과 논리 파일의 블록 제한 수가 다름.

 하나의 논리 파일을 다수의 물리파일 블록으로 구현가능한 형태로.


 */
int copyFileToUserFile(UserInfo *thisUser, FileController* fileController, char *filePath){


	int flag;
	//filePath : 복사 대상 파일이 존재하는지 확인함
	flag = checkFileOpen(filePath);

	if(flag <= 0 ){
        printf(":%s:\n",filePath);
		printf("%d copy target file not exist\n", flag);
		return -1;
	}


	char readBuffer[blockSize]; //한번에 읽을 사이즈 == blockSize

	int fd;
	int readAmount=0, totalReadAmount=0; //복사 대상 파일로부터 읽은 문자수 확인함.

	int newBlockNodeIndex; //논리 블록 단위 생성

	//filePath는 복사대상의 파일이름임 : 똑같이 만든다 치고, 전체 파일path를 잘라내던지 해야함.
	//지금은 같은 디렉토리에 있는 것만 가능한 구조임
	addLogicalFile(thisUser, filePath); //사용자가 지정한 파일명으로 논리 파일 생성.
	//사용자 파일리스트에 추가됨

	FileNode* newFileNode = thisUser->file_list[thisUser->last_file_index];
	BlockNode* newBlockNode;
	BlockInfo* newBlockInfo;


	//복사대상 파일을 엽니다.
	fd = openLinuxFile(filePath);
	int fileSize = lseek(fd,0,SEEK_END);
	printf("fileSize : %d\n",fileSize);
	printf("maxFileSize : %d\n", blockSize * maxBlocksInFile);
	if(fileSize > blockSize * maxBlocksInFile){
		printf("%d : 복사 가능 파일 크기를 넘었습니다.", fileSize);
		return -1;
	}
	lseek(fd,0,SEEK_SET);//file cursor initialize.


	while(1){

		memset(readBuffer, 0, blockSize); //readBuffer 초기화
		readAmount = read(fd,readBuffer, blockSize-1); // --1은 null character 공간

		printf("**readAmount : %d \n", readAmount);
		//printf("%s\n", readBuffer);

		//while문 중단 조건
		if(readAmount <= 0){
			break;
		}

		newBlockNodeIndex = ++(newFileNode->last_block_index);
		newBlockInfo = getBlockInfo(fileController);
		//printBlockInfo(newBlockInfo);
		//파일이 가질 수 있는 최대블록 개수 보다 작을때 수행.
		//크면?  새로 만들어야 되는데 이건 물리적인 내용일때 해야하고
		//omg
		//편하게 처리하는 방법은??
		//복사할 수 있는 파일의 크기를 제한하면 편하다.

		if(newBlockNodeIndex < maxBlocksInFile){
			//printf("callw\n");
			writeBlock(newBlockInfo, readBuffer);
			//fileNode는 BlockNode 리스트를 갖습니다.
			//BlockInfo -> BlockNode로 적절히 변환해서 넣어야 하죠.
			initBlockNode(&newBlockNode, newFileNode);
			newBlockNode->thisBlock = newBlockInfo;
			memset(newBlockNode->physical_file_name, 0, fileNameLength);
			sprintf(newBlockNode->physical_file_name, "%s", newBlockInfo->file->file_name);
			newBlockNode->physical_block_index = newBlockInfo->block_index;

			newBlockNode->logical_block_index =  newBlockNodeIndex;

			newFileNode->block_list[newBlockNodeIndex] = newBlockNode;


		}
		printf("loop\n");
		//printBlockInfo(newBlockNode->thisBlock);
	}
	close(fd);
	return 1;
}

//###### USERINFO API END ######



//###### FILECONTROLLER API ######
//typedef struct phyisical_file_controller{
//
//	//물리파일의 생성 크기는 차후 변경할 수 있습니다.
//	//이 개수로 인해서 최대개수의 논리적인 파일의 생성에 제한이 있을 수 있습니다.
//	FileInfo *file_list[maxUserFileSize];
//	int last_file_index;
//
//}FileContoller;

int initFileController(FileController **newFileController){

	(*newFileController) = (FileController*) calloc(1, sizeof(FileController));
	memset((*newFileController)->file_list , 0 , sizeof(FileInfo)*maxUserFileSize);

	//-1은 아직 물리 파일이 없다는 것을 의미합니다.
	(*newFileController)->last_file_index = -1;

	return 1;
}

bool checkAvailableBlockInLinuxFile(FileInfo* thisFile){

	//printf("filename : %s\n", thisFile->file_name);

	if(thisFile == NULL){
		return false;
	}
	else if( thisFile->last_block_index+1 >= maxBlocksInFile ){
		return false;
	}

	return true;
}


BlockInfo* getBlockInfo(FileController *thisFileController){

	bool flag;
	FileInfo *lastFileInfo;
	BlockInfo *newBlockInfo;
	int fileIndex, blockIndex;

	fileIndex = thisFileController->last_file_index;


	printf("call getBlockInfo\n");
	//fileIndex가 -1인 경우는 물리파일이 존재 하지 않을때임.
	// >=0 이라면 파일이 존재함.
	if(fileIndex >= 0){
		printf("file exist\n");
		lastFileInfo = thisFileController->file_list[fileIndex];

        flag = checkAvailableBlockInLinuxFile(lastFileInfo);
	}else{
		printf("file not exist\n");
		flag = false;
	}

	if(flag == false){
		//CREATE LINUX FILE
		printf("call false\n");

		if(thisFileController->last_file_index+1 >= maxUserFileSize ){
			printf("limit number of files\n");
			return NULL;
		}


		char fileName[bufferSize];
		FileInfo *newFileInfo;


		fileIndex = ++(thisFileController->last_file_index);

		sprintf(fileName, "%d", fileIndex);

		printf("physical File name : %s\n", fileName);

		createLinuxFile(fileName);
		initFileInfo(&newFileInfo, fileName);
		thisFileController->file_list[fileIndex] = newFileInfo;
		//file_list에 새로운 fileNode 넣기 완료


		//새 BlockInfo 생성
		initBlockInfo(&newBlockInfo, newFileInfo);
		newBlockInfo->block_index = ++(newFileInfo->last_block_index);

		//처음이니깐
		newFileInfo->blocks[0] = newBlockInfo;


	}else{

		printf("call true\n");

		initBlockInfo(&newBlockInfo, lastFileInfo);
		blockIndex = ++(lastFileInfo->last_block_index);
		newBlockInfo->block_index = blockIndex;


		lastFileInfo->blocks[blockIndex] = newBlockInfo;

	}
	//FLASE : createNewFileInfo();
	//and createNewBlockInfo();
	//return Block주소.


	return newBlockInfo;
}



//###### FILECONTROLLER API END ######

