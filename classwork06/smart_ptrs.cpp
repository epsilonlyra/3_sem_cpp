#include<iostream>

template <typename T>
class unique_ptr {

    private:
        T* ptr = nullptr;

    public:

        explicit unique_ptr(T* ptr) : ptr(ptr) {}

        unique_ptr (unique_ptr&& other) : ptr(ptr.other) {
            other.ptr =nullptr;
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
        shared_ptr(T* ptr) {
            cptr = new ContolBlock;
            cptr->counter = 1;
            cptr->object = ptr;
        }

        shared_ptr(const T&other) : {
            other.cptr->counter++;
            cptr = other.cptr;
        }

        shared_ptr(T&& other) : cptr(other.cptr) {
            other.cptr = nullptr;
        }

        size_t use_count() const {
            return cptr->counter;
        }

        ~shared_ptr(){
            cptr->counter--;

            if (cptr->counter == 0) {
                delete cptr->object;
                delete cptr->counter;
            }

            delete cptr;

        }

    private:

        template <typename U>
        struct ControlBlock {
            size_t counter = 0;
            U object = nullptr;
        };

        ControlBlock* cptr = nullptr;

        template <typename U, typename... Args>
        friend shared_ptr<U> make_shared(Args&&... args);
};


int main() {




return 0;

}
