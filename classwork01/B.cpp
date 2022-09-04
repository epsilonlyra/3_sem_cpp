#include <iostream>

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


int min(void* arr, int arr_size, int type_size, int (*compare)(void*, void*)){


    int current_min_index = 0;
    void* current_min = arr;

    for (int i = 0; i < arr_size; i++){

        if (compare(arr + i * type_size, current_min)){
            current_min_index = i;
            current_min = arr + i * type_size;
        }
    }

    return current_min_index;
}

int max(void* arr, int arr_size, int type_size, int (*compare)(void*, void*)){


    int current_max_index = 0;
    void* current_max = arr;

    for (int i = 0; i < arr_size; i++){

        if (compare(current_max, arr + i * type_size)){
            current_max_index = i;
            current_max = arr + i * type_size;
        }
    }

    return current_max_index;
}


int main(){

int E [5] = {-10, -107 ,3 , 4 , 108}; // test array


int (*compare) (void*, void*); // pointer to function
compare = compare_int;

std :: cout << min(E, 5, sizeof(int), compare) << ' ' << max(E, 5 , sizeof(int), compare) << '\n';


/*
Otherthise we can use min function to search for the biggest element,
if we reverese comparing functiin
*/

compare = compare_int_reverse;
std :: cout << min(E, 5, sizeof(int), compare) << '\n';

return 0;
}
