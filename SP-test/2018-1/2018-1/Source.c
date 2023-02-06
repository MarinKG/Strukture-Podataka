#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct _stablo;
typedef struct _stablo* Tree;
typedef struct _stablo {
	Tree left, right;
	char grad[100];

}Grad;

struct _list;
typedef struct _list* List;
typedef struct _list {
	int id;
	char drzava[100];
	Tree gradovi;
	List next;
}Drzava;

int insertList(List P, char *drzava, int id);
int printlist(List P);
List findCountry(List P,int id);
Tree insertTree(Tree T, char* grad);
int inorder(Tree T);

int main() {
	FILE* drzave=NULL, * gradovi=NULL;
	List find=NULL;
	List head = NULL;
	int id = 0, provjera = 0;
	char drzava[100] = { '\0' };
	char grad[100] = { '\0' };
	head = (List)malloc(sizeof(Drzava));
	if (head == NULL) {
		printf("\nGreska pri alokaciji memorije");
		return -1;
	}
	head->next = NULL;
	drzave = fopen("drzave.txt", "r");
	gradovi = fopen("gradovi.txt", "r");
	if (gradovi == NULL || drzave == NULL) {
		printf("\nGreska pri otvaranju datoteke");
		return -1;
	}
	while (!feof(drzave)) {
		provjera=fscanf(drzave, " %s %d", drzava, &id);
		if (provjera == 2) {
			insertList(head, drzava, id);
		}
	}
	while (!feof(gradovi)) {
		provjera = fscanf(gradovi, " %d %s", &id, grad);
		if (provjera == 2) {


			find=findCountry(head, id);
			printf("%s", find->drzava);
			find->gradovi = insertTree(find->gradovi, grad);


		}
	}
	printf("\nUnesite id drzave:");
	provjera = scanf(" %d", &id);
	if (provjera == 1) {
		find = findCountry(head, id);

		if (find == NULL)
		{
			printf("drzava ne postoji");
			return -1;
		}
		inorder(find->gradovi);
	}
	printlist(head->next);
}

int insertList(List P, char* drzava, int id) {
	List r=P, q=NULL;
	while (r->next != NULL && strcmp(r->next->drzava,drzava) < 0)
		r = r->next;
	q = (List)malloc(sizeof(Drzava));
	if (q == NULL) {
		printf("\nGreska pri alokaciji memorije");
		return -1;
	}
	q->id = id;
	strcpy(q->drzava, drzava);
	q->gradovi = NULL;
	q->next = r->next;
	r->next = q;
	return 0;
}

int printlist(List P) {
	while (P != NULL)
	{
		printf("\n%s %d", P->drzava, P->id);
		P = P->next;
	}
	return 0;
}

List findCountry(List P, int id) {
	List r = P;
	while (r->next != NULL && id != r->next->id) {
		r = r->next;
	}
	if (r == NULL)
		return NULL;
	return r->next;
}

Tree insertTree(Tree T, char* grad) {
	if (T == NULL) {
		T = (Tree)malloc(sizeof(Grad));
		if (T == NULL) {
			printf("\nGreska pri alokaciji memorije");
			return NULL;
		}
		strcpy(T->grad, grad);
		T->left =  NULL;
		T->right = NULL;
	}
	else if (strcmp(grad, T->grad) < 0) {
		T->left = insertTree(T->left, grad);
	}
	else if (strcmp(grad, T->grad) > 0) {
		T->right = insertTree(T->right, grad);
	}
	return T;
}

int inorder(Tree T) {

	if (T == NULL)
		return 0;
	inorder(T->left);
	printf("\n%s", T->grad);
	inorder(T->right);

	return 0;

}