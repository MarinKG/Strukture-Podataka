#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct _broj;
typedef struct _broj* List;
typedef struct _broj {
	unsigned int broj;
	unsigned int redni_br;
	List next;
}Broj;

int insert(List P, unsigned int broj, unsigned int i);
int staviNaPocetak(List P, unsigned int redni_br);
int ispisiListu(List P);


int main() {
	srand((unsigned int)time(NULL));
	unsigned int broj = 0, i = 0;
	unsigned int niz[5] = { NULL };
	List head = NULL;
	int brojac = 0;
	head = (List)malloc(sizeof(Broj));
	if (head == NULL) {
		printf("\nGreska pri alokaciji memorije");
		return -1;
	}
	head->next = NULL;
	for (i = 0; i < 20; i++) {
		broj = rand() % (150 - 100 + 1) + 100;
		insert(head, broj, i);
	}
	i = 0;
	while (i < 5) {
		brojac = 0;
		broj = rand() % 20;
		for (int j = 0; j < 5; j++) {
			if (niz[j] != broj) {
				brojac++;
			}
		}
		if (brojac == 5) {
			niz[i] = broj;
			i++;
		}
	}
	for (int j = 0; j < 5; j++) {
		printf("\n%d", niz[j]);
	}
	for (int j = 0; j < 5; j++) {//pod a
		staviNaPocetak(head, niz[j]);
	}
	/*for (int j = 4; j >= 0; j--) {//pod b
		staviNaPocetak(head, niz[j]);
	}*/

	ispisiListu(head->next);
	return 0;
}

int ispisiListu(List P) {
	while (P != NULL) {
		printf("\n%d %d", P->broj, P->redni_br);
		P = P->next;
	}
	return 0;
}

int staviNaPocetak(List P, unsigned int redni_br) {
	List A = P, B = P, C = NULL, D = P->next;
	while (B->next != NULL && B->next->redni_br != redni_br) {
		B = B->next;
	}
	C = B->next;
	B->next = C->next;
	A->next = C;
	C->next = D;
	return 0;

}

int insert(List P, unsigned int broj, unsigned int i) {
	List q = NULL, r = P;
	while (r->next != NULL) {
		r = r->next;
	}
	q = (List)malloc(sizeof(Broj));
	if (q == NULL) {
		printf("\nGreska pri alokaciji memorije");
		return -1;
	}
	q->broj = broj;
	q->redni_br = i;
	q->next = r->next;
	r->next = q;
	return 0;
}