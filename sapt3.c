#include <stdio.h>
#include <stdlib.h>

int citire_n() {
    int n;
    printf("dimensiunea vectorului:");
    scanf("%d", &n);

    return n;
}

void citire_vector(int n, int *v) {
    int *end = v + n;
    for (int i = 0; v + i != end; i++) {
        printf("v[%d] = ", i);
        scanf("%d", v + i);
    }
}

int isPalindrome(int n, int *v) {
    for (int i = 0; i < n / 2; i++) {
        if (*(v + i) == *(v + n - i - 1)) {}
        else {
            return 0;
        }
    }
    return 1;
}

void ex1() {
    double x = 0.5, y = -2.1;

    double *aux_x, *aux_y, aux;
    aux_x = &x, aux_y = &y;
    aux = *aux_y;

    y = *aux_x;
    x = aux;
    printf("x = %f, y = %f", x, y);
}

int global;
void ex2() {
    int local;
    printf("global \t-> %p\nlocal \t-> %p\n", &global, &local); // variabila locala este situata prima in memorie

}

void ex3() {
    long x, y;
    printf("%lld", &x - &y); // rezultatul este 1 => sunt situate consecutiv in memorie
}

void ex4() {
    int n = citire_n();
    if (n <= 0 || n > 10)
        return;

    int *v = (int*)malloc(n * sizeof(int));
    citire_vector(n, v);

    int duplicate1 = 0, duplicate2 = 0;

    // metoda 1
    int *frecv = (int*)malloc(1000 * sizeof(int));
    for (int i = 0; i < 1000; i++)
        *(frecv + i) = 0;

    for (int i = 0; i < n; i++) {
        (*(frecv + *(v + i)))++;
    }

    for (int i = 0; i < 1000; i++) {
        if (*(frecv + i) > 1) {
            duplicate1 += *(frecv + i) - 1;
        }
    }

    // metoda 2
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (*(v + i) == *(v + j) && *(v + j) != -1) {
                duplicate2++;
                *(v + j) = -1;  // il modific sa nu se puna acelasi numar de mai multe ori din cauza cum merge for ul
            }
        }
    }

    free(v);
    free(frecv);

    printf("exista %d (%d) duplicate", duplicate1, duplicate2);
}

void ex5() {
    int n = citire_n();
    if (n <= 0 || n > 10)
        return;

    int *v = (int*)malloc(n * sizeof(int));
    citire_vector(n, v);

    int rez = isPalindrome(n, v);
    printf("elementele vectolurui %salcatuiesc un palindrom", rez == 0? "nu " : "");

    free(v);
}

void ex6() {
    int n = 0, x;
    int *v = (int*)malloc(10 * sizeof(int));
    while (123456) {
        printf("v[%d] = ", n);
        scanf("%d", &x);
        if (x == 0) {
            break;
        }
        *(v + n++) = x;
        if (n <= 0 || n > 10)
            return;
    }

    int end = *(v + n - 1);
    for (int i = n - 1; i >= 0; i--) {
        *(v + i) = *(v + i - 1);
    }
    *v = end;

    printf("vectorul rotit la dreapta: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", *(v + i));
    }

    free(v);
}

void ex7() {
    int n = citire_n();
    if (n <= 0 || n > 10)
        return;

    int *v = (int*)malloc(n * sizeof(int));
    citire_vector(n, v);

    int secv = 1, max = 1, x = *v;
    for (int i = 1; i < n; i++) {
        if (x < *(v + i)) {
            secv++;
            if (max < secv) {
                max = secv;
            }
        }
        else {
            secv = 1;
        }
        x = *(v + i);
    }
    printf("secventa maxima este formata din %d elemente", max);

    free(v);
}

int main() {
    // ex1();
    // ex2();
    // ex3();
    // ex4();
    // ex5();
    // ex6();
    ex7();
}