#include<iostream>
#include<cstring>

void swap (void* a, void* b, int type_size){

    void* tmp = malloc(type_size);

    std :: memcpy (tmp, a, type_size );
    std :: memcpy (a, b, type_size );
    std :: memcpy (b, tmp, type_size );

    free(tmp);
}

void* move_void_pointer(void* pointer, int step){
    /*
    This function is an ugly appendage used to bypass
    impossibility to add a number to a void* pointer
    in some architectures
    */

    char* temp = reinterpret_cast<char*>(pointer);
    temp = temp + step;

    void* moved_pointer = reinterpret_cast<void*>(temp);
    return moved_pointer;
}

void qsort(void* arr, int type_size, int left, int right, int (*compare)(void *, void *)){

    int i = left;
    int j = right;

    int pivot = (left + right) / 2;

    if (i == j){
        return;
    }

    while (i != j){

        for (i = left; i < pivot; i++){
            if (compare(move_void_pointer(arr, pivot * type_size), move_void_pointer(arr, i * type_size))){
                break;
            }
        }

        for (j = right; j > pivot; j--){
            if (compare(move_void_pointer(arr, j * type_size), move_void_pointer(arr,pivot * type_size))){
                break;
            }
        }

    swap(move_void_pointer(arr,j * type_size), move_void_pointer(arr, i * type_size), type_size);

    qsort(arr, type_size, 0, pivot, compare);
    qsort(arr, type_size, pivot + 1, right, compare);

    }






}

int compare_int (void* left, void* right){

    if ((*reinterpret_cast<int*>(left)) < (*reinterpret_cast<int*>(right))){
        return 1; // right is strictly  greater that left
    }

    return 0;
}

int compare_int_reverse (void* left, void* right){

    if ((*reinterpret_cast<int*>(left)) > (*reinterpret_cast<int*>(right))){
        return 1; // left  is strictly  greater that left
    }

    return 0;
}

int compare_float(void* left, void* right){
    if ((*reinterpret_cast<float*>(left)) < (*reinterpret_cast<float*>(right))){
        return 1; // right is strictly  greater that left
    }

    return 0;

}

int main(){

float E [5]; // test array
for (int i = 0; i < 5; i++){
    std :: cin >> E[i];

}

int (*compare[]) (void*, void*) = {compare_int, compare_int_reverse, compare_float}; // array of comparators

qsort(E, sizeof(float), 0, 4, compare[2]);

for (int i = 0; i < 5; i++){
    std :: cout << E[i] << ' ';

}

std :: cout << '\n';

return 0;
}
