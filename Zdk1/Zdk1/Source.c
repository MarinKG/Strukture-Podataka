#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_IME (256)
#define FILE_ERROR (-1)
#define MAX_LINIJA (1024)
#define MAX_BODOVI (100)
//1. Napisati program koji prvo proèita koliko redaka ima datoteka, tj. koliko ima studenata
//zapisanih u datoteci.Nakon toga potrebno je dinamièki alocirati prostor za niz struktura
//studenata(ime, prezime, bodovi) i uèitati iz datoteke sve zapise.Na ekran ispisati ime,
//prezime, apsolutni i relativni broj bodova.
//Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
//relatvan_br_bodova = br_bodova / max_br_bodova * 100
typedef struct 
{
    char ime[MAX_IME];
    char prezime[MAX_IME];
    int bodovi;
}student;

int broj_studenata(char* ime_file);
int upis(char* ime_file, int broj_studenata, student *studenti);

int main()
{
	char ime_filea[MAX_IME] = { 0 };
	int br_studenata = 0;
    student * studenti = NULL;
    float relativan_br_bodova = 0;
	printf("Upisite ime filea ");

    scanf("%[^\n]s", ime_filea);

    printf("%s", ime_filea);

	br_studenata = broj_studenata(ime_filea);
	
    if (br_studenata < 1)
    
    printf("Broj studenata u datoteci %s je %d\n", ime_filea, br_studenata);
    studenti = (student*)malloc(sizeof(student) * br_studenata);

    if (!studenti) {
    }

    upis(ime_filea, br_studenata, studenti);
    for (int i = 0; i < br_studenata; i++)
    {
         relativan_br_bodova = (float)studenti[i].bodovi / MAX_BODOVI * 100;

         printf("IME: %s\t PREZIME: %s\t APSOLUTNI_BODOVI: %d\t RELATIVNI_BODOVI: %.2f\n", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi,relativan_br_bodova);
    }
    free(studenti);
    return 0;

}
int broj_studenata(char* ime_file)
{
    FILE * file = NULL;
    int count = 0;
    char buffer[MAX_LINIJA] = { 0 };

    file = fopen(ime_file, "r");

    if (file == NULL)
    {
        printf("Datoteka %s se nije mogla otvoriti!\r\n", ime_file);
        return FILE_ERROR;
    }

    while (!feof(file))
    {
        fgets(buffer, MAX_LINIJA, file);
        if (strcmp("\n", buffer) != 0)
        {
            count++;
        }
    }
    fclose(file);
    return count;
}
int upis(char* ime_file, int broj_studenata, student *studenti)
{
    FILE* file = NULL;
    int count = 0;

    file = fopen(ime_file, "r");

    if (file == NULL)
    {
        printf("Datoteka %s se nije mogla otvoriti!\r\n", ime_file);
        return FILE_ERROR;
    }
    while (!feof(file))
    {
        
        if (fscanf(file, "%s %s %d", studenti[count].ime, studenti[count].prezime, &studenti[count].bodovi) == 3) 
        {   
            count++;
        }
        else
        {
            printf("Fali varijabla");
            return FILE_ERROR;
        }
    }
    return 0;
}