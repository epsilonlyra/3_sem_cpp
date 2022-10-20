#include<iostream>
#include<memory>

template <typename T>
struct Comparator {
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

// qsort realisation
template <typename Element, typename Comparator>
void qsort(Element* array, int N, Comparator &compare) {
    /*
    N - number of the last element in arrayay (size - 1)
    */
    int i = 0;
    int j = N;

    int pivot = N /2;

    while (i <= j) {
        while (compare(array[i], array[pivot])) {
            i++;
        }

        while (compare(array[pivot], array[j])) {
            j--;
        }

        if (i <= j) {
            Element temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++;
            j--;
        }

        if (j > 0) {
            qsort(array, j, compare);
        }
        if (N > i) {
            qsort(array + i, N - i, compare);
        }

    }
}

template <typename Element>
void autoqsort(Element* array, int N) {
    DefaultComparator<Element> compare;
    qsort(array, N, compare);
}



// Queue realisation
template <typename T, typename Comparator = DefaultComparator<T>>
class PriorityQueue{
    protected:
        std :: unique_ptr<T[]> array;
        Comparator compare;
        int size;
        int capacity;

        int parent(int i) {
            return (i - 1) / 2;
        }

        int left_child(int i) {
            return (2 * i + 1);
        }

        int right_child(int i) {
            return (2 * i + 2);
        }

        void heapify(int index) {

            if (size <= 1){
                return;
            }


            int left = left_child(index);
            int right = right_child(index);

            int smallest = index;


            if (left < size && compare(array[left], array[index])){
                smallest = left;
            }
            if (right < size && compare(array[right], array[smallest])){
                smallest = right;
            }

            if (smallest != index)
            {
                T temp = array[index];
                array[index] = array[smallest];
                array[smallest] = temp;
                heapify(smallest);
            }
        }

    public:

        PriorityQueue(const Comparator &compare) : capacity(10), size(0), compare(compare) {
            array =  std :: make_unique<T[]>(capacity);
        }

        PriorityQueue() : PriorityQueue(Comparator() ) {}

        T peek() {
            if (size == 0){
                std :: cout << "error, queue is empty" << '\n';
                return T();
            }

            return array[0];
        }

        void push (T element) {

            if (size == capacity) {
                std :: cout << "error, queue full" <<'\n';
                return;
            }

            size++;
            array[size - 1] = element;

            int curr = size - 1;

            while (curr > 0 && compare(array[curr], array[parent(curr)])) {
                T temp = array[parent(curr)];
                array[parent(curr)] = array[curr];
                array[curr] = temp;
                curr = parent(curr);
            }
        }

        void  poll() {
            if (size == 0){
                return;
            }

            T last_element = array[size - 1];

            array[0] = last_element;
            size--;

            heapify(0);

        }

        bool is_empty(){
            return (size == 0);
        }

        void free(){
            size = 0;
            array.release();
        }
};


int main() {

ReverseIntComparator compare;

bool testing_qsort = false;
if (testing_qsort) {
    int a[] = {17, 25, 3, 4, 5};
    float b[] = {1.0, 2.0, 4.5, 0.4, 7.2};

    autoqsort(b, 4);

    for (int i = 0; i < 5; i++){
        std :: cout << b[i] << ' ' ;
    }
    std :: cout << '\n';

    qsort(b, 4, compare);
    for (int i = 0; i < 5; i++){
        std :: cout << a[i] << ' ' ;
    }
}

bool testing_queue = true;
if (testing_queue) {

    PriorityQueue<int, ReverseIntComparator> Test (compare);

    PriorityQueue<int> Test2;

    for (int i = 5; i < 10; i++){
        Test.push(i);
        Test2.push(i);
    }

    Test.poll();
    //Test.free();

    std :: cout << Test.peek() << '\n';
    std :: cout << Test2.peek();
}

return 0;
}
