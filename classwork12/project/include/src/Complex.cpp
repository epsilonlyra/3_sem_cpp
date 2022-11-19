#include  "Complex.hpp"


Complex :: Complex (double r ,  double i)  : real(r), imag(i) {
    real = r;
    imag = i;
}

std::istream &operator>>(std::istream &in_file, Complex &number) {
    double re, is;
    char ch;
    if (in_file >> ch && ch == '('&& in_file >> re >> ch && ch == ',' && in_file >> is >> ch && ch == ')') {
        number.Set(re, is);
    } else {
        std::cerr << "Finish the input" << std::endl;
    }
    return in_file;
}

std::ostream &operator<<(std::ostream &out_file, Complex number) {
    out_file << '(' << number.Real() << ',' << number.Imaginary() << ')';
    return out_file;
}


//  define overloaded + (plus) operator
Complex Complex::operator+(Complex c) {
    Complex result = c;
    result.real = (this->real + result.real);
    result.imag = (this->imag + result.imag);
    return result;
}

// define overloaded + (plus) operator (with double)
Complex Complex::operator+(double d) {
    Complex result = Complex(d);
    result.real = (this->real +d);
    result.imag = (this->imag);
    return result;
}

// define overloaded - (minus) operator
Complex Complex::operator-(Complex c) {
    Complex result = c;
    result.real = (this->real - c.real);
    result.imag = (this->imag - c.imag);
    return result;
}

// define overloaded * (multiplication) operator
Complex Complex::operator*(Complex c) {
    Complex result = c;
    result.real = (this->real * c.real) - (this->imag * c.imag);
    result.imag = (this->imag * c.imag) + (this->imag * c.real);
    return result;
}

// define overloaded = bool operator
bool Complex::operator==(Complex b) {
    return ((this->real == b.real) && (this->imag == b.imag));
}

double Complex:: Real() {
    return real;
}

 void  Complex:: Set(double new_real, double new_imaginary) {
        real = new_real;
        imag = new_imaginary;
}


//  Returns the imaginary part of the complex number.
double Complex:: Imaginary() {
    return imag;
}

