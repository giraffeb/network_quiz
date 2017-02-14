#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <unistd.h>

#include <string.h>
#include <stdbool.h>

#include <time.h>


//set
#define bufferSize 256
#define blockSize 256


//make sth
//
int createLinuxFile(char *fileName);
int openLinuxFile(char* fileName);
//bool checkAvailableBlockOnLinuxFile(char* fileName);
int writeBlockOnLinuxFile(char* fileName, int blockNumber, char* buffer);
int readBlockOnLinuxFile(char* fileName, int blockNumber, char* buffer);
int countBlockSizeOnLinuxFile(char* fileName, int blockNumber);
