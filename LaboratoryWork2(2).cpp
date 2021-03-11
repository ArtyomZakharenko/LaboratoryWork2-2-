#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

struct student {
    char fio[20];
    int recbook;
    int marks[4];
};

void ShowMenu();
void OperationsWithFile(FILE *, student*, int * , int);
void SetAmount(int*);
struct student * CreateStruct(int*);
void FillStruct(student*, int *);
void CreateNewFile(FILE*, student* , int *);
void ViewFile(FILE*, student *, int*);
void WorkWithFile(FILE*, student*, int*);
void AddInfo(FILE*, int*);

int main()
{
    FILE* binFile;
    struct student* array;
    int size;
    SetAmount(&size);
    array = CreateStruct(&size);
    FillStruct(array, &size);
    binFile = fopen("C:\\file.dat", "w+b");
    WorkWithFile(binFile, array, &size);

    return 0;
}

void ShowMenu() {
    printf("\nPlease choose what you would like to do:\n");
    printf("1. Create new file\n");
    printf("2. View file\n");
    printf("3. Add information to file\n");
    printf("4. Show information about bad students\n");
    printf("\n0. Exit\n");
}

void OperationsWithFile(FILE* lib, student * arr, int * amount, int option) {
    switch (option)
    {
    case 1:
  
        CreateNewFile(lib, arr, amount);
        break;
    case 2: 
        ViewFile(lib, arr, amount);
        break;

    case 3:
        AddInfo(lib, amount);
        break;

    case 4:

        break;
    case 0:

        break;
    default:
        printf("Error! You have choosen wrong option! Try again!");
        break;
    }
}

void SetAmount(int* amount) {
    printf("Set number of students: ");
    scanf("%d", amount);
}

struct student * CreateStruct(int* amount) {
    struct student* arr;
    arr = (student*)calloc(*amount, sizeof(student));
    return arr;
}

void FillStruct(student* arr, int* amount) {
    int i;
    printf("\nEnter information about students:\n");
    for (i = 0; i < *amount; i++) {
        printf("\nStudent %d:\n", i + 1);
        printf("Student's name: ");
        scanf("%20s", arr[i].fio);
        printf("Student's record book number: ");
        scanf("%d", &arr[i].recbook);
        printf("Student's 4 marks (use spacebar as a separator): ");
        scanf("%d %d %d %d", &arr[i].marks[0], &arr[i].marks[1], &arr[i].marks[2], &arr[i].marks[3]);
    }
    system("cls");
}

 void CreateNewFile(FILE * lib, student * arr, int * amount) {
     lib = fopen("C:\\file.dat", "ab");
     fwrite(arr, sizeof(student), *amount, lib);
     rewind(lib);
     printf("File has been created!\n");
 }

 void ViewFile(FILE* lib, student * arr, int* amount) {
     lib = fopen("C:\\file.dat", "rb");
     int i;
     fread(arr, sizeof(student), *amount, lib);
     for (i = 0; i < *amount; i++) {
         printf("\nStudent %d:\n", i + 1);
         printf("Student's name: %s\n", arr[i].fio);
         printf("Student's record book number: %d\n", arr[i].recbook);
         printf("Student's 4 marks: %d, %d, %d, %d\n", arr[i].marks[0], 
         arr[i].marks[1], arr[i].marks[2], arr[i].marks[3]);
     }
 }

 void WorkWithFile(FILE* lib, student * arr, int* size) {
     int opt;
     do {
         ShowMenu();
         scanf("%d", &opt);
         system("cls");
         OperationsWithFile(lib, arr, size, opt);
     } while (opt != 0);

 }

 void AddInfo(FILE* lib, int* size) {
     struct student profile;

     printf("\nEnter information about students:\n");
     printf("Student's name: ");
     scanf("%20s", &profile.fio);
     printf("Student's record book number: ");
     scanf("%d", &profile.recbook);
     printf("Student's 4 marks (use spacebar as a separator): ");
     scanf("%d %d %d %d", &profile.marks[0], &profile.marks[1], &profile.marks[2], &profile.marks[3]);

     lib = fopen("C:\\file.dat", "ab");
     fwrite(&profile, sizeof(student), 1, lib);
     rewind(lib);
     printf("File has been updated!\n");
     (*size)++;
 }