#include <stdio.h>

void eliminare(int pos, int v[], int n) {
    for (int i = pos; i < n - 1; i++) {
        v[i] = v[i + 1];
    }
}

void afisare(int v[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

int main() {
    // la ex unde nu zice cifrele maxime ale lui n o sa presupun
    // ca nu sunt la modul 10^6+

    // ex 1
    int n;
    int frecv[1000];
    printf("introduceti lungimea vectorului: ");
    scanf("%d", &n);
    printf("\n");

    int v[n];
    for (int i = 0; i < n; i++) {
        printf("v[%d] = ", i);
        scanf("%d", &v[i]);
        frecv[v[i]]++;
    }

    for (int i = 0; i < n; i++) {
        if (frecv[v[i]] > 1)
            eliminare(i, v, n);
    }
    afisare(v, n);
}