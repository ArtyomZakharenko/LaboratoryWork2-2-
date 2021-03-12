/*Используя функции и режим меню, создать бинарный файл из N структур,
просмотреть файл, добавить в файл новую информацию и, применяя режим прямого
доступа, выполнить задание по своему варианту.

Структура имеет вид: фамилия студента, номер зачетной книжки, 4 оценки за
экзамен. Выводить информацию о всех двоечниках и корректировать ее.*/

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
void ShowBadStudents(FILE*, int*);
void AskForEdit(FILE*, int*);
void EditBadStudent(FILE*, int*);

int main()
{
    FILE* binFile;
    struct student* array;
    int size;
    SetAmount(&size);
    array = CreateStruct(&size);
    FillStruct(array, &size);
    if (!(binFile = fopen("C:\\file.dat", "w+b"))) {
        printf("\nCannot read file!");
        return 1;
    }
    binFile = fopen("C:\\file.dat", "w+b");
    WorkWithFile(binFile, array, &size);
    fclose(binFile);
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
        ShowBadStudents(lib, amount);
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
     lib = fopen("C:\\file.dat", "wb");
     fwrite(arr, sizeof(student), *amount, lib);
     free(arr);
     rewind(lib);
     printf("File has been created!\n");
     fclose(lib);
 }

 void ViewFile(FILE* lib, student * arr, int* amount) {
     int i;
     lib = fopen("C:\\file.dat", "r+b");
     fread(arr, sizeof(student), *amount, lib);
     for (i = 0; i < *amount; i++) {
         printf("\nStudent %d:\n", i + 1);
         printf("Student's name: %s\n", arr[i].fio);
         printf("Student's record book number: %d\n", arr[i].recbook);
         printf("Student's 4 marks: %d, %d, %d, %d\n", arr[i].marks[0], 
         arr[i].marks[1], arr[i].marks[2], arr[i].marks[3]);
     }
     rewind(lib);
     
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
     lib = fopen("C:\\file.dat", "r+b");
     printf("\nEnter information about students:\n");
     printf("Student's name: ");
     scanf("%20s", &profile.fio);
     printf("Student's record book number: ");
     scanf("%d", &profile.recbook);
     printf("Student's 4 marks (use spacebar as a separator): ");
     scanf("%d %d %d %d", &profile.marks[0], &profile.marks[1], &profile.marks[2], &profile.marks[3]);

     lib = fopen("C:\\file.dat", "ab");
     fwrite(&profile, sizeof(student), 1, lib);
     printf("\nFile has been updated!\n");
     rewind(lib);
     
     
     (*size)++;
 }

 void ShowBadStudents(FILE* lib, int* size) {
     struct student* arr = CreateStruct(size);
     int i, j, temp = -1;
     fread(arr, sizeof(student), *size, lib);

     for (i = 0; i < *size; i++) {
         for (j = 0; j < 4; j++) {
             if (arr[i].marks[j] <= 2) {
                 temp = i;
             } 
         }
         if (temp == i) {
             printf("Student's name: %s\n", arr[i].fio);
             printf("Student's record book number: %d\n", arr[i].recbook);
             printf("Student's 4 marks: %d, %d, %d, %d\n\n", arr[i].marks[0],
                 arr[i].marks[1], arr[i].marks[2], arr[i].marks[3]);
         }
         
         
     }

     if (temp == -1) {
         printf("There aren't bad students here :)\n");
     }
     else {
         AskForEdit(lib, size);
     }
     rewind(lib);
     fclose(lib);
 }

 void AskForEdit(FILE * lib, int * size) {
     //lib = fopen("C:\\file.dat", "rb");
     char input;
     getchar();
     printf("\nWould you like to edit something? Press y for yes or n for no: ");
     input = getchar();
     while (input != 'y' && input != 'n') {
         getchar();
         printf("Error! You've entered wrong key! Try again!");
         input = getchar();
     }
     switch (input) {
     case 'y':
         EditBadStudent(lib, size);
         
         break;
     case 'n':
         
         break;
     }
 }

 void EditBadStudent(FILE* lib, int* size) {
     lib = fopen("C:\\file.dat", "r+b");
     struct student* arr = CreateStruct(size);
     int i, j, temp = -1;
     fread(arr, sizeof(student), *size, lib);

     for (i = 0; i < *size; i++) {
         for (j = 0; j < 4; j++) {
             if (arr[i].marks[j] <= 2) {
                 temp = i;
             }
         }
         if (temp == i) {
             printf("Student's new 4 marks (use spacebar as a separator): ");
             scanf("%d %d %d %d", &arr[temp].marks[0], &arr[temp].marks[1], &arr[temp].marks[2], &arr[temp].marks[3]);

         }
     }
     lib = fopen("C:\\file.dat", "w+b");
     fwrite(arr, sizeof(student), *size, lib);
     rewind(lib);
     fclose(lib);
 }