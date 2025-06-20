#ifndef COMPLEXE_H
#define COMPLEXE_H

#include <stdbool.h>

typedef struct complex {
    float a, b;
} Complex;

Complex adunare(Complex x, Complex y);
Complex scadere(Complex x, Complex y);
Complex inmultire(Complex x, Complex y);
bool isEqual(Complex x, Complex y);
void printComplex(Complex z);


#endif //COMPLEXE_H
