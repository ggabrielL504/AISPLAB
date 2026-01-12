#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>

struct _Node;
typedef struct _Node* Position;

struct _Node
{
	int Element;
	Position Next;
};

int GetValueFromRange(int, int);
int Push(Position, int, int);
int Pop(Position, int);
void PrintList(Position, int);

void main(void)
{
	struct _Node S;
	char choice = 0;
	int n = 0;
	int max = 0;

	S.Next = NULL;
	S.Element = -1;

	while (max < 5)
	{
		printf("\nInput stack size <5-20> : ");
		scanf_s(" %d", &max);
		if (max < 5 || max > 20)
		{
			max = 0;
			printf("\nWrong input!");
		}
	}

	S.Next = NULL;
	srand((unsigned)time(NULL));

	while (choice != 'K' && choice != 'k')
	{
		
		printf("\n\t\t1.\tStack push");
		printf("\n\t\t2.\tStack pop");
		printf("\n\t\tk.\tEnd of program");
		printf("\nChoice : ");
		scanf_s(" %c", &choice, 1);

		switch (choice)
		{
		case '1':
			if (n < max)
				n = Push(&S, GetValueFromRange(0, 10000), n);
			else
				printf("\nStack is fulln!\r\n");
			PrintList(S.Next, n);
			break;
		case '2':
			if (n > 0)
				n = Pop(&S, n);
			PrintList(S.Next, n);
			break;
		
		case 'k':
			printf("\n");
			break;
		default:
			printf("\nTry again.\n");
		}
	}


}

int GetValueFromRange(int min, int max)
{
	int x = 0;

	x = rand() % (max - min) + min;

	return x;
}

int Push(Position P, int x, int n)
{
	static Position last;
	Position q;

	q = (Position)malloc(sizeof(struct _Node));
	if (q)
	{
		if (P->Next == NULL)
			last = q;

		q->Element = x;

		printf("\nSaving list %d.", x);
		q->Next = P->Next;
		P->Next = q;

		last->Next = q;
		n++;
	}
	return n;
}

int Pop(Position P, int n)
{
	static Position last = NULL;
	Position tmp;

	if (P->Next != NULL)
	{

		tmp = P->Next;

		printf("\nDownloading from list %d.", tmp->Element);

		P->Next = tmp->Next;

		if (last == NULL && n > 1)
		{
			while (P->Next != tmp)
				P = P->Next;
			last = P;
		}

		last->Next = tmp->Next;

		free(tmp);
		n--;
		if (n == 0)
			last = NULL;
	}
	else
		printf("\nList is empty.");

	return n;
}

void PrintList(Position P, int n)
{
	printf("\nList contains %d elements:\n", n);
	while (n > 0)
	{
		printf(" %d", P->Element);
		P = P->Next;
		n--;
	}
}
