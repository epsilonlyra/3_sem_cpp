#ifndef H_TESTER
#define H_TESTER

#include<iostream>
#include<sstream>
#include<map>
#include<set>

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
    assert_equal<bool, bool>(b, true, hint);
}

template<typename T, typename U>
class Assertion_equality_Functor {
    private:
        T a;
        U  b;
        std :: string message = "";

    public:
        Assertion_equality_Functor (T a, U b , std :: string  message = "") : a(a), b(b), message(message){}

        void operator()() {
            assert_equal<T, U>(a, b, message);
        }

};
template<>
class Assertion_equality_Functor<bool, bool> {
    private:
        bool  a;

        std :: string message = "condition is false";

    public:
        Assertion_equality_Functor (bool a, std :: string  message = "condition is false") : a(a), message(message){}

        void operator()() {
            Assert(a, message);
        }

};
/*
template<typename T>
class Assertion_equality_Functor<bool, bool> {
    private:
        bool a;
        std :: string message = "not true";

    public:
        Assertion_equality_Functor (bool a, bool b = true,  std :: string  message = "not true") : a(a), message(message){}

        void operator()() {
            Assert(a, message);
}






};
*/


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

    ~TestRunner();



 private:
    int fail_count = 0;
};

#endif
