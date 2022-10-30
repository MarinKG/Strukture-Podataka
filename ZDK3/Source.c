#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
/*3. Prethodnom zadatku dodati funkcije :
A.dinamièki dodaje novi element iza odreðenog elementa,
B.dinamièki dodaje novi element ispred odreðenog elementa,
C.sortira listu po prezimenima osoba,
D.upisuje listu u datoteku,
E.èita listu iz datoteke.*/

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
int unos_pocetak(int god, char* ime, char* prezime,  Pozicija P);
int unos_kraj(int god, char* ime, char* prezime,  Pozicija P);
Pozicija trazi_osobu(Pozicija P);
int ispisi_listu(Pozicija P);
int brisi_osobu(Pozicija P);
int unos_nakon(int god, char* ime, char* prezime,   Pozicija P);
int brisi_sve(Pozicija P);
int unos_ispred(int god, char* ime, char* prezime, Pozicija P);
Pozicija trazi_pret(Pozicija P);
void sortiraj_listu(Pozicija P);
int ispisi_u_datoteku(Pozicija P);
int ucitaj_listu(Pozicija P);
int sortirani_unos(int god, char* ime, char* prezime, Pozicija P);

int main()
{
	int godina = 0;
	int provjera = 0;
	char ime[100] = { NULL };
	char prezime[100] = { NULL };
	char trazi_prezime[100] = { NULL };
	char opcija[100] = { '\0' };
	osoba* head = NULL;
	head = (osoba*)malloc(sizeof(osoba));
	head->next = NULL;

	while (opcija[0] != 'X')
	{
		printf(
			"Pritisnite:\n"
			"  A-unos na pocetak liste\n"
			"  B-unos na kraj liste\n"
			"  C-ispisuje memorijsku lokaciju elementa liste\n" 
			"  D-brisanje clana liste\n" 
			"  E-ispisuje listu\n" 
			"  F-dodati novi element nakon odredjenog clana\n"
			"  G-dodati novi element ispred odredjenog clana\n"
			"  H-sortiraj listu prema prezimenima osoba\n"
			"  I-upis liste u datoteku\n"
			"  J-izvlacenje liste iz datoteke\n"
			"  X-ugasi program\n");
		provjera = scanf(" %s", opcija);
		if (provjera != 1)
		{
			printf("\nPogreska pri unosu");
			return(-1);
		}
		opcija[0] = toupper(opcija[0]);
		switch (opcija[0])
		{
		case 'A':
			unos_pocetak(godina, ime, prezime, head);
			break;
		case 'B':
			unos_kraj(godina, ime, prezime,  head);
			break;
		case 'C':
			printf("\nClan liste se nalazi na poziciji %p\n", trazi_osobu(head->next));
			break;
		case 'D':
			brisi_osobu(head);
			break;
		case 'E':
			ispisi_listu(head->next);
			break;
		case 'F':
			unos_nakon(godina, ime, prezime, head->next);
			break;
		case 'G':
			unos_ispred(godina, ime, prezime, head);
			break;
		case 'H':
			sortiraj_listu(head);
			break;
		case 'I':
			sortiraj_listu(head);
			ispisi_u_datoteku(head->next);
			break;
		case 'J':
			ucitaj_listu(head);
			break;
		case 'X':
			brisi_sve(head);
			free(head);
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

Pozicija trazi_osobu(Pozicija P)
{
	int provjera = 0;
	char trazi_prezime[100] = { '\0' };
	printf("Unesite prezime osobe koju trazite: ");
	provjera = scanf(" %s", trazi_prezime);
	if (provjera != 1)
	{
		printf("\nPogreska pri unosu");
		return(NULL);
	}
	while ((P != NULL) && (strcmp(P->prezime, trazi_prezime) != 0))
	{
		P = P->next;
	}
	return P;
}

int brisi_osobu(Pozicija P)
{
	Pozicija prev = NULL, temp = NULL;
	P=trazi_osobu(P);
	if (P->next == NULL)
	{
		printf("\nClan nije u listi\n");
		return -1;
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

int unesi_osobu(int* god, char ime[], char prezime[])
{
	int scanf_provjera = 0;
	int provjera = 0;
	printf("Unesite ime osobe: ");
	scanf_provjera = scanf(" %[^\n]s", ime);
	if (scanf_provjera != 1)
	{
		printf("\nPogreska pri unosu");
		return provjera;
	}
	provjera++;
	printf("\nUnesite prezime osobe: ");
	scanf_provjera = scanf(" %[^\n]s", prezime);
	if (scanf_provjera != 1)
	{
		printf("\nPogreska pri unosu");
		return provjera;
	}
	provjera++;
	printf("\nUnesite godinu rodenja osobe: ");
	scanf_provjera = scanf(" %d", god);
	if (scanf_provjera != 1)
	{
		printf("\nPogreska pri unosu");
		return provjera;
	}
	provjera++;
	return provjera;
}

int unos_pocetak(int god, char* ime, char* prezime,  Pozicija P)
{
	int provjera=unesi_osobu(&god, ime, prezime);
	Pozicija q;
	if (provjera == 3)
	{
		q = (Pozicija)malloc(sizeof(osoba));
		q->godina = god;
		strcpy(q->ime, ime);
		strcpy(q->prezime, prezime);
		q->next = P->next;
		P->next = q;
	}
		return 0;
}

int unos_kraj(int god, char* ime, char* prezime,  Pozicija P)
{
	int provjera=unesi_osobu(&god, ime, prezime);
	Pozicija q;
	if (provjera == 3)
	{
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
	}
	return 0;
}

int unos_nakon(int god, char* ime, char* prezime,  Pozicija P)
{
	P=trazi_osobu(P);
	if (P == NULL)
	{
		printf("\nOsoba ne postoji\n");
		return -1;
	}
	int provjera = unesi_osobu(&god, ime, prezime);
	Pozicija q;
	if (provjera == 3)
	{
		q = (Pozicija)malloc(sizeof(osoba));
		q->godina = god;
		strcpy(q->ime, ime);
		strcpy(q->prezime, prezime);
		q->next = P->next;
		P->next = q;
		return 0;
	}
	return -1;
}

int brisi_sve(Pozicija P)
{
	while (P->next != NULL)
	{
		Pozicija prev = NULL, temp = NULL;
			prev = P;
			temp = prev->next;
			prev->next = temp->next;
			free(temp);
	}
	return 1;
}

int unos_ispred(int god, char* ime, char* prezime, Pozicija P)
{
	Pozicija q;
	P = trazi_pret(P);
	if (P == NULL)
	{
		printf("\nOsoba ne postoji\n");
		return -1;
	}
	int provjera = unesi_osobu(&god, ime, prezime);
	if (provjera == 3)
	{
		q = (Pozicija)malloc(sizeof(osoba));
		q->godina = god;
		strcpy(q->ime, ime);
		strcpy(q->prezime, prezime);
		q->next = P->next;
		P->next = q;
		return 0;
	}
}

Pozicija trazi_pret(Pozicija P)
{
	int provjera = 0;
	char trazi_prezime[100] = { '\0' };
	printf("Unesite prezime osobe koju trazite: ");
	provjera = scanf(" %s", trazi_prezime);
	if (provjera != 1)
	{
		printf("\nPogreska pri unosu");
		return(NULL);
	}
	while ((P->next != NULL)&& (strcmp(P->next->prezime, trazi_prezime) != 0))
	{
		P = P->next;
	}
	if (P->next == NULL)
	{
		return NULL;
	}
	else
	{
		return P;
	}
}

void sortiraj_listu(Pozicija P)
{
	Pozicija j, prev_j, temp, end;

	end = NULL;
	while (P->next != end)
	{
		prev_j = P;
		j = P->next;
		while (j->next != end)
		{
			if (strcmp(j->prezime, j->next->prezime) > 0)
			{
				temp = j->next;
				prev_j->next = temp;
				j->next = temp->next;
				temp->next = j;

				j = temp;
			}

			prev_j = j;
			j = j->next;
		}
		end = j;
	}
	return;
}

int ispisi_u_datoteku(Pozicija P)
{
	printf("\nUnesite ime datoteke u koju zelite ispisati listu:\n");
	
	char ime_datoteke[100] = { '\0' };
	scanf("%s", ime_datoteke);
	FILE* file=fopen(ime_datoteke, "w");
	if (file == NULL)
	{
		printf("Datoteka %s se nije mogla otvoriti!\r\n", ime_datoteke);
		return -1;
	}
	while (P != NULL)
	{
		fprintf(file,"\nIME: %s\tPREZIME: %s\t GODINA_RODENJA: %d\n", P->ime, P->prezime, P->godina);
		P = P->next;
	}
	fclose(file);
	return 0;
}

int ucitaj_listu(Pozicija P)
{
	int godina = 0;
	char ime[100] = { '\0' };
	char prezime[100] = { '\0' };
	int broj_neupisanih = 0;
	printf("\nUnesite ime datoteke iz koje zelite ispisati listu:\n");

	char ime_datoteke[100] = { '\0' };
	scanf("%s", ime_datoteke);
	FILE* file = fopen(ime_datoteke, "r");
	if (file == NULL)
	{
		printf("Datoteka %s se nije mogla otvoriti!\r\n", ime_datoteke);
		return -1;
	}
	while (!feof(file))
	{

		if (fscanf(file, "%s %s %d", ime, prezime, &godina) == 3)
		{
			sortirani_unos(godina, ime, prezime,P);
		}
		else
		{
			broj_neupisanih++;
		}
	}
	printf("\nBroj neuspjesno upisanih osoba: %d\n", (broj_neupisanih==0)  ? broj_neupisanih : broj_neupisanih-1);
	fclose(file);
	return 0;
}
int sortirani_unos(int god, char* ime, char* prezime, Pozicija P)
{
	Pozicija q;
	while (P->next != NULL && strcmp(P->next->prezime, prezime) < 0)
	{
		P = P->next;
	}
	q= (Pozicija)malloc(sizeof(osoba));
	q->godina = god;
	strcpy(q->ime, ime);
	strcpy(q->prezime, prezime);
	q->next = P->next;
	P->next = q;
	return 0;
}