#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

struct _red;
typedef struct _red* List;
typedef struct _red {
	unsigned int prioritet;
	char rijec[1024];
	List next;
}red;

int insert(List P, char* rijec, unsigned int prioritet);
int printlist(List P);

int main() {
	char rijec[1024] = { '\0' };
	int provjera = 0;
	List head = NULL;
	char c = '\0';
	FILE *prioritet1=NULL, *prioritet2=NULL;
	FILE *file = fopen("asdf.txt","r");
	if (file == NULL)
	{
		printf("\nGreska pri otvaranju ");
		return -1;
	}
	head = (List)malloc(sizeof(red));
	if (head == NULL)
	{
		printf("\nGreska pri alokaciji memorije");
		return -1;
	}
	head->next = NULL;
	while (!feof(file)) {
		provjera=fscanf(file, " %s", rijec);
		if (provjera == 1) {
			c = toupper(rijec[0]);
			if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
				insert(head, rijec, 1);
			}
			else
				insert(head, rijec, 2);
		}
	}
	prioritet1 = fopen("prioritet1.txt", "w");
	prioritet2 = fopen("prioritet2.txt", "w");
	List P = head->next;
	printlist(head->next);
	if (prioritet1 == NULL || prioritet2 == NULL)
	{
		printf("Greksa pri otvaranju filea\n");
		return -1;
	}
	while (P!=NULL&&P->prioritet != 2) {
		fprintf(prioritet2, "%s ", P->rijec);
		P = P->next;
	}
	while (P != NULL) {
		fprintf(prioritet1, "%s ", P->rijec);
		P = P->next;
	}

	return 0;
}

int insert(List P, char* rijec, unsigned int prioritet) {
	List q = NULL, r = P;
	while (r->next != NULL && prioritet > 1) {
		r = r->next;
	}
	
	q = (List)malloc(sizeof(red));
	if (q == NULL) {
		printf("\nGreska pri alokaciji memorije");
		return -1;
	}
	q->prioritet = prioritet;
	printf("\n%d", prioritet);
	strcpy(q->rijec, rijec);
	q->next = r->next;
	r->next = q;
	return 0;
}

int printlist(List P) {
	while (P != NULL) {
		printf("%s ", P->rijec);
		P = P->next;
	}
	return 0;
}