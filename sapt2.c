#include <math.h>
#include <stdint.h>
#include <stdio.h>

void copy_vector(int old[], int new[], int n) {
    for (int i = 0; i < n; i++) {
        new[i] = old[i];
    }
}

void bubble_sort_invers(int v[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (v[i] < v[j]) {
                int t = v[i];
                v[i] = v[j];
                v[j] = t;
            }
        }
    }
}

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

void ex5() {
    int n = citire();
    int v[n];
    citire_vector(v, n);
    int par[n], impar[n], p = 0, i = 0;
    for (int j = 0; j < n; j++) {
        if (v[j] & 1)
            impar[i++] = v[j];
        else par[p++] = v[j];
    }

    bubble_sort_invers(par, p);
    bubble_sort_invers(impar, i);
    for (int j = 0; j < i; j++)
        v[j] = impar[j];
    for (int j = 0; j < p; j++)
        v[j + i] = par[j];

    afisare(v, n, 0);
}

void ex6() {
    int max_secv[100], max_index = 0, secv[100], index = 0, max = 1, x = 1, y;
    printf("introduceti numere si terminati cu 0\n");

    scanf("%d", &x);
    secv[index++] = x, max_secv[max_index++] = x;

    while (x) {
        scanf("%d", &y);
        if (x < y) {
            secv[index++] = y;
            if (max < index) {
                max = index;
                copy_vector(secv, max_secv, index); // nu cred ca e cea mai eficienta metoda
                max_index = index;
            }
        }
        else {
            index = 0;
            secv[index++] = y;
        }
        x = y;
    }
    afisare(max_secv, max_index, 0);
}

void ex7() {
    int n = citire();
    int v[n];
    citire_vector(v, n);

    // se putea si sa le setez pe primul element dar facea urat cand
    // primul element se intampla sa fie si absolut minimul
    int min1 = INT32_MAX, min2 = INT32_MAX, min3 = INT32_MAX;
    for (int i = 0; i < n; i++) {
        if (min1 > v[i])
        {
            min3 = min2;
            min2 = min1;
            min1 = v[i];
        }
        else if (min2 > v[i]) {
            min3 = min2;
            min2 = v[i];
        }
        else if (min3 > v[i]) {
            min3 = v[i];
        }
    }
    printf("%d %d %d", min1, min2, min3);
}

int main() {
    // nu zice cifrele maxime ale lui n deci o sa presupun ca nu sunt la modul 10^6+

    // ex1();
    // ex2();
    // ex3();
    // ex4();
    // ex5();
    // ex6();
    ex7();
}