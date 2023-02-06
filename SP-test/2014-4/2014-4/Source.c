#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

struct _student;
typedef struct _student* Tree;
typedef struct _student {
	char ime[128];
	char prezime[128];
	int broj_bodova;
	int relativni_broj_bodova;
	Tree left, right;
}Student;

Tree insert(Tree T, char* ime, char* prezime, int broj_bodova);
int nadiMax(Tree T);
int upisiRelativneBodove(Tree T, int relativni_bodovi);
int inorder(Tree T);
int preorder(Tree T);

int main() {
	char ime[128] = { '\0' };
	char prezime[128] = { '\0' };
	int provjera = 0;
	int broj_bodova = 0, max_bodovi = 0;
	Tree Root = NULL;
	FILE* file = fopen("student.txt", "r");
	if (file == NULL) {
		printf("\nGreska pri otvaranju datoteke");
		return -1;
	}
	while (!feof(file)) {
		provjera=fscanf(file, " %s %s %d", ime, prezime, &broj_bodova);
		if (provjera == 3) {
			Root = insert(Root, ime, prezime, broj_bodova);
		}
	}
	fclose(file);
	max_bodovi = nadiMax(Root);
	printf("\n%d", max_bodovi);
	upisiRelativneBodove(Root, max_bodovi);
	inorder(Root);
	printf("\n");
	preorder(Root);
	return 0;
}

int preorder(Tree T) {
	if (T == NULL)
		return 0;
	printf("\n %s %s %d %d", T->ime, T->prezime, T->broj_bodova, T->relativni_broj_bodova);
	inorder(T->left);
	inorder(T->right);
	return 0;
}

int inorder(Tree T) {
	if (T == NULL)
		return 0;
	inorder(T->left);
	printf("\n %s %s %d %d", T->ime, T->prezime, T->broj_bodova, T->relativni_broj_bodova);
	inorder(T->right);
	return 0;
}

int nameCompare(char* ime, char* prezime, Tree T) {
	if (strcmp(prezime, T->prezime) == 0) {
		if (strcmp(ime, T->ime) == 0) {
			return 0;
		}
		else {
			return strcmp(ime, T->ime);
		}
	}
	else {
		return strcmp(prezime, T->prezime);
	}

}

Tree insert(Tree T, char* ime, char* prezime, int broj_bodova) {
	if (T == NULL) {
		T = (Tree)malloc(sizeof(Student));
		if (T == NULL) {
			printf("\nGreska pri alokaciji memorije");
			return NULL;
		}
		strcpy(T->ime, ime);
		strcpy(T->prezime, prezime);
		if (0 < broj_bodova && broj_bodova < 100)
			T->broj_bodova = broj_bodova;
		T->relativni_broj_bodova = 0;
		T->left = T->right = NULL;
	}
	if (nameCompare(ime, prezime, T) < 0) {
		T->left = insert(T->left, ime, prezime, broj_bodova);
	}
	if (nameCompare(ime, prezime, T) > 0) {
		T->right = insert(T->right, ime, prezime, broj_bodova);
	}
	return T;
}

int nadiMax(Tree T) {
	if (T == NULL)
		return 0;
	int max1=T->broj_bodova, max2 = 0, max3 = 0;
	max2 = nadiMax(T->left);
	max3 = nadiMax(T->right);
	if (max2 > max3 && max2 > max1)
		return max2;
	else if (max3 > max1 && max3 > max2)
		return max3;
	else if (max1 > max2 && max1 > max3)
		return max1;
}

int upisiRelativneBodove(Tree T, int relativni_bodovi) {
	if (T == NULL)
		return 0;
	upisiRelativneBodove(T->left, relativni_bodovi);
	T->relativni_broj_bodova = T->broj_bodova*100 / relativni_bodovi;
	upisiRelativneBodove(T->right, relativni_bodovi);
	return 0;
}