#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FOLDER_PATH "D:/CLionProjects/chestii tp/"
#define FILENAME_MAX 100
#define BUFFER_MAX 10000

// (putin heavy in comments ca fac yapping random)

// btw la astea binare, nu am inteles exact daca ar trebui sa fie extensia neaparat
// .bin, dar am observat ca daca deschid un .txt in modul binar il trateaza practic la fel

// uhh pentru alea cu linia de comanda o sa dau comment la unu dintre main uri,
// sper ca ai shortcut sa dai uncomment :))

// filler, aceleasi functii ca alte sapt, skip
void* safe_malloc(size_t size) {
    void *p = malloc(size);

    if (p == NULL) {
        perror("Failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }

    return p;
}

void flush() {
    int c;

    while ((c = getchar()) != '\n' && c != EOF);
}

void flush_string(char *buffer) {
    if (buffer == NULL) {
        return;
    }

    if (strchr(buffer, '\n') == NULL) {
        flush();
    }
}

void get_input_int(char *message, int *n, int min, int max) {
    printf("%s", message);

    while (scanf("%d", n) != 1 || *n < min || *n > max) {
        printf("incercati din nou ");
        flush();
    }

    flush();
}

void get_input_string(char *message, char *buffer, int size) {
    if (buffer == NULL) {
        return;
    }

    printf(message);
    fgets(buffer, size, stdin);
    flush_string(buffer);

    buffer[strcspn(buffer, "\n")] = '\0';
}

// no more filler

// hmmm
FILE* open_file(const char* filename, const char* mode) {
    // tehnic asta foloseste exact cata memorie are nevoie, dar era si optiunea sa
    // il declar global cu un FILENAME_MAX si atunci se aloca doar o data in tot programul
    // dar am zis sa il las asa sa fie mai lizibil, who knows cine o fi path intr o mie de
    // variabile globale :))
    char *path = (char*)safe_malloc(strlen(FOLDER_PATH) + strlen(filename) + 1);

    strcpy(path, FOLDER_PATH);
    strcat(path, filename);

    FILE *file = fopen(path, mode);

    if (file == NULL) {
        perror("nu s a putut deschide fisierul fraere");
        exit(EXIT_FAILURE);
    }

    free(path);
    return file;
}

long get_file_size(FILE* file) {
    long size;

    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fseek(file, 0, SEEK_SET);

    return size;
}

void ex1() {
    char filename[FILENAME_MAX + 1], c;
    get_input_string("numele fisierului: ", filename, FILENAME_MAX);

    FILE *f = open_file(filename, "rb");
    long size = get_file_size(f);

    for (long i = 0; i < size; i++) {
        // chestia cu 16 bytes/linie
        if (i % 16 == 0)
            printf("\n");

        fread(&c, 1, 1, f);
        if (c >= 32)
            printf("%c ", c);
        else {
            // a trebuit sa caut cum se face schema asta dar e
            // prea frumoasa sa nu o las, practic adauga padding
            // sa fie minim 2 digits si le ia pe ultimele 2, merge si
            // pentru coduri ascii mai mari dar aici nu se va intampla, still cool

            // also, pe windows fiecare newline pare sa fie insotit de \r\n,
            // deci afiseaza DA la fiecare newline, la final nu are nimic iar
            // in exemplu nu inteleg de unde a scos un \0, poate asa e pe linux? idr
            printf("%0X", c & 0xFF);
        }
    }

    fclose(f);
}


// aici e putin cam vag, nu zice anume daca prin "continut identic" se refera
// la aceleasi cuvinte/litere/numere/whatever indiferent de pozitie in fisier sau
// o copie 1:1, adica daca as da copy paste la fisier... o sa merg pe a doua
void ex2() {
    char filename1[FILENAME_MAX + 1], filename2[FILENAME_MAX + 1], temp;

    get_input_string("nume fisier 1: ", filename1, FILENAME_MAX);
    get_input_string("nume fisier 2: ", filename2, FILENAME_MAX);

    FILE *f1 = open_file(filename1, "rb");
    FILE *f2 = open_file(filename2, "rb");

    // hmm tehnic pot face schema asta ca am vazut parametrul in debugger
    // trebuie sa dau un read inainte ca _base e NULL pana cand fac asta
    // si nu am nici cea mai mica idee de ce
    fread(&temp, 1, 1, f1);
    fread(&temp, 1, 1, f2);
    int result = strcmp(f1->_base, f2->_base);

    printf("fisierele %sau acelasi continut\n", result == 0 ? "" : "nu ");

    // alternativ, as face doua buffere egale cu size urile, as baga in ele totul si
    // as compara dupa

    fclose(f1);
    fclose(f2);
}

// daca nu era intervalul de reprezentare asa de mare la asta, ar fi fost un
// exercitiu mai misto sa dai plot la puncte intr o  matrice si sa o afisezi
void ex3() {
    // seed ul pentru generatorul de numere random, iar unrelated
    // (scriu comentariul asta dupa al doilea), dar asta implementeaza
    // un linear congruential generator si are perioada RAND_MAX
    srand(1);

    int n, xCoord, yCoord, minXCoord = 1000, minYCoord = 1000, minDistance = 1000000, tempDistance;
    FILE *output = open_file("out.txt", "wb");

    get_input_int("numarul de puncte de generat: ", &n, 1, 100);

    // unrelated dar de ce e imi arata clion ca RAND_MAX e egal cu 2147418112 lol,
    // unless im dumb si nu stiu sa il calculez (0x7fff), de obicei ar fi egal cu INT_MAX
    for (int i = 0; i < n; i++) {
        // practic genereaza numere uniform distribuite in intervalul [-1000, 1000)
        // nu prea are cum sa atinga capatul de 1000 din cauza cum e implementat in C
        xCoord = (int)(-1000 + 2000 * (rand() * 1.0f / RAND_MAX));
        yCoord = (int)(-1000 + 2000 * (rand() * 1.0f / RAND_MAX));

        tempDistance = xCoord * xCoord + yCoord * yCoord;

        if (tempDistance < minDistance) {
            minDistance = tempDistance;
            minXCoord = xCoord;
            minYCoord = yCoord;
        }

        // nu sunt sigur daca e neaparat corect sa le afisez intr un fisier
        // binar asa? ar lua un byte pentru fiecare char ma gandesc? atunci e ok
        // hmm, sunt curios cum ar fi cu extended ascii care trece de un byte
        fprintf(output, "%d %d\n", xCoord, yCoord);
        printf("(%d, %d)\n", xCoord, yCoord);
    }

    printf("punctul cel mai apropriat de originea axelor este (%d, %d)", minXCoord, minYCoord);
    fclose(output);
}

typedef struct db {
    char name[101];
    int zi, luna, an;
}DB;

int adaugare(DB *db, int size) {
    if (db == NULL) {
        return size;
    }

    get_input_string("numele persoanei: ", db[size].name, 100);
    get_input_int("ziua nasterii: ", &db[size].zi, 1, 31);
    get_input_int("luna nasterii: ", &db[size].luna, 1, 12);
    get_input_int("anul nasterii: ", &db[size].an, 0, 2025);

    return size + 1;
}

void salvare_binar(DB *db, int size) {
    if (db == NULL) {
        return;
    }

    char filename[FILENAME_MAX + 1];
    get_input_string("numele fisierului: ", filename, FILENAME_MAX);

    // "scriind direct structurile din memorie" o sa presupun ca
    // vrea sa le rescriu, weird wording tho

    // also, am verificat si merge si la reading data daca
    // o deschid in reading mode, deci nice
    FILE *file = open_file(filename, "wb");


    for (int i = 0; i < size; i++) {
        // nvm am facut niste research intre timp la adaugare
        fwrite(&db[i], sizeof(DB), 1, file);
    }

    fclose(file);
}

int load_db(DB *db) {
    if (db == NULL) {
        return 0;
    }

    int size = 0, endSize;
    char filename[FILENAME_MAX + 1];
    get_input_string("numele fisierului: ", filename, FILENAME_MAX);

    FILE *file = open_file(filename, "r+b");

    // ceva extrem de tampit incoming
    fseek(file, 0, SEEK_END);
    endSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    while (ftell(file) != endSize) {
        fread(&db[size++], sizeof(DB), 1, file);
    }

    // asta ii da wipe complet, initial punea toti bytes-ii (suna atat de ciudat)
    // pe 0 dar tot existau in fisier
    fclose(file);
    file = open_file(filename, "wb");
    fclose(file);

    return size;
}

int find_age(DB *db, struct tm local) {
    if (db == NULL) {
        return 0;
    }

    int varsta = local.tm_year + 1900 - db->an;

    // mi a trebuit putin de gpt la conditie ca e aiurea formatata
    // libraria, chestii precum ianuarie = 0 sunt enervante, aproape o nimerisem tho
    if (db->luna > local.tm_mon + 1 || (db->luna == local.tm_mon + 1 && db->zi > local.tm_mday)) {
        varsta--;
    }

    return varsta;
}

// tehnic intotdeauna vor fi toate persoanele loaded in db
// deci pot doar sa trec prin ea fara griji ca ratez pe cineva
void afisare(DB *db, int size) {
    if (db == NULL) {
        return;
    }

    // DE CE TIME() RETURNEAZA UN EPOCH TIME SI LOCALTIME() RETURNEAZA
    // O STRUCTURA BRO
    time_t currentTime = time(NULL);
    struct tm *local = localtime(&currentTime);

    for (int i = 0; i < size; i++) {
        int age = find_age(&db[i], *local);
        printf("%s are %d ani\n", db[i].name, age);
    }

}

void ex4() {
    // eventual ar putea fi declarata ca un pointer ca sa
    // pot face realloc dupa dar n am chef sa i o fac iar
    DB db[100];
    char text_meniu[] = "1. adaugare\n"
                        "2. salvare in fisier binar\n"
                        "3. load persoane in db\n"
                        "4. afisare\n"
                        "5. iesire\n";
    int size = 0, meniu = 0;

    while (1) {
        get_input_int(text_meniu, &meniu, 1, 5);

        switch (meniu) {
            case 1: {
                size = adaugare(db, size);
                break;
            }

            case 2: {
                salvare_binar(db, size);
                break;
            }

            case 3: {
                size = load_db(db);
                break;
            }

            case 4: {
                afisare(db, size);
                break;
            }

            case 5: {
                return;
            }

            default: {}
        }
    }
}

// ex 5 gen

// int main(int argc, char *argv[]) {
//     float sum = 0;
//
//     for (int i = 1; i < argc; i++) {
//         sum += atof(argv[i]);
//     }
//
//     // oare de ce daca fac 1.0 * argc il considera double dar
//     // majoritatea chestiilor returneaza float, like bro e atat de annoying
//     // si in c# patesc la fel cu unele chestii
//     sum /= (float)(argc - 1);
//
//     printf("media numerelor este %.2f", sum);
//
//     return 0;
// }

// si ex 6

// cine naiba scrie enunturile astea diabolice

// int main(int argc, char *argv[]) {
//     // ignora cat de weird sunt declarate astea
//     char buffer[BUFFER_MAX + 1];
//     char total[5 * BUFFER_MAX + 1] = "";
//     FILE *file;
//
//     for (int i = 1; i < argc - 1; i++) {
//         file = open_file(argv[i], "rb");
//
//         fread(buffer, sizeof(char), BUFFER_MAX, file);
//         strcat(total, buffer);
//
//         fclose(file);
//     }
//
//     file = open_file(argv[argc - 1], "wb");
//     fwrite(total, sizeof(char), strlen(total), file);
//     fclose(file);
//
//     return 0;
// }

int main() {
    // ex1();
    // ex2();
    // ex3();
    ex4();

    return 0;
}