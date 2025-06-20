#include <stdio.h>
#include <stdbool.h>

// nu am sa numesc fila cpx ca wtf is clarity dupa

typedef struct complex {
    float a, b;
}Complex;

Complex adunare(Complex x, Complex y) {
    Complex z;

    z.a = x.a + y.a;
    z.b = x.b + y.b;

    return z;
}

Complex scadere(Complex x, Complex y) {
    Complex z;

    z.a = x.a - y.a;
    z.b = x.b - y.b;

    return z;
}

Complex inmultire(Complex x, Complex y) {
    // (a+bi)(a+bi) = a^2 + 2abi - b^2
    Complex z;

    z.a = x.a * y.a - x.b * y.b;
    z.b = 2 * x.a * y.b;

    return z;
}

bool isEqual(Complex x, Complex y) {
    return x.a == y.a && x.b == y.b;
}

void printComplex(Complex z) {
    // ma dor ochii dar asta e singurul print nice
    printf("%.2f%s%.2fi\n", z.a, z.b >= 0? "+" : "", z.b);
}

