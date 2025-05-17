#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// mini warning, putin yapping in comments

// asta e o biblioteca generica pe care am facut o pentru un proiect la sda,
// hence the name, cu pointeri void* dar a trebuit sa o modific putin sa
// ii adaug si parametrul de aparitii, in rest e chiar nice :) i guess pot sa o
// asatez si pe aia daca chiar vrei dar mai mult am vrut sa ma joc putin cu ea
#include "generic_sll.h"

#define FOLDER_PATH "D:/CLionProjects/chestii tp/"
#define WORD_MAX_SIZE 16

void* safe_malloc(size_t size) {
    void *p = malloc(size);

    if (p == NULL) {
        perror("Failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }

    return p;
}

void flush() {
    int c;

    while ((c = getchar()) != '\n' && c != EOF);
}

void flush_string(char *buffer) {
    if (buffer == NULL) {
        return;
    }

    if (strchr(buffer, '\n') == NULL) {
        flush();
    }
}

void get_input_string(char *message, char *buffer, int size) {
    if (buffer == NULL) {
        return;
    }

    printf(message);
    fgets(buffer, size, stdin);
    flush_string(buffer);

    if (strchr(buffer, '\n')) {
        buffer[strcspn(buffer, "\n")] = '\0';
    }
}

void get_input_float(char *message, float *n, float min, float max) {
    printf("%s", message);

    while (scanf("%f", n) != 1 || *n < min || *n > max) {
        printf("incercati din nou ");
        flush();
    }

    flush();
}

void get_input_int(char *message, int *n, int min, int max) {
    printf("%s", message);

    while (scanf("%d", n) != 1 || *n < min || *n > max) {
        printf("incercati din nou ");
        flush();
    }

    flush();
}

void ex1() {
    char buffer[100][100],
         *input_word = (char*)safe_malloc(100),
         *file_name = (char*)safe_malloc(100),
         file_path[150] = FOLDER_PATH;
    int words = 0;

    get_input_string("numele fisierului: ", file_name, 100);
    get_input_string("cuvantul: ", input_word, 100);
    strcat(file_path, file_name);

    FILE *f = fopen(file_path, "r");
    if (f == NULL) {
        perror("n ai fisier fraere");
        exit(1);
    }

    while (fgets(buffer[words], 100, f)) {
        // asta trateaza corect situatia in care exista un match
        // ca si ultimul cuvant, aka cand nu are \n ca e eof
        if (strchr(buffer[words], '\n')) {
            buffer[words][strlen(buffer[words]) - 1] = '\0';
        }

        words++;
    }

    for (int i = 0; i < words; i++) {
        if (strcmp(input_word, buffer[i]) == 0) {
            printf("exista cuvantul la linia %d\n", i + 1);
        }
    }

    fclose(f);
    free(file_name);
    free(input_word);
}

void ex2() {
    char buffer[300],
         *file_name_output = (char*)safe_malloc(100),
         *file_name_input = (char*)safe_malloc(100),
         file_path_input[150] = FOLDER_PATH,
         file_path_output[150] = FOLDER_PATH;
 
    get_input_string("numele fisierului input: ", file_name_input, 100);
    get_input_string("numele fisierului output: ", file_name_output, 100);
    strcat(file_path_input, file_name_input);
    strcat(file_path_output, file_name_output);
 
    FILE *file_input = fopen(file_path_input, "r");
    FILE *file_output = fopen(file_path_output, "w");

    // ok o chestie mai generala aici, am auzit ca e bad practice daca
    // verific cand un pointer == null in loc sa fac !pointer, dar de ce
    // anume? mi se pare mai clar asa, ! ar fi mai greu de vazut in viteza as zice
    if (file_input == NULL || file_output == NULL) {
        perror("n ai fisier fraere");
        exit(1);
    }

    // aici presupun ca nu scrii mai mult de 300 caractere/linie
    while (fgets(buffer, 300, file_input)) {
        // bro cine scrie cerintele astea, macar un exemplu per cerinta ar ajuta
        // ca mereu pot exista false positives, in teorie nimic nu ma opreste
        // doar sa ii dau yeet daca contine orice fel de // in linie,
        // dar exista si cazuri ca linia aia in sine, gen strstr(sir, "//")
        // si atunci mi ar scoate linia aia, nu exista o alta metoda mai buna
        // sa stiu cand  e legit si cand e comentariu. asta e doar in cazul in care
        // se refera la ce cred eu ca se refera, dar hey how could i know exactly

        if (strstr(buffer, "//") == NULL) {
            fprintf(file_output, "%s", buffer);
        }
    }

    fclose(file_input);
    fclose(file_output);
    free(file_name_input);
    free(file_name_output);
}

// ok asta e enervant pentru ca nu specifica un size anume la
// nr de cuvinte, deci realloc (kinda) (o sa vezi) here we go

// ok mi a venit o idee amuzanta sa o rezolv mai usor
// https://cdn.discordapp.com/emojis/1196212820262527086.png

// o alta metoda in loc de a face alocari la greu la metoda 1 ar fi
// sa numar cate \n-uri am in fisier si dupa sa ma intorc prin el sa
// bag intr un array normal cu un size pe care il stiu, dar ar fi lent

// as for efficiency, as zice ca primele 2 ar fi roughly equal? poate a doua
// metoda ar fi putiiiiiiin mai eficienta pentru extrem de multe date
int contains_word(char **s, char *word, int size) {
    if (word == NULL || s == NULL || size == 0) {
        return -1;
    }

    for (int i = 0; i < size; i++) {
        if (strcmp(word, s[i]) == 0) {
            return i;
        }
    }

    return -1;
}

int compare(const void *a, const void *b) {
    return *(int *)a < *(int *)b;
}

// urasc functia asta la cat de lunga e
void ex3_metoda_1() {
    // init stuff
    int total_size = 100, total_index = 0, unique_index = 0;
    char **word_list = (char**)safe_malloc(sizeof(char*) * total_size),
         *file_name = (char*)safe_malloc(100),
         file_path[150] = FOLDER_PATH;

    get_input_string("numele fisierului: ", file_name, 100);
    strcat(file_path, file_name);

    for (int i = 0; i < total_size; i++) {
        word_list[i] = (char*)safe_malloc(WORD_MAX_SIZE);
    }

    // actual solution
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("n ai fisier fraere");
        exit(1);
    }

    while (fgets(word_list[total_index], WORD_MAX_SIZE, file)) {
        if (strchr(word_list[total_index], '\n')) {
            word_list[total_index][strlen(word_list[total_index]) - 1] = '\0';
        }

        if (total_index == total_size - 1) {
            total_size *= 2;

            // allegedly are un leak aici dar nu il cred
            char **temp = (char**)safe_malloc(sizeof(char*) * total_size);
            memcpy(temp, word_list, sizeof(char*) * (total_size / 2));
            free(word_list);

            for (int i = total_size / 2; i < total_size; i++) {
                temp[i] = (char*)safe_malloc(WORD_MAX_SIZE);
            }

            word_list = temp;
        }

        total_index++;
    }

    // pe asta il aloc dupa ce stiu cate cuvinte am, also nu inteleg de ce
    // dar nu ma lasa sa compilez (desi ar trebui) cu frecv[total] = {0}, trebuie
    // sa ii trantesc schema de care mi ai zis
    char **unique_word_list = (char**)safe_malloc(sizeof(char*) * total_index);
    int *frecv = (int*)calloc(total_index, sizeof(int));
    if (frecv == NULL) {
        perror("n ai memorie fraere");
        exit(1);
    }

    for (int i = 0; i < total_index; i++) {
        int rez = contains_word(unique_word_list, word_list[i], unique_index);

        if (rez == -1) {
            unique_word_list[unique_index] = word_list[i];

            frecv[unique_index]++;
            unique_index++;
        }
        else {
            frecv[rez]++;
        }
    }

    for (int i = 0; i < unique_index; i++) {
        for (int j = i + 1; j < unique_index; j++) {
            if (frecv[i] < frecv[j]) {
                int temp = frecv[i];
                char *temp2 = unique_word_list[i];

                frecv[i] = frecv[j];
                frecv[j] = temp;

                unique_word_list[i] = unique_word_list[j];
                unique_word_list[j] = temp2;
            }
        }
    }

    for (int i = 0; i < unique_index; i++) {
        printf("%s apare de %d ori\n", unique_word_list[i], frecv[i]);
    }

    // free stuff
    for (int i = 0; i < total_size; i++) {
        free(word_list[i]);
    }

    fclose(file);
    free(file_name);
    free(word_list);
    free(unique_word_list);
    free(frecv);
}

// btw as fi facut asta cu multimap ul pe care coincidentally il am
// daca nu era facut doar pentru int, asa e prea mult de schimbat la el
void ex3_metoda_2() {
    // ia ca parametru o functie custom de free, dar
    // aici nu e neaparat nevoie de una sofisticata
    Sll *sll = createSll(free);

    char buffer[WORD_MAX_SIZE],
         *file_name = (char*)safe_malloc(100),
         file_path[150] = FOLDER_PATH;

    get_input_string("numele fisierului: ", file_name, 100);
    strcat(file_path, file_name);

    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("n ai fisier fraere");
        exit(1);
    }

    // cumva n am functie in biblioteca de contains(ceva)
    while (fgets(buffer, WORD_MAX_SIZE, file)) {
        int found = 0;
        if (strchr(buffer, '\n')) {
            buffer[strlen(buffer) - 1] = '\0';
        }

        for (Node *node = sll->head; node != NULL; node = node->next) {
            if (strcmp(node->data, buffer) == 0) {
                (*(int*)node->aparitii)++;
                found = 1;
                break;
            }
        }

        if (!found) {
            char *temp = (char*)safe_malloc(WORD_MAX_SIZE);
            memcpy(temp, buffer, WORD_MAX_SIZE);

            pushBack(sll, temp);
        }
    }

    bubbleSort(sll, compare);
    for (Node *node = sll->head; node != NULL; node = node->next) {
        printf("%s apare de %d ori\n", (char*)node->data, *(int*)node->aparitii);
    }

    fclose(file);
    free(file_name);
    freeSll(sll);
}

typedef struct student {
    char name[100];
    float note[3];
    float medie;
}Student;
 
void sort(Student students[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (students[i].medie < students[j].medie) {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
}

// aici chiar nu mai am chef sa fac nebunia cu malloc sa fie
// size "infinit" doar pentru ca nu zice in enunt, word it better
void ex4() {
    Student studenti[100];
    int nr_stud = 0;
    char buffer[100],
         *file_name = (char*)safe_malloc(100),
         file_path[150] = FOLDER_PATH;

    get_input_string("numele fisierului: ", file_name, 100);
    strcat(file_path, file_name);

    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("n ai fisier fraere");
        exit(1);
    }
 
    while (fgets(buffer, 100, file)) {
        if (strchr(buffer, '\n')) {
            buffer[strlen(buffer) - 1] = '\0';
        }
 
        char *p = strtok(buffer, ",");
        strcpy(studenti[nr_stud].name, p);

        p = strtok(NULL, ",");
        int note = 0;
        while (p != NULL) {
            studenti[nr_stud].note[note] = (float)atof(p);
            studenti[nr_stud].medie += studenti[nr_stud].note[note];
 
            note++;
            p = strtok(NULL, ",");
        }
        studenti[nr_stud].medie /= 3;
 
        nr_stud++;
    }

    sort(studenti, nr_stud);
 
    for (int i = 0; i < nr_stud; i++) {
        printf("%s are media %f\n", studenti[i].name, studenti[i].medie);
    }

    fclose(file);
    free(file_name);
}

typedef struct db {
    char produs[100];
    float pret;
}DB;

void adaugare(DB *db, int index) {
    char name[100];
    float pret;

    get_input_string("numele produsului: ", name, 100);
    get_input_float("pretul produsului: ", &pret, 0, 99999);

    strcpy(db[index].produs, name);
    db[index].pret = pret;
}

void afisare(DB *db, int size) {
    for (int i = 0; i < size; i++) {
        printf("Produs: %s\nPret: %f\n\n", db[i].produs, db[i].pret);
    }
}

// nici aici n am chef sa fac aia, also o sa presupun ca toate
// datele din db sunt valide to begin with
void ex5() {
    DB produse[100];
    char buffer[100],
         *file_name = (char*)safe_malloc(100),
         file_path[150] = FOLDER_PATH;
    int nr_prod = 0, meniu = 1, nr_prod_new = 0;

    get_input_string("numele fisierului: ", file_name, 100);
    strcat(file_path, file_name);

    FILE *file = fopen(file_path, "a+");
    if (file == NULL) {
        perror("n ai fisier fraere");
        exit(1);
    }

    while (fgets(buffer, 100, file)) {
        if (strchr(buffer, '\n')) {
            buffer[strlen(buffer) - 1] = '\0';
        }

        char *p = strtok(buffer, ",");
        strcpy(produse[nr_prod].produs, p);

        // btw ca tot ai zis, atof returneaza double in ciuda
        // acelui f care cel mai probabil vine de la float
        p = strtok(NULL, ",");
        produse[nr_prod].pret = (float)atof(p);

        nr_prod++;
    }

    while (meniu != 3) {
        char message[] = "1. Adaugare produs\n2. Listare produse\n3. Iesire\n";
        get_input_int(message, &meniu, 1, 3);

        switch (meniu) {
            case 1: {
                adaugare(produse, nr_prod);
                nr_prod++;
                nr_prod_new++;
            }
            case 2: {
                afisare(produse, nr_prod);
            }
            case 3: {
                break;
            }
            default: {}
        }
    }

    for (int i = nr_prod - nr_prod_new; i < nr_prod; i++) {
        fprintf(file, "%s,%f\n", produse[i].produs, produse[i].pret);
    }

    fclose(file);
    free(file_name);
}

int main() {
    // ex1();
    // ex2();
    // ex3_metoda_1();
    // ex3_metoda_2();
    // ex4();
    ex5();
}
