#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct _broj;
typedef struct _broj* List;
typedef struct _broj {
	unsigned int broj;
	List next;
}Broj;

struct _3ree;
typedef struct _3ree* Tree;
typedef struct _3ree {
	unsigned int broj;
	Tree left, right;
}tree;

int insert(List P, int broj);
int findMax(List P);
int findMin(List P);
int urediListu(List P, unsigned int broj, int broj_vecih_od_srednje);
int ispisiListu(List P);
int izracunajBrojVecih(List P,int srednja);
int nadiNajblizu(List P, int srednja);
Tree insertTree(Tree T, unsigned int vrijednost);
int inorder(Tree T);
/*int levelOrder(Tree T, List P); ne radi
int ubaciNaKraj(List P, Tree T);*/

int main() {
	srand((unsigned int)time(NULL));
	List head = NULL, levelorder=NULL;
	Tree Root = NULL;
	List P = NULL;
	unsigned int max = 0,min=0,broj=0,srednja=0,broj_vecih_od_srednje=0,root_vrijednost=0;
	head = (List)malloc(sizeof(Broj));
	levelorder = (List)malloc(sizeof(Broj));
	if (head == NULL||levelorder==NULL) {
		printf("\nGreska pri alokaciji memorije");
		return -1;
	}
	head->next = NULL;
	levelorder->next = NULL;
	for (int i = 0; i < 15; i++) {
		broj = rand() % (120 - 100 + 1) + 100;
		printf("%d\n",broj);
		insert(head, broj);
	}
	ispisiListu(head->next);

	max=findMax(head);
	min = findMin(head);
	srednja = (min + max) / 2;
	printf("\n\n%d %d %d\n", min, max,srednja);
	broj_vecih_od_srednje = izracunajBrojVecih(head,srednja);
	printf("\n%d\n", broj_vecih_od_srednje);
	urediListu(head, srednja, broj_vecih_od_srednje);
	ispisiListu(head->next);
	root_vrijednost = nadiNajblizu(head, srednja);
	printf("\n%d\n", root_vrijednost);
	Root = insertTree(Root, root_vrijednost);
	P = head;
	while (P->next != NULL) {
		Root = insertTree(Root, P->next->broj);
		P = P->next;
	}
	inorder(Root);
	//levelOrder(Root, levelorder);
	//printf("\n");
	//ispisiListu(levelorder->next);
	return 0;
}

/* ne radi

int ubaciNaKraj(List P, Tree T) {
	if (T == NULL)
		return;
	List r = P, q = NULL;
	while (r->next != NULL) {
		r = r->next;
	}
	q = (List)malloc(sizeof(Broj));
	if (q == NULL) {
		printf("\nGreska pri alokaciji memorije");
		return -1;
	}
	q->broj = T->broj;
	q->next = r->next;
	r->next = q;
	levelOrder(T->left, P);
	levelOrder(T->right, P);
	return 0;
}

int levelOrder(Tree T, List P) {
	if (T == NULL)
		return 0;
	ubaciNaKraj(P, T);

	return 0;
}*/

int inorder(Tree T) {
	if (T == NULL)
		return 0;
	inorder(T->left);
	printf("%d ", T->broj);
	inorder(T->right);
	return 0;

}

Tree insertTree(Tree T, unsigned int vrijednost) {
	if (T == NULL) {
		T = (Tree)malloc(sizeof(tree));
		if (T == NULL) {
			printf("\nGreska pri alokaciji memorije");
		}
		T->broj = vrijednost;
		T->left = T->right = NULL;
	}
	else if (vrijednost < T->broj) {
		T->left = insertTree(T->left, vrijednost);
	}
	else if (vrijednost > T->broj) {
		T->right = insertTree(T->right, vrijednost);
	}
	return T;
}


int nadiNajblizu(List P, int srednja) {
	List r = P;
	int temp = P->next->broj, min = 0;
	while (r->next != NULL) {
	r = r->next;
	if (abs(srednja - r->broj) < temp) {
		temp = abs(srednja - r->broj);
		min = r->broj;
	}
	}

	return min;
}

int izracunajBrojVecih(List P,int srednja) {
	unsigned int brojac = 0;
	while (P->next != NULL) {
		P = P->next;
		if (P->broj >= srednja)
			brojac++;
	}
	return brojac;
}

int ispisiListu(List P) {
	while (P != NULL) {
		printf("%d ", P->broj);
		P = P->next;
	}
	return 0;
}

int urediListu(List P, unsigned int broj, int broj_vecih_od_srednje) {
	for (int i = 0; i < broj_vecih_od_srednje; i++)
	{
		List r = P, q = NULL, v = NULL;
		while (r->next != NULL && r->next->broj < broj) {
			r = r->next;
		}
		v=r;
		while (v->next != NULL) {
			v = v->next;
		}
		q = r->next;
		r->next = q->next;
		v->next = q;
		q->next = NULL;
	}
	return 0;
}

int findMin(List P) {
	List r = P;
	unsigned int min = r->next->broj;
	while (r->next != NULL) {
		if (r->next->broj < min) {
			min = r->next->broj;
		}
		r = r->next;
	}
	return min;
}

int findMax(List P) {
	List r = P;
	unsigned int max = r->next->broj;
	while (r->next != NULL) {
		if (r->next->broj > max) {
			max = r->next->broj;
		}
		r = r->next;
	}
	return max;
}

int insert(List P, int broj) {
	List q = NULL, r = P;
	while (r->next != NULL&&r->next->broj!=broj) {
		r = r->next;
	}
	if (r->next != NULL) {
		return 0;
	}
	q = (List)malloc(sizeof(Broj));
	if (q == NULL) {
		printf("\nGreska pri alokaciji memorije");
		return -1;
	}
	q->broj = broj;
	q->next = r->next;
	r->next = q;
	return 0;
}