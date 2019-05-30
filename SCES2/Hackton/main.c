/*Hackton
Names: Anthony Eitan Fleysher ID: 203192331
	   Roni Gerkerov ID: 316583145
	   Eli Manashirov ID: 208676742
	   CAMPUS: Ashdod
*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define id 9
#define BUF 30
#define DEFUALTTIMEMAX 24
#define DEFUALTTIMEMIN 0
#define DEFUALTYEAR 2019
#define DEFUALTDAYMAX 31
#define DEFUALTMONTHMAX 12
#define DEFUALTMONTHMIN 1
#define MINCHOICE 1
#define MAXCHOICE 5
typedef enum { FALSE, TRUE }Boolean;

typedef struct Date {
	int Day;
	int Month;
	int Year;
}Date;
typedef struct Time {
	float time;
}Time;

typedef struct Flight {
	Date DayOfFlight;
	Time TimeOfFlight;
	Time Duration;
	char *Departing;
	char *Ariving;
	float Distance;
	float Price;
}Flight;
typedef struct Person {
	char *Name;
	char *Surname;
	char ID[id];
	Flight *FlightInfo;
	int Number_Of_Flights;
}Person;
void mainMenu();
void GetMember(Person *, int);
void GetFlight(Flight *, int);
Person * alloc1D(int *);
FILE* getFile(FILE*,char*);
void readPersonFromFile(FILE*, Person*);
void readFlightFromFile(FILE*, Flight*, int);
int CheckForID(FILE*,char*);
void PrintFlight(Person *);
int CheckForIDInFile(FILE*,char*);
void printToFile(FILE**, Person*);
void freePerson(Person*, int *);
void freeFlight(Flight*);
void printIDToFILE(FILE**, Person*);
void addFlightToPerson(FILE*, FILE*, Person*,int,char* );
void checkDurationLimit(Person*, int);
void checkPriceLimit(Person*, int);
void printPerson(FILE*, FILE*,char*,char*);


int main() {
	mainMenu();
	return 0;
}

Person* alloc1D(int *size) {
	Person *p = NULL;
	printf("Enter number of person\n");
	scanf("%d", size);
	p = (Person *)malloc(*size * sizeof(Person));
	if (!p) {
		printf("Cannot allocate person\n");
		exit(1);
	}
	return p;
}
void GetFlight(Flight *Details, int Index) {
	char Buffer[BUF];
	printf("Enter details for flight number %d\n", Index + 1);
	printf("Enter Day: ");
	do {
		scanf("%d", &Details->DayOfFlight.Day);
	} while (Details->DayOfFlight.Day > DEFUALTDAYMAX || Details->DayOfFlight.Day < DEFUALTTIMEMIN);
	printf("Enter Month: ");
	do {
		scanf("%d", &Details->DayOfFlight.Month);
	} while (Details->DayOfFlight.Month > DEFUALTMONTHMAX || Details->DayOfFlight.Month < DEFUALTMONTHMIN);
	printf("Enter Year: ");
	do {
		scanf("%d", &Details->DayOfFlight.Year);
	} while (Details->DayOfFlight.Year < DEFUALTYEAR);
	printf("Enter Time of flight(Hours/Minutes)(flaot): ");
	do {
		scanf("%f", &Details->TimeOfFlight.time);
	} while (Details->TimeOfFlight.time > DEFUALTTIMEMAX || Details->TimeOfFlight.time < DEFUALTTIMEMIN);

	printf("Enter Destnation: ");
	scanf("%s", Buffer);
	Details->Ariving = (char*)malloc(strlen(Buffer) + 1);
	strcpy(Details->Ariving, Buffer);
	printf("Enter Departing: ");
	scanf("%s", Buffer);
	Details->Departing = (char*)malloc(strlen(Buffer) + 1);
	strcpy(Details->Departing, Buffer);
	printf("Enter flight Duration(float): ");
	scanf("%f", &Details->Duration.time);
	printf("Enter Distance of flight(float): ");
	scanf("%f", &Details->Distance);
	printf("Enter price of flight(float): ");
	scanf("%f", &Details->Price);

}
void GetMember(Person *Member, int Index) {
	char Buffer[BUF];
	int i;
	printf("Enter Detail for person %d\n", Index + 1);
	while ((getchar()) != '\n');
	printf("Enter Person ID: ");
	scanf("%s", Member->ID);
	printf("Enter Person Name: ");
	while ((getchar()) != '\n');
	scanf("%s", Buffer);
	Member->Name = (char*)malloc(strlen(Buffer) + 1);
	strcpy(Member->Name, Buffer);
	printf("Enter Person Surname: ");
	while ((getchar()) != '\n');
	scanf("%s", Buffer);
	Member->Surname= (char*)malloc(strlen(Buffer) + 1);
	strcpy(Member->Surname, Buffer);
	do {
		printf("Enter number of flights: ");
		scanf("%d", &Member->Number_Of_Flights);
	} while (Member->Number_Of_Flights < DEFUALTTIMEMIN);
	Member->FlightInfo = (Flight*)malloc(Member->Number_Of_Flights * sizeof(Flight));
	Flight *Flt = Member->FlightInfo;
	for (i = 0; i < Member->Number_Of_Flights; ++i) {
		GetFlight(Flt + i, i);
	}
}
FILE* getFile(FILE* fp,char *name) {
	char filename[BUF];
	printf("Enter filename at the end add .txt: ");
	scanf("%s", filename);
	strcpy(name, filename);
	fp = fopen(filename, "w");
	return fp;
}
void mainMenu() {
	FILE *Names = NULL, *Details = NULL;
	char id_filename[BUF], details_filename[BUF];
	printf("Enter ID filename\n");
	Names = getFile(Names,id_filename);
	printf("Enter Details filename\n");
	Details = getFile(Details,details_filename);
	Person* Prs = NULL;
	int i;
	int numbers_of_person;
	Prs = alloc1D(&numbers_of_person);
	for (i = 0; i < numbers_of_person; i++) {
		GetMember(Prs + i, i);
		printIDToFILE(&Names, Prs + i);
		printToFile(&Details, Prs + i);
	}
	fclose(Names); fclose(Details);
	for (;;) {
		int choice;
		do
		{
			printf("\n\nPlease enter Choice 1-5:\n");
			printf("1. Add flight to a certian person\n");
			printf("2. Find all person that thier flight duration above certian limit\n");
			printf("3. Find all person that thier flight cost above certian limit\n");
			printf("4. Print all flights of certian person\n");
			printf("5. To exit \n");
			scanf("%d", &choice);
		} while (MINCHOICE > choice || MAXCHOICE < choice);
		{

			switch (choice)
			{
			case 1: {
				addFlightToPerson(Names, Details, Prs, numbers_of_person,details_filename);
				break;
			}
			case 2: {
				checkDurationLimit(Prs, numbers_of_person);
				break;
			}
			case 3: {
				checkPriceLimit(Prs, numbers_of_person);
				break;
			}
			case 4: {
				printPerson(Names, Details,id_filename,details_filename);
				break;
			}
			case 5: {
				freePerson(Prs, &numbers_of_person);
				printf("Good Bye\n");
				return;
			}
			}
		}
	}
}
void printPerson(FILE* Names,FILE* Details,char* id_filename,char* details_filename) {
	Names = fopen(id_filename, "r");
	char ID[BUF];
	if (!CheckForID(Names,ID)) {
		printf("Cannot find person\n");
		fclose(Names);
		return;
	}
	else {
		int size=1;
		Details = fopen(details_filename, "r");
		CheckForIDInFile(Details,ID);
		Person* Member = NULL;
		Member = (Person*)malloc(size*sizeof(Person));
		readPersonFromFile(Details, Member);
		PrintFlight(Member);
		freePerson(Member,&size);
		fclose(Names); fclose(Details);
	}
}
void checkPriceLimit(Person* Prs, int numbers_of_person) {
	int i, j;
	int limit;
	printf("enter min price limit\n");
	scanf("%d", &limit);
	for (i = 0; i < numbers_of_person; i++) {
		for (j = 0; j < (Prs + i)->Number_Of_Flights; ++j) {
			Flight* Flt = (Prs + i)->FlightInfo;
			if ((Flt + j)->Price > limit)
				printf("%s\n", (Prs + i)->Name);
		}
	}
}
void checkDurationLimit(Person* Prs,int numbers_of_person) {
	int i,j;
	float limit;
	printf("enter min duration limit(float): ");
	scanf("%f", &limit);
	for (i = 0; i < numbers_of_person; i++) {
		for (j = 0; j < (Prs + i)->Number_Of_Flights; ++j) {
			Flight* Flt = (Prs + i)->FlightInfo;
			if ((Flt + j)->Duration.time > limit)
				printf("%s\n", (Prs + i)->Name);
		}
	}
}
void addFlightToPerson(FILE* Names,FILE* Details,Person* Prs,int numbers_of_person,char* details_filename) {
	int i;
	char ID[BUF];
	printf("Enter ID to search: ");
	while ((getchar()) != '\n');
	scanf("%s", ID);
	for (i = 0; i < numbers_of_person; ++i) {
		if (strcmp((Prs + i)->ID, ID) == 0) {
			(Prs + i)->Number_Of_Flights += 1;
			(Prs + i)->FlightInfo = (Flight*)realloc((Prs + i)->FlightInfo, ((Prs + i)->Number_Of_Flights) * sizeof(Flight));
			Flight* Flt = (Prs + i)->FlightInfo;
			GetFlight(Flt + ((Prs + i)->Number_Of_Flights - 1), ((Prs + i)->Number_Of_Flights - 1));
		}
	}
	Details = fopen(details_filename, "w");
	for (i = 0; i < numbers_of_person; i++) {
		printToFile(&Details, Prs + i);

	}
	fclose(Details); fclose(Names);
}
void readPersonFromFile(FILE*Details, Person*Member)
{
	char Buffer[BUF];
	int i;
	printf("Detail for person:\n");
	fscanf(Details, "%s", Member->ID);
	fscanf(Details, "%s", Buffer);
	Member->Name = (char*)malloc(strlen(Buffer) + 1);
	strcpy(Member->Name, Buffer);
	fscanf(Details, "%s", Buffer);
	Member->Surname = (char*)malloc(strlen(Buffer) + 1);
	strcpy(Member->Surname, Buffer);
	fscanf(Details, "%d", &Member->Number_Of_Flights);
	Member->FlightInfo = (Flight*)malloc(Member->Number_Of_Flights * sizeof(Flight));
	Flight *Flt = Member->FlightInfo;
	for (i = 0; i < Member->Number_Of_Flights; ++i) {
		readFlightFromFile(Details, Flt + i, i);
	}

}
void readFlightFromFile(FILE*DetailsFile, Flight* Details, int Index)
{
	char Buffer[BUF];
	fscanf(DetailsFile, "%d", &Details->DayOfFlight.Day);
	fscanf(DetailsFile, "%d", &Details->DayOfFlight.Month);
	fscanf(DetailsFile, "%d", &Details->DayOfFlight.Year);
	fscanf(DetailsFile, "%f", &Details->TimeOfFlight.time);
	fscanf(DetailsFile, "%s", Buffer);
	Details->Ariving = (char*)malloc(strlen(Buffer) + 1);
	strcpy(Details->Ariving, Buffer);
	fscanf(DetailsFile, "%s", Buffer);
	Details->Departing = (char*)malloc(strlen(Buffer) + 1);
	strcpy(Details->Departing, Buffer);
	fscanf(DetailsFile, "%f", &Details->Duration.time);
	fscanf(DetailsFile, "%f", &Details->Distance);
	fscanf(DetailsFile, "%f", &Details->Price);


}
int CheckForID(FILE*Names,char* ids){
	char ch;
	char ID[BUF];
	char Buffer[BUF];
	printf("Enter ID for Search: ");
	while ((getchar()) != '\n');
	scanf("%[^\n]", ID);
	strcpy(ids, ID);
	while (!feof(Names)) {
		fscanf(Names, "%[^\n]", Buffer);
		if (strcmp(ID, Buffer) == 0)
			return 1;
		for (ch = getc(Names); ch != '\n'; ch = getc(Names)); //newline
	}
	return 0;
}
int CheckForIDInFile(FILE*Details,char *ids){
	char ch;
	int len = 0;
	char Buffer[BUF];
	while ((getchar()) != '\n');
	len = strlen(ids);
	while (!feof(Details)) {
		fscanf(Details, "%[^\n]", Buffer);
		if (strcmp(ids, Buffer) == 0) {
			fseek(Details, -len, SEEK_CUR);
			return 1;
		}
		for (ch = getc(Details); ch != '\n'; ch = getc(Details));
	}
	return 0;
}
void PrintFlight(Person *Member) {
	int i;
	Flight* Flt = Member->FlightInfo;
	for (i = 0; i < Member->Number_Of_Flights; ++i) {
		printf("flight information for flight %d\n", i + 1);
		printf("Ariving at: %s\n", (Flt + i)->Ariving);
		printf("Departing from: %s\n", (Flt + i)->Departing);
		printf("Duration of flight: %.2f\n", (Flt + i)->TimeOfFlight.time);
		printf("Flight Distance: %.2fKM\n", (Flt + i)->Distance);
		printf("Day of flight: %d/%d/%d\n", (Flt + i)->DayOfFlight.Day, (Flt + i)->DayOfFlight.Month, (Flt + i)->DayOfFlight.Year);
		printf("Price in USD %.2f$\n", (Flt + i)->Price);
		printf("Time of flight: %.2f\n", (Flt + i)->TimeOfFlight.time);

	}
}
void printIDToFILE(FILE** Names, Person* Member) {
	fprintf(*Names, "%s\n", Member->ID);
}
void printToFile(FILE** Details, Person* Member) {
	int i;
	fprintf(*Details, "%s\n", Member->ID);
	fprintf(*Details, "%s %s\n", Member->Name,Member->Surname);
	fprintf(*Details, "%d\n", Member->Number_Of_Flights);
	Flight *Flt = Member->FlightInfo;
	for (i = 0; i < Member->Number_Of_Flights; ++i) {
		fprintf(*Details, "%d\n", (Flt + i)->DayOfFlight.Day);
		fprintf(*Details, "%d\n", (Flt + i)->DayOfFlight.Month);
		fprintf(*Details, "%d\n", (Flt + i)->DayOfFlight.Year);
		fprintf(*Details, "%.2f\n", (Flt + i)->TimeOfFlight.time);
		fprintf(*Details, "%s\n", (Flt + i)->Ariving);
		fprintf(*Details, "%s\n", (Flt + i)->Departing);
		fprintf(*Details, "%.2f\n", (Flt + i)->Duration.time);
		fprintf(*Details, "%.2f\n", (Flt + i)->Distance);
		fprintf(*Details, "%.2f\n", (Flt + i)->Price);
	}
}
void freePerson(Person* Prs, int *person) {
	int i,j;
	for (i = 0; i < *person; ++i) {
		Flight* Flt = (Prs + i)->FlightInfo;
		for(j=0;j<(Prs+i)->Number_Of_Flights;++j)
			freeFlight(Flt+j);
	}
	for (i = 0; i < *person; ++i) {
		free((Prs + i)->Name);
		free((Prs + i)->Surname);

	}
	*person = 0;
	free(Prs);
}
void freeFlight(Flight* Flt) {
	free(Flt->Ariving);
	free(Flt->Departing);

}