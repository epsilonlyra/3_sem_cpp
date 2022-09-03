#include<iostream>
#include <cstring>

void swap (void* a, void* b, int type_size){

    void* tmp = malloc(type_size);

    std :: memcpy (tmp, a, type_size );
    std :: memcpy (a, b, type_size );
    std :: memcpy (b, tmp, type_size );

    free(tmp);
}


int main(){

char a = 'a';
char b = 'b';

swap(&a , &b, sizeof(char));

std :: cout << a << b << '\n';

return 0;
}
