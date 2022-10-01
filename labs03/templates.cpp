#include<iostream>

template <typename T>
struct Comparator{
    virtual bool operator () (T const &, T const &) const = 0;
};


struct IntComparator final : Comparator<int> {
    bool operator() (int  const &left, int const &right) const override {
        return left < right;
    }
};

struct ReverseIntComparator final : Comparator<int> {
    bool operator() (int  const &left, int const &right) const override {
        return left > right;
    }
};

template <typename T>
struct DefaultComparator final : Comparator<T> {
    bool operator() (T const &left, T const &right) const override {
        return left < right;
    }
};


template <typename Element, typename Comparator>
void qsort(Element* arr, int N, Comparator &compare) {
    /*
    N - number of the last element in array (size - 1)
    */
    int i = 0;
    int j = N;

    int pivot = N /2;

    while (i <= j) {
        while (compare(arr[i], arr[pivot])) {
            i++;
        }

        while (compare(arr[pivot], arr[j])) {
            j--;
        }

        if (i <= j) {
            Element temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }

        if (j > 0) {
            qsort(arr, j, compare);
        }
        if (N > i) {
            qsort(arr + i, N - i, compare);
        }

    }
}

template <typename Element>
void autoqsort(Element* arr, int N) {
    DefaultComparator<Element> compare;
    qsort(arr, N, compare);
}

int main() {

ReverseIntComparator compare;

int a[] = {17, 25, 3, 4, 5};
float b[] = {1.0, 2.0, 4.5, 0.4, 7.2};

autoqsort(a, 4);

for (int i = 0; i < 5; i++){
    std :: cout << a[i] << ' ' ;
}
std :: cout << '\n';

qsort(a, 4, compare);
for (int i = 0; i < 5; i++){
    std :: cout << a[i] << ' ' ;
}

return 0;
}
