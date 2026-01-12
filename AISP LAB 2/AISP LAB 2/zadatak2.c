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


int main() {
	Person head;
	head.next = NULL;

	int isRunning = 1;
	int action = 1;
	int result = 0;


	do
	{
		printf("Unesite akciju\n");
		printf("1:Dodaj na pocetak\t 2:Dodaj na kraj\t 3:Pronadi element\t 4:Izbrisi element\t 5:Isprintaj listu\n");
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