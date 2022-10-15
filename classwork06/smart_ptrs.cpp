#include<iostream>

template <typename T>

class unique_ptr {

    private:
        T* ptr = nullptr;

    public:

        explicit unique_ptr(T* ptr) : ptr(ptr) {}

        unique_ptr (unique_ptr&& other) : ptr(other.ptr) {
            other.ptr = nullptr;
        }

        unique_ptr& operator=(unique_ptr&& other) {
            ptr = other.ptr;
            other.ptr = nullptr;
        }

        unique_ptr (const unique_ptr& other) = delete;

        unique_ptr& operator=(const unique_ptr& other) = delete;

        ~unique_ptr() {
            delete ptr;
        }

        T& operator* ()  const {
            return *ptr;
        }

        T* operator-> () const {
            return ptr;
        }
};

template <typename T>

class shared_ptr {

    public:
        explicit shared_ptr(T* ptr) {
            control_pointer = new ControlBlock<T*>;
            control_pointer->counter = 1;
            control_pointer->object = ptr;
        }

        shared_ptr (const shared_ptr& other) : control_pointer(other.control_pointer) {
            control_pointer->counter++;
        }

        shared_ptr (shared_ptr&& other) : control_pointer(other.control_pointer) {
                other.control_pointer = nullptr;
        }

        shared_ptr& operator= (shared_ptr&& other) = delete;

        shared_ptr& operator= (const shared_ptr& other) = delete;

        size_t use_count() const {
            return control_pointer->counter;
        }

        ~shared_ptr() {
            control_pointer->counter--;
            if (control_pointer->counter == 0) {
                delete control_pointer;
            }
        }

        T& operator* ()  const {
            return *(control_pointer->object);
        }

        T* operator-> () const {
            return control_pointer->object;
        }

    private:

        template <typename U>
        struct ControlBlock {
            size_t counter = 0;
            U object = nullptr;

            ~ControlBlock() {
                delete object;
            }
        };

        ControlBlock<T*>* control_pointer = nullptr;

        template <typename U, typename... Args>
        friend shared_ptr<U> make_shared(Args&&... args);
};

template <typename T, typename... Args>

    shared_ptr<T> make_shared(Args&&... args) {
      auto ptr = new T(std::forward<Args>(args)...);
      return shared_ptr<T>(ptr);
    }



int main() {


shared_ptr<int> A(new int);


shared_ptr<int> K  = make_shared<int>(1);


//shared_ptr<int> B(A);


//std :: cout << A.use_count();
return 0;

}
