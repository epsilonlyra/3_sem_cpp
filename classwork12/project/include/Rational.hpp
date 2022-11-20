#ifndef H_RATIONAL
#define H_RATIONAL

#include<iostream>

class Rational {

    public:
        Rational();

        Rational(int a, int b);

        int Numerator();

        int Denominator();

    private:
        int nod(int a, int b );

        int numer;
        int denomin;

};


#endif
