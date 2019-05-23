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
void writeToFile(FILE**, Company*);
void readFromFile(FILE*, Company**);

//MAIN//
int main() {
	Company *cmp = NULL;
	FILE *fp = NULL;
	int choice;
	do {
		printf("Please enter your choice: \n");
		printf("1 Read a company from keyboard\n");
		printf("2 Read a company from file\n");
		printf("3 Add a department to the company\n");
		printf("4 Write the company to file\n");
		printf("5 Recursive menu\n");
		printf("6 Exit\n");
		scanf("%d", &choice);
	} while (choice < 0 || choice>6);
	switch (choice) {
	case 1: {
		getCompany(&cmp);
		break;
	}
	case 2: {
		readFromFile(fp, &cmp);
		break;
	}
	case 3:
	case 4: {
		writeToFile(&fp, cmp);
		break;
	}
	case 5: {
		break;
	}
	case 6: {
		printf("Good bye\n");
		return 0; 
	}
	}
	readFromFile(fp, &cmp);
	printCompany(cmp);
	freeCompany(cmp);
	return 0;
}
//FUNCTIONS//
void readFromFile(FILE* fp, Company** cmp) {
	*cmp = (Company*)malloc(sizeof(Company));
	char filename[buffer];
	char buf[buffer];
	int i, j;
	printf("enter filename\n");
	scanf("%s", filename);
	filename[strlen(filename)] = '\0';
	fp = fopen(filename, "r");
	if (!fp) {
		printf("error open file,file not found!\n");
		exit(1);
	}
	fscanf(fp, "%s", buf);
	(*cmp)->CEO.name = (char*)malloc(strlen(buf) + 1);
	strcpy((*cmp)->CEO.name, buf);
	fscanf(fp, "%d", &(*cmp)->CEO.date.Day);
	fscanf(fp, "%d", &(*cmp)->CEO.date.Month);
	fscanf(fp, "%d", &(*cmp)->CEO.date.Year);
	fscanf(fp, "%d", &(*cmp)->numOfDepartment);
	(*cmp)->department = (Department*)malloc((*cmp)->numOfDepartment * sizeof(Department));
	Department* dep = (*cmp)->department;
	for (i = 0; i < (*cmp)->numOfDepartment; ++i) {
		fscanf(fp, "%s", buf);
		(dep+i)->departmentName = (char*)malloc(strlen(buf) + 1);
		strcpy((dep + i)->departmentName, buf);
		fscanf(fp, "%s", buf);
		(dep + i)->BossDepartment.name = (char*)malloc(strlen(buf) + 1);
		strcpy((dep + i)->BossDepartment.name, buf);
		fscanf(fp, "%d", &(dep + i)->BossDepartment.date.Day);
		fscanf(fp, "%d", &(dep + i)->BossDepartment.date.Month);
		fscanf(fp, "%d", &(dep + i)->BossDepartment.date.Year);
		fscanf(fp, "%d", &(dep + i)->numOfWorkers);
		(dep + i)->workers = (Person*)malloc((dep + i)->numOfWorkers * sizeof(Person));
		Person* worker = (dep + i)->workers;
		for (j = 0; j < (dep + i)->numOfWorkers; ++j) {
			fscanf(fp, "%s", buf);
			(worker + j)->name = (char*)malloc(strlen(buf) + 1);
			strcpy((worker + j)->name, buf);
			fscanf(fp, "%d", &(worker + j)->date.Day);
			fscanf(fp, "%d", &(worker + j)->date.Month);
			fscanf(fp, "%d", &(worker + j)->date.Year);
		}
	}
	fclose(fp);
}
void writeToFile(FILE** fp, Company* cmp) {
	Department* dep = cmp->department;
	char filename[buffer];
	int i, j;
	printf("enter filename\n");
	scanf("%s", filename);
	filename[strlen(filename) - 1] = '\0';
	*fp = fopen(filename, "w+");
	if (!*fp) {
		printf("error open file!");
		return;
	}
	fprintf(*fp, "%s\n", cmp->CEO.name);
	fprintf(*fp, "%d\n", cmp->CEO.date.Day);
	fprintf(*fp, "%d\n", cmp->CEO.date.Month);
	fprintf(*fp, "%d\n", cmp->CEO.date.Year);
	fprintf(*fp, "%d\n", cmp->numOfDepartment);
	for (i = 0; i < cmp->numOfDepartment; ++i) {
		fprintf(*fp, "%s\n", (dep+i)->departmentName);
		fprintf(*fp, "%s\n", (dep + i)->BossDepartment.name);
		fprintf(*fp, "%d\n", (dep + i)->BossDepartment.date.Day);
		fprintf(*fp, "%d\n", (dep + i)->BossDepartment.date.Month);
		fprintf(*fp, "%d\n", (dep + i)->BossDepartment.date.Year);
		fprintf(*fp, "%d\n", (dep + i)->numOfWorkers);
		Person* worker = (dep + i)->workers;
		for (j = 0; j < (dep + i)->numOfWorkers; ++j) {
			fprintf(*fp, "%s\n",(worker+j)->name);
			fprintf(*fp, "%d\n", (worker + j)->date.Day);
			fprintf(*fp, "%d\n", (worker + j)->date.Month);
			fprintf(*fp, "%d\n", (worker + j)->date.Year);
		}
	}
	fclose(*fp);
}
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