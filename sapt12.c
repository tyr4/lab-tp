#include <stdio.h>
#include <stdlib.h>
#include "sapt12.h"

// nu ii doresc celui mai mare dusman al meu sa
// lucreze cu asa ceva

// also m ai luat prin surprindere cand ai zis ca n ai
// stiut la ex 5 lul, nu raman problemele alea an de an?

#define divizibil(A, B) (A % B == 0)

#define eroare(A) (A == NULL)

#define ceva float

#define ARRAY(tip, nume, ...) tip nume[] = {__VA_ARGS__}

void ex1() {
    int a, b;

    do {
        printf("a si b:\n");
        scanf("%d %d", &a, &b);
    } while (b != 0);

    printf("%d\n", divizibil(a, b));
}

void ex2() {
    char *p;
    int *a = (int*)malloc(sizeof(int));
    *a = 12;

    if (eroare(a)) {
        perror("e null bos");
        exit(1);
    }

    if (eroare(p)) {
        perror("e null bos");
        exit(1);
    }

    free(a);
}

// ex 3, zice doar sa o definesc deci na
typedef struct Pt_float {
    ceva x, y;
}Punct;

// dark magic aici ngl
void ex4() {
    // hmm "variable a is only used in unevaluated context", wonder
    // what that means, nu ma prea ajuta google
    ARRAY(int, a, 1, 2, 6, 4, 3, 2);
    int a_len = sizeof(a) / sizeof(a[0]);

    printf("size %d", a_len);
}

// cine naiba scrie ex astea diabolice part 2 (ex 5)
void ex5() {
    LINE;
}

int main() {
    // ex1();
    // ex2();
    // ex4();
    ex5();

    return 0;
}