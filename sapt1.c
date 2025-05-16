#include <stdio.h>

void ex1() {
    printf("\"Ion\"\t20\\1\n"
           "\"Ana\"\t21\\2\n"
           "\"Maria\"\t19\\3\n");
}

void ex3() {
    int n;
    printf("lungimea turnului de stele: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            printf(" ");
        }
        printf("*\n");
    }
}

void ex4() {
    int n;
    printf("un numar pt cifrele impare: ");
    scanf("%d", &n);
    int cifre = 0, copie = n;
    while (n) {
        if (n % 10 % 2) cifre++;
        n /= 10;
    }
    printf("in %d exista %d cifre impare\n", copie, cifre);
}

void ex5() {
    int n;
    printf("introduceti numere pana cand e 0\n");
    scanf("%d", &n);
    int prev, ok = 1;
    scanf("%d", &prev);
    if (n > prev)
        ok = 0;
    else {
        while (prev != 0) {
            n = prev;
            scanf("%d", &prev);
            if (n > prev) {
                ok = 0;
                break;
            }
        }
    }
    printf("\nseria este %screscatoare", ok? "" : "des");
}

void ex6() {
    printf("introduceti x1 y1 x2 y2 si x y\n");
    int x1, y1, x2, y2, x, y;
    scanf("%d %d %d %d %d %d", &x1, &y1, &x2, &y2, &x, &y);

    if (x > x1 && x < x2 && y > y1 && y < y2)
        printf("punctul (%d, %d) este in interiorul dreptunghiului\n", x, y);
    else if ((x == x1 || x == y2) && (y == y1 || y == y2))
        printf("punctul (%d, %d) este pe latura dreptunghiului\n", x, y);
    else
        printf("punctul (%d, %d) nu este pe latura/in dreptunghi\n", x, y);
}

void ex7() {
    int ok = 0;
    printf("introduceti perechile [a, b] si [c, d]\n");
    int a, b, c, d;
    ok = 0;
    scanf("%d %d %d %d", &a, &b, &c, &d);

    // conditia asta verifica toate lungimile intervalelor, gen daca [a,b] e inclus in [b,d] sau invers etc etc
    if (a >= c && b <= d)
        ok = 1;
    if (a <= c && b <= d && b >= c)
        ok = 1;
    if (a <= c && b >= d)
        ok = 1;
    if (a >= c && b <= d)
        ok = 1;


    // if ((a >= c && b <= d) || !(a >= c && b <= d) || (a >= c && b >= d) || !(a >= c && b >= d))
    //     ok = 1;

    printf("\n%sexista suprapunere intre intervalele [%d, %d] si [%d, %d]", ok? "" : "nu ", a, b, c, d);
}

int main() {
    // ex1();
    // ex3();
    // ex4();
    // ex5();
    // ex6();
    ex7();
}