//LAB-12 SCE-Campus Ashdod//
//STRUCT//
//Author: Anthony Eitan Fleysher//
//ID: 203192331// 


#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>


//////EXERCISE1//
//typedef struct {
//	double x;
//	double y;
//}Point;
//
//void getDetails(Point *,int);
//void printDetails(Point);
//double distance(const Point, const Point);
//void distancev2(const Point*,int);
//Point* alloc1D(int *);
//
//int main() {
//	Point *point=NULL;
//	int size,i;
//	point=alloc1D(&size);
//	for (i = 0; i < size; ++i) {
//		getDetails(&point[i],i);
//	}
//	distancev2(point, size);
//	free(point);
//	return 0;
//}
//Point* alloc1D(int *size) {
//	Point *pPoint = NULL;
//	printf("enter number of points: ");
//	scanf("%d", size);
//	pPoint = (Point*)malloc(*size * sizeof(Point));
//	if (!pPoint)
//		puts("error allocate struct");
//	return pPoint;
//}
//void getDetails(Point *p,int size) {
//	printf("enter %d point:\n",size+1);
//	printf("enter x: ");
//	scanf("%lf", &(p->x));
//	printf("enter y: ");
//	scanf("%lf", &(p->y));
//}
//
//double distance(const Point p1,const Point p2) {
//	double distance = 0;
//	distance = sqrt(((p2.x - p1.x) * (p2.x - p1.x))+ ((p2.y - p1.y) * (p2.y - p1.y)));
//	return distance;
//}
//void distancev2(const Point *p,int size) {
//	double distanceV2 = 0,d;
//	int i, j;
//	distanceV2 = distance(p[0], p[1]);
//	for(i=1;i<size-1;++i){
//		for (j = i + 1; j < size; ++j) {
//			d = distance(p[i], p[j]);
//			if (d < distanceV2)
//				distanceV2 = d;
//		}
//	}
//	printf("the shortest distance is %lf", distanceV2);
//}

////EXERCISE2//
//#define SIZE 30
//typedef struct {
//	char *bookName;
//	char *name;
//	int numOfPages;
//	int numOfPhotos;
//	int year;
//}Book;
//
//Book* alloc1D(int *);
//void getBook(Book*, int);
//void freeBook(Book**, int);
//void sortBookByYear(Book**, int);
//void printBook(Book*,int);
//void swap(Book*, Book*);
//void printBookByPages(Book*, int);
//void addRemoveBook(Book**, int*);
//
//	int main() {
//	Book *book = NULL;
//	int size,i;
//	book = alloc1D(&size);
//	for (i = 0; i < size; ++i) {
//		getBook(&book[i], i);
//	}
//	printBookByPages(book, size);
//	addRemoveBook(&book, &size);
//	sortBookByYear(&book, size);
//	for (i = 0; i < size; ++i) {
//		printBook(book + i, i);
//	}
//	freeBook(&book, size);
//	free(book);
//	return 0;
//}
//Book* alloc1D(int *size) {
//	Book *pBook = NULL;
//	printf("enter number of books: ");
//	scanf("%d", size);
//	pBook = (Book*)malloc(*size * sizeof(Book));
//	if (!pBook)
//		puts("error allocate struct");
//	return pBook;
//}
//void getBook(Book* pb, int index) {
//	printf("enter details for %d book\n", index + 1);
//	getchar();
//	char buffer[SIZE];
//	printf("enter book name: ");
//	scanf("%[^\n]", buffer);
//	getchar();
//	pb->bookName = (char*)malloc(strlen(buffer) + 1);
//	strcpy(pb->bookName, buffer);
//	printf("enter book Author: ");
//	scanf("%[^\n]", buffer);
//	getchar();
//	pb->name = (char*)malloc(strlen(buffer) + 1);
//	strcpy(pb->name, buffer);
//	printf("enter number of pages: ");
//	scanf("%d", &(pb->numOfPages));
//	printf("enter number of photos: ");
//	scanf("%d", &(pb->numOfPhotos));
//	printf("enter year: ");
//	scanf("%d", &(pb->year));
//}
//void printBookByPages(Book* b, int size) {
//	int i,max=b[0].numOfPages,index=0;
//	for (i = 1; i < size; ++i) {
//		if (b[i].numOfPages > max) {
//			max = b[i].numOfPages;
//			index = i;
//		}
//	}
//	printBook(b+index, index);
//}
//void freeBook(Book **pb, int size) {
//	int i;
//	for (i = 0; i < size; ++i) {
//		free((*pb+i)->bookName);
//		free((*pb+i)->name);
//	}
//}
//
//void sortBookByYear(Book** pb, int size) {
//	int i,j;
//	for (i = 0; i < size; ++i) {
//		for (j = 0; j < (size-i-1); ++j) {
//			if ((*pb + j)->year > ((*pb + j + 1)->year)) {
//				swap(&(*pb)[j], &(*pb)[j + 1]);
//			}
//		}
//	}
//}
//void printBook(Book* b,int index) {
//	printf("Details for Book %d :\n", index + 1);
//	printf("Book name: %s\n", b->bookName);
//	printf("Book Author: %s\n", b->name);
//	printf("Pages: %d\n", b->numOfPages);
//	printf("Photos: %d\n", b->numOfPhotos);
//	printf("Year: %d\n", b->year);
//}
//
//void swap(Book* A, Book* B) {
//	Book temp = *A;
//	*A = *B;
//	*B = temp;
//}
//void addRemoveBook(Book** pb, int* pSize) {
//	int choice, rBook, i;
//	for (;;) {
//		do {
//			printf("what you would like to do?\n");
//			printf("enter 1 for add Book\n");
//			printf("enter 2 for delete Book\n");
//			printf("enter 0 for exit\n");
//			scanf("%d", &choice);
//		} while (choice > 2 || choice < 0);
//		if (choice == 1) {
//			(*pSize)++;
//			*pb = (Book*)realloc(*pb, *pSize * sizeof(Book));
//			getBook(&(*pb)[*pSize - 1], *pSize - 1);
//		}
//		else if (choice == 2) {
//			do {
//				printf("which book you would like to remove?\n");
//				scanf("%d", &rBook);
//				rBook--;
//			} while (rBook > *pSize - 1 || rBook < 0);
//			for (i = rBook; i < *pSize-1; ++i) {
//				(*pb)[i] = (*pb)[i + 1]; //swap to disired location.
//			}
//			(*pSize)--;
//			free((*pb)[*pSize].bookName);
//			free((*pb)[*pSize].name);
//			*pb = (Book*)realloc(*pb, *pSize * sizeof(Book));
//		}
//		else
//			break;
//	}
//}

////EXERCISE3//
#define SIZE 10
#define BUFFER 128
typedef enum{FEMALE,MALE}Sex;
typedef struct {
	int day;
	int month;
	int year;
}Birthday;
typedef struct {
	char* name;
	char* surname;
	Sex gender;
	Birthday list;
	char id[SIZE];
}Person;



void getPerson(Person*,int);
void printPerson(Person* , int);
Person* alloc1D(int*);

int main() {
	Person *pPerson = NULL;
	int size, i;
	pPerson = alloc1D(&size);
	for (i = 0; i < size; ++i) {
		getPerson(&pPerson[i], i);
	}
	for (i = 0; i < size; ++i) {
		printPerson(pPerson+i, i);
	}
	free(pPerson);
	return 0;
}
Person* alloc1D(int *size) {
	Person *pPerson = NULL;
	printf("enter number of Persons: ");
	scanf("%d", size);
	pPerson = (Person*)malloc(*size * sizeof(Person));
	if (!pPerson)
		puts("error allocate struct");
	return pPerson;
}
void getPerson(Person* p, int index) {
	printf("enter details for %d Person\n", index + 1);
	getchar();
	char buffer[BUFFER];
	printf("enter Person name: ");
	scanf("%[^\n]", buffer);
	getchar();
	p->name = (char*)malloc(strlen(buffer) + 1);
	strcpy(p->name, buffer);
	printf("enter Person surname : ");
	scanf("%[^\n]", buffer);
	getchar();
	p->surname = (char*)malloc(strlen(buffer) + 1);
	strcpy(p->surname, buffer);
	printf("enter ID: ");
	scanf("%[^\n]", p->id);
	getchar();
	do {
		printf("enter Gender 1 for male 0 for female\n");
		scanf("%d", &p->gender);
	} while (p->gender <0 || p->gender > 1);
	printf("enter Birthday: day,month,year\n");
	scanf("%d", &p->list.day);
	scanf("%d", &p->list.month);
	scanf("%d", &p->list.year);
}

void printPerson(Person* p, int index) {
	printf("Details for Person %d :\n", index + 1);
	printf("Person name: %s\n", p->name);
	printf("Person surname: %s\n", p->surname);
	printf("Person ID: %s\n", p->id);
	printf("Person Birthday %d/%d/%d\n", p->list.day, p->list.month, p->list.year);
	printf("Person Gender: ");
	if (p->gender == 0)
		printf("Female");
	else
		printf("Male");
	printf("\n");
}