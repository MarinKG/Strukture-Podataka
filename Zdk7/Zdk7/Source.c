#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
/*napisati program koji pomoću vezanih listi (stabala) predstavlja strukturu direktorija. Omogućiti unos novih direktorija i pod-direktorija,
ispis sadržaja direktorija i povratak u prethodni direktorij. Točnije program treba preko menija simulirati korištenje DOS naredbi:
1- "md", 2- "cd dir", 3- "cd..", 4- "dir" i 5- izlaz.*/
#define MAX_LINE 100


struct _stablo;
typedef struct _stablo* Pozicija;
typedef struct _stablo {
	char naziv[MAX_LINE];
	Pozicija sibling;
	Pozicija child;
}stablo;

struct _stog;
typedef struct _stog* Poz;
typedef struct _stog {
	Poz next;
	Pozicija direktorij;
}stog;

Pozicija sortirani_unos(Pozicija P, Pozicija q);
int brisi_sve(Pozicija p);
int unesi_podatke(Pozicija P);
int ispisi_direktorij(Pozicija P);
Pozicija ulazi(Pozicija P, Poz q);
Pozicija vrati(Poz q);
int obrisi_zadnjeg(Poz q);
int brisi_stog(Poz q);

int main()
{
	int opcija = 0;
	Poz head = NULL;
	Pozicija Root = NULL, current=NULL;
	Root = (Pozicija)malloc(sizeof(stablo));//dodat provjeru
	Root->sibling = NULL;
	Root->child = NULL;
	head = (Poz)malloc(sizeof(stog));
	head->next = NULL;
	current = Root;
	strcpy(Root->naziv, "C:");
	while (opcija != 5) {
		printf("Trenutacni direktorij: %s", current->naziv);
		printf("\nUnesite broj za:\n"
			"1-napraviti novi direktorij\n"//imamo
			"2-ulazi u direktorij\n"//
			"3-vraca se u prethodni direktorij\n"//
			"4-ispisuje sve datoteke u direktoriju\n"//imamo
			"5-izlazi iz programa\n");//imamo
		scanf(" %d", &opcija);
		switch (opcija) {
		case 1:
			unesi_podatke(current);
			break;
		case 2:
			current=ulazi(current, head);
			break;
		case 3:
			if (strcmp(current->naziv, Root->naziv) == 0)
			{
				printf("\nPrethodni direktorij ne postoji");

			}
			else {

				current = vrati(head);
				obrisi_zadnjeg(head);
			}
			break;
		case 4:
			ispisi_direktorij(current);
			break;
		case 5:
			break;
		default:
			printf("Krivo unesen broj");
			break;
		}
	}
	brisi_sve(Root);
	brisi_stog(head);

	return 0;
}

int brisi_sve(Pozicija p)
{
	if (p == NULL)
	{
		return 0;
	}

	brisi_sve(p->child);
	brisi_sve(p->sibling);
	free(p);
	return 0;
}

Pozicija sortirani_unos(Pozicija P, Pozicija q)
{
	if (P == NULL) {
		return q;
	}
	if (strcmp(P->naziv, q->naziv) > 0) {
		q->sibling= P;
		return q;
	}
	P->sibling = sortirani_unos(P->sibling, q);
	return P;
}

int unesi_podatke(Pozicija P)
{
	Pozicija r = P;
	Pozicija q=NULL;
	char naziv[MAX_LINE];
	printf("\nUnesite ime direktorija: ");
	scanf(" %s", naziv);

	q = (Pozicija)malloc(sizeof(stablo));//dodat provjeru
	q->sibling = NULL;
	q->child = NULL;
	strcpy(q->naziv, naziv);
	if (r->child == NULL)
	{
		r->child = q;
		return 0;
	}
	r->child=sortirani_unos(r->child, q);

	return 0;
}

int ispisi_direktorij(Pozicija P)
{
	Pozicija q;
	q = P->child;
	while (q != NULL)
	{
		printf("\n%s", q->naziv);
		q = q->sibling;
	}
	return 0;
}

Pozicija ulazi(Pozicija P, Poz q)
{
	Poz r=NULL;
	r = (Poz)malloc(sizeof(stog));
	r->direktorij = P;
	r->next = NULL;
	printf(" %s", r->direktorij->naziv);
	char naziv[MAX_LINE] = { '\0' };
	while (q->next != NULL)
	{
		q = q->next;
	}
	q->next = r;

	printf("\nUnesite naziv direktorija: ");
	scanf(" %s", naziv);
	P = P->child;
	while (P != NULL && strcmp(P->naziv, naziv) != 0)
	{
		P = P->sibling;
	}
	if (P == NULL)
	{
		printf("\ndirektorij ne postoji");
	}


	return P;
}


Pozicija vrati(Poz q)
{
	Poz P = q;
	while (P->next!= NULL)
	{
		P = P->next;

	}

	return P->direktorij;
}

int obrisi_zadnjeg(Poz q)
{
	Poz tmp = q, zadnji=NULL;
	while (tmp->next->next != NULL)
	{
		tmp = tmp->next;
	}
	zadnji = tmp->next;
	tmp->next = NULL;
	free(zadnji);
	return 0;
}

int brisi_stog(Poz q)
{
	while (q->next != NULL)
	{
		Poz prev = NULL, temp = NULL;
		prev = q;
		temp = prev->next;
		prev->next = temp->next;
		free(temp);
	}
	free(q);
	return 0;
}