#include "Rational.hpp"



Rational :: Rational() : numer(0), denomin(1) { }

int Rational ::  nod(int numerator, int denominator) {
            return !denominator ? abs(numerator) :
                                  nod(denominator, numerator % denominator);
}

Rational ::  Rational (int numerator, int denominator) : numer(0), denomin(1) {
    if (denominator < 0) {
        if (numerator < 0) {
            denominator = abs(denominator);
            numerator = abs(numerator);
        } else {
            denominator = abs(denominator);
            numerator = numerator - 2 * numerator;
        }
    }

    if (numerator == 0) {
        denominator = 1;
    }

    int nod_value = nod(numerator, denominator);
    numer = numerator / nod_value;
    denomin = denominator / nod_value;
}

int Rational ::  Numerator() const {
    return numer;
}

int  Rational :: Denominator() const {
    return denomin;
}


