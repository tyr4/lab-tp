#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "multimi.h"
#include "complexe.h"

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

void get_input_int(char *message, int *n, int min, int max) {
    printf("%s", message);

    while (scanf("%d", n) != 1 || *n < min || *n > max) {
        printf("incercati din nou ");
        flush();
    }

    flush();
}

void get_input_float(char *message, float *n, float min, float max) {
    printf("%s", message);

    while (scanf("%f", n) != 1 || *n < min || *n > max) {
        printf("incercati din nou ");
        flush();
    }

    flush();
}

int* initEx1A(int *sizeA) {
    *sizeA = 0;
    char buffer[10];

    get_input_int("numarul de elemente din prima multime: ", sizeA, 1, 100);
    int *a = (int*)safe_malloc(*sizeA * sizeof(int));

    for (int i = 0; i < *sizeA; i++) {
        sprintf(buffer, "a[%d]: ", i);

        get_input_int(buffer, &a[i], -INT_MAX, INT_MAX);
    }

    return a;
}

int* initEx1B(int *sizeB) {
    *sizeB = 0;
    char buffer[10];

    get_input_int("numarul de elemente din a doua multime: ", sizeB, 1, 100);
    int *b = (int*)safe_malloc(*sizeB * sizeof(int));

    for (int i = 0; i < *sizeB; i++) {
        sprintf(buffer, "b[%d]: ", i);

        get_input_int(buffer, &b[i], -INT_MAX, INT_MAX);
    }

    return b;
}

void printArray(int *arr, int size) {
    if (size == 0) {
        printf("vida");
    }

    else for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n");
}

void ex1() {
    // o sa modific putin cerinta pentru ca e boring sa
    // hard-codez array urile, asa o sa fac si la 2
    int meniu = 0, sizeA, sizeB, sizeC = 0;
    char buffer[100] = "1. intersectie\n"
                       "2. reuniune\n"
                       "3. diferenta\n"
                       "4. reintroducere date\n"
                       "5. iesire\n";

    int *a = initEx1A(&sizeA);
    int *b = initEx1B(&sizeB);

    while (1) {
        get_input_int(buffer, &meniu, 1, 5);

        switch (meniu) {
            case 1: {
                int *c = intersectie(a, sizeA, b, sizeB, &sizeC);

                printf("intersectia este: ");
                printArray(c, sizeC);

                free(c);
                break;
            }

            case 2: {
                int *c = uniune(a, sizeA, b, sizeB, &sizeC);

                printf("reuniunea este: ");
                printArray(c, sizeC);

                free(c);
                break;
            }

            case 3: {
                int *c = diferenta(a, sizeA, b, sizeC, &sizeA);

                printf("diferenta este: ");
                printArray(c, sizeA);

                free(c);
                break;
            }

            case 4: {
                free(a);
                free(b);

                a = initEx1A(&sizeA);
                b = initEx1B(&sizeB);

                break;
            }

            case 5: {
                free(a);
                free(b);

                return;
            }

            default: {}
        }
    }
}

void getComplexInput(Complex *z) {
    get_input_float("partea reala: ", &z->a, -FLT_MAX, FLT_MAX);
    get_input_float("partea imaginara: ", &z->b, -FLT_MAX, FLT_MAX);
}


void ex2() {
    Complex x, y, z = {0, 0};
    int meniu = 0;

    // vai de mine cata meniu..
    char buffer[200] = "1. adunare\n"
                       "2. scadere\n"
                       "3. inmultire\n"
                       "4. verificare egalitate\n"
                       "5. afisare rezultat\n"
                       "6. reintroducere x si y\n"
                       "7. iesire\n";

    printf("Numarul x:\n");
    getComplexInput(&x);

    printf("\nNumarul y:\n");
    getComplexInput(&y);

    while (1) {
        get_input_int(buffer, &meniu, 1, 7);

        switch (meniu) {
            case 1: {
                z = adunare(x, y);
                break;
            }

            case 2: {
                z = scadere(x, y);
                break;
            }

            case 3: {
                z = inmultire(x, y);
                break;
            }

            case 4: {
                printf("x si y %ssunt egale\n", isEqual(x, y)? "" : "nu ");
                break;
            }

            case 5: {
                printComplex(z);
                break;
            }

            case 6: {
                printf("Numarul x:\n");
                getComplexInput(&x);

                printf("\nNumarul y:\n");
                getComplexInput(&y);

                break;
            }

            case 7: {
                return;
            }

            default: {}
        }
    }
}

int main() {
    // ex1();
    ex2();

    return 0;
}