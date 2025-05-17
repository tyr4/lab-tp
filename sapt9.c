#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>

#define ARRAY_MAX 100
#define BUFFER_MAX 100

// ignore dis, copy paste de la saptamana trecuta
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

int get_input_int(char *message, int min, int max) {
    int n;
    printf("%s", message);

    while (scanf("%d", &n) != 1 || n < min || n > max) {
        printf("incercati din nou ");
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
        flush();
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
    flush_string(buffer);

    if (strchr(buffer, '\n')) {
        buffer[strcspn(buffer, "\n")] = '\0';
    }

    return buffer;
}

// can stop ignoring :)

// functii ex1
typedef struct produse {
    char categorie[ARRAY_MAX];
    char nume[ARRAY_MAX];
    float pret;
}Produs;

Produs citire_produs() {
    Produs produs;

    get_input_string("categoria: ", produs.categorie, BUFFER_MAX);
    get_input_string("nume: ", produs.nume, BUFFER_MAX);
    produs.pret = get_input_float("pret: ", 0, FLT_MAX);

    return produs;
}

int sortare_produs_dual(const Produs *a, const Produs *b) {
    // are categories equal? if not, sort by category. if yes, sort by name
    int c = strcmp(a->categorie, b->categorie);

    if (c != 0)
        return c;

    return strcmp(a->nume, b->nume);
}

void ex1() {
    int n = get_input_int("numarul de produse: ", 1, ARRAY_MAX);
    Produs *produs = (Produs*)malloc(n * sizeof(Produs));

    for (int i = 0; i < n; i++) {
        printf("Produsul %d\n", i + 1);
        produs[i] = citire_produs();
    }

    qsort(produs, n, sizeof(Produs), sortare_produs_dual);

    for (int i = 0; i < n; i++) {
        printf("\nProdusul %d\n", i + 1);
        printf("categoria %s\nnumele %s\npret %f\n", produs[i].categorie, produs[i].nume, produs[i].pret);
    }
    free(produs);
}

// functii ex 2
void prime(int n, void (*f)(int)) {
    f(2);
    for (int i = 3; i <= n; i += 2) {
        f(i);
    }
}

void isPrime(int n) {
    if (n == 1) return;

    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            return;
        }
    }

    printf("%d este prim\n", n);
    // return 1;
}

// exercitiul cere ca functia din prime sa fie void deci nu pot pasa
// isPrime ca int, asa ca se repeta verificarea pentru prime aici
void cifre_prim(int n) {
    int ok = 1;

    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            ok = 0;
            break;
        }
    }

    if (ok) {
        int rez = 0, copy = n;

        while (copy) {
            copy /= 10;
            rez++;
        }

        printf("numarul %d are %d cifre\n", n, rez);
    }
}

// ok putin yapping aici. enuntul e complet lipsit de logica unless nu stiu sa citesc.
// zice "Funcția va genera toate numerele PARE din intervalul [0,n]", si dupa aceea
// se asteapta sa, citez, "primul va afișa fiecare număr PRIM, iar al doilea va afișa
// numărul de cifre din fiecare număr PRIM" DAR NU POATE FI PRIM DACA E NUMAR PAR INAFARA
// DE 2, asa ca l am facut sa treace prin toate numerele impare instead
void ex2() {
    int n = get_input_int("capatul intervalului: ", 1, INT_MAX);

    prime(n, isPrime);
    prime(n, cifre_prim);
}

// functii ex 3
float patrat(float n) {
    return n * n;
}

float cub(float n) {
    return n * n * n;
}

float idk_add_123(float n) {
    return n + 123;
}

float *map(float *a, int n, float (*f)(float)) {
    if (a == NULL) {
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        a[i] = f(a[i]);
    }

    return a;
}

void ex3() {
    int n = get_input_int("size ul array ului: ", 1, ARRAY_MAX);

    float *a = (float *)malloc(sizeof(float) * n);
    for (int i = 0; i < n; i++) {
        printf("a[%d] = ", i);
        *(a + i) = get_input_float("", 1, FLT_MAX);
    }

    // a = map(a, n, idk_add_123);
    // a = map(a, n, patrat);
    a = map(a, n, cub);
    for (int i = 0; i < n; i++) {
        printf("%f ", *(a + i));
    }

    free(a);
}

// functii ex 4
bool test(int n, int min, int max,...) {
    if (min > max || n <= 0) {
        printf("invalid data");
        return false;
    }

    int current;
    va_list args;

    va_start(args, max);
    for (int i = 0; i < n; i++) {
        current = va_arg(args, int);
        if (current < min || current > max) {
            printf("%d nu se afla in intervalul [%d, %d]\n", current, min, max);
            return false;
        }
    }

    va_end(args);
    printf("toate valorile se afla in interval\n");
    return true;
}

void ex4() {
    // asta efectiv va da crash pentru orice type diferit de int
    // si din ce am cautat, nu exista validare la runtime cu biblioteca
    // asta deci tzeapa. aparent exista versiunea upgraded in C++0x tho
    test(5, 1, 100, 1, 2, 3, 4, 5);
    test(5, 1, 3, 1, 1, 1, 1, 1, 1, 1, 4, 4,4 ,4 ,44,4, 4,4 ,4 ,4);
    test(5, 69, 420, 123, 420, 111, 43, 83);
    test(1, 1, 100, 0);
    test(-1, -2, -1, 2, 3, 4, 5, 6, 7, 8);
}

// functii ex 5
char* format(char* s,...) {
    va_list args;
    va_start(args, s);

    char buffer[BUFFER_MAX];
    int len = vsnprintf(buffer, sizeof(buffer), s, args);

    char *rez = (char*)malloc(len);
    strcpy(rez, buffer);

    va_end(args);
    return rez;
}

void ex5() {
    char *s;
    s = format("hello world cmf am %d mere si %d pere din bananiere", 4, 5);
    // s = format("%s a zburat cu forta a %f porumbei in aer", "gigel", 1234.56);
    // s = format("oh, youre %d me?", "approaching");
    // s = format("i cant %x you without getting %s", "beat", "smoothie");
    // s = format("%domain expansion: malevolent crashing");

    printf("%s", s);
    free(s);
}

bool descrescator(int a, int b) {
    return a < b;
}

bool par_impar(int a, int b) {
    if (a % 2 == 1 && b % 2 == 0) return false;
    if (a % 2 == 0 && b % 2 == 1) return true;

    return a < b;
}

void bubble_sort_conditional(int a[], int n, bool (*func)(int, int)) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n ; j++) {
            if (func(a[i], a[j])) {
                int temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}

void ex_extra_lab_2_5() {
    int n = get_input_int("size ul array ului: ", 1, ARRAY_MAX);
    int a[n];

    for (int i = 0; i < n; i++) {
        printf("a[%d] = ", i);
        a[i] = get_input_int("", 1, INT_MAX);
    }

    bubble_sort_conditional(a, n, descrescator);
    bubble_sort_conditional(a, n, par_impar);

    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    // efectiv 40 de linii (+ inca vreo 10 daca vrei sa pui functia de validare
    // a input ului), comparat cu 73 de linii cat am scris la test, nice improvement
}

int main() {
    // ex1();
    // ex2();
    // ex3();
    // ex4();
    // ex5();
    ex_extra_lab_2_5();
}