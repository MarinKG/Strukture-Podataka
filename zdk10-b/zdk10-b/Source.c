#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LINE 100


/*napisi prog koji cita file drzave.txt u kojoj su zapisana imena pojedinigh država i uz ta imena nalazi se naziv datotake koja drži gradove te države
* npr. Hrvatska hrv.txt.  primjer datoteke gradova: naziv_grada broj_stanovnika.
* a) formiraj sortiranu vezanu listu država po nazivu. Svaki èvor te liste sadrži stablo gradova sortirano prvo po broju stanovnika pa onda po imenu
*
* b) formiraj stablo država sortirano po nazivu. Svaki èvor stabla sadrži vezanu listu gradova sortiranu po broju stanovnika a zatim po nazivu
*/
//veci broj ide livo, manji desno 

struct _city;
typedef struct _city* Pozicija;
typedef struct _city
{
	Pozicija next;
	char naziv[MAX_LINE];
	int brStan;
}City;

struct _state;
typedef struct _state* Poz;
typedef struct _state {
	Poz left,right;
	Pozicija grad;
	char ime_filea[MAX_LINE];
	char naziv_drzave[MAX_LINE];
}State;


int delete_all(Poz T);
int delete_stack(Pozicija P);
char** ucitajDatoteku(char* datoteka, int broj);
int izbrojiBrojDrzava(char* datoteka);
int cityCompare(City* c, int broj_stanovnika, char* ime_grada);
int unesiGradove(Pozicija P, char* ime_datoteke);
Poz find(char* drzava, Poz T);
int ispisiVeceOd(Pozicija T, int broj);
int unesiGradSortirano(Pozicija P, char* ime_grada, int br_stanovnika);
Poz insert(char* drzava, char* ime_filea, Poz T);

int main() {
	char datoteka[MAX_LINE] = { '\0' };
	char** gradoviFile;
	int broj = 0,provjera=0;
	char drzava[MAX_LINE] = { '\0' };
	int br_stan = 0;
	Poz Root = NULL;
	Poz state = NULL;
	

	printf("\nUnesite naziv datoteke: ");
	provjera=scanf(" %s", datoteka);
	if (provjera != 1) {
		printf("\nGreska pri unosu");
		return -1;
	}
	broj = izbrojiBrojDrzava(datoteka);
	gradoviFile = ucitajDatoteku(datoteka, broj);
	for (int i = 0; i < broj * 2; i = i + 2) {
		Root=insert(gradoviFile[i], gradoviFile[i+1],Root);
	}
	printf("\nUnesite drzavu koju trazite: ");
	provjera=scanf(" %s", drzava);
	if (provjera != 1) {
		printf("\nGreska pri unosu");
		return -1;
	}
	state=find(drzava, Root);
	if (state == NULL) {
		printf("Drzava ne postoji\n");
		return -1;
	}

	printf("\nUnesite broj stanovnika: ");
	provjera=scanf(" %d", &br_stan);
	if (provjera != 1) {
		printf("\nGreska pri unosu");
		return -1;
	}
	ispisiVeceOd(state->grad, br_stan);

	delete_all(Root);
	return 0;

}

int ispisiVeceOd(Pozicija T, int broj) {
	while (T != NULL) {
		if (T->brStan > broj) {
			printf("\n %d %s\n", T->brStan, T->naziv);
		}
		T = T->next;

	}
	
	return 0;
}

Poz find(char* drzava, Poz T)
{
	if (T == NULL)
		return NULL;
	if (strcmp(T->naziv_drzave, drzava) > 0)
		return(find(drzava, T->left));
	if (strcmp(T->naziv_drzave, drzava) < 0)
		return(find(drzava, T->right));
	else
		return T;
}

int unesiGradove(Pozicija P, char* ime_datoteke) {
	Pozicija temp=NULL;
	FILE* file = NULL;
	char ime_grada[MAX_LINE] = { '\0' };
	int br_stanovnika = 0,provjera=0;

	file = fopen(ime_datoteke, "r");
	if (file == NULL) {

		printf("Greska pri otvaranju filea\n");
		return -1;
	}
	while (!feof(file))
	{
		temp = P;
		provjera=fscanf(file, " %s %d ", ime_grada, &br_stanovnika);
		if (provjera == 2) {
			printf("%s %d\n", ime_grada, br_stanovnika);
			unesiGradSortirano(temp, ime_grada, br_stanovnika);
		}
	}
	fclose(file);
	return 0;
}

int unesiGradSortirano(Pozicija P, char*ime_grada, int br_stanovnika ) {
	Pozicija q = NULL;
	while (P->next != NULL && cityCompare(P,br_stanovnika,ime_grada) < 0) {
		P = P->next;
	}
	q = (Pozicija)malloc(sizeof(City));
	if (q == NULL)
	{
		printf("Greska pri alokaciji memorije");
		return -1;
	}
	strcpy(q->naziv, ime_grada);
	q->brStan = br_stanovnika;
	q->next = P->next;
	P->next = q;
	return 0;
}

int cityCompare(City* c, int broj_stanovnika, char* ime_grada)
{
	int result = 0;
	result = c->brStan - broj_stanovnika;
	if (result == 0)
	{
		result = strcmp(c->naziv, ime_grada);
	}
	return result;
}


int izbrojiBrojDrzava(char* datoteka) {
	int broj = 0, provjera=0;
	char buffer[MAX_LINE] = { '\0' };
	FILE* file = fopen(datoteka, "r");
	if (file == NULL) {
		printf("\nGreska pri otvaranju datoteke");
		return -1;
	}
	while (!feof(file)) {
		provjera=fscanf(file, " %[^\n]", buffer);
		if (provjera == 1) {
			if (strcmp(buffer, "\n") != 0) {
				broj++;
			}
		}
	}
	fclose(file);
	return broj;
}

char** ucitajDatoteku(char* datoteka, int broj) {
	FILE* file = fopen(datoteka, "r");
	char** gradoviFile = NULL;
	int i = 0, provjera=0;
	if (file == NULL) {
		printf("\nGreska pri otvaranju datoteke");
		return NULL;
	}
	gradoviFile = (char**)malloc(sizeof(char*) * (broj * 2));
	if (gradoviFile == NULL) {

		printf("\nGreska\n");
		return NULL;
	}
	for (int i = 0; i < broj * 2; i++) {
		gradoviFile[i] = (char*)malloc(sizeof(char) * MAX_LINE);
	}
	while (!feof(file)) {
		provjera=fscanf(file, " %s %s ", gradoviFile[i], gradoviFile[i + 1]);
		if (provjera == 2) {
			i = i + 2;
		}
	}
	fclose(file);
	return gradoviFile;
}

Poz insert(char* drzava, char* ime_filea, Poz T)
{
	
	if (T == NULL)
	{
		T = (Poz)malloc(sizeof(State));
		if (T == NULL)
		{
			printf("\nGreska pri alokaciji memorije\n");
			return NULL;
		}
		else
		{
			strcpy(T->naziv_drzave, drzava);
			strcpy(T->ime_filea, ime_filea);
			printf("\n%s\n %s\n\n", T->naziv_drzave, T->ime_filea);
			T->left = T->right = NULL;
			T->grad = NULL;
			T->grad = (Pozicija)malloc(sizeof(City));
			if (T->grad == NULL) {
				printf("Greska pri alokaciji memorije");
				return NULL;		
			}
			T->grad->next = NULL;
			unesiGradove(T->grad,T->ime_filea);
			return T;
		}

	}
	if (strcmp(T->naziv_drzave,drzava) > 0)
	{
		T->left = insert(drzava, ime_filea, T->left);
	}
	else if (strcmp(T->naziv_drzave, drzava) < 0)
	{
		T->right = insert(drzava, ime_filea, T->right);
	}

	return T;
}

int delete_all(Poz T) {
	Poz temp = T;
	if (!temp)
		return -1;
	delete_stack(T->grad);
	delete_all(temp->left);
	delete_all(temp->right);
	if (!temp->left && !temp->right) {
		free(temp);
		return 0;
	}
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
	free(P);
	return 0;
}