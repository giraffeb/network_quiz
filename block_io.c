// STATE : 사용되지 않는 파일입니다.
//#pragma once
//#include "block_io.h"
//
//
///*TODO : 아래의 내용처럼 변경해야 합니다.
// * 잠깐만 유저 정보는 레벨을 분리해야겠는데,
// *
// * 실제 리눅스를 만들 수 있는지 여부()
// * 유저가 최대파일개수르 넘지 않았는지 확인()
// *
// * 위의에러처리
// *
// * 포괄하는 createUserFile()로 감싸야겠다.
// * */
//int createLinuxFile(UserInfo* thisUser){
//	//파라미터 널 체크
//	if(thisUser == NULL){
//		printf("UserInfo is NULL\n");
//		return -1;
//	}
//
//
//	//리눅스 파일 생성 시작
//	int newFileIndex;
//	int fd;
//
//
//	if( thisUser->last_file_index >= maxUserFileSize ){
//		printf("exceed maxUserFileSize\n");
//		return -1;
//	}
//
//
//	newFileIndex = thisUser->last_file_index + 1;
//
//	char fileName[maxFileNameLength];
//	memset(fileName, 0, sizeof(fileName));
//	/*파라미터
//		1) 변환할 정수변수
//		2) 정수-> 문자열로 변환된 저장공간
//		3) 진수
//	*/
//
//	sprintf(fileName,"%d", newFileIndex);
//	fd = open(fileName, O_CREAT, 0644);
//
//	//파일생성 에러시
//	if(fd < 0){
//		printf("file create error\n");
//		return -1;
//	}
//
//	//파일 생성을 성공했다면 파일디스크립터 넘버를 넘기자.
//	return fd;
//}
//
//
