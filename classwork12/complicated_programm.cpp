#include <iostream>
#include <sstream>
#include <set>
#include <map>

// Unit test framework
template <class T>
std::ostream &operator<<(std::ostream &os, const std::set<T> &s) {
    os << "{";
    bool first = true;
    for (const auto &x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}
// -------------------------------------------------------------------------------------------------
template <class K, class V>
std::ostream &operator<<(std::ostream &os, const std::map<K, V> &m) {
    os << "{";
    bool first = true;
    for (const auto &kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}
// -------------------------------------------------------------------------------------------------
template<typename T, typename U>
void assert_equal(const T& t, const U& u, const std::string& hint) {
    if (t != u) {
        std::ostringstream os;
        os << " Assertion failed: " << t << " != " << u << " hint: " << hint;
        throw std::runtime_error(os.str());
    }
}

// -------------------------------------------------------------------------------------------------
inline void Assert(bool b, const std::string& hint) {
    assert_equal(b, true, hint);
}
// -------------------------------------------------------------------------------------------------
class TestRunner {
 public:
    template <class TestFunc>
    void RunTest(TestFunc func, const std::string &test_name) {
        try {
            func();
            std::cerr << test_name << " OK" << std::endl;
        }
        catch (std::runtime_error &e) {
            ++fail_count;
            std::cerr << test_name << " fail: " << e.what() << std::endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            std::cerr << fail_count << " unit tests failed. Terminate"
                      << std::endl;
            exit(1);
        }
    }

 private:
    int fail_count = 0;
};
// -------------------------------------------------------------------------------------------------
// class Rational
class Rational {
    public:
        Rational() : numer(0), denomin(1) { }

        Rational(int numerator, int denominator) : numer(0), denomin(1) {
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

        int Numerator() const {
            return numer;
        }

        int Denominator() const {
            return denomin;
        }

    private:
        int nod(int numerator, int denominator) {
            return !denominator ? abs(numerator) :
                                  nod(denominator, numerator % denominator);
        }
        int numer;
        int denomin;
};


// -------------------------------------------------------------------------------------------------
class Complex {
 private:
    double real;
    double imag;

 public:
    explicit Complex(double real = 0, double imag = 0);  //  constructor
    Complex operator+(Complex);                  //  operator+()
    Complex operator+(double);                   //  operator+()with double
    Complex operator-(Complex);                  //  operator-()
    Complex operator*(Complex);                  //  operator*()
    bool operator==(Complex);                    //  operator==()

    //  Sets private data members.
    void Set(double new_real, double new_imaginary) {
        real = new_real;
        imag = new_imaginary;
    }

    //  Returns the real part of the complex number.
    double Real() {
        return real;
    }

    //  Returns the imaginary part of the complex number.
    double Imaginary() {
        return imag;
    }
};

//  define I/O stream

//  define constructor
Complex::Complex(double r, double i): real(r), imag(i) {
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


// -------------------------------------------------------------------------------------------------
int main() {
    std :: cout << abs(5);
    return 0;
}
