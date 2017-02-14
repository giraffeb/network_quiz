//
//#include "data_structure_io.h"
//
//int main(){
//
//	FileInfo *newFile;
//	BlockInfo *newBlock;
//
//	char *fileName = "./newfile2.txt";
//
//  initFileInfo(&newFile, fileName);
//	printf("FileInfo\n");
//	printf("%s\n",newFile->file_name);
//	printf("%d\n", newFile->fd);
//	printf("%d\n", newFile->number_of_block);
//	printf("%s\n", newFile->create_time);
//ㅁ	printf("%s\n", newFile->update_time);
//
//
//	initBlockInfo(&newBlock, newFile);
//	printf("BlockInfo\n");
//	printf("%s\n",newBlock->file->file_name);
//	printf("%d\n", newBlock->block_id);
//	printf("%s\n", newBlock->create_time);
//	printf("%s\n", newBlock->update_time);
//
//	//블록 하나의 크기를 정하고, 가득찰때까지 기록하는걸 만들기
//	//여러 블록만들기
//	//파일 하나를 벗어나는 것 만들기.
//
//	return 0;
//}
//
///*
// * 블록단위로 구조체 만들기
// * >만드는 자료구조의 순서가 어떻게 되야 할까?
// * >>실제 파일 -> 자료구조 -> 초기화?
// *
// * 블록단위로 쓰기해보기
// *
// * */
//
