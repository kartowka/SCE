/*
Assignment: 5
Campus: SCE-Ashdod
Author: Anthony Eitan Fleysher, ID: 203192331
*/

//LIBRARY//
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//DEFINE COMMANDS//
#define buffer 20
#define MONTHLOW 1
#define MONTHHIGH 12
#define DAYHIGH 31
#define DAYLOW 1
#define YEARLOW 1900
typedef struct {
	int Day;
	int Month;
	int Year;
}DOB;

typedef struct {
	char *name;
	DOB date;
}Person;

typedef struct {
	char *departmentName;
	Person BossDepartment;
	int numOfWorkers;
	Person *workers;
}Department;

typedef struct {
	Person CEO;
	int numOfDepartment;
	Department *department;
}Company;

//FUNCTION DECLARATION//
void getPerson(Person*);
void getDOB(DOB*);
void getDepartment(Department*);
void getCompany(Company**);
void printPerson(Person *);
void freePerson(Person*);
void printCompany(Company*);
void printDepartment(Department*);
void printWorker(Person*);
void freeCompany(Company*);
void freeDepartment(Department*);
void freeWorker(Person*);

//MAIN//
int main() {
	Company *cmp = NULL;
	getCompany(&cmp);
	printCompany(cmp);
	freeCompany(cmp);
	return 0;
}
//FUNCTIONS//
void freeCompany(Company* cmp) {
	int i;
	for (i = 0; i < cmp->numOfDepartment; ++i) {
		freeDepartment(cmp->department + i);
	}
	free(cmp->department);
	free(cmp->CEO.name);
	free(cmp);
}
void freeWorker(Person* p) {
	free(p->name);
}
void freeDepartment(Department* dep) {
	int i;
	for (i = 0; i < dep->numOfWorkers; ++i)
		freeWorker(dep->workers + i);
	free(dep->BossDepartment.name);
	free(dep->departmentName);

}
void getCompany(Company** company) {
	int i;
	*company = (Company*)malloc(sizeof(Company));
	printf("--------------------------\n");
	printf("enter details: \n");
	printf("enter CEO name:\n");
	getPerson(&(*company)->CEO);
	printf("enter number of Departments:\n");
	scanf("%d", &(*company)->numOfDepartment);
	while ((getchar()) != '\n');
	(*company)->department = (Department*)malloc((*company)->numOfDepartment * sizeof(Department));
	for (i = 0; i < (*company)->numOfDepartment; ++i) {
		printf("enter department name:\n");
		getDepartment((*company)->department+i);
	}
}
void getDepartment(Department* dep) {
	int i;
	char str[buffer];
	scanf("%[^\n]", str);
	while ((getchar()) != '\n');
	dep->departmentName = (char*)malloc(strlen(str) + 1);
	strcpy(dep->departmentName, str);
	printf("enter Boss Department name: \n");
	getPerson(&dep->BossDepartment);
	printf("enter number of workers: \n");
	scanf("%d", &dep->numOfWorkers);
	while ((getchar()) != '\n');
	dep->workers = (Person*)malloc(dep->numOfWorkers * sizeof(Person));
	for (i = 0; i < dep->numOfWorkers; ++i) {
		printf("enter worker name:\n");
		getPerson(dep->workers + i);
		while ((getchar()) != '\n');
	}

}
void getPerson(Person* p) {
	char str[buffer];
	scanf("%[^\n]", str);
	while ((getchar()) != '\n');
	p->name = (char*)malloc(strlen(str) + 1);
	strcpy(p->name, str);
	getDOB(&p->date);
}
void getDOB(DOB *date) {
	printf("enter DOB by following: dd/mm/yyyy\n");
	do {
		printf("enter day: ");
		scanf("%d", &(*date).Day);
	} while ((*date).Day < DAYLOW || (*date).Day>DAYHIGH);
	do {
		printf("enter month: ");
		scanf("%d", &(*date).Month);
	}while ((*date).Month < MONTHLOW || (*date).Month>MONTHHIGH);
	do {
		printf("enter year: ");
		scanf("%d", &(*date).Year);
	} while ((*date).Year < YEARLOW);
	printf("-------------------------\n");
}
void printCompany(Company *cmp) {
	int i;
	printf("-------------------------\n");
	printf("SEO name: %s\n", cmp->CEO.name);
	printf("DOB: %d/%d/%d\n", cmp->CEO.date.Day, cmp->CEO.date.Month, cmp->CEO.date.Year);
	printf("Number of department: %d\n", cmp->numOfDepartment);
	for (i = 0; i < cmp->numOfDepartment; ++i) {
		printDepartment(cmp->department + i);
	}
}
void printDepartment(Department* dep) {
	int i;
	printf("-------------------------\n");
	printf("Department name: %s\n", dep->departmentName);
	printf("Department Boss name: %s\n", dep->BossDepartment.name);
	printf("Boss DOB: %d/%d/%d\n", dep->BossDepartment.date.Day, dep->BossDepartment.date.Month, dep->BossDepartment.date.Year);
	printf("Number of Workers in department: %d\n", dep->numOfWorkers);
	for (i = 0; i < dep->numOfWorkers; ++i) {
		printWorker(dep->workers + i);
	}
	printf("-------------------------\n");
}

void printWorker(Person* p) {
	printf("Worker: %s\n", p->name);
	printf("Worker DOB: %d/%d/%d\n", p->date.Day, p->date.Month, p->date.Year);
}