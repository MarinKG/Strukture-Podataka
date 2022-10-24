#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct _osoba;
typedef struct _osoba* Pozicija;
typedef struct _osoba
{
	char ime[100];
	char prezime[100];
	int godina;
	Pozicija next;
}osoba;


int unesi_osobu(int* god, char ime[], char prezime[]);
int unos_pocetak(int god, char* ime, char* prezime, int* broj_osoba, Pozicija P);
int unos_kraj(int god, char* ime, char* prezime, int* broj_osoba, Pozicija P);
Pozicija trazi_osobu(char* prezime, Pozicija P);
int ispisi_listu(Pozicija P);
int brisi_osobu(char* prezime, int* broj_osoba, Pozicija P);

int main()
{
	int godina = 0;
	int broj_osoba = 0;
	int provjera = 0;
	char ime[100] = { NULL };
	char prezime[100] = { NULL };
	char trazi_prezime[100] = { NULL };
	char opcija = '\0';
	osoba* head = NULL;
	head = (osoba*)malloc(sizeof(osoba));
	head->next = NULL;

	while (opcija!='X')
	{
		
		printf("Lista ima %d clanova.\n", broj_osoba);
		printf("Pritisnite:\n P-unos na pocetak liste\n K-unos na kraj liste\n T-ispisuje memorijsku lokaciju elementa liste\n B-brisanje clana liste\n I-ispisuje listu\n X-ugasi program\n");
		provjera=scanf(" %c", &opcija);
		if (provjera != 1)
		{
			printf("\nPogreska pri unosu");
			exit(-1);
		}
		opcija = toupper(opcija);
		switch (opcija)
		{
		case 'P':
			unesi_osobu(&godina, ime, prezime);
			unos_pocetak(godina, ime, prezime, &broj_osoba, head);
			break;
		case 'K':
			unesi_osobu(&godina, ime, prezime);
			unos_kraj(godina, ime, prezime, &broj_osoba, head);
			break;
		case 'T':
			printf("\nUnesite clana liste\n");
			provjera = scanf(" %s", trazi_prezime);
			if (provjera != 1)
			{
				printf("\nPogreska pri unosu");
				exit(-1);
			}
			printf("\nClan liste se nalazi na poziciji %p\n",trazi_osobu(trazi_prezime, head->next));
			break;
		case 'B':
			printf("\nUnesite clana liste kojeg zelite obrisati\n");
			provjera = scanf(" %s", trazi_prezime);
			if (provjera != 1)
			{
				printf("\nPogreska pri unosu");
				exit(-1);
			}
			fflush(stdin);
			brisi_osobu(trazi_prezime, &broj_osoba, head);
			break;
		case 'I':
			ispisi_listu(head->next);
			break;
		case 'X':
			break;
		default:
			printf("\nKrivo unesen znak\n");
			break;
		}
		
	}
	return 0;

}

int ispisi_listu(Pozicija P)
{
	while (P != NULL)
	{
		printf("\nIME: %s\tPREZIME: %s\t GODINA_RODENJA: %d\n", P->ime, P->prezime, P->godina);
		P = P->next;
	}
	return 0;
}

Pozicija trazi_osobu(char* prezime, Pozicija P) 
{
	while ((P != NULL) && (strcmp(P->prezime, prezime) != 0))
	{
		P = P->next;
	}
	return P;
}

int brisi_osobu(char* prezime, int* broj_osoba, Pozicija P)
{
	Pozicija prev=NULL, temp=NULL;
	while (P->next != NULL && strcmp(P->next->prezime, prezime) != 0)
	{
		P = P->next;
	}
	if (P->next == NULL)
	{
		printf("\nClan %s nije u listi\n",prezime);
		return NULL;
	}
	else
	{
		prev = P;

		temp = prev->next;
		prev->next = prev->next->next;
		free(temp);
		(* broj_osoba)--;
		return 0;
	}
}

int unesi_osobu(int* god, char ime[], char prezime[])
{
	int provjera = 0;
	printf("Unesite ime osobe: ");
	provjera = scanf(" %[^\n]s", ime);
	
	if (provjera != 1)
	{
		printf("\nPogreska pri unosu");
		exit(-1);
	}
	printf("\nUnesite prezime osobe: ");
	provjera = scanf(" %[^\n]s", prezime);
	if (provjera != 1)
	{
		printf("\nPogreska pri unosu");
		exit(-1);
	}
	printf("\nUnesite godinu rodenja osobe: ");
	provjera = scanf(" %d", god);
	if (provjera != 1)
	{
		printf("\nPogreska pri unosu");
		exit(-1);
	}
	return 0;
}

int unos_pocetak(int god, char* ime, char* prezime, int* broj_osoba, Pozicija P)
{
	Pozicija q;
	q = (Pozicija)malloc(sizeof(osoba));
	q->godina = god;
	strcpy(q->ime, ime);
	strcpy(q->prezime, prezime);
	q->next = P->next;
	P->next = q;
	(* broj_osoba)++;
	return 0;
}

int unos_kraj(int god, char* ime, char* prezime, int* broj_osoba, Pozicija P)
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
	(* broj_osoba)++;
	return 0;
}