#include <iostream>
#include <set>

/*
This algorithm is extremly inefficent
Time complexity O(N^3) ??????
Memory complexity  O(N)

However if all the values in the array are different,
one can use sort_iterator_unique, which is far more efficient

*/

template <typename T>

struct Ascending {
    static bool compare  (T const &left, T const &right) {
        return left < right;
    }
};

template <typename T>

struct Descending {
    static bool compare  (T const &left, T const &right) {
        return left > right;
    }
};


template<typename T, typename Comparator = Ascending<T>>
struct SortIterator {

    using iterator_category = std::forward_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = T;
    using pointer           = T*;
    using reference         = T&;

    SortIterator(pointer begin, pointer end) : begin(begin), end(end) {

        current = begin;

        for (pointer i = begin; i != end; ++i) {
            if (Comparator :: compare(*i, *current)) {
                current = i;
            }
        }

        forbidden_pointers.insert(current);
    }

    SortIterator(pointer end) : begin(nullptr), end(nullptr), current(end) {

    }

    // pre increment
    SortIterator& operator++ () {

        pointer new_current = nullptr;
        bool last = true;

        for (pointer i = begin; i != end; ++i) {

            if (forbidden_pointers.count(i) == 0) {

                if (new_current == nullptr) {
                    new_current = i;
                }

                if (Comparator :: compare(*i, *new_current)) {
                    new_current = i;
                }

                last = false;
            }
        }

        if (last) {
            current = end;
        }
        else {
            current = new_current;
            forbidden_pointers.insert(current);
        }

        return *this;
    }

    SortIterator operator++(int) {
            SortIterator tmp = *this;
            ++(*this);
            return tmp;
    }


    reference operator*() const {
        return *current;
    }

    pointer operator->() {
        return current;
    }

   friend bool operator != (const SortIterator& a, const SortIterator& b) {
        return a.current != b.current;
   }

    private:
        pointer begin;
        pointer end;
        pointer current;
        std :: set<pointer> forbidden_pointers;
};

int main() {

int input[5]  = { 5, 4, 3, 2, 2};
int output[5] = { 0, 0, 0, 0, 0 };

int * input_ptr  = input;
int * output_ptr = output;

std::copy(SortIterator<int, Descending<int>>(input_ptr, input_ptr + 5),
          SortIterator<int, Descending<int>>(input_ptr + 5),
          output_ptr);


for (int i = 0; i < 5; i++) {
    std :: cout << output_ptr[i];
}

return 0;
}

