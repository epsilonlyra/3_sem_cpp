#include <iostream>

/*
This algorithm works provided all the values in the array are different
Time complexity O(N^2)


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
    }

    SortIterator(pointer end) : begin(nullptr), end(nullptr), current(end) {

    }

    // pre increment
    SortIterator& operator++ () {
        pointer new_current = begin;
        bool last = true;

        for (pointer i = begin; i != end; i++) {

            if ((Comparator :: compare(*current, *i))) {
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
};

int main() {

int input[5]  = { 5, 4, 3, 2, 1};
int output[5] = { 0, 0, 0, 0, 0 };

int * input_ptr  = input;
int * output_ptr = output;

std::copy(SortIterator<int>(input_ptr, input_ptr + 5),
          SortIterator<int>(input_ptr + 5),
          output_ptr);


for (int i = 0; i < 5; i++) {
    std :: cout << output_ptr[i];
}





return 0;
}

