#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <unistd.h>

#include <string.h>
#include <stdbool.h>

#include <time.h>

#include "linux_file_test.h"
#include "data_structure_io.h"


int writeUserInfoToFile(UserInfo* thisUser);
int writeFileNodeToFile(FileNode *thisFile);

int writeBlockNodeToFile(BlockNode *thisBlock);
int writeFileNodeListToFile(FileNode **fileNodeList);
int writeBlockNodeListToFile(BlockNode **blockNodeList);
//###### writeAPI END ######

//###### readAPI ######
int readUserInfoFromFile();
int readFileNodeFromFile();
int readBlockNodeFromFile();

//###### read API END ######
