#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct _list;
typedef struct _list* List;
typedef struct _list {
	char rijec[100];
	List next;
}kopija;

struct _tree;
typedef struct _tree* Tree;
typedef struct _tree {
	char rijec[100];
	List head;
	Tree left, right;
	unsigned int broj_kopija;
}Rijec;
Tree findWord(Tree T, char* rijec);
Tree insert(Tree T, char* rijec);
int insertList(List P, char* rijec);
int main() {
	int provjera=0;
	char rijec[100] = { '\0' };
	Tree Root = NULL;
	Tree find = NULL;
	FILE* file = fopen("text.txt", "r");
	if (file == NULL) {
		printf("\nGreska pri otvaranju datoteke");
		return -1;
	}
	while (!feof(file)) {
		provjera = fscanf(file, " %s", rijec);
		if (provjera == 1) {
			Root = insert(Root, rijec);
		}
	}
	printf("\nUnesi rijec:");
	scanf(" %s", rijec);
	find = findWord(Root, rijec);
	if (find == NULL) {
		printf("\nRijec ne postoji");
		return -1;
	}
	printf("\nRijec %s se ponavlja %d puta", rijec, find->broj_kopija+1);

	return 0;
}

Tree insert(Tree T, char* rijec) {
	if (T == NULL) {
		T = (Tree)malloc(sizeof(Rijec));
		if (T == NULL) {
			printf("\nGreska pri alokaciji memorije");
			return -1;
		}
		strcpy(T->rijec, rijec);
		T->broj_kopija = 0;
		T->left = T->right = NULL;
		T->head = (List)malloc(sizeof(kopija));
		if (T->head == NULL) {
			printf("\nGreska pri alokaciji memorije");
			return -1;
		}
		T->head->next = NULL;
	}
	else if (strcmp(rijec, T->rijec) < 0) {
		T->left = insert(T->left, rijec);
	}
	else if (strcmp(rijec, T->rijec) > 0) {
		T->right = insert(T->right, rijec);
	}
	else {
		T->broj_kopija++;
		insertList(T->head, T->rijec);
	}
	return T;
}

int insertList(List P, char* rijec) {
	List r = P, q = NULL;
	while (r->next != NULL) {
		r = r->next;
	}
	q = (List)malloc(sizeof(kopija));
	if (q == NULL) {
		printf("\nGreska pri alokaciji memorije");
		return -1;
	}
	strcpy(q->rijec, rijec);
	q->next = r->next;
	r->next = q;
	return 0;
}

Tree findWord(Tree T, char* rijec) {
	if (T == NULL)
		return T;
	if (strcmp(rijec, T->rijec) < 0) {
		return(findWord(T->left, rijec));
	}
	if (strcmp(rijec, T->rijec) > 0) {
		return(findWord(T->right, rijec));
	}
	return T;

}