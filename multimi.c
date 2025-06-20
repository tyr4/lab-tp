#include <stdio.h>
#include <stdlib.h>

// e atat de overly complicated dar ma lasa sa adaug
// cate vreau dupa destul de usor deci hey

typedef enum {Intersection, Union, Difference} operationMode;

int existsInArray(int *arr, int size, int x) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == x) {
            return 1;
        }
    }

    return 0;
}

int intersectionCondition(int *a, int i, int *b, int j, int *newArr, int sizeNew, int sizeA, int sizeB) {
    return a[i] == b[j] && !existsInArray(newArr, sizeNew, a[i]);
}

int unionCondition(int *a, int i, int *b, int j, int *newArr, int sizeNew, int sizeA, int sizeB) {
    return (!existsInArray(newArr, sizeNew, a[i]) || !existsInArray(newArr, sizeNew, b[j])) && a[i] != b[j];
}

int differenceCondition(int *a, int i, int *b, int j, int *newArr, int sizeNew, int sizeA, int sizeB) {
    return !existsInArray(b, sizeB, a[i]) && !existsInArray(newArr, sizeNew, a[i]);
}

int elementToAdd(int a, int b, int *new, int sizeNew, operationMode mode) {
    switch (mode) {
        case Difference:
        case Intersection:
            return a;

        case Union: {
            if (existsInArray(new, sizeNew, a)) {
                return b;
            }

            return a;
        }

        default: {}
    }

    return 0;
}

int* addToSetConditional(int *a, int sizeA, int *b, int sizeB, int *sizeNew, int (*condition)(int*, int, int*, int, int*, int, int, int), operationMode mode) {
    // assumes worst case scenario
    int maxSize = sizeA > sizeB? sizeA : sizeB;
    int *new = (int*)malloc(maxSize * sizeof(int));

    if (new == NULL) {
        return NULL;
    }

    *sizeNew = 0;
    for (int i = 0; i < sizeA; i++) {
        for (int j = 0; j < sizeB; j++) {
            if (condition(a, i, b, j, new, *sizeNew, sizeA, sizeB)) {
                // lmao ma intrebam de ce nu mergea inainte, meanwhile
                // incrementam adresa si puneam pe indexul ala instead

                // aici face o decizie pe care dintre a si b sa il adauge din
                // cauza diferitelor conditii, aproape nu era sa mearga si sa sterg tot
                new[(*sizeNew)++] = elementToAdd(a[i], b[j], new, *sizeNew, mode);

                // verifica iar toata nebunia pentru ca si a[i] si b[j] pot fi bagate in
                // array intr un singur loop, ceea ce cam strica the previous logic
                if (mode == Union && condition(a, i, b, j, new, *sizeNew, sizeA, sizeB)) {
                    new[(*sizeNew)++] = elementToAdd(a[i], b[j], new, *sizeNew, mode);
                }
            }
        }
    }

    return new;
}

int* intersectie(int *a, int sizeA, int *b, int sizeB, int *sizeNew) {
    operationMode mode = Intersection;

    return addToSetConditional(a, sizeA, b, sizeB, sizeNew, intersectionCondition, mode);
}

int* uniune(int *a, int sizeA, int *b, int sizeB, int *sizeNew) {
    operationMode mode = Union;

    return addToSetConditional(a, sizeA, b, sizeB, sizeNew, unionCondition, mode);
}

int* diferenta(int *a, int sizeA, int *b, int sizeB, int *sizeNew) {
    operationMode mode = Difference;

    return addToSetConditional(a, sizeA, b, sizeB, sizeNew, differenceCondition, mode);
}