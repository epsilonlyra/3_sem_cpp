#include <iostream>
#include <unordered_set>

/*
This algorithm is extremly inefficent
Time complexity O(N^2)
Memory complexity  O(N)

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

    SortIterator(const pointer begin, const  pointer end) : begin(begin), end(end) {

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

            if (forbidden_pointers.find(i) == forbidden_pointers.end()) {

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
        std :: unordered_set <pointer> forbidden_pointers;
};

int main() {

using Descending = Descending<int>;
using Ascending = Ascending<int>;

int input[5]  = { 5, 4, 3, 7, 2};
int output[5] = { 0, 0, 0, 0, 0 };

int * input_ptr  = input;
int * output_ptr = output;



std::copy(SortIterator<int, Descending>(input_ptr, input_ptr + 5),
          SortIterator<int, Descending>(input_ptr + 5),
          output_ptr);


for (int i = 0; i < 5; i++) {
    std :: cout << output_ptr[i];
}

return 0;
}

