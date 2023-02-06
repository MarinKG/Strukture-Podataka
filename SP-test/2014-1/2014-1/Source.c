#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _Cvor;
typedef struct _Cvor* Tree;
typedef struct _Cvor {
    char rijec[100];
    unsigned int length;
    Tree left, right;
}Cvor;

struct _lista;
typedef struct _lista* List;
typedef struct _lista{
    char rijec[100];
    List next;
}lista;

Tree insert(char* rijec, Tree T);
int fillList(Tree T, List P, float length);
int inorder(Tree T);
int printlist(List P);
int main()
{
    List head = NULL;
    int provjera = 0;
    int br_rijeci = 0;
    float suma = 0;
    float avg_length = 0;
    char rijec[100] = { '\0' };
    FILE* file = fopen("text.txt", "r");
    if (file == NULL) {
        printf("Greska pri otvaranju\n");
        return -1;
    }
    head = (List)malloc(sizeof(lista));
    if (head == NULL) {
        printf("Greska pri alokaciji memorije\n");
        return -1;
    }    
    head->next = NULL;
    Tree Root = NULL;
    while (!feof(file)) {
        provjera = fscanf(file, " %s", rijec);
        if (provjera == 1) {
            br_rijeci++;
            suma = suma + strlen(rijec);
            Root = insert(rijec, Root);
        }
    }
    avg_length = suma / br_rijeci;
    printf("\n%f\n", avg_length);
    fillList(Root, head, avg_length);
    inorder(Root);
    printf("\n\n\n");
    printlist(head->next);
}

Tree insert(char* rijec, Tree T) {
    if (T == NULL) {
        T = (Tree)malloc(sizeof(Cvor));
        if (T == NULL) {
            printf("Greska pri alokaciji memorije\n");
            return NULL;
        }
        T->length = strlen(rijec);
        T->right = T->left = NULL;
        strcpy(T->rijec, rijec);
    }
    if (strcmp(rijec, T->rijec) < 0) {
        T->left = insert(rijec, T->left);
    }
    if (strcmp(rijec, T->rijec) > 0) {
        T->right = insert(rijec, T->right);
    }
    return T;
}

int fillList(Tree T, List P, float length) {
    if (T == NULL) {
        return 0;
    }
    List q = NULL, r = NULL;
    r = P;
    if (T->length >= length) {
        while (r->next != NULL && strcmp(r->next->rijec, T->rijec) < 0) {
            r = r->next;
        }
        q = (List)malloc(sizeof(lista));
        if (q == NULL) {
            printf("Greska pri alokaciji memorije\n");
            return -1;
        }
        strcpy(q->rijec, T->rijec);
        q->next = r->next;
        r->next = q;
    }

    fillList(T->right, P, length);
    fillList(T->left, P, length);
    return 0;
}

int inorder(Tree T) {
    if (T == NULL)
        return 0;
    inorder(T->left);
    printf("\n%s", T->rijec);
    inorder(T->right);
    return 0;
}

int printlist(List P) {
    while (P != NULL) {
        printf("\n%s", P->rijec);
        P = P->next;
    }
    return 0;
}