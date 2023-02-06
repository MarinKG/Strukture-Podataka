#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct _broj;
typedef struct _broj* List;
typedef struct _broj {
	unsigned int broj;
	List next;
}Broj;

int insert(List P, int broj);
int findMax(List P);
int findMin(List P);
int urediListu(List P, unsigned int broj, int broj_vecih_od_srednje);
int ispisiListu(List P);
int izracunajBrojVecih(List P,int srednja);

int main() {
	srand((unsigned int)time(NULL));
	List head = NULL;
	unsigned int max = 0,min=0,broj=0,srednja=0,broj_vecih_od_srednje=0;
	head = (List)malloc(sizeof(Broj));
	if (head == NULL) {
		printf("\nGreska pri alokaciji memorije");
		return -1;
	}
	head->next = NULL;
	for (int i = 0; i < 15; i++) {
		broj = rand() % (120 - 100 + 1) + 100;
		printf("%d\n",broj);
		insert(head, broj);
	}
	ispisiListu(head->next);

	List P = head;
	max=findMax(head);
	min = findMin(head);
	srednja = (min + max) / 2;
	printf("\n\n%d %d %d\n", min, max,srednja);
	broj_vecih_od_srednje = izracunajBrojVecih(head,srednja);
	printf("\n%d\n", broj_vecih_od_srednje);
	urediListu(head, srednja, broj_vecih_od_srednje);
	ispisiListu(P->next);
	return 0;
}

int izracunajBrojVecih(List P,int srednja) {
	unsigned int brojac = 0;
	while (P->next != NULL) {
		P = P->next;
		if (P->broj >= srednja)
			brojac++;
	}
	return brojac;
}

int ispisiListu(List P) {
	while (P != NULL) {
		printf("%d ", P->broj);
		P = P->next;
	}
	return 0;
}

int urediListu(List P, unsigned int broj, int broj_vecih_od_srednje) {
	for (int i = 0; i < broj_vecih_od_srednje; i++)
	{
		List r = P, q = NULL, v = NULL;
		while (r->next != NULL && r->next->broj < broj) {
			r = r->next;
		}
		v=r;
		while (v->next != NULL) {
			v = v->next;
		}
		q = r->next;
		r->next = q->next;
		v->next = q;
		q->next = NULL;
	}
	return 0;
}

int findMin(List P) {
	List r = P;
	unsigned int min = r->next->broj;
	while (r->next != NULL) {
		if (r->next->broj < min) {
			min = r->next->broj;
		}
		r = r->next;
	}
	return min;
}

int findMax(List P) {
	List r = P;
	unsigned int max = r->next->broj;
	while (r->next != NULL) {
		if (r->next->broj > max) {
			max = r->next->broj;
		}
		r = r->next;
	}
	return max;
}

int insert(List P, int broj) {
	List q = NULL, r = P;
	while (r->next != NULL&&r->next->broj!=broj) {
		r = r->next;
	}
	if (r->next != NULL) {
		return 0;
	}
	q = (List)malloc(sizeof(Broj));
	if (q == NULL) {
		printf("\nGreska pri alokaciji memorije");
		return -1;
	}
	q->broj = broj;
	q->next = r->next;
	r->next = q;
	return 0;
}