#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
struct _broj;
typedef struct _broj* List;
typedef struct _broj {
	List next;
	unsigned int broj;
}Broj;

int insert(List P, unsigned int broj);
List formiraj(List L1, List L2);
int unija(List P, List L1);
int printList(List P);

int main() {
	srand((unsigned int)time(NULL));
	unsigned int broj = 0;
	char buffer[100] = { '\0' };
	char* p = buffer;
	int provjera = 0;
	int i = 0,n=0;
	List head1 = NULL, head2=NULL, head3=NULL;
	FILE* f1 = NULL, * f2 = NULL;
	f1 = fopen("dat1.txt", "w+");
	f2 = fopen("dat2.txt", "w+");
	if (f1 == NULL || f2 == NULL) {
		printf("\nGreska pri otvaranjue filea");
		return -1;
	}
	head1 = (List)malloc(sizeof(Broj));
	head2 = (List)malloc(sizeof(Broj));
	if (head1 == NULL|| head2 == NULL) {
		printf("\nGreska pri alokaciji memorije");
		return -1;
	}
	head1->next = NULL;
	head2->next = NULL;
	for (int i = 0; i < 10; i++) {
		broj = rand() % (35 - 25 + 1) + 25;
		fprintf(f1, "%d ", broj);
	}
	for (int i = 0; i < 10; i++) {
		broj = rand() % (35 - 25 + 1) + 25;
		fprintf(f2, "%d ", broj);
	}
	rewind(f1);
	rewind(f2);
	while (!feof(f1)) {
		provjera = fscanf(f1, " %d", &broj);

		if (provjera == 1) {
			insert(head1, broj);
		}
	}
	while (!feof(f2)) {
		provjera = fscanf(f2, " %d", &broj);

		if (provjera == 1) {
			insert(head2, broj);
		}
	}
	head3 = formiraj(head1, head2);
	printList(head1->next);
	printf("\n");
	printList(head2->next);
	printf("\nPresjek");

	printList(head3->next);
	return 0;
}

int insert(List P, unsigned int broj) {
	List r = P, q = NULL;
	while (r->next != NULL && broj > r->next->broj) {
		r = r->next;
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

List formiraj(List L1, List L2)
{
	List L3 = NULL;
	L3 = malloc(sizeof(Broj));
	if (L3 == NULL) {
		printf("\nGreska pri alokaciji memorije");
		return -1;
	}
	L3->next = NULL;
	while (L1->next != NULL && L2->next != NULL) {
		if (L1->next->broj == L2->next->broj) {

			if (L1->next->broj % 2 == 0) {
				presjek(L3, L1);
			}
			L1 = L1->next;
			L2 = L2->next;
		}
		else if (L1->next->broj > L2->next->broj) {
			L2 = L2->next;
		}
		else if (L1->next->broj < L2->next->broj){
			L1 = L1->next;
		}
		else if (L1->next == NULL) {
			L2 = L2->next;
		}
		else if (L2->next == NULL) {
			L1 = L1->next;
		}
	}
	return L3;
}

int presjek(List P, List L1) {
	List q = L1, r = P;
	while (r->next != NULL) {
		if (r->next->broj == q->next->broj)
			return 1;
		r = r->next;
	}
	r->next = L1->next;
	L1->next = L1->next->next;
	r->next->next = NULL;

	return 0;

}

int printList(List P) {
	while (P != NULL) {
		printf(" %d ", P->broj);
		P = P->next;
	}
	return 0;
}