#include<iostream>
#include<limits.h>
#include<limits>


int main(){

std :: cout << "char" << ' '<<  CHAR_BIT * sizeof(char) << ' ' <<
    int(std::numeric_limits<char>::min()) << ' ' <<  int(std::numeric_limits<char>::max()) << '\n';

std :: cout << "short int" << ' '<<  CHAR_BIT * sizeof(short int) << ' ' <<
    std::numeric_limits<short int>::min() << ' ' <<  std::numeric_limits<short int>::max() << '\n';

std :: cout << "int" << ' '<<  CHAR_BIT * sizeof(int) << ' ' <<
    std::numeric_limits<int>::min() << ' ' <<  std::numeric_limits<int>::max() << '\n';

std :: cout << "long int" << ' '<<  CHAR_BIT * sizeof(long int) << ' ' <<
    std::numeric_limits<long int>::min() << ' ' <<  std::numeric_limits<long int>::max() << '\n';

std :: cout << "float" << ' '<<  CHAR_BIT * sizeof(float) << ' ' <<
    std::numeric_limits<float>::min() << ' ' <<  std::numeric_limits<float>::max() << '\n';

std :: cout << "double" << ' '<<  CHAR_BIT * sizeof(double) << ' ' <<
    std::numeric_limits<double>::min() << ' ' <<  std::numeric_limits<double>::max() << '\n';

return 0;
}
