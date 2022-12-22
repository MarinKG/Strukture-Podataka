#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>


/*Napisati program koji omoguæava rad s binarnim stablom pretraživanja. Treba
omoguæiti unošenje novog elementa u stablo, ispis elemenata (inorder, preorder, postorder i
level order), brisanje i pronalaženje nekog elementa.*/
struct _tree;
typedef struct _tree* Poz;

typedef struct _tree
{
	int element;
	Poz left;
	Poz right;

}tree;

Poz delete(int x, Poz T);
Poz find(int x, Poz T);
int inorder(Poz T);
int preorder(Poz T);
int postorder(Poz T);
int level_order(Poz T);
Poz insert(int x, Poz T);
Poz find_min(Poz T);
int print(Poz T);
int print_level(Poz T, int i);
int delete_all(Poz T);

int main()
{
	int provjera = 0;
	int element = 0;
	char opcija = '\0';
	Poz Root = NULL;
	Poz nadi = NULL;
	while (toupper(opcija) != 'X')
	{
		printf("\nA- ubaci clan"
			"\nB- inorder ispis"
			"\nC- preorder ispis"
			"\nD- postorder ispis"
			"\nE- level order ispis"
			"\nF- izbrisi clan"
			"\nG- nadi clan"
			"\nX- izadi iz programa\n");
		provjera = scanf(" %c", &opcija);
		if(provjera==1)
		{
			switch (toupper(opcija))
			{
			case 'A':
				printf("\nUnesi vrijednost clana:\n");
				provjera=scanf(" %d", &element);
				if (provjera == 1) {
					Root = insert(element, Root);
				}
				break;
			case 'B':
				inorder(Root);
				break;
			case 'C':
				preorder(Root);
				break;
			case 'D':
				postorder(Root);
				break;
			case 'E':
				level_order(Root);
				break;
			case 'F':
				printf("\nUnesite vrijednost elementa kojeg zelite obrisati:\n");
				provjera=scanf(" %d", &element);
				if (provjera == 1) {
					delete(element, Root);
				}
				break;
			case 'G':
				printf("\nUnesite vrijednost elementa kojeg zelite naci:\n");
				provjera=scanf(" %d", &element);
				if (provjera == 1) {
					nadi = find(element, Root);
					if (nadi != NULL)
						printf("\nElement s vrijednoscu %d se nalazi na memorijskoj lokaciji %p\n", element, nadi);
					else
						printf("\nElement s vrijednoscu %d ne postoji", element);
				}
				break;
			case 'X':
				break;
			}
		}

	}
	delete_all(Root);
	return 0;
}

Poz insert(int x, Poz T)
{
	if (T == NULL)
	{
		T = (Poz)malloc(sizeof(tree));
		if (T == NULL)
		{
			printf("\nGreska pri alokaciji memorije\n");
			return NULL;
		}
		else
		{
			T->element = x;
			T->left = T->right = NULL;
		}

	}
	else if (x < T->element)
	{
		T->left = insert(x, T->left);
	}
	else if (x > T->element)
	{
		T->right = insert(x, T->right);
	}
	return T;
}

Poz find(int x, Poz T)
{
	if (T == NULL)
		return NULL;
	if (x < T->element)
		return(find(x, T->left));
	if (x > T->element)
		return(find(x, T->right));
	else
		return T;
}

Poz delete(int x, Poz T)
{
	Poz temp = NULL, child = NULL;
	if (T == NULL)
		printf("\nElement ne postoji");

	else if (x < T->element)
		T->left = delete(x, T->left);

	else if (x > T->element)
		T->right = delete(x, T->right);

	else if (T->left && T->right) {
		temp = find_min(T->right);
		T->element = temp->element;
		T->right = delete(T->element, T->right);
	}
	else
	{
		temp = T;
		if (T->left == NULL)
			child = T->right;
		if (T->right == NULL)
			child = T->left;
		free(temp);
		return child;
	}
	return T;
}

Poz find_min(Poz T)
{
	if (T != NULL)
		while (T->left != NULL)
			T = T->left;

	return T;
}

int print(Poz T)
{
	printf(" %d ", T->element);
	return 0;
}

int inorder(Poz T)
{
	if (T != NULL)
	{
		inorder(T->left);
		print(T);
		inorder(T->right);
	}
	return 0;
}

int preorder(Poz T)
{
	if (T != NULL)
	{
		print(T);
		preorder(T->left);
		preorder(T->right);
	}
	return 0;
}

int postorder(Poz T)
{
	if (T != NULL)
	{
		postorder(T->left);
		postorder(T->right);
		print(T);
	}
	return 0;
}

int tree_height(Poz T)
{
	int left_height = 0, right_height = 0;
	if (T == NULL)
		return 0;
	else {
		left_height = tree_height(T->left);
		right_height = tree_height(T->right);

		return max(left_height, right_height) + 1;
	}
}
int level_order(Poz T) {
	int height = tree_height(T);
	for (int i = 0; i < height; i++) {
		print_level(T, i);
	}
	return 0;
}

int print_level(Poz T, int i)
{
	if (!T)
		return -1;
	if (i == 0) {
		printf(" %d ", T->element);
	}
	else {
		print_level(T->left, i - 1);
		print_level(T->right, i - 1);
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