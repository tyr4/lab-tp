#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int binToInt(const char *s) {
    int len = (int)strlen(s);
    unsigned int nr = 0;

    for (int i = len - 1; i >= 0; i--) {
        // Pointer may be null when called from function 'binSub' da nu are cum sa fie null??
        nr += (int)pow(2, len - i - 1) * (s[i] - '0');
    }

    return nr;
}

void intToBin(unsigned int n, char *rez) {
    int i = 0;
    while (n) {
        n /= 2;
        // nu inteleg de ce tipa clion ca Narrowing conversion from 'int' to signed type 'char'
        // is implementation-defined, n am idee cum sa scap de asta sau daca fac ceva gresit 💀
        rez[i++] = (char)('0' + n % 2);
    }
    // aici + mai sus o linie la fel faza cu may be null
    rez[i]= '\0';
    strrev(rez);
}

// la astea doua *sper* ca nu se asteapta sa implementez un FAC sau ceva
void binAdd(char *dst,const char *a,const char *b) {
    intToBin(binToInt(a) + binToInt(b), dst);
}

void binSub(char *dst,const char *a,const char *b) {
    intToBin(binToInt(a) - binToInt(b), dst);
}

int get_msb_value(unsigned int n) {
    int p = 0;
    while (n) {
        p = p == 0? 1 : p << 1;
        n >>= 1;
    }
    return p;
}

unsigned int rgba(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) {
    // schema interesanta aici
    int red2, green2, blue2, alpha2;

    red2 = red;
    green2 = green;
    blue2 = blue;
    alpha2 = alpha;

    blue2 <<= 8;
    green2 <<= 16;
    red2 <<= 24;

    unsigned __int32 n = red2 + green2 + blue2 + alpha2;
    return n;
}

// i am schimbat putin numele
unsigned char getGreen(unsigned int color) {
    return color >> 16 & 0b11111111;
}

void ex4() {
    char s[31];

    printf("introduceti un numar in baza 2\n");
    scanf("%s", s);

    unsigned int nr = binToInt(s);

    printf("numarul %s in baza 2 este %u in baza 10", s, nr);
}

void ex5() {
    char *a = (char*)malloc(31 * sizeof(char)), *b = (char*)malloc(31 * sizeof(char));
    printf("introduceti a si b in baza 2\n");
    scanf("%s %s", a, b);

    char *suma = (char*)malloc(31 * sizeof(char));
    char *diferenta = (char*)malloc(31 * sizeof(char));

    binAdd(suma, a, b);
    binSub(diferenta, a, b);

    printf("suma: %s\ndiferenta: %s", suma, diferenta);

    free(a);
    free(b);
    free(suma);
    free(diferenta);
}

void ex6() {
    unsigned int n;
    int counter = 0;

    printf("introduceti un numar in baza 10\n");
    scanf("%u", &n);

    while (n) {
        if (n & 1)
            counter++;
        n >>= 1;
    }
    printf("%d biti de 1", counter);
}

void ex7() {
    unsigned int n;

    printf("introduceti un numar in baza 10\n");
    scanf("%u", &n);

    char s[32];
    intToBin(n, s);
    int len = (int)strlen(s);

    for (int i = 1; i < len - 1; i++) {
        if (s[i] == '0' && s[i + 1] == '1' && s[i - 1] == '1') {
            printf("la poz %d bitul 0 este inconjurat de biti de 1\n", i);
        }
    }
}

void ex8() {
    unsigned int n;
    int p = 1, size = 0;

    printf("introduceti un numar in baza 10\n");
    scanf("%u", &n);

    unsigned int copie = n;
    while (copie) {
        size++;
        copie >>= 1;
    }

    // parcurge bit cu bit (efectiv) de la dreapta la stanga
    for (int i = 0; i < size - 1; i++) {
        while (n & p && n & p * 2) {
            // conditia asta e gen daca enuntul se refera prin stergerea bitilor la a setarea lor pe 0
            // n = n & ~p
            n -= get_msb_value(n);  // asta efectiv sterge bitul
        }
        p <<= 1;
    }
    printf("noul numar este %u", n);
}

void ex9() {
    unsigned char red, green, blue, alpha;
    int temp;

    // absolut urasc sa citesc caractere
    printf("introduceti valorile rgba in baza 10:\n");
    printf("red: "); scanf("%d", &temp); red = temp;
    printf("green: "); scanf("%d", &temp); green = temp;
    printf("blue: "); scanf("%d", &temp); blue = temp;
    printf("alpha: "); scanf("%d", &temp); alpha = temp;

    unsigned __int32 n = rgba(red, green, blue, alpha);

    char *s = (char*)malloc(33 * sizeof(char));
    intToBin(n, s);

    printf("valoarea rgba (in baza 2) este: %s\n", s);
    free(s);

    unsigned char green_value = getGreen(n);
    printf("valoarea green (in baza 10) este: %d", green_value);
}

int main() {
    // ex4();
    // ex5();
    // ex6();
    // ex7();
    // ex8();
    ex9();
}