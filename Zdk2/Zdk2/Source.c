#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//Definirati strukturu osoba(ime, prezime, godina roðenja) i napisati program koji :
//A.dinamièki dodaje novi element na poèetak liste,
//B.ispisuje listu,
//C.dinamièki dodaje novi element na kraj liste,
//D.pronalazi element u listi(po prezimenu),
//E.briše odreðeni element iz liste,
//U zadatku se ne smiju koristiti globalne varijable.

struct _osoba;
typedef struct _osoba* Pozicija;
typedef struct _osoba
{
	char ime[100];
	char prezime[100];
	int godina;
	Pozicija next;
}osoba;

int unos(int *god, char ime[], char prezime[]);
int unosP(int god, char *ime, char *prezime, Pozicija P);
int unosK(int god, char* ime, char* prezime, Pozicija P);
Pozicija trazi(char* prezime, Pozicija P);
int ispis(Pozicija P);
int brisi(char* prezime, Pozicija P);

int main()
{
	int godina = 0;
	char ime[100] = { "\0"};
	char prezime[100] = { "\0"};
	char trazi_prezime[100]={"\0"};
	osoba* head = NULL;
	head = (osoba*)malloc(sizeof(osoba));
	head->next = NULL;
	unos(&godina, ime, prezime);
	unosP(godina, ime, prezime, head);
	ispis(head->next);
	unos(&godina, ime, prezime);
	unosK(godina, ime, prezime, head);
	ispis(head->next);
	
	printf("\nUnesite prezime osobe koje trazite:");

	fflush(stdin);
	scanf("%s", trazi_prezime);
	printf("\nLokacija u memoriji gdje se clan nalazi:\n%p",trazi(trazi_prezime, head->next));
	
	printf("\nUnesite prezime osobe koje zelite obrisat:");
	fflush(stdin);
	scanf("%s", trazi_prezime);
	brisi(trazi_prezime, head);
	ispis(head->next);
	return 0;

}

int unos(int *god, char ime[], char prezime[])
{
	int provjera = 0;
	printf("Unesite ime osobe: ");
	provjera=scanf(" %[^\n]s", ime);

	if (provjera == 1)
	{
		printf("\nUnesite prezime osobe: ");
		provjera=scanf(" %[^\n]s", prezime);
		if (provjera == 1)
		{
			printf("\nUnesite godinu rodenja osobe: ");
			provjera=scanf(" %d", god);
			fflush(stdin);
			if (provjera == 1)
			{
				return 0;
			}
			else
			{
				printf("\nPogreska pri unosu");
				exit(-1);
			}
		}
		else
		{
			printf("\nPogreska pri unosu");
			exit(-1);
		}
	}
	else
	{
		printf("\nPogreska pri unosu");
		exit(-1);
	}
}
int unosP(int god, char *ime, char *prezime, Pozicija P)
{
	Pozicija q;
	q = (Pozicija)malloc(sizeof(osoba));
	q->godina = god;
	strcpy(q->ime, ime);
	strcpy(q->prezime, prezime);
	q->next = P->next;
	P->next = q;
	return 0;
}

int ispis(Pozicija P)
{
	while(P!=NULL)
	{
		printf("\n%s\t %s\t %d\n",P->ime,P->prezime,P->godina);
		P = P->next;
	}
	return 0;
}

int unosK(int god, char* ime, char* prezime, Pozicija P)
{
	Pozicija q;
	while (P->next != NULL)
	{
		P = P->next;
	}
	q = (Pozicija)malloc(sizeof(osoba));
	q->godina = god;
	strcpy(q->ime, ime);
	strcpy(q->prezime, prezime);
	P->next = q;
	q->next = NULL;
	return 0;
}

Pozicija trazi(char* prezime, Pozicija P)
{
	while ((P != NULL) && (strcmp(P->prezime, prezime)!=0))
	{
		P = P->next;
	}
	return P;
}

int brisi(char* prezime, Pozicija P)
{
	Pozicija prev, temp;
	while (P->next != NULL && strcmp(P->next->prezime, prezime) != 0)
	{
		P = P->next;
	}
	if (P->next == NULL)
	{
		return NULL;
	}
	else
	{
		prev = P;
		temp = prev->next;
		prev->next = prev->next->next;
		free(temp);
		return 0;
	}
}