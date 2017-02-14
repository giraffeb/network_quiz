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
//
////set
//#define bufferSize 256
//#define blockSize 256
//
//
////make sth
////
//int createLinuxFile(char *fileName);
//int openLinuxFile(char* fileName);
//int writeBlockOnLinuxFile(char* fileName, int blockNumber, char* buffer);
//int readBlockOnLinuxFile(char* fileName, int blockNumber, char* buffer);

#include "linux_file_test.h"

/*
 	 * 파일 생성이 성공하면 파일 디스크립터를 반환한다.
	 *
	 * 유저명은 유니크하다.
	 * 유저별로 유니크한 디렉토리를 가진다.
	 * 파일은 유저별로 유니크하게 가진다.
	 * 파일은 디렉토리에 속한다.
	 *
	 * */
int createLinuxFile(char *fileName){

	int fd = -1;

	//파일 디스크립터 얻기
	fd = open(fileName, O_CREAT | O_RDWR | O_APPEND , 0644);
	if( fd < 0){
		printf("file create error\n");
		return fd;
	}
	close(fd);

	//생성되었다는 것만 체크
	return fd;
}


int openLinuxFile(char* fileName){

	int fd;

	fd = open(fileName, O_RDWR);
		if( fd < 0){
			printf("file open error\n");
			return fd;
		}

		return fd;
}

//
//bool checkAvailableBlockOnLinuxFile(char* fileName){
//
//
//
//	return true;
//}


int writeBlockOnLinuxFile(char* fileName, int blockNumber, char* buffer){
	int writeAmount=0;
	int fd;

	fd = openLinuxFile(fileName);
	if(fd <= 0 ){
		return -1;
	}

	printf("##fileName : %s\n", fileName);
	lseek(fd, blockNumber * blockSize ,SEEK_SET);

	writeAmount = write(fd, buffer, bufferSize-1);
	if( writeAmount < 0 ){
		printf("write error \n");
		return writeAmount;
	}

	if( fsync(fd) == -1){
		printf("fsync error\n");
	}

	printf("write amount : %d\n", writeAmount);
	close(fd);
	return writeAmount;
}


//block 구분을 위해서는 시작의 offset 값이 필요하겠습니다.
int readBlockOnLinuxFile(char* fileName, int blockNumber, char* buffer){
	int readAmount=1;
	int totalReadAmount=0;
	int fd;
//	char buffer[bufferSize];

	fd = openLinuxFile(fileName);
	if(fd <= 0 ){
		return -1;
	}

	//bufferSize == blockSize
	lseek(fd, blockSize * blockNumber, SEEK_SET);
	memset(buffer, 0, bufferSize);
	readAmount = read(fd, buffer, bufferSize);
	printf("%s\n",buffer);
	if(readAmount < 0){
		printf("read error\n");
		return -1;
	}
	close(fd);

	totalReadAmount += readAmount;

	return totalReadAmount;
}


int printBlock(char* fileName, int blockNumber){

	int fd;
	fd = openLinuxFile(fileName);
	if( fd < 0 ){
		return -1;
	}

	return 1;
}

//어차피 블록단위로 파일 사이즈가 결정될텐데 카운트할 필요가 있나? 싶다.
int countBlockSizeOnLinuxFile(char* fileName, int blockNumber){
return -1;
}


/*
 * Linux File
 * 1) create
 * 2) read
 * 3) write
 *
 *
 * */
//int main(){
//
//	char *fileName = "test1.txt";
//	char buffer[bufferSize];
//
//	int thisFd;
//	int writeAmount;
//	int readAmount;
//
//	memset(buffer,0,bufferSize);
//	sprintf(buffer, "%s","Hello new World");
////	printf("%s\n",buffer);
//
//	thisFd = createLinuxFile(fileName);
//	printf("fd -> %d\n", thisFd);
//
//
//	writeAmount = writeBlockOnLinuxFile(fileName, 1, buffer);
//	printf("write -> %d\n", writeAmount);
//
//
//	memset(buffer, 0, bufferSize);
//	readAmount = readBlockOnLinuxFile(fileName, 1, buffer);
//	printf("read -> %d\n",readAmount);
//	printf("readAmount -> %d\n",readAmount);
//	printf("%s\n", buffer);
//
//
//	close(thisFd);
//	return 0;
//}


