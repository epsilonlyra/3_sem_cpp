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

class Buffer {

    private:
        T* array = nullptr;
        size_t max_size = 0;

    public:

        Buffer() = default;

        Buffer(int size, T value) : max_size(size) {
            array = new T[max_size];
            for (int i = 0; i < size; i++) {
                array[i] = value;
            }
        }

        Buffer (Buffer const& other) :  max_size(other.max_size) {
                array = new T[max_size];
                std :: memcpy (array, other.array, max_size * sizeof(T));
        }

        Buffer(Buffer &&other) noexcept : max_size(other.max_size) {
                array = other.array;
                other.array = nullptr;
                other.max_size = 0;

         }

        Buffer& operator= (Buffer const& other) {

                max_size = other.max_size;

                delete []  array;
                array = new T[max_size];
                std :: memcpy (array, other.array, max_size * sizeof(T));

                return *this;
        }

        Buffer& operator= (Buffer &&other)  noexcept {
            max_size = other.max_size;

            delete [] array;
            array = other.array;

            other.array = nullptr;
            other.max_size = 0;

            return *this;
        }

        ~Buffer() {
            delete [] array;
        }

        void add_memory() {

            T* new_array = new T[2 * max_size + 1];
            std :: memcpy (new_array, array, max_size * sizeof(T));
            max_size = 2 * max_size + 1;

            delete [] array;
            array = new_array;
        }

        T& operator[] (size_t index) {
            return array[index];
        }

        const T& operator[](size_t index) const  {
            return array[index];
        }

        size_t capacity() const {
            return max_size;
        }

};

template <typename T>
class Vector {
private:
    size_t size = 0;
    Buffer<T> buffer = Buffer<T>();

public:

    Vector() = default;

    Vector(int size, T value) : size(size) {
        buffer = Buffer<T>(size, value);
    }

    Vector(Vector const& other) = default;

    Vector& operator= (Vector const& other) = default;

    Vector(Vector && other) {
        buffer = std :: move (other.buffer);
        other.size = 0;
    }

    Vector& operator= (Vector && other) {
        buffer = std :: move (other.buffer);
        other.size = 0;
        return *this;
    }

    ~Vector() = default;


    void push_back(const T& value) {
       if (size == buffer.capacity()) {
            buffer.add_memory();
       }

       buffer[size] = value;
       size++;
    }


    T& top() {
        return buffer[0];
    }

    bool is_empty() const {
        return (size == 0);
    }

    size_t capacity() const {
        return buffer.capacity();
        }


    void pop() {
        if (this->is.empty()) {
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
