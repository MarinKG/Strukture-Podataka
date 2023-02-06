#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct _rijec;
typedef struct _rijec* Tree;
typedef struct _rijec {
	char rijec[1024];
	Tree left, right;
}Rijec;

Tree insert(Tree T, char* rijec);
int unosSamoglasnici(Tree T, FILE* samoglasnici);
int unosSuglasnici(Tree T, FILE* file);
int inorder(Tree T);
int main() {
	char rijec[1024] = { '\0' };
	int provjera = 0;
	FILE* in = fopen("text.txt", "r");
	Tree Root = NULL;
	if (in == NULL) {
		printf("\nGreska pri otvaranju datoteke");
		return -1;
	}
	while (!feof(in)) {
		provjera=fscanf(in, " %s", rijec);
		if (provjera == 1) {
			Root = insert(Root, rijec);
		}
	}
	fclose(in);

	FILE* samoglasnici = NULL;
	samoglasnici = fopen("samoglasnici.txt", "w");
	if (samoglasnici == NULL ) {
		printf("\nGreska pri otvaranju datoteke");
		return -1;
	}
	unosSamoglasnici(Root, samoglasnici);
	fclose(samoglasnici);

	FILE* suglasnici = NULL;
	suglasnici = fopen("suglasnici.txt", "w");
	if (suglasnici == NULL) {
		printf("\nGreska pri otvaranju datoteke");
		return -1;
	}
	unosSuglasnici(Root, suglasnici);
	return 0;
}

int inorder(Tree T) {
	if (T == NULL)
		return 0;
	inorder(T->left);
	printf(" %s ", T->rijec);
	inorder(T->right);
}

Tree insert(Tree T, char* rijec) {
	if (T == NULL) {
		T = (Tree)malloc(sizeof(Rijec));
		if (T == NULL) {
			printf("\nGreska pri alokaciji memorije");
			return NULL;
		}
		strcpy(T->rijec, rijec);
		T->left = T->right = NULL;
	}
	else if (strcmp(rijec, T->rijec) < 0) {
		T->left = insert(T->left, rijec);
	}
	else if (strcmp(rijec, T->rijec) > 0) {
		T->right = insert(T->right, rijec);
	}
	return T;
}

int unosSamoglasnici(Tree T, FILE* samoglasnici) {
	if (T == NULL)
		return 0;
	char c = toupper(T->rijec[0]);
	unosSamoglasnici(T->left,samoglasnici);
	if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
		fprintf(samoglasnici, "%s ", T->rijec);
	}
	unosSamoglasnici(T->right, samoglasnici);
	return 0;
}

int unosSuglasnici(Tree T, FILE* file) {
	if (T == NULL)
		return 0;
	unosSuglasnici(T->left, file);
	char c = toupper(T->rijec[0]);
	if (c != 'A' && c != 'E' && c != 'I' && c != 'O' && c != 'U') {
		fprintf(file, "%s ", T->rijec);
	}
	unosSuglasnici(T->right, file);
	return 0;
}