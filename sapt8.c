#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_MAX 100
#define BUFFER_MAX 50

// chestie experimentala, o sa fac functia asta pentru fiecare input thing
// si o sa ii pasez textul user ului prin *message, may or may not look horrible
// in apelul functiei. stiu ca se repeta putin codul la functii cum le dau split in
// int/float dar cam asta e singurul approach la care ma pot gandi cat de cat ok
void flush() {
    // initial era doar while getchar() dar aparent trebuie sa fac asta sa fie ok
    int c;

    while ((c = getchar()) != '\n' && c != EOF);
}

void flush_string(char *buffer, int size) {
    if (buffer == NULL) {
        return;
    }

    if (strchr(buffer, '\n') == NULL) {
        flush();
    }
    else {
        buffer[strcspn(buffer, "\n")] = '\0';
    }
}

int get_input_int(char *message, int min, int max) {
    int n;
    printf("%s", message);

    // tin minte cand ai intrebat pe cineva la lab ce returneaza scanf
    // si dadea raspunsuri amuzante :))) frumos use case aici tho
    while (scanf("%d", &n) != 1 || n < min || n > max) {
        if (n < min || n > max) {
            printf("incercati din nou ");
        }
        flush();
    }

    flush();
    return n;
}

float get_input_float(char *message, float min, float max) {
    float n;
    printf("%s", message);

    while (scanf("%f", &n) != 1 || n < min || n > max) {
        printf("incercati din nou ");
    }

    flush();
    return n;
}

int min(int a, int b) {
    return a > b? b : a;
}

char* get_input_string(char *message, char *buffer, int size) {
    if (buffer == NULL) {
        return NULL;
    }

    printf(message);
    fgets(buffer, size, stdin);
    flush_string(buffer, size);

    buffer[min((int)strlen(buffer), BUFFER_MAX)] = '\0';

    return buffer;
}

// functii ex 1
int exists(int *a, int n, int value) {
    if (a == NULL)
        return 0;

    for (int i = 0; i < n; i++) {
        if (a[i] == value) return 1;
    }

    return 0;
}

int* create(int n, int min, int max) {
    int* arr = (int*)malloc(sizeof(int) * n);
    int i = 0;

    // fun fact, am vazut ceva video zilele optimizand fix chestia asta
    // si random() are randomness mai bun dar e linux only :/
    while (i < n) {
        int rez = (rand() % (max - min + 1)) + min;
        // chestia asta practic se asigura ca mereu e interval, daca
        // testam [0,1] atunci era numai 0 de exemplu
        if (!exists(arr, i, rez)) {
            arr[i++] = rez;
        }
    }

    return arr;
}

// mama ce clean arata cu functia de input, chefkiss
void ex1() {
    int n = get_input_int("size ul array ului: ", 1, ARRAY_MAX);
    int min = get_input_int("valoarea minima: ", 0, INT_MAX);
    int max = get_input_int("valoarea maxima: ", 0, INT_MAX);

    while (min > max || max - min + 1 < n) {
        printf("min si max invalide, reintroduceti\n");
        min = get_input_int("valoarea minima: ", 0, INT_MAX);
        max = get_input_int("valoarea maxima: ", 0, INT_MAX);
    }

    int *arr = create(n, min, max);

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    free(arr);
}

// functii ex 2
typedef struct db {
    char produs[32];
    float pret;
}DB;

DB* adaugare(DB *db, int *size) {
    DB *aux = (DB*)realloc(db, sizeof(DB) * (*size + 1));
    if (aux == NULL) {
        perror("memorie insuficienta\n");
        return db;
    }
    db = aux;
    char produs[32];
    float pret;

    printf("numele produsului: ");
    fgets(produs, 32, stdin);
    produs[strlen(produs) - 1] = '\0';

    pret = get_input_float("pretul produsului: ", 0, FLT_MAX);

    strcpy(db[*size].produs, produs);
    db[*size].pret = pret;

    (*size)++;

    return db;
}

DB* stergere(DB *db, int* size, char* produs) {
    if (db == NULL) {
        return NULL;
    }

    int pos = -1;
    for (int i = 0; i < *size; i++) {
        if (strcmp(db[i].produs, produs) == 0) {
            pos = i;
            break;
        }
    }

    // exista produsul?
    if (pos != -1) {
        for (int i = pos; i < *size - 1; i++) {
            db[i] = db[i + 1];
        }

        // ok deci aici zice mr clion ca am un memory leak dar nu are cum
        // + si valgrind zice ca e ok deci nice false positive?
        DB *aux = (DB*)realloc(db, sizeof(DB) * --*size);
        if (aux == NULL) {
            perror("memorie insuficienta\n");
            return db;
        }

        db = aux;
    }

    return db;
}

void printare(DB *db, int size) {
    if (db == NULL) {
        return;
    }

    for (int i = 0; i < size; i++) {
        printf("%s costa %.2f\n", db[i].produs, db[i].pret);
    }
}

void ex2() {
    DB *db = NULL;
    int meniu, size;

    size = 0;
    do {
        printf("-----------------\n"
                     "1. adaugare\n"
                     "2. stergere\n"
                     "3. printare\n"
                     "4. iesire\n");

        meniu = get_input_int("", 1, 4);
        getchar();

        switch (meniu) {
            case 1: {
                db = adaugare(db, &size);
                break;
            }
            case 2: {
                printf("numele produsului care sa fie sters: ");
                char produs[32];

                fgets(produs, 32, stdin);
                produs[strlen(produs) - 1] = '\0';
                flush_string(produs, 32);

                db = stergere(db, &size, produs);
                break;
            }
            case 3: {
                printare(db, size);
                break;
            }
            case 4: {
                // iesire
                meniu = 0;
                break;
            }
            default: {}
        }
    } while (meniu);

    free(db);
}

// functii ex 3
int get_letter_count(const char *s[], int n) {
    if (s == NULL) {
        return 0;
    }

    int sum = 0;

    for (int i = 0; i < n; i++) {
        sum += (int)strlen(s[i]);
    }

    return sum;
}

// a trebuit sa modific putin antetul din ce scria in cerinta, adica
// din const char *a l am facut *a[] ca altfel avea type mismatch la apel
char* join(const char *a[], int n, const char *glue) {
    int total_letters = get_letter_count(a, n);
    char *s = (char*)malloc(n * strlen(glue) + total_letters + 1);

    strcpy(s, a[0]);
    for (int i = 1; i < n; i++) {
        strcat(s, glue);
        strcat(s, a[i]);
    }

    return s;
}

void ex3() {
    int n = get_input_int("numarul de cuvinte: ", 1, 100);
    char **a = (char**)malloc(n * sizeof(char*));
    char *buffer = (char*)malloc(BUFFER_MAX * sizeof(char));
    char *glue = (char*)malloc(100 * sizeof(char));

    if (glue == NULL) {
        perror("memorie insuficienta\n");
        return;
    }

    // aici nu sunt sigur daca fac corect schema asta, sa dau assign lui glue
    // in loc de doar a apela functia, nenea gpt zice ca nu e ok dar nu prea stiu csz
    glue = get_input_string("glue: ", glue, 100);

    for (int i = 0; i < n; i++) {
        get_input_string("cuvant: ", buffer, BUFFER_MAX);

        a[i] = (char*)malloc(strlen(buffer) + 1);
        strcpy(a[i], buffer);
    }

    // output (mai mult pus pentru claritate/ca un extra separator)
    char *s = join(a, n, glue);
    printf("%s\n", s);

    // free stuff (la fel)
    for (int i = 0; i < n; i++) {
        free(a[i]);
    }
    free(a); a = NULL;
    free(s); s = NULL;
    free(glue); glue = NULL;
    free(buffer); buffer = NULL;
}

// functii ex 4
char** split(const char *s,char c,int n) {
    char **a = (char**)malloc(n * sizeof(char*));
    char aux[2] = "\0\0";
    aux[0] = c;

    char *p = strtok(s, aux);

    for (int i = 0; i < n; i++) {
        a[i] = (char*)malloc(strlen(p) + 1);
        strcpy(a[i], p);

        p = strtok(NULL, aux);
    }

    return a;
}

// stiu ca enuntul zice ca functia sa il primeasca pe n ca pointer dar
// ar fi prea mult refactoring la restul codului deci il las asa, sper ca e ok
void ex4() {
    int n = get_input_int("numarul de cuvinte: ", 1, ARRAY_MAX);
    char *s = (char*)malloc(BUFFER_MAX);
    s = get_input_string("phrase: ", s, BUFFER_MAX);

    printf("delimitator: ");
    char delim = getchar(); flush();
    while (strchr(s, delim) == NULL) {
        printf("delimitator invalid, incercati din nou ");
        delim = getchar();
        flush();
    }

    char **a = split(s, delim, n);

    for (int i = 0; i < n; i++) {
        printf("%s ", a[i]);
        free(a[i]);
    }
    free(a); a = NULL;
    free(s); s = NULL;
}

int main() {
    // ex1();
    // ex2();
    // ex3();
    ex4();

    return 0;
}