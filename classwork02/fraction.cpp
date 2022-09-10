#include<iostream>

class Fraction {

    public:
        Fraction(int numerator, int denominator) : numerator(numerator), denominator(denominator) {}

        Fraction(int numerator) : Fraction(numerator, 1){}

        Fraction() =  delete;

        Fraction(const Fraction& other) : numerator(other.numerator), denominator(other.denominator) {}

        void printFraction(){
            std :: cout << numerator << '/' << denominator << '\n';
        }

        double calc(){
            return double(numerator) / double(denominator);
        }

        void fracSimplify(){
            int gcd = euclid(numerator, denominator);

            numerator = numerator / gcd;
            denominator = denominator / gcd;
        }

        void multByNumber(int value){

            numerator *= value;
        }

        void multByFrac(const Fraction& other){
            numerator *= other.numerator;
            denominator *= other.denominator;
        }

        Fraction multByFracReturn(const Fraction& other){
            int num, den;

            num = other.numerator * this->numerator;
            den = other.denominator * this->denominator;

            Fraction result = Fraction(num, den);

            return result;
        }

        void addFrac(const Fraction& other){
            numerator = numerator * other.denominator + other.numerator * denominator;
            denominator *= other.denominator;
        }

        Fraction addFracReturn(const Fraction& other){
            int num, den;

            num = other.numerator * this->denominator + this->numerator * other.denominator;
            den = other.denominator * this->denominator;

            Fraction result = Fraction(num, den);

            return result;
        }

        void fracReverse(){
            int temp = denominator;

            denominator = numerator;
            numerator = temp;

        }

        int getNumerator(){
            return numerator;
        }

        int getDenominator(){
            return denominator;
        }

    private:
        int numerator;
        int denominator;

        int euclid(int a, int b) {
            int temp;

            if (a < b) {
                temp = a;
                a = b;
                b = temp;
            }

            int  r1 = 1;
            while (r1 != 0) {
                r1 = a % b;
                a = b;
                b = r1;
            }

            return a;
        }
};

int main(){

    Fraction matvet = Fraction(5, 8);

return 0;
}
