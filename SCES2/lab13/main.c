//LAB-13 SCE-Campus Ashdod//
//FILES//
//Author: Anthony Eitan Fleysher//
//ID: 203192331// 


#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>


////EXERCISE1//
//
//#define SIZE 256
//
//int main() {
//	FILE *fp;
//	char filename[SIZE];
//	char buffer[SIZE];
//	char firstChar, secondChar;
//	int count1=0, count2=0,c;
//	puts("enter filename");
//	fgets(filename, SIZE, stdin);
//	filename[strlen(filename) - 1] = '\0';
//	fp=fopen(filename,"w+");
//	if (!fp)return EOF;
//	puts("enter a string");
//	scanf("%[^\n]", buffer);
//	for (int i = 0; buffer[i] != '\0';++i) {
//		if (buffer[i] >= 'A'&&buffer[i] <= 'Z')
//			buffer[i]+='a'-'A';
//	}
//	fprintf(fp,"%s", buffer);
//	fclose(fp);
//	fp = fopen(filename, "r");
//	puts("enter first char to search");
//	getchar();
//	scanf("%c", &firstChar);
//	getchar();
//	puts("enter second char to search");
//	scanf("%c", &secondChar);
//	while ((c = fgetc(fp)) != EOF) {
//		if (c == firstChar)
//			count1++;
//		else if (c == secondChar)
//			count2++;
//	}
//	if (count1 > count2)
//		printf("The char %c appears %d times", firstChar, count1);
//	else if (count2 > count1)
//		printf("The char %c appears %d times", secondChar, count2);
//	else
//		printf("the char you have entered wasn`t found in the string\n");
//	fclose(fp);
//	return 0;
//}

////EXERCISE2//
#define SIZE 30
typedef enum{FALSE,TRUE}Boolean;
typedef struct {
	int ID;
	char *name;
	char *tel;
}Student;

Student* alloc1D(int *);
void getStudent(FILE*,Student*, int);
void freeStr(Student*, int);
void printFromFile(FILE*);
void printByID(FILE*, int);

int main() {
	FILE *fp;
	Student *pStd=NULL;
	int size,i,ID;
	char filename[SIZE];
	puts("enter filename");
	fgets(filename, SIZE, stdin);
	filename[strlen(filename) - 1] = '\0';
	fp = fopen(filename, "w+");
	pStd=alloc1D(&size);
	fprintf(fp, "%-9s %-16s %s\n", "ID", "NAME", "TELEPHONE");
	for (i = 0; i < size; ++i)
		getStudent(fp,&pStd[i], i);
	fclose(fp);
	fp = fopen(filename, "r");
	printFromFile(fp);
	printf("enter ID you like to print\n");
	scanf("%d", &ID);
	printByID(fp,ID);
	freeStr(pStd, size);
	fclose(fp);
	return 0;
}
void printFromFile(FILE* fp) {
	char ch;
	printf("The contents of the file are:\n");
	while ((ch = fgetc(fp)) != EOF)
		printf("%c", ch);
	rewind(fp);

}
void printByID(FILE* fp, int ID) {
	int idCheck, len=0,check=ID;
	Boolean flag = FALSE;
	char c;
	while (check != 0) {
		check /= 10;
		len++;
	}
	for (c = getc(fp); c != '\n'; c = getc(fp)); //newline
	fscanf(fp, "%d", &idCheck);//search for number
	while (!feof(fp)&&flag==FALSE) {
		if(idCheck==ID) {
			fseek(fp,-len,SEEK_CUR); //return len of id
			for (c = getc(fp); c != '\n'; c = getc(fp)) { //print line
				printf("%c", c);
			}
			flag = TRUE; //exit
		}
		else {
			for (c = getc(fp); c != '\n'; c = getc(fp)); //newline
			fscanf(fp, "%d", &idCheck); //search for number
			if (feof(fp)) { //exit case if not found
				printf("ID not found\n");
				flag = TRUE;
			}
		}
	}
}

void freeStr(Student* p, int size) {
	int i;
	for (i = 0; i < size; ++i) {
		free((p)[i].name);
		free((p)[i].tel);
	}
	free(p);
}

Student* alloc1D(int *size) {
	Student *pStd = NULL;
	puts("enter number of students you would like to add");
	scanf("%d", size);
	pStd = (Student*)malloc(*size * sizeof(Student));
	if (!pStd)
		printf("error allocate struct!\n");
	return pStd;
}

void getStudent(FILE* fp,Student* p, int index) {
	char buffer[SIZE];
	printf("enter details for student %d\n", index + 1);
	printf("enter student ID:");
	scanf("%d", &p->ID);
	getchar();
	printf("enter student name:");
	scanf("%[^\n]", buffer);
	p->name = (char*)malloc(strlen(buffer) + 1);
	strcpy(p->name, buffer);
	getchar();
	printf("enter student telephone number:");
	scanf("%[^\n]", buffer);
	p->tel = (char*)malloc(strlen(buffer) + 1);
	strcpy(p->tel, buffer);
	fprintf(fp, "%d %s %s\n", p->ID,p->name,p->tel);
}