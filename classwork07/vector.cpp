#include<iostream>
#include<cstring>

struct base_exception {
    virtual std :: string what() = 0;
};

struct no_elements_exception final : base_exception {
    std :: string what() override {
        return "no elements to delete";
    }
};

struct out_of_range final : base_exception {
    std :: string what() override {
        return "no element in that index";
    }
};

template <typename T>
class Vector {
private:
    size_t size = 0;
    T* buffer = nullptr;
    size_t max_size = 0;

public:

    Vector() = default;

    Vector(int size, T value) : size(size), max_size(size) {
        buffer = new T[size];
        for (int i = 0; i < size; i++) {
            buffer[i] = value;
        }
    }

    Vector(Vector const& other) : size(other.size), max_size(other.max_size) {
            buffer = new T[max_size];
            std :: memcpy (buffer, other.buffer, size * sizeof(T));
    }

    Vector(Vector &&other) noexcept : size(other.size), max_size(other.max_size) {
            buffer = other.buffer;
            other.buffer = nullptr;
            other.size = 0;
            other.max_size = 0;

     }

    Vector& operator= (Vector const& other) {

            max_size = other.max_size;
            size = other.size;

            delete []  buffer;
            buffer = new T[max_size];
            std :: memcpy (buffer, other.buffer, size * sizeof(T));

            return *this;
    }

    Vector& operator= (Vector &&other)  noexcept {
            max_size = other.max_size;
            size = other.size;
            delete [] buffer;
            buffer = other.buffer;

            other.buffer = nullptr;
            other.size = 0;
            other.max_size = 0;

            return *this;
    }

    ~Vector() {
        delete [] buffer;
    }

    void add_memory() {
        max_size = 2 * max_size + 1;
        T* new_buffer = new T[max_size];
        std :: memcpy (new_buffer, buffer, size * sizeof(T));

        delete [] buffer;

        buffer = new_buffer;
    }


    void push_back(const T& value) {
       if (size == max_size) {
            this->add_memory();
       }
       buffer[size] = value;
       size++;
    }


    T& top() {
        return buffer[0];
    }

    size_t capacity() const {
        return max_size;
    }

    bool is_empty() const {
        return (size == 0);
    }

    void pop() {
        if (size == 0) {
            throw no_elements_exception();
        }
        size--;
    }

    T& at(size_t index) {
        if (index < 0 || index >= size) {
            throw out_of_range();
        }
        return buffer[index];
    }

    T& operator[](size_t index) {
        return buffer[index];
    }

    const T& operator[](size_t index) const  {
        return buffer[index];
    }
};



int main() {

Vector<int> a (20, 1);

a[19] = 10;
Vector<int> b(10, 2);


Vector<int> c(1, 7);
b.push_back(3);

a = std :: move (b);
std :: cout << b.capacity();
return 0;
}
