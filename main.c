#include <math.h>
#include <stdio.h>

void citire_vector(int v[], int n) {
    for (int i = 0; i < n; i++) {
        printf("v[%d]=", i);
        scanf("%d", &v[i]);
    }
    printf("\n");
}

int citire() {
    int n;
    printf("lungimea vectorului:");
    scanf("%d", &n);
    printf("\n");

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

void ex3() {
    int n = citire();
    int v[20];
    citire_vector(v, n);

    int m = citire();
    int w[20];
    citire_vector(w, m);

    int pos;
    printf("pozitia la care sa fie inserat vectorul m:");
    scanf("%d", &pos);

    int temp[abs(n - pos)], t_size = 0;
    for (int i = pos; i < n; i++)
        temp[t_size++] = v[i];

    for (int i = 0; i < m; i++) {
        v[i + pos] = w[i];
    }
    for (int i = 0; i < t_size; i++) {
        v[pos + m + i] = temp[i];
    }
    n += m;

    afisare(v, n, 0);
}

void ex4() {
    int n = citire();
    int v[10];
    citire_vector(v, n);

    int m = citire();
    int w[10];
    citire_vector(w, m);

    int intersectie[10], reuniune[20], i = 0, r = 0;
    for (int j = 0; j < n; j++) {
        reuniune[r++] = v[j];
        for (int k = 0; k < m; k++) {
            if (v[j] == w[k]) {
                intersectie[i++] = v[j];
                break;
            }
        }
    }
    for (int j = 0; j < m; j++)
        reuniune[r++] = w[j]; // combina n si m

    // copy paste aia de la ex1 sa scoata duplicatele
    for (int j = 0; j < r; j++) {
        for (int k = j + 1; k < r; k++) {
            if (reuniune[j] == reuniune[k]) {
                eliminare(j, reuniune, r);
                r--;
                j--;
            }
        }
    }
    printf("intersectie:\n");
    afisare(intersectie, i, 0);

    printf("reuniune:\n");
    afisare(reuniune, r, 0);
}

int main() {
    // la ex unde nu zice cifrele maxime ale lui n o sa presupun
    // ca nu sunt la modul 10^6+

    // ex1();
    // ex2();
    // ex3();
    ex4();

}