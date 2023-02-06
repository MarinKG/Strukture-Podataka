#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct _student;
typedef struct _student* Student;
typedef struct _student {
	char sifra_studenta[100];
	char ime[100];
	char prezime[100];
	char sifra_ispita[100];
	Student next;
}student;

struct _ispit;
typedef struct _ispit* Ispit;
typedef struct _ispit {
	char sifra_ispita[100];
	char naziv[100];
	Ispit next;
}ispit;

int insertStudent(Student P, char* sifra_studenta, char* ime, char* prezime, char* sifra_ispita);
int nameCompare(char* ime, char* prezime, Student T);
int insertIspit(Ispit P, char* sifra_ispita, char* naziv);
char* nadiIspit(Ispit P, char* ispit);
int ispisiispite(Ispit P);
int ispisi_listu(Student P);
int main() {
	int provjera = 0;
	char sifra_studenta[100] = { '\0' };
	char ime[100] = { '\0' };
	char prezime[100] = { '\0' };
	char sifra_ispita[100] = { '\0' };
	char naziv[100] = { '\0' };
	char sifra[100] = { '\0' };
	Student head_student = NULL,P=NULL;
	Ispit head_ispit = NULL;
	FILE* studenti = fopen("studenti.txt", "r");
	FILE* ispiti = fopen("ispiti.txt", "r");
	if (studenti == NULL || ispiti == NULL) {
		printf("\nGreska pri otvaranju datoteke");
		return -1;
	}
	head_student = (Student)malloc(sizeof(student));
	head_ispit = (Ispit)malloc(sizeof(ispit));
	if (head_student == NULL || head_ispit == NULL) {
		printf("\nGreska pri alokaciji memorije");
		return -1;
	}
	head_student->next = NULL;
	head_ispit->next = NULL;
	while (!feof(studenti)) {
		provjera = fscanf(studenti, " %s %s %s %s", sifra_studenta, ime, prezime, sifra_ispita);
		insertStudent(head_student, sifra_studenta, ime, prezime, sifra_ispita);
	}
	fclose(studenti);
	while (!feof(ispiti)) {
		provjera = fscanf(ispiti, " %s %s", sifra_ispita, naziv);
		insertIspit(head_ispit, sifra_ispita, naziv);
	}
	fclose(ispiti);
	ispisi_listu(head_student->next);
	printf("\n");
	ispisiispite(head_ispit->next);
	printf("\nUnesi naziv ispita\n");
	scanf(" %s", naziv);
	strcpy(sifra, nadiIspit(head_ispit, naziv));
	printf("\n");
	P = head_student->next;
	while (head_student != NULL) {
		if (strcmp(sifra, head_student->sifra_ispita) == 0)
			printf("Student: %s %s %s\n", head_student->sifra_ispita, head_student->ime, head_student->prezime);
		head_student = head_student->next;
	}
	
	return 0;


}

int ispisiispite(Ispit P) {
	Ispit q = P;
	while (q != NULL) {
		printf("\n%s %s", q->naziv, q->sifra_ispita);
		q = q->next;
	}
}

int ispisi_listu(Student P) {
	Student q = P;
	while (q != NULL) {
		printf("\n%s %s %s %s", q->sifra_studenta, q->ime, q->prezime, q->sifra_ispita);
		q = q->next;
	}
}

char* nadiIspit(Ispit P, char* ispit) {
	Ispit r = P;
	while (r->next != NULL && (strcmp(ispit,r->next->naziv) != 0)) {
		r = r->next;
	}
	if (r == NULL) {
		return "ne postoji";
	}
	return r->next->sifra_ispita;
}

int insertIspit(Ispit P, char* sifra_ispita, char* naziv) {
	Ispit q = NULL, r = P;
	while (r->next != NULL && strcmp(naziv, r->next->naziv) < 0) {
		r = r->next;
	}
	q = (Ispit)malloc(sizeof(ispit));
	if (q == NULL) {
		printf("\nGreska pri alokaciji memorije");
		return -1;
	}
	strcpy(q->naziv, naziv);
	strcpy(q->sifra_ispita, sifra_ispita);
	q->next = r->next;
	r->next = q;
	return 0;
}

int insertStudent(Student P, char* sifra_studenta, char* ime, char* prezime, char* sifra_ispita) {
	Student q = NULL, r = P;
	while (r->next != NULL && nameCompare(ime, prezime, r->next)>0) {
		r = r->next;
	}
	q = (Student)malloc(sizeof(student));
	if (q == NULL) {
		printf("\nGreska pri alokaciji memorije");
		return -1;
	}
	strcpy(q->sifra_studenta, sifra_studenta);
	strcpy(q->ime, ime);
	strcpy(q->prezime, prezime);
	strcpy(q->sifra_ispita, sifra_ispita);
	q->next = r->next;
	r->next = q;
	return 0;
}

int nameCompare(char* ime, char* prezime, Student T) {
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