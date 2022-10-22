#include<iostream>
#include<string>
#include<cmath>

struct base_exception {
    virtual std :: string what() = 0;
};

struct math_exception final : base_exception {
    std :: string what() override {
        return "math_exception";
    }
};

struct invalid_argument final : base_exception {
    std :: string what() override {
        return "invalid_argument";
    }
};


double inverse(double x) {
    if (x == 0) {
        throw math_exception();
    }
    return 1./ x;
}

double root(double x) {
    if (x < 0) {
        throw invalid_argument();
    }
    return std :: sqrt(x);
}


int main() {

try {
    root(-1);
    //inverse(0);
}

catch (base_exception &error) {
    std :: cout << error.what();
}

return 0;
}
