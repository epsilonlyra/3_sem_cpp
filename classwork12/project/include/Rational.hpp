#ifndef H_RATIONAL
#define H_RATIONAL

#include<iostream>

class Rational {

    public:
        Rational();

        Rational(int , int);

        int Numerator() const;

        int Denominator() const;

    private:
        int nod(int, int );
        int numer;

        int denomin;

};










#endif
