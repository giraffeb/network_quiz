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
//typedef struct person{
//
//	int number;
//	char name[256];
//	int age;
//
//
//}Person;
//
//
//void initPerson(Person** this){
//	(*this) = (Person*)calloc(1, sizeof(Person));
//	(*this)->number = 256;
//	(*this)->age = 257;
//	sprintf((*this)->name, "%s", "mynameis");
//}
//
//
//
///*
// * DEPRECATED : struct io test완료함 :D
// *
// * */
//int main(){
//
//	Person* new;
//	initPerson(&new);
//
//	int fd;
//
//	printf("size : %d\n", sizeof(Person));
//
//	printf("number %d\n", new->number);
//	printf("age %d\n", new->age);
//	printf("name %s\n", new->name);
//
//	fd = open("111",O_CREAT | O_RDWR, 0644);
//	write(fd, new, sizeof(Person));
//	close(fd);
//
//	FILE *fp;
//
//	fp = fopen("222","w");
//	fwrite(&new, sizeof(Person), 1, fp);
//	fclose(fp);
//
//	int fd2;
//
//	fd2 = open("111", O_RDWR);
//	read(fd2, new, sizeof(Person));
//	close(fd2);
//
//
//	printf("number %d\n", new->number);
//	printf("name %s\n", new->name);
//	printf("age %d\n", new->age);
//
//
//
//
//	return 0;
//}
