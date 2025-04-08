#include <stdio.h>
#include <stdlib.h>

// swap fancy, ms autocomplete de sugestie (l as fi facut cu aux in mod normal)
void swap(int *a, int *b) {
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

int contains_vector(int n, int v1[], int m, int v2[]) {
    int found = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (v1[i] == v2[j]) {
                found++;
                break;
            }
        }
    }
    return found == m;
}

void ex1() {
    int *a = (int*)malloc(sizeof(int)), *b = (int*)malloc(sizeof(int));
    printf("a: ");
    scanf("%d", a);

    printf("b: ");
    scanf("%d", b);

    if (*a < *b) {}
    else {
        swap(a, b);
    }

    printf("a si b in ordine crescatoare: %d %d", *a, *b);

    free(a);
    free(b);
}

void ex2() {
    int n;
    printf("size ul stelei: ");
    scanf("%d", &n);
    if (n <= 2)
        return;

    // un alt approach fara if
    char a[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = ' ';
        }
        a[i][i] = '*';
        a[i][n - i - 1] = '*';
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%c ", a[i][j]);
        }
        printf("\n");
    }
}

void ex3() {
    // enuntul zicea sa fie deja initializati deci da
    int v1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int v2[5] = {4, 5, 6, 7, 8};

    int rez = contains_vector(10, v1, 5, v2);
    printf("al doilea %sse afla in primul vector", rez == 1? "" : "nu ");
}

// ex 4 e copy paste de la saptamana 3 ex 7

// ex 5 e copy paste de la saptamana 2 ex 3 💀

int main() {
    // ex1();
    // ex2();
    ex3();
}
