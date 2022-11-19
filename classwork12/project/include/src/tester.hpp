#include<iostream>
#include<map>
#include<string>

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



template<class TestFunc>
void TestRunner :: RunTest (TestFunc func, const std::string &test_name) {
        try {
            func();
            std::cerr << test_name << " OK" << std::endl;
        }
        catch (std::runtime_error &e) {
            ++fail_count;
            std::cerr << test_name << " fail: " << e.what() << std::endl;
        }
}

TestRunner :: ~TestRunner() {
     if (fail_count > 0) {
                std::cerr << fail_count << " unit tests failed. Terminate"
                          << std::endl;
                exit(1);
            }
}



