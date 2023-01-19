#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LINE 100

/*napisi prog koji cita file drzave.txt u kojoj su zapisana imena pojedinigh država i uz ta imena nalazi se naziv datotake koja drži gradove te države
* npr. Hrvatska hrv.txt.  primjer datoteke gradova: naziv_grada broj_stanovnika.
* a) formiraj sortiranu vezanu listu država po nazivu. Svaki čvor te liste sadrži stablo gradova sortirano prvo po broju stanovnika pa onda po imenu
* 
* b) formiraj stablo država sortirano po nazivu. Svaki čvor stabla sadrži vezanu listu gradova sortiranu po broju stanovnika a zatim po nazivu
*/
//veci broj ide livo, manji desno 
struct _city;
typedef struct _city *Poz; 
typedef struct _city
{
	Poz left, right;
	char naziv[MAX_LINE];
	int brStan;
}City;

struct _state;
typedef struct _state* Pozicija;
typedef struct _state {
	Pozicija next;
	Poz grad;
	char ime_filea[MAX_LINE];
	char naziv_drzave[MAX_LINE];
}State;

int inorder(Poz T);
Poz insert(int broj_stanovnika,char* ime_grada, Poz T);
int cityCompare(City* c, int broj_stanovnika, char*ime_grada);
char** ucitajDatoteku(char* datoteka, int broj);
int izbrojiBrojDrzava(char* datoteka);
int unesiDrzavuSortirano(Pozicija P, char* txt_file, char* ime_drzave);
int unesiGradove(Pozicija P);
int ispisiVeceOd(Poz T, int broj);
int delete_stack(Pozicija P);
int delete_all(Poz T);

int main() {
	char datoteka[MAX_LINE] = { '\0' };
	char** gradoviFile;
	int broj =0, provjera = 0;
	char drzava[MAX_LINE] = { '\0' };
	Pozicija head = (Pozicija)malloc(sizeof(State));
	if (head == NULL) {
		printf("\nGreska pri alokaciji memorije");
		return -1;
	}
	head->next = NULL;
	Pozicija P = NULL,Q=NULL;
	int br_stan = 0;

	printf("\nUnesite naziv datoteke: ");
	provjera=scanf(" %s", datoteka);
	if(provjera!=1){
		printf("\nGreska pri unosu");
	return -1;
	}
	broj=izbrojiBrojDrzava(datoteka);
	gradoviFile=ucitajDatoteku(datoteka,broj);
	for (int i = 0; i < broj * 2; i = i + 2) {
		unesiDrzavuSortirano(head, gradoviFile[i+1], gradoviFile[i]);
	}
	P = head->next;
	while (P != NULL)
	{
		unesiGradove(P);
		P = P->next;
	}
	P = head->next;
	Q = head->next;
	printf("\nUnesite drzavu koju trazite: ");
	provjera=scanf(" %s", drzava);
	if (provjera != 1) {
		printf("\nGreska pri unosu");
		return -1;
	}
	while (Q != NULL && (strcmp(Q->naziv_drzave, drzava) < 0)) {
		Q = Q->next;
	}
	if (Q == NULL) {
		printf("\nDrzava ne postoji\n");
		return -1;
	}
	printf("\n%s", Q->naziv_drzave);
	printf("\nUnesite minimalni broj stanovnika za pretragu:");
	provjera= scanf(" %d", &br_stan);
	if (provjera != 1) {
		printf("\nGreska pri unosu");
		return -1;
	}
	ispisiVeceOd(Q->grad, br_stan);
	
	while (P != NULL) {
		delete_all(P->grad);
		P = P->next;
	}
	delete_stack(head);
	free(head);
	return 0;
}

int ispisiVeceOd(Poz T, int broj) {
	if (T == NULL) {
		return 0;
	}
	ispisiVeceOd(T->right, broj);
	if (T->brStan > broj) {
		printf("\n %d\t %s", T->brStan, T->naziv);
	}
	ispisiVeceOd(T->left, broj);
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
	int broj = 0,provjera=0;
	char buffer[MAX_LINE] = { '\0' };
	FILE* file = fopen(datoteka, "r");
	if (file == NULL) {
		printf("\nGreska pri otvaranju datoteke");
		return -1;
	}
	while (!feof(file)) {
		provjera = fscanf(file, " %[^\n]", buffer);
		if (provjera == 1) {
			if (strcmp(buffer, "\n") != 0) {
				broj++;
			}
		}
	}
	fclose(file);
	return broj;
}

char** ucitajDatoteku(char* datoteka,int broj) {
	FILE* file = fopen(datoteka, "r");
	char** gradoviFile=NULL;
	int i = 0,provjera=0;
	if (file == NULL) {
		printf("\nGreska pri otvaranju datoteke");
		return NULL;
	}
	gradoviFile = (char**)malloc(sizeof(char*) * (broj*2));
	if (gradoviFile == NULL) {

		printf("\nGreska\n");
		return NULL;
	}
	for (int i = 0; i < broj*2; i++) {
		gradoviFile[i] = (char*)malloc(sizeof(char) * MAX_LINE);
	}
	while (!feof(file)) {
		provjera=fscanf(file," %s %s ", gradoviFile[i], gradoviFile[i + 1]);
		if (provjera == 2) {
			i = i + 2;
		}
	}
	fclose(file);
	return gradoviFile;
}

int unesiDrzavuSortirano(Pozicija P, char* txt_file, char* ime_drzave) {
	Pozicija q=NULL;
	while (P->next != NULL && strcmp(P->next->naziv_drzave, ime_drzave) < 0) {
		P = P->next;
	}
	q = (Pozicija)malloc(sizeof(State));
	if (q == NULL) {
		printf("\nGreska pri alokaciji memorije");
		return -1;
	}
	printf("\n%s\n", ime_drzave);
	strcpy(q->naziv_drzave, ime_drzave);
	strcpy(q->ime_filea, txt_file);
	q->next = P->next;
	q->grad = NULL;
	P->next = q;
	return 0;
}

int unesiGradove(Pozicija P) {
	printf("\n%s\n", P->ime_filea);
	FILE* file = fopen(P->ime_filea, "r");
	char ime_grada[MAX_LINE] = { '\0' };
	int br_stanovnika = 0, provjera=0;
	if (file == NULL) {

		return -1;
	}
	while (!feof(file))
	{
		provjera=fscanf(file, " %s %d ", ime_grada, &br_stanovnika);
		if (provjera == 2) {
			printf("%s %d\n", ime_grada, br_stanovnika);
			P->grad = insert(br_stanovnika, ime_grada, P->grad);
		}
	}

	fclose(file);
	return 0;
}

Poz insert(int broj_stanovnika, char*ime_grada, Poz T)
{
	if (T == NULL)
	{
		T = (Poz)malloc(sizeof(City));
		if (T == NULL)
		{
			printf("\nGreska pri alokaciji memorije\n");
			return NULL;
		}
		else
		{
			strcpy(T->naziv, ime_grada);
			T->brStan = broj_stanovnika;
			T->left = T->right = NULL;
		}

	}
	else if (cityCompare(T,broj_stanovnika,ime_grada) < 0)
	{
		T->left = insert(broj_stanovnika, ime_grada, T->left);
	}
	else if (cityCompare(T, broj_stanovnika, ime_grada) > 0)
	{
		T->right = insert(broj_stanovnika, ime_grada, T->right);
	}
	return T;
}

int inorder(Poz T)
{
	if (T != NULL)
	{
		inorder(T->left);
		printf("\n%s \t%d",T->naziv,T->brStan);
		inorder(T->right);
	}
	return 0;
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
	return 0;
}

int delete_all(Poz T) {
	Poz temp = T;
	if (!temp)
		return -1;
	delete_all(temp->left);
	delete_all(temp->right);
	if (!temp->left && !temp->right) {
		free(temp);
		return 0;
	}
}