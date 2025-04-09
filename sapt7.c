#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// mini warning, e putin cam heavy in comments asta pentru ca enunturile lasa atata loc
// de interpretare

// functii ex 1
typedef struct nr_aparitii {
    int n;
    char cuvant[51];
}Nr_aparitii;

int increase_appearances(Nr_aparitii *appearances, char *cuv, int n) {
    for (int i = 0; i < n; i++) {
        if (strcmp(cuv, appearances[i].cuvant) == 0) {
            appearances[i].n++;
            return n;
        }
    }
    // il adauga in caz ca nu exista
    appearances[n].n = 1;
    strcpy(appearances[n].cuvant, cuv);
    return ++n;
}

void ex1() {
    Nr_aparitii aparitii[100];
    int index = 0;
    char cuvant[51];
    printf("introduceti cuvinte\n");
    for (;index < 100;) {
        scanf("%s", cuvant);
        if (strcmp(cuvant, ".") == 0) {
            break;
        }
        index = increase_appearances(aparitii, cuvant, index);
    }

    for (int i = 0; i < index; i++) {
        printf("%s apare de %d ori\n", aparitii[i].cuvant, aparitii[i].n);
    }
}

// functii ex 2
typedef struct punct {
    int x, y;
}Punct;

float calc_distance(int x1, int y1, int x2, int y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void find_max_distance(Punct *puncte, int n) {
    int x1 = puncte[0].x,
        y1 = puncte[0].y,
        x2 = puncte[1].x,
        y2 = puncte[1].y;
    int t_x1, t_y1, t_x2, t_y2;
    float max = calc_distance(x1, y1, x2, y2);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            // cat de frumos ar fi aratat daca puteam sa returnez 4 valori usor intr o functie
            // gen tuple unpacking ca in python
            t_x1 = puncte[i].x,
            t_y1 = puncte[i].y,
            t_x2 = puncte[j].x,
            t_y2 = puncte[j].y;

            float distance = calc_distance(t_x1, t_y1, t_x2, t_y2);
            if (max < distance) {
                max = distance;
                x1 = t_x1;
                y1 = t_y1;
                x2 = t_x2;
                y2 = t_y2;
            }
        }
    }
    printf("distanta maxima este %.2f intre punctele (%d, %d) si (%d, %d)", max, x1, y1, x2, y2);
}

void ex2() {
    Punct puncte[100];
    int n;
    printf("numarul de puncte (x,y) in plan: ");
    scanf("%d", &n);

    printf("introduceti puncte de genul (x,y)\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &puncte[i].x, &puncte[i].y);
    }

    find_max_distance(puncte, n);
}

// functii ex 3
typedef struct student {
    float note[5];
    char nume[51];
    float medie; // o adaug aici sa imi fie mai usor
}Student;

void calc_medie_studenti(Student *studenti, int n) {
    float temp = 0;
    for (int i = 0; i < n; i++) {
        temp = 0;
        int nr_note = 0;
        // pot sa fac doar cu o singura variabila asta dar am zis sa fie mai
        // clar cu j separat de nr_note
        // also, conditia de nota != -1 e ca asa le initializez sa stiu cand sa ma opresc
        for (int j = 0; studenti[i].note[j] != -1 && j < 5; j++, nr_note++) {
            temp += studenti[i].note[j];
        }
        temp /= (float)nr_note;
        studenti[i].medie = temp;
    }
}

void sort_descrescator(Student *studenti, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            // ok deci funny story aici, la test acel bubble sort *era* normal, in sensul ca
            // sorta crescator, dar in functiile de split parcurgeam array ul invers si efectiv
            // uitasem cum implementasem aia, dar aici chiar il face invers
            if (studenti[i].medie < studenti[j].medie) {
                Student temp = studenti[i];
                studenti[i] = studenti[j];
                studenti[j] = temp;
            }
        }
    }
}

void ex3() {
    // enunt ambiguu, deci:
    // 1. nu zice cati studenti sunt deci o sa presupun ca nu sunt gen 10^6
    // 2. o sa presupun ca fiecare student este unic, adica nu il citeste pe
    // gigel si dupa se intoarce sa ii mai puna o nota dupa 5 alti studenti
    Student studenti[100];
    int index = 0, temp_note;
    for (;index<100; index++) {
        printf("cititi numele studentului (se iese cu .)\n");
        fgets(studenti[index].nume, sizeof(studenti[index].nume), stdin);

        for (int i = 0; i < 5; i++) {
            studenti[index].note[i] = -1;
        }
        // scot \n de la final pentru pretty print
        studenti[index].nume[strlen(studenti[index].nume) - 1] = '\0';

        // nu precizeaza conditia magica de iesire dar o sa o pun eu
        if (strcmp(studenti[index].nume, ".") == 0)
            break;

        printf("cate note are %s? ", studenti[index].nume);
        // am testat niste chestii pe asta si se cam duce daca ii dai un float,
        // gen daca ii zici ca ai 5.4 note atunci ia prima nota ca fiind .4 xd
        scanf("%d", &temp_note);
        while (temp_note < 1 || temp_note > 5) {
            printf("introduceti intre 1 si 5 note plz\n");
            scanf("%d", &temp_note);
        }
        for (int i = 0; i < temp_note; i++) {
            printf("nota %d: ", i + 1);
            scanf("%f", &studenti[index].note[i]);
        }
        // \n de la ultima nota strica urmatoru scanf for some unbeknownst reason
        getchar();
    }

    calc_medie_studenti(studenti, index);
    sort_descrescator(studenti, index);
    for (int i = 0; i < index; i++) {
        printf("Nume: %s\tMedie: %.2f\n", studenti[i].nume, studenti[i].medie);
    }
}

// functii ex 4
typedef enum {Programator = 1, Designer} Functie;

typedef struct angajat {
    char name[101];
    float salariu; // float i guess?? idk tbh
    Functie functie;
    union {
        char portfolio[101];
        char languages[3][20];
    }info;
}Angajat;

Angajat citire() {
    Angajat angajat;
    int functie;

    printf("numele angajatului: ");
    fgets(angajat.name, 101, stdin);
    angajat.name[strlen(angajat.name) - 1] = '\0';

    printf("salariul angajatului: ");
    scanf("%f", &angajat.salariu);

    // nu prea am idee cum altcumva as citi astea, also am zis sa o citesc asa sa
    // nu intre de atatea multe ori direct in angajat.functie
    printf("ce functie are?\n1 - programator\n2 - designer ");
    scanf("%d", &functie);
    while (functie != 1 && functie != 2) {
        printf("introduceti o functie valida plz\n");
        scanf("%d", &functie);
    }
    angajat.functie = functie;
    switch (functie) {
        case 1: {
            int nr_limbaje;

            // initializare sir ca sa pot da loop pe el fara trucuri
            for (int i = 0; i < 3; i++) {
                strcpy(angajat.info.languages[i], "");
            }

            printf("cate limbaje stie programatorul? ");
            scanf("%d", &nr_limbaje);
            while (nr_limbaje < 1 || nr_limbaje > 3) {
                printf("introduceti un numar intre 1 si 3 plz\n");
                scanf("%d", &nr_limbaje);
            }

            for (int i = 0; i < nr_limbaje; i++) {
                printf("limbajul %d: ", i + 1);
                scanf("%s", angajat.info.languages[i]);
            }
            break;
        }
        case 2: {
            printf("adresa portofoliului: ");
            scanf("%s", angajat.info.portfolio);
            break;
        }
        default: {
            perror("cumva ai trecut prin validare, in which case bravo");
            exit(69);
        }

    }
    // FINALLY!!!!
    printf("--------------------------\n");
    return angajat;
}

void afisare(Angajat *a) {
    int functie = a->functie;

    printf("Numele angajatului:\t%s\n", a->name);
    printf("Salariul angajatului:\t%.2f\n", a->salariu);
    printf("Functia angajatului:\t%s\n", a->functie == 1? "Programator" : "Designer");
    switch (functie) {
        case 1: {
            printf("Limbajele cunoscute de catre angajat:\n");
            for (int i = 0; i < 3; i++) {
                if (strcmp(a->info.languages[i], "") != 0) {
                    printf("- %s\n", a->info.languages[i]);
                }
                else break;
            }
            break;
        }
        case 2: {
            printf("Portofoliul designerului: %s", a->info.portfolio);
            break;
        }
        default: {}
    }
    printf("\n--------------------------\n");
}

void ex4() {
    int n;
    printf("introduceti cati angajati are firma: ");
    scanf("%d", &n);
    Angajat angajat[n];
    for (int i = 0; i < n; i++) {
        getchar();
        angajat[i] = citire();
    }

    for (int i = 0; i < n; i++) {
        afisare(&angajat[i]);
    }
}

int main() {
    // ex1();
    // ex2();
    // ex3();
    ex4();
}