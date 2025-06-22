#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void print_matrix(int *m[], int linie, int col) {
    for (int i = 0; i < linie; i++) {
        for (int j = 0; j < col; j++) {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
}

void free_matrix(void **m, int lineCount) {
    if (m == NULL) {
        return;
    }

    for (int i = 0; i < lineCount; i++) {
        free(m[i]);
    }

    free(m);
}

void* safe_malloc(size_t size) {
    void *p = malloc(size);

    if (p == NULL) {
        perror("n ai memorie");
        exit(EXIT_FAILURE);
    }

    return p;
}

void** matrix_alloc(int n, int m, size_t size) {
    // asta e array ul de pointeri la pointeri, iar toti pointerii
    // dupa cate stiu acelasi size, deci pot pune sizeof(void*) linistit
    void **matrix = safe_malloc(n * sizeof(void*));

    for (int i = 0; i < n; i++) {
        matrix[i] = safe_malloc(m * size);
    }

    return matrix;
}

// identic cu ce ne ai aratat la lab :)
// prima data am incercat sa ma gandesc la o conditie care
// o poate face in O(n) dar nu am putut o gasi in a timely manner
void matrix_pattern_ex1(int **a, int n, int start) {
    if (a == NULL || n < 1) {
        return;
    }

    for (int i = start; i < n - start; i++) {
        a[start][i] = n - start;
        a[n - 1 - start][i] = n - start;
        a[i][start] = n - start;
        a[i][n - 1 - start] = n - start;
    }
}

// am facut o asa cu void** ca sa o pot folosi si la alt
// exercitiu, altfel nu ma omoram cu whatever se intampla aici..
void** transpusa(void **a, int line, int col, size_t size) {
    void **transp = matrix_alloc(col, line, size);

    for (int i = 0; i < col; i++) {
        for (int j = 0; j < line; j++) {
            // mi a trebuit putin gpt ca sa fac
            // schema asta general purpose, interesting tho

            // ce pot vedea ca face e ca umbla direct cu adresele,
            // asta e foarte scary daca gresesti logica operatiilor
            void *src  = (char*)a[j] + i * size;
            void *dest = (char*)transp[i] + j * size;

            memcpy(dest, src, size);

        }

        memcpy((char*)transp[i] + line * size, "\0", size);
    }

    return transp;
}

void ex1() {
    int n;
    get_input_int("un nr de linii si coloane intre 2 si 30: ", &n, 2, 30);

    int **a = (int**)matrix_alloc(n, n, sizeof(int));

    for (int i = n; i >= n / 2; i--) {
        matrix_pattern_ex1(a, n, n - i);
    }

    print_matrix(a, n, n);
    free_matrix((void**)a, n);
}

void ex2() {
    int n;
    char cuv[16];

    get_input_int("un nr de cuvinte intre 2 si 20 cu max 15 litere: ", &n, 2, 20);

    char **a = (char**)matrix_alloc(n, 16, sizeof(char));

    for (int i = 0; i < n; i++) {
        printf("introduceti un cuvant in matrice pe linia %d: ", i);
        scanf("%15s", a[i]);

        // am nevoie sa nu fie sirul plin de uninit stuff
        int len = (int)strlen(a[i]);
        for (int j = len; j < 16; j++) {
            a[i][j] = 1;
        }

        a[i] = strlwr(a[i]);
    }

    printf("cititi un cuvant inafara matricei: ");
    scanf("%15s", cuv);
    printf("\n");

    strcpy(cuv, strlwr(cuv));

    // brooo abia acum m am prins la ce se refera enuntul, EVIL
    char **transp = (char**)transpusa((void**)a, n, 16, sizeof(char));

    for (int i = 0; i < n; i++) {
        if (strstr(transp[i], cuv)) {
            printf("exista cuvantul pe coloana %d\n", i + 1);
        }
    }

    free_matrix((void**)a, n);
    free_matrix((void**)transp, n);
}

int cmp(const int *a, const int *b) {
    return *a - *b;
}

void ex3() {
    int n, m;
    get_input_int("un nr de linii intre 2 si 30: ", &m, 2, 30);
    get_input_int("un nr de coloane intre 2 si 30: ", &n, 2, 30);

    // no way, nu cred ca are clion un asa warning
    // Arguments passed in possibly wrong order. Review following
    // parameters and their corresponding arguments: n(m), m(n)

    // ba dar acuma chiar nu inteleg de ce in probleme ni se dau
    // matrici m x n in loc de n x m, asta e tactica de confuzie
    int **a = (int**)matrix_alloc(m, n, sizeof(int));
    int lines_concat[m * n];
    int index = 0;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("a[%d][%d] = ", i, j);
            scanf("%d", &a[i][j]);
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            lines_concat[index++] = a[i][j];
        }
    }

    qsort(lines_concat, m * n, sizeof(int), cmp);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = lines_concat[i * m + j];
        }
    }

    print_matrix(a, m, n);
    free_matrix((void**)a, m);
}

void ex4() {
    int n, m;
    int col_max = 0, secv = 1, max = 1;

    get_input_int("un nr de linii intre 2 si 30: ", &m, 2, 30);
    get_input_int("un nr de coloane intre 2 si 30: ", &n, 2, 30);

    int **a = (int**)matrix_alloc(m, n, sizeof(int));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("a[%d][%d] = ", i, j);
            get_input_int("", &a[i][j], -INT_MAX, INT_MAX);
        }
    }

    int **transp = (int**)transpusa((void**)a, m, n, sizeof(int));

    for (int i = 0; i < n; i++) {
        secv = 1;
        for (int j = 1; j < m; j++) {
            if (transp[i][j] > transp[i][j - 1]) {
                secv++;
            }

            else {
                break;
            }
        }

        if (max < secv) {
            max = secv;
            col_max = i;
        }
    }

    printf("\ncoloana cu secventa cea mai mare de numere strict crescatoare este %d", col_max + 1);

    free_matrix((void**)transp, m);
    free_matrix((void**)a, n);
}

// atat de annoying e cand se citesc 2 matrici
void ex5() {
    int n, m, found = 0;
    get_input_int("un nr de linii intre 2 si 30: ", &m, 2, 30);
    get_input_int("un nr de coloane intre 2 si 30: ", &n, 2, 30);

    int **a = (int**)matrix_alloc(m, n, sizeof(int));
    int **b = (int**)matrix_alloc(m, n, sizeof(int));
    int concatA[m * n], concatB[m * n];

    // mna, poate mi ar fi trebuit o functie de read_matrix dar
    // acum e prea tarziu

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("a[%d][%d] = ", i, j);
            get_input_int("", &a[i][j], -INT_MAX, INT_MAX);

            concatA[i * m + j] = a[i][j];
        }
    }

    printf("\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("b[%d][%d] = ", i, j);
            get_input_int("", &b[i][j], -INT_MAX, INT_MAX);

            concatB[i * m + j] = b[i][j];
        }
    }

    // algoritm blana si lent ca...

    // ok deci aici ideea mea e sa caute fiecare element
    // din A in B, si daca dau ambele match atunci le da nuke
    // din ambele array uri. initial m as fi gandit sa il stearga
    // la propriu, dar s ar cam strica logica cu indecsii + ar fi super
    // lent, al doilea approach e sa ii setez pe o alta valoare pe care
    // stiu ca nu o voi atinge, dar din pacate vreau sa includ tot
    // intervalul de int, deci :)) chiar nu stiu ce altceva as folosi
    // in acest caz, asa ca uhh o sa ma folosesc de faptul ca nu
    // folosesc ultima valoare din intervalul INT_MAX dupa cum poti
    // vedea in get_input_int()

    // daca ar fi sa nu fac chestia de mai sus, atunci uhhhhhh
    // cred ca as sorta array urile de concatA si concatB, si as merge
    // cu un double pointer approach pe fiecare array:
    // daca concatA[i] == concatB[j] atunci i++ si j++, else delete concatB[j]
    // si continua acest loop, si daca size ul lui concatA < concatB atunci nu
    // e inclus tot A in B, actually lemme test (zici ca am diary aici lol)

    // wait abia acum realizez ca ambele matrici au acelasi size, initial
    // ma gandeam la size uri diferite (nu ma intreba de ce) deci merge
    // doar sa le sortez si sa le compar direct cu prima metoda faowfweoifjaoeiwf
    // a fost un bun exercitiu at least :))

    // metoda 1
    // for (int i = 0; i < m * n; i++) {
    //     for (int j = 0; j < m * n; j++) {
    //         if (concatA[i] == concatB[j] != -INT_MAX - 1) {
    //             found++;
    //
    //             concatA[i] = -INT_MAX - 1;
    //             concatB[j] = -INT_MAX - 1;
    //             break;
    //         }
    //     }
    // }

    // metoda 2
    qsort(concatA, m * n, sizeof(int), cmp);
    qsort(concatB, m * n, sizeof(int), cmp);

    found = m * n;
    for (int i = 0; i < m * n; i++) {
        if (concatA[i] != concatB[i]) {
            found = 0;
            // break;
        }
    }

    printf("\nmatricea A %seste inclusa in matricea B", found == m * n? "" : "nu ");

    free_matrix((void**)a, m);
    free_matrix((void**)b, m);
}

int main() {
    // ex1();
    // ex2();
    // ex3();
    // ex4();
    ex5();

    return 0;
}
