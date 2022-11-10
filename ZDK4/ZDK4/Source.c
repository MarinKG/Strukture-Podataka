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

int ispisi_listu(Pozicija P);
int brisi_sve(Pozicija P);
int ucitaj_listu(Pozicija P);
int sortirani_unos(int coef, int exp, Pozicija P);//editat
int brisi_clan(Pozicija P);
Pozicija trazi_clan(Pozicija P);
Pozicija zbroji(Pozicija P1, Pozicija P2, Pozicija P3);
Pozicija mnozi(Pozicija P1, Pozicija P2, Pozicija P4);


int main()
{
	polinom* head1;
	polinom* head2;
	polinom* head3;
	polinom* head4;

	head1 = (polinom*)malloc(sizeof(polinom));
	head1->next = NULL;
	head2 = (polinom*)malloc(sizeof(polinom));
	head2->next = NULL;
	head3 = (polinom*)malloc(sizeof(polinom));
	head3->next = NULL;
	head4 = (polinom*)malloc(sizeof(polinom));
	head4->next = NULL;
	ucitaj_listu(head1);
	ispisi_listu(head1->next);

	ucitaj_listu(head2);
	ispisi_listu(head2->next);

	zbroji(head1, head2, head3);
	ispisi_listu(head3->next);

	mnozi(head1, head2, head4);
	ispisi_listu(head4->next);

	brisi_sve(head1);
	free(head1);
	brisi_sve(head2);
	free(head2);
	brisi_sve(head3);
	free(head3);
	brisi_sve(head4);
	free(head4);
	return 0;
}

int ispisi_listu(Pozicija P)
{
	printf("\n");
	while (P != NULL)
	{

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

int ucitaj_listu(Pozicija P)
{
	int provjera = 0;
	char buffer[MAX_LINE] = { '\0' };
	char* p = buffer;
	int exp = 0;
	int coef = 0;
	int n = 0;
	printf("\nUnesite ime datoteke iz koje zelite ispisati listu:\n");

	char ime_datoteke[MAX_LINE] = { '\0' };
	provjera = scanf("%s", ime_datoteke);
	if (provjera == 1)
	{
		FILE* file = fopen(ime_datoteke, "r");
		if (file == NULL)
		{
			printf("Datoteka %s se nije mogla otvoriti!\r\n", ime_datoteke);
			return -1;
		}
		while (!feof(file))
		{

			if (fgets(p, MAX_LINE, file) != NULL)
			{
				while (strlen(p) > 0)
				{
					if (sscanf(p, "%d %d %n", &coef, &exp, &n) == 2)
					{
						p = p + n;
						if (coef != 0)
						{
							sortirani_unos(coef, exp, P);
						}
					}
				}
			}
			else
			{
				return -1;
			}
		}
		fclose(file);
	}
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
	Pozicija q=P;
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
			return 0;
		}
	}
	else
	{
		P->coef = P->coef + coef;
		if (P->coef == 0)
		{
			brisi_clan(q->next);
		}
	}
	return -1;
}

Pozicija zbroji(Pozicija P1, Pozicija P2, Pozicija P3)
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
}
