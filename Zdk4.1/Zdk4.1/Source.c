#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
//4. Napisati program za zbrajanje i množenje polinoma.Koeficijenti i eksponenti se
//èitaju iz datoteke.
//Napomena: Eksponenti u datoteci nisu nužno sortirani.

#define MAX_LINE 200

struct _polinom;
typedef struct _polinom* Pozicija;
typedef struct _polinom
{
	int coef;
	int exp;
	Pozicija next;
}polinom;

int izbroji_polinome( char *ime_datoteke);
int ispisi_listu(Pozicija P);
int brisi_sve(Pozicija P);
int ucitaj_listu(char* ime_datoteke, int broj_polinoma, Pozicija *P);
int sortirani_unos(int coef, int exp, Pozicija P);//editat
int brisi_clan(Pozicija P);
Pozicija trazi_clan(Pozicija P);
Pozicija zbroji(Pozicija P1, Pozicija P2, Pozicija P3);
Pozicija mnozi(Pozicija P1, Pozicija P2, Pozicija P4);


int main()
{
	Pozicija* head_polinomi;
	Pozicija head_mnozi = (Pozicija)malloc(sizeof(polinom));
	Pozicija head_zbroji = (Pozicija)malloc(sizeof(polinom));
	int br_polinoma = 0;
	char ime_datoteke[MAX_LINE] = { '\0' };
	printf("Unesite ime datoteke:\n");
	scanf("%s", ime_datoteke);
	head_mnozi->next = NULL;
	head_zbroji->next = NULL;
	br_polinoma=izbroji_polinome( ime_datoteke);
	head_polinomi = (Pozicija*)malloc(sizeof(Pozicija));
	if (head_zbroji == NULL || head_mnozi == NULL)
	{
		return -1;
	}
	printf("%d", br_polinoma);
	
	ucitaj_listu(ime_datoteke,br_polinoma, head_polinomi);
	ispisi_listu(&head_polinomi[0]->next);

	return 0;
}

int ispisi_listu(Pozicija P)
{
	while (P->next != NULL)
	{
		printf("test");
		if (P->exp == 0)
		{
			printf("%d", P->coef);
		}
		else if (P->exp == 1)
		{
			printf("%dx", P->coef);
		}
		else
		{
			printf("%dx^%d", P->coef, P->exp);
		}
		if (P->next != NULL)
		{
			printf(" + ");

		}
		P = P->next;
	}
	printf("\n");
	return 0;
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

int ucitaj_listu(char* ime_datoteke, int broj_polinoma, Pozicija* P)
{
	FILE* file = fopen(ime_datoteke, "r");
	if (file == NULL)
	{
		printf("Datoteka %s se nije mogla otvoriti!\r\n", ime_datoteke);
		return -1;
	}
	P = (Pozicija*)calloc(broj_polinoma, sizeof(Pozicija));
	for (int i = 0; i < broj_polinoma; i++)
	{
		Pozicija q;
		q = (Pozicija)malloc(sizeof(polinom));
		if (q == NULL)
		{
			printf("greska\n");
		}
		P[i]->next = q;
		printf("%p\n", P[i]->next);
		q->next = NULL;
		int i = 0;
		int provjera = 0;
		char buffer[MAX_LINE] = { '\0' };
		char* p = buffer;
		int exp = 0;
		int coef = 0;
		int n = 0;
		
		if (P[i] == NULL)
		{
			printf("greska\n");
		}
		if (fgets(p, MAX_LINE, file) != NULL)
		{
			while (!feof(file))
			{
				while (strlen(p) > 0)
				{
					if (sscanf(p, "%d %d %n", &coef, &exp, &n) == 2)
					{
						printf("%d %d \n", coef, exp);

						if (coef != 0)
						{
							sortirani_unos(coef, exp, q);
						}
					}
					p = p + n;
				}
			}
		}
		else
		{
			return -1;
		}
		printf("\n\n%d", i);
	}
		fclose(file);
	return 0;
}

int brisi_clan(Pozicija P)
{
	Pozicija prev = NULL, temp = NULL;
	P = trazi_clan(P);
	if (P->next == NULL)
	{
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


Pozicija trazi_clan(Pozicija P)
{
	while ((P->next != NULL) && (P->next->coef != 0))
	{
		P = P->next;
	}
	return P;
}

int sortirani_unos(int coef, int exp, Pozicija P)
{
	Pozicija q;

	while ((P->next != NULL) && (P->next->exp <= exp))
	{
		P = P->next;
	}

	if (P->exp != exp)
	{
		q = (Pozicija)malloc(sizeof(polinom));
		if (q != NULL)
		{
			q->coef = coef;
			q->exp = exp;
			q->next = P->next;
			P->next = q;
			printf("%d %d\n", q->coef,q->exp);
			return 0;
		}
	}
	else
	{
		P->coef = P->coef + coef;
		if (P->coef == 0)
		{
			brisi_clan(P->next);
		}
	}
	return -1;
}

/*Pozicija zbroji(Pozicija P1, Pozicija P2, Pozicija P3)
{
	while ((P1->next != NULL) && (P2->next != NULL))
	{
		if (P1->next->exp == P2->next->exp)
		{
			if ((P1->next->coef + P2->next->coef) != 0)
			{
				sortirani_unos((P1->next->coef + P2->next->coef), P1->next->exp, P3);
			}
			P1 = P1->next;
			P2 = P2->next;
		}
		else if (P1->next->exp > P2->next->exp)
		{
			sortirani_unos(P2->next->coef, P2->next->exp, P3);
			P2 = P2->next;
		}
		else
		{
			sortirani_unos(P1->next->coef, P1->next->exp, P3);
			P1 = P1->next;
		}
	}
	if (P1->next == NULL)
	{
		while (P2 != NULL)
		{
			sortirani_unos(P2->coef, P2->exp, P3);
			P2 = P2->next;

		}
	}
	else if (P2->next == NULL)
	{
		while (P1 != NULL)
		{
			sortirani_unos(P1->coef, P1->exp, P3);
			P1 = P1->next;

		}
	}
	else
	{
		return;
	}
}

Pozicija mnozi(Pozicija P1, Pozicija P2, Pozicija P4)
{
	Pozicija start = P2;
	while (P1->next != NULL)
	{
		P2 = start;
		while (P2->next != NULL)
		{
			sortirani_unos(P1->next->coef * P2->next->coef, P1->next->exp + P2->next->exp, P4);
			P2 = P2->next;
		}
		P1 = P1->next;
	}
	return;
}*/

int izbroji_polinome(char*ime_datoteke)
{
	int i = 0;
	char buffer[200] = { '\0' };
	FILE* f = fopen(ime_datoteke, "r");
	if (f != NULL)
	{
		while (!feof(f))
		{
			if (fgets(buffer, MAX_LINE, f)!=NULL)
			{
				if (buffer[0] != '\n')
				{
					i++;
				}
			}
		}
	}
	fclose(f);
	return i;
}