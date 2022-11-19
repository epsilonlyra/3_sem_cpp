#ifndef H_COMPLEX
#define H_COMPLEX
#include<iostream>

class Complex {
 private:
    double real;
    double imag;

 public:
    explicit Complex(double r = 0, double l = 0);  //  constructor
    Complex operator+(Complex);                  //  operator+()
    Complex operator+(double);                   //  operator+()with double
    Complex operator-(Complex);                  //  operator-()
    Complex operator*(Complex);                  //  operator*()
    bool operator==(Complex);                    //  operator==()

    //  Sets private data members.
    void Set(double , double);


    //  Returns the real part of the complex number.
    double Real();

    //  Returns the imaginary part of the complex number.
    double Imaginary();
};

std::istream &operator>>(std::istream &in_file, Complex &number);
std::ostream &operator<<(std::ostream &out_file, Complex number);




#endif
