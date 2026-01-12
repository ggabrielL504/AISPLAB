#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Person {
	char name[128];
	char surname[128];
	int yearOfBirth;

	struct Person* next;
}Person;
typedef struct Person* Position;


int pushFront(Position);
void printList(Position);
int pushBack(Position);
void findElement(Position);
void deleteElement(Position);
void fillData(Position);
Position createNode();
void freeList(Position);
int pushBefore(Position, char*);
int pushAfter(Position, char*);
int writeToFile(Position, char*);
int readFromFile(Position, char*);
void sortList(Position);

Position findPrevious(Position, char*);


int main() {
	Person head;
	head.next = NULL;

	int isRunning = 1;
	int action = 1;
	int result = 0;
	char lastName[128];
	char fileName[128];

	do
	{
		printf("\n");
		printf("Unesite akciju\n");
		printf("1:Dodaj na pocetak\t 2:Dodaj na kraj\t 3:Pronadi element\t 4:Izbrisi element\t 5:Isprintaj listu\n");
		printf("6:Dodaj iza odredenog elementa\t 7:Dodaj ispred odredenog elementa\t 8:Ispisi listu u datoteku\t 9:Citaj listu iz datoteke\t 10:Sortiraj listu po prezimenu\n");
		printf("\n");
		scanf(" %d", &action);

		switch (action)
		{
		case 1:
			result = pushFront(&head);
			if (result == 0)
			{
				printf("OK\n");
				break;
			}
			else if (result == -1)

			{
				printf("NOT OK\n");
				isRunning = 0;
				break;
			}
		case 2:
			result = pushBack(&head);
			if (result == 0)
			{
				printf("OK\n");
				break;
			}
			else if (result == -1)

			{
				printf("NOT OK\n");
				isRunning = 0;
				break;
			}
			break;
		case 3:
			findElement(&head);
			break;
		case 4:
			deleteElement(&head);
			break;
		case 5:
			printList(&head);
			break;
		case 6:
			printf("Unesi prezime\n");
			scanf(" %s", lastName);
			result = pushBefore(&head, lastName);
			if (result == 0)
			{
				printf("OK\n");
				break;
			}
			else if (result == -1)

			{
				printf("NOT OK\n");
				isRunning = 0;
				break;
			}
		case 7:
			printf("Unesi prezime\n");
			scanf(" %s", lastName);
			result = pushAfter(&head, lastName);
			if (result == 0)
			{
				printf("OK\n");
				break;
			}
			else if (result == -1)

			{
				printf("NOT OK\n");
				isRunning = 0;
				break;
			}

		case 8:
			printf("Unesi ime datoteke\n");
			scanf(" %s", fileName);
			result = writeToFile(&head, fileName);
			if (result == 0)
			{
				printf("OK\n");
				break;
			}
			else if (result == -1)

			{
				printf("NOT OK\n");
				isRunning = 0;
				break;
			}
		case 9:
			printf("Unesi ime datoteke\n");
			scanf(" %s", fileName);
			result = readFromFile(&head, fileName);
			if (result == 0)
			{
				printf("OK\n");
				break;
			}
			else if (result == -1)

			{
				printf("NOT OK\n");
				isRunning = 0;
				break;
			}
		case 10:
			sortList(&head);
			break;
		default:
			break;
		}
	} while (isRunning);

	freeList(&head);
	return 0;
}


int pushFront(Position head) {
	Position p = NULL;
	p = createNode(p);
	if (p == NULL)
	{
		return -1;
	}
	fillData(p);
	p->next = head->next;
	head->next = p;
	return 0;
}

int pushBack(Position prev) {
	Position p = NULL;
	p = createNode();
	if (p == NULL)
	{
		return -1;
	}
	fillData(p);
	while (prev->next != NULL)
	{
		prev = prev->next;
	}
	prev->next = p;
	p->next = NULL;
}

void findElement(Position p) {
	Position tmp = NULL;
	char surname[128];
	printf("Unesi zeljeno prezime\n");
	scanf(" %s", surname);

	while (p->next != NULL)
	{
		if (strcmp(p->surname, surname) == 0)
		{
			tmp = p;
			printf("Pronaden je element: %s %s %d\n", tmp->name, tmp->surname, tmp->yearOfBirth);
		}
		p = p->next;
	}
	if (tmp == NULL)
	{
		printf("Nije pronaden element\n");
	}
}

void deleteElement(Position prev) {
	Position tmp;
	char surname[128];
	printf("Unesi zeljeno prezime za brisanje\n");
	scanf(" %s", surname);

	while (prev->next != NULL)
	{
		if (strcmp(prev->next->surname, surname) == 0)
		{
			tmp = prev->next;
			prev->next = tmp->next;
			printf("Obrisan je element: %s %s %d\n", tmp->name, tmp->surname, tmp->yearOfBirth);
			free(tmp);
		}
		prev = prev->next;
	}
}
Position createNode() {
	return (Position)malloc(sizeof(Person));
}

void fillData(Position p) {
	printf("Unesi podatke(Ime Prezime xxxx)\n");
	scanf(" %s %s %d", p->name, p->surname, &p->yearOfBirth);
}

void printList(Position head)
{
	Position p = head->next;
	if (p == NULL)
	{
		printf("Prazna lista\n");
		return 0;
	}
	else
	{
		while (p != NULL)
		{
			printf("%s %s %d\n", p->name, p->surname, p->yearOfBirth);
			p = p->next;
		}
	}
}

int pushBefore(Position p, char* surname) {
	p = findPrevious(p, surname);
	if (p==NULL)
	{
		return -1;
	}
	return pushFront(p);
}

int pushAfter(Position p, char* surname) {
	p = findPrevious(p, surname);
		if (p==NULL)
		{
			return -1;
		}
		p = p->next;
		return pushFront(p);
}

Position findPrevious(Position p, char* lastName) {
	while (p->next!=NULL && strcmp(p->next->surname,lastName)!=0)
	{
		p = p->next;
	}
	if (p->next!=NULL)
	{
		return p;
	}
	else
	{
		return NULL;
	}
}


int writeToFile(Position p, char* filename) {
	FILE* fp = NULL;
	fp = fopen(filename, "w");
	p = p->next;
	if (fp==NULL)
	{
		printf("Datoteka nije otvorena!\n");
		return -1;
	}
	while (!feof(fp) && p!=NULL)
	{
		fprintf(fp, " %s %s %d\n", p->name, p->surname, p->yearOfBirth);
		p = p->next;
	}
	fclose(fp);
	return 0;
}

int readFromFile(Position head, char* filename) {
	FILE* fp = NULL;
	Position q = NULL;

	fp = fopen(filename, "r");
	if (fp==NULL)
	{
		printf("Datoteka nije otvorena!\n");
		return -1;
	}

	while (!feof(fp))
	{
		q = createNode(q);
		if (q==NULL)
		{
			printf("Memorija se nije alocirala\n");
			fclose(fp);
			return -1;
		}

		if (fscanf(fp, " %s %s %d",q->name,q->surname,&q->yearOfBirth)==3)
		{
			q->next = head->next;
			head->next = q;
			printf("%s %s %d\n", q->name, q->surname, q->yearOfBirth);
		}
	}
	fclose(fp);
	return 0;
}

void sortList(Position head) {
	Position i = NULL, j = NULL;
	if (head->next == NULL) {
		printf("Prazna lista\n");
	};

	for (i = head->next; i != NULL; i = i->next) {
		for (j = i->next; j != NULL; j = j->next) {
			if (_strcmpi(i->surname, j->surname) > 0) {

				char tempName[128], tempSurname[128];
				int tempYear;
				strcpy(tempName, i->name);
				strcpy(tempSurname, i->surname);
				tempYear = i->yearOfBirth;

				strcpy(i->name, j->name);
				strcpy(i->surname, j->surname);
				i->yearOfBirth = j->yearOfBirth;

				strcpy(j->name, tempName);
				strcpy(j->surname, tempSurname);
				j->yearOfBirth = tempYear;
			}
		}
	}
}

void freeList(Position head) {
	Position p = head->next;
	Position tmp = NULL;

	while (p->next != NULL)
	{
		tmp = p;
		p = p->next;
		free(tmp);
	}
	head->next = NULL;
}