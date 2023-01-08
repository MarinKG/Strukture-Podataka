#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>

/*Zadan je niz brojeva 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 koji su spremljeni u èvorove binarnog stabla.
a) Napisati funkciju insert koja dodaje element u stablo tako da se pozivima te funkcije za
sve element zadanog niza brojeva stvori stablo kao na slici Slika 1. Funkcije vraæa
pokazivaè na korijen stabla.
b) Napisati funkciju replace koja æe svaki element stabla zamijeniti sumom elemenata u
njegovom lijevom i desnom podstablu (tj. sumom svih potomaka prije zamjene
vrijednosti u tim potomcima). Npr. stablo sa slike Slika 1 transformirat æe se u stablo na
slici Slika 2.
c) Prepraviti program na naèin da umjesto predefiniranog cjelobrojnog polja korištenjem
funkcije rand() generira sluèajne brojeve u rasponu <10, 90>. Takoðer, potrebno je
upisati u datoteku sve brojeve u inorder prolasku nakon korištenja funkcije iz a), zatim b)
dijela zadatka.*/

struct _tree;
typedef struct _tree* Poz;

typedef struct _tree
{
	int element;
	Poz left;
	Poz right;

}tree;

struct _stack;
typedef struct _stack* Pozicija;
typedef struct _stack {
	int element;
	Pozicija next;
}stack;

int pop(Pozicija P);
int push(int x, Pozicija P);
Poz delete(int x, Poz T);
Poz find(int x, Poz T);
int inorder(Poz T);
int preorder(Poz T);
int postorder(Poz T);
Poz insert(int x, Poz T);
Poz find_min(Poz T);
int print(Poz T);
int delete_all(Poz T);
int print_stack(Pozicija P);
int delete_stack(Pozicija P);
int replace(Poz T);
int calculate_sum(Poz T);
int napravi_inorder_listu(Poz T, Pozicija P);
int inorder_datoteka(char* datoteka, Pozicija P);

int main()
{
	srand((unsigned)time(NULL));
	int provjera = 0;
	int element = 0;
	char opcija = '\0';
	char datoteka[100] = {'\0'};
	Poz Root = NULL;
	Poz nadi = NULL;
	Pozicija head = NULL;
	head = (Pozicija)malloc(sizeof(stack));
	if (head == NULL)
	{
		printf("Greska pri alokaciji memorije");
		return -1;
	}
	head->next = NULL;	
	while (toupper(opcija) != 'X')
	{
		printf("\nA- ubaci clan"
			"\nB- inorder ispis"
			"\nC- preorder ispis"
			"\nD- postorder ispis"
			"\nE- izbrisi clan"
			"\nF- nadi clan"
			"\nG- zamijeni s sumom listova"
			"\nH- ubaci nasumican clan u rasponu od 10 do 90"
			"\nI- inorder ispis u datoteku"
			"\nX- izadi iz programa\n");
		provjera = scanf(" %c", &opcija);
		if (provjera == 1)
		{
			switch (toupper(opcija))
			{
			case 'A':
				printf("\nUnesi vrijednost clana:\n");
				provjera = scanf(" %d", &element);
				if (provjera == 1) {
					Root = insert(element, Root);
				}
				break;
			case 'B':
				inorder(Root);
				break;
			case 'C':
				preorder(Root);
				break;
			case 'D':
				postorder(Root);
				break;
			case 'E':
				printf("\nUnesite vrijednost elementa kojeg zelite obrisati:\n");
				provjera = scanf(" %d", &element);
				if (provjera == 1) {
					delete(element, Root);
				}
				break;
			case 'F':
				printf("\nUnesite vrijednost elementa kojeg zelite naci:\n");
				provjera = scanf(" %d", &element);
				if (provjera == 1) {
					nadi = find(element, Root);
					if (nadi != NULL)
						printf("\nElement s vrijednoscu %d se nalazi na memorijskoj lokaciji %p\n", element, nadi);
					else
						printf("\nElement s vrijednoscu %d ne postoji", element);
				}
				break;
			case 'G':
				replace(Root);
				break;
			case 'H':
				Root = insert((rand() % 80) + 10, Root);
				break;
			case 'I':
				napravi_inorder_listu(Root, head);
				printf("\nUnesite ime datoteke:");
				scanf(" %s", datoteka);
				inorder_datoteka(datoteka, head);

				delete_stack(head);
				break;
			case 'X':
				break;
			}
		}

	}
	delete_stack(head);

	free(head);
	delete_all(Root);
	return 0;
}

Poz insert(int x, Poz T)
{
	if (T == NULL)
	{
		T = (Poz)malloc(sizeof(tree));
		if (T == NULL)
		{
			printf("\nGreska pri alokaciji memorije\n");
			return NULL;
		}
		else
		{
			T->element = x;
			T->left = T->right = NULL;
		}

	}
	else if (x < T->element)
	{
		T->right = insert(x, T->right);
	}
	else if (x > T->element)
	{
		T->left = insert(x, T->left);
	}
	else if (x == T->element)
	{
		T->left = insert(x, T->left);
	}
	return T;
}

Poz find(int x, Poz T)
{
	if (T == NULL)
		return NULL;
	if (x < T->element)
		return(find(x, T->left));
	if (x > T->element)
		return(find(x, T->right));
	else
		return T;
}

Poz delete(int x, Poz T)
{
	Poz temp = NULL, child = NULL;
	if (T == NULL)
		printf("\nElement ne postoji");

	else if (x < T->element)
		T->left = delete(x, T->left);

	else if (x > T->element)
		T->right = delete(x, T->right);

	else if (T->left && T->right) {
		temp = find_min(T->right);
		T->element = temp->element;
		T->right = delete(T->element, T->right);
	}
	else
	{
		temp = T;
		if (T->left == NULL)
			child = T->right;
		if (T->right == NULL)
			child = T->left;
		free(temp);
		return child;
	}
	return T;
}

Poz find_min(Poz T)
{
	if (T != NULL)
		while (T->left != NULL)
			T = T->left;

	return T;
}

int print(Poz T)
{
	printf(" %d ", T->element);
	return 0;
}

int inorder(Poz T)
{
	if (T != NULL)
	{
		inorder(T->left);
		print(T);
		inorder(T->right);
	}
	return 0;
}

int preorder(Poz T)
{
	if (T != NULL)
	{
		print(T);
		preorder(T->left);
		preorder(T->right);
	}
	return 0;
}

int postorder(Poz T)
{
	if (T != NULL)
	{
		postorder(T->left);
		postorder(T->right);
		print(T);
	}
	return 0;
}

int print_stack(Pozicija P) {//ne koristi nicemu
	while (P != NULL) {
		printf(" %d ", P->element);
		P = P->next;
	}
	return 0;
}

int delete_stack(Pozicija P) {
	Pozicija prev = NULL, temp = NULL;
	while (P->next != NULL)
	{
		prev = NULL, temp = NULL;
		prev = P;
		temp = prev->next;
		prev->next = temp->next;
		free(temp);
	}
}


int delete_all(Poz T) {
	Poz temp = T;
	if (!temp)
		return -1;
	delete_all(temp->left);
	delete_all(temp->right);
	if (!temp->left && !temp->right) {
		free(temp);
		return 0;
	}
}

int push(int x, Pozicija P)
{
	Pozicija q = NULL;
	while (P->next != NULL) {
		P = P->next;
	}
	q = (Pozicija)malloc(sizeof(stack));
	if (q!=NULL) {
		q->element = x;
		P->next = q;
		q->next = NULL;
		return 0;
	}
	return -1;
}

int napravi_inorder_listu(Poz T, Pozicija P) {
	if (T != NULL) {
		napravi_inorder_listu(T->left, P);
		push(T->element, P);
		napravi_inorder_listu(T->right, P);
	}
	return 0;
}

int inorder_datoteka(char* datoteka, Pozicija P) {
	FILE* f = fopen(datoteka, "w");
	P = P->next;
	while (P != NULL) {
		fprintf(f, " %d ", P->element);
		P = P->next;
	}
	fclose(f);
	return 0;
}

int pop(Pozicija P) { //ne koristi nicemu
	Pozicija temp = NULL;
	while (P->next->next != NULL) {
		P = P->next;
	}
	temp = P->next;
	P->next = temp->next;
	free(temp);
	return 0;
}
int calculate_sum(Poz T) {
	int suma = 0;
	if (T->left == NULL && T->right == NULL) {
		return 0;
	}
	else if (T->left == NULL && T->right != NULL){
		suma = T->right->element + calculate_sum(T->right);
		printf("\n(nema livo)%d\n", suma);
		return suma;
	}
	else if (T->left != NULL && T->right == NULL) {
		suma = T->left->element + calculate_sum(T->left);
		printf("\n(nema desno)%d\n", suma);
		return suma;
	}
	else {
		suma = T->left->element + T->right->element + calculate_sum(T->left) + calculate_sum(T->right);
		printf("\n(ima oba)%d\n", suma);
		return suma;
	}
}

int replace(Poz T) {
	if (T == NULL) {
		return 0;
	}
	T->element=calculate_sum(T);
	replace(T->left);
	replace(T->right);
	return 0;
}
