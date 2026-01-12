#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node* Position;

typedef struct node {
	int coefficient;
	int exponent;
	Position next;
}node;

int readPoynomial(Position);
void printList(Position);
int sumPolynomial(Position, Position, Position);
int mulPolynomial(Position, Position, Position);

int main() {
	node head1;
	node head2;
	node headSum;
	node headMultiply;
	int result = 0;

	head1.next = NULL;
	head2.next = NULL;
	headSum.next = NULL;
	headMultiply.next = NULL;

	result = readPolynomial(&head1);
	if (result == -1) {
		printf("Datoteka se ne moze otvoriti!\n");
		return 0;
	}
	else if (result == -2) {
		printf("Memorija nije alocirana!\n");
		freePolynom(&head1);
		return 0;
	}
	else {
		printf("OK!\n");
	}

	result = readPolynomial(&head2);
	if (result == -1) {
		printf("Datoteka se ne moze otvoriti!\n");
		freePolynom(&head1);
		return 0;
	}
	else if (result == -2) {
		printf("Memorija nije alocirana!\n");
		freePolynom(&head1);
		freePolynom(&head2);
		return 0;
	}
	else {
		printf("OK!\n");
	}

	printList(head1.next);
	printList(head2.next);

	result = sumPolynomial(head1.next, head2.next, &headSum);
	if (result==-2)
	{
		printf("Memorija nije alocirana\n");
		freePolynom(&head1);
		freePolynom(&head1);
		freePolynom(&headSum);
	}
	else
	{
		printf("OK\n");
	}

	printList(headSum.next);

	result = mulPolynomial(head1.next, head2.next, &headMultiply);
	if (result == -2) {
		printf("Error!\n");
		freePolynom(&head1);
		freePolynom(&head1);
		freePolynom(&headMultiply);
		return 0;
	}
	else {
		printf("OK!\n");
		
	}

	printList(headMultiply.next);
	freePolynom(&head1);
	freePolynom(&head2);
	freePolynom(&headSum);
	freePolynom(&headMultiply);
	printList(headMultiply.next);
	printList(headSum.next);
	printList(head1.next);
	printList(head2.next);
	return 0;
}

	int readPolynomial(Position p) {
	FILE* fp = NULL;
	char* filename[128];
	Position q = NULL;
	Position start = p;
	printf("Unesi ime datoteke\n");
	scanf(" %s", filename);

	fp = fopen(filename, "r");
	if (fp==NULL)
	{
		printf("Datoteka nije otvorena\n");
		return -1;
	}
	while (!feof (fp))
	{
		q = (Position)malloc(sizeof (node));
		if (q==NULL)
		{
			printf("Greska u alokaciji\n");
			fclose(fp);
			return -2;
		}
		if (fscanf(fp," %d %d",&(q->coefficient),&(q->exponent))==2)
		{
			while (p->next!=NULL && p->next->exponent > q->exponent)
			{
				p=p->next;
			}
			q->next = p->next;
				p->next = q;
		}
		p=start;

	}
	fclose(fp);
	return 0;
    }	

	int sumPolynomial(Position p1, Position p2, Position sum) {
		
		Position q = NULL;

		while (p1 != NULL || p2 != NULL)
		{
			q = (Position)malloc(sizeof(struct node));
			if (q == NULL) {
				printf("Allocation failed!!!\n");
				return -1;
			}

			if (p1==NULL)
			{
				q->coefficient = p2->coefficient;
				q->exponent = p2->exponent;
				
				p2 = p2->next;
			}
			else if (p2==NULL)
			{
				q->coefficient = p1->coefficient;
				q->exponent = p1->exponent;

				p1 = p1->next;
			}
			else
			{
				if (p1->exponent>p2->exponent)
				{
					q->coefficient = p1->coefficient;
					q->exponent = p1->exponent;

					p1 = p1->next;
				}
				else if (p1->exponent < p2->exponent)
				{
					q->coefficient = p2->coefficient;
					q->exponent = p2->exponent;

					p2 = p2->next;
				}
				else
				{
					q->coefficient = p1->coefficient + p2->coefficient;
					q->exponent = p1->exponent;

					p1 = p1->next;
					p2 = p2->next;
				}
			}
			q->next = sum->next;
			sum->next = q;
			sum = sum->next;
		}
		return 0;
	}

	int mulPolynomial(Position p1, Position p2, Position multiply) {
		Position q = NULL, i = NULL, j = NULL, tmp = NULL;
		int eksp = 0;
		int koef = 0;
		i = p1;

		while (i !=NULL)
		{
			j = p2;
			while (j!=NULL)
			{
				koef = i->coefficient * j->coefficient;
				eksp = i->exponent + j->exponent;
				tmp = multiply;
				while (tmp->next != NULL && tmp->next->exponent > eksp)
				{
					tmp = tmp->next;
				}
					if (tmp->next != NULL && tmp->next->exponent == eksp)
					{
						tmp->next->coefficient += koef;
					}
					else
					{
						q = (Position)malloc(sizeof(struct node));
						if (q == NULL) {
							printf("Alokacija nije uspjela!\n");
							return -1;
						}
						q->exponent = eksp;
						q->coefficient = koef;
						q->next = tmp->next;
						tmp->next = q;
					}
					j = j->next;
			}
				i = i->next;
		}
			
		
		return 0;
	}
	void printList(Position p) {
		Position start = p;
		if (start==NULL)
		{
			printf("Prazna lista\n");
			return 0;
		}

		while (p!=NULL)
		{
			if (p!=start && p->coefficient>0)
			{
				printf("+%dx^%d", p->coefficient, p->exponent);
			}
			else
			{
				printf("%dx^%d",p->coefficient,p->exponent);
			}
			p = p->next;
		}
		printf("\n");
	}

	int freePolynom(Position P) {
		Position temp = NULL, start = P;
		while (P->next != NULL)
		{
			temp = P->next;
			P->next = temp->next;
			free(temp);

		}
		return 0;
	}