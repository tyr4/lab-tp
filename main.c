#include <stdio.h>

int citire() {
    int n;
    printf("lungimea vectorului:");
    scanf("%d", &n);

    return n;
}

void eliminare(int pos, int v[], int n) {
    for (int i = pos; i < n - 1; i++) {
        v[i] = v[i + 1];
    }
    v[n - 1] = 0;
}

void afisare(int v[], int n, int invers) {
    if (invers) {
        for (int i = n - 1; i >= 0; i--) {
            printf("%d ", v[i]);
        }
    }
    else {
        for (int i = 0; i < n; i++) {
            printf("%d ", v[i]);
        }
    }
    printf("\n");
}

void ex1() {
    int n = citire();
    int v[n];

    int frecv[1000];
    for (int i = 0; i < 1000; i++)
        frecv[i] = 0;

    for (int i = 0; i < n; i++) {
        printf("v[%d]=", i);
        scanf("%d", &v[i]);
        frecv[v[i]]++;
    }

    // metoda 1 (nu pastreaza ordinea dar e mai eficienta)
    for (int i = 0; i < n; i++) {
        if (frecv[v[i]] > 1) {
            frecv[v[i]]--;
            eliminare(i, v, n);
            n--;
            i--;
        }
    }

    // metoda 2 (pastreaza ordinea dar dublu for)
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (v[i] == v[j]) {
                eliminare(j, v, n);
                n--;
                i--;
            }
        }
    }

    afisare(v, n, 0);
}

void ex2() {
    int n = 0, v[100], x = -1, par[100], impar[100], p = 0, i = 0;
    while (x) {
        printf("v[%d]=", n);
        scanf("%d", &x);
        if (x)
            v[n++] = x;
    }

    for (int j = 0; j < n; j++) {
        if (v[j] & 1)
            impar[i++] = v[j];
        else par[p++] = v[j];
    }
    afisare(par, p, 1);
    afisare(impar, i, 1);
}

int main() {
    // la ex unde nu zice cifrele maxime ale lui n o sa presupun
    // ca nu sunt la modul 10^6+

    // ex1();
    ex2();
}