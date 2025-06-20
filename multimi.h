#pragma once

#ifndef MULTIMI_H
#define MULTIMI_H

typedef enum { Intersection, Union, Difference } operationMode;

int existsInArray(int *arr, int size, int x);

int intersectionCondition(int *a, int i, int *b, int j, int *newArr, int sizeNew, int sizeA, int sizeB);
int unionCondition(int *a, int i, int *b, int j, int *newArr, int sizeNew, int sizeA, int sizeB);
int differenceCondition(int *a, int i, int *b, int j, int *newArr, int sizeNew, int sizeA, int sizeB);

int elementToAdd(int a, int b, int *new, int sizeNew, operationMode mode);

// putini parametri..
int* addToSetConditional(int *a, int sizeA, int *b, int sizeB, int *sizeNew,
                         int (*condition)(int*, int, int*, int, int*, int, int, int),
                         operationMode mode);

int* intersectie(int *a, int sizeA, int *b, int sizeB, int *sizeNew);
int* uniune(int *a, int sizeA, int *b, int sizeB, int *sizeNew);
int* diferenta(int *a, int sizeA, int *b, int sizeB, int *sizeNew);

#endif //MULTIMI_H
