#include <math.h>
#include <stdio.h>
#include <string.h>

int vocale(char s[21]) {
    int len = (int)strlen(s), v = 0;

    for (int i = 0; i < len; i++) {
        if (strchr("aeiouAEIOU", s[i])) {
            v++;
        }
    }
    return v;
}

int contains_letters(char s1[], char s2[]) {
    int found = 0, len_s1 = (int)strlen(s1), len_s2 = (int)strlen(s2);
    for (int i = 0; i < len_s1; i++) {
        for (int j = 0; j < len_s2; j++) {
            if (s1[i] == s2[j]) {
                found++;
            }
        }
    }
    return found >= len_s1;
}

void ex1() {
  	// il initializez pe temp in cazul in care niciun cuvant nu are vocale
    char cuv[21] = "", temp[21] = "";
    int max = 0, current = 0;

    printf("introduceti cuvinte (iesiti cu caracterul '.')\n");
    for (;;) {
        scanf("%s", cuv);
        if (strcmp(cuv, ".") == 0)
            break;

        current = vocale(cuv);
        if (max < current) {
            max = current;
            strcpy(temp, cuv);
        }
    }
    printf("cuvantul cu maximul de %d vocale este: %s\n", max, temp);
}

void ex2() {
    char nume[21], temp[21];
    int varsta;

    printf("introduceti nume (iesiti cu caracterul '.')\n");
    scanf("%s", nume);
    getchar();

    printf("varsta lui %s:", nume);
    scanf("%d", &varsta);

    int varsta_pers_sortat = varsta;

    for (;;) {
        scanf("%s", temp);
        getchar();
        if (strcmp(temp, ".") == 0)
            break;

        printf("varsta lui %s:", temp);
        scanf("%d", &varsta);

        if (strcmp(temp, nume) < 0) {
            varsta_pers_sortat = varsta;
            strcpy(nume, temp);
        }
    }

    printf("varsta primei persoane: %d", varsta_pers_sortat);
}

// cam ambiguu enuntul la asta
void ex3() {
    char linie1[201], linie2[201];
    printf("introduceti linii\n");

    fgets(linie1, 201, stdin);
    for (;;) {
        fgets(linie2, 201, stdin);
        if (linie2[0] == '\n')
            break;

        int rez = contains_letters(linie1, linie2);
        printf("linia curenta %scontine literele liniei precedente\n\n", rez == 1? "" : "nu ");

        strcpy(linie1, linie2);
    }

}

void ex4() {
    char produs[201], min_produs[201];
    float min_price;

    printf("introduceti produse\n");
    fgets(produs, 201, stdin);
    // lumea era prea perfecta daca nu avea \n la final
    produs[strlen(produs) - 1] = '\0';

    min_price = (float)atof(strstr(produs, ",") + 1);
    strcpy(min_produs, produs);

    for (;;) {
        fgets(produs, 201, stdin);
        if (produs[0] == '\n')
            break;

        produs[strlen(produs) - 1] = '\0';
        float price = (float)atof(strstr(produs, ",") + 1);
        if (min_price > price) {
            min_price = price;
            strcpy(min_produs, produs);
        }
    }

    // urasc asta, dar sterge pretul din sir pentru un print frumos
    min_produs[strstr(min_produs, ",") - min_produs] = '\0';
    printf("produsul cu pretul minim de %.2f este %s", min_price, min_produs);
}

void ex5() {
    char sentence[201];
    int zi, luna, an;
    printf("introduceti propozitii\n");

    for (;;) {
        fgets(sentence, 201, stdin);
        if (sentence[0] == '\n')
            break;  // mai merge si return in cazul asta

        // ar fi fost prea frumos daca sscanf returna toate match urile din string
        // sau ceva in loc sa fac schema asta
        char *p = strtok(sentence, " ");
        while (p) {
            if (sscanf(p, "%d/%d/%d", &zi, &luna, &an) == 3) {
                printf("Zi: %d\nLuna: %d\nAn: %d\n\n", zi, luna, an);
            }
            p = strtok(NULL, " ");
        }
    }
}

int main() {
    // ex1();
    // ex2();
    // ex3();
    // ex4();
    ex5();
}