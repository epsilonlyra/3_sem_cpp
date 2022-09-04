#include<iostream>
#include<limits>


int main(){

std :: cout << "char" << ' '<<  8 * sizeof(char) << ' ' <<
    int(std::numeric_limits<char>::min()) << ' ' <<  int(std::numeric_limits<char>::max()) << '\n';

std :: cout << "short int" << ' '<<  8 * sizeof(short int) << ' ' <<
    std::numeric_limits<short int>::min() << ' ' <<  std::numeric_limits<short int>::max() << '\n';

std :: cout << "int" << ' '<<  8 * sizeof(int) << ' ' <<
    std::numeric_limits<int>::min() << ' ' <<  std::numeric_limits<int>::max() << '\n';

std :: cout << "long int" << ' '<<  8 * sizeof(long int) << ' ' <<
    std::numeric_limits<long int>::min() << ' ' <<  std::numeric_limits<long int>::max() << '\n';

std :: cout << "float" << ' '<<  8 * sizeof(float) << ' ' <<
    std::numeric_limits<float>::min() << ' ' <<  std::numeric_limits<float>::max() << '\n';

std :: cout << "double" << ' '<<  8 * sizeof(double) << ' ' <<
    std::numeric_limits<double>::min() << ' ' <<  std::numeric_limits<double>::max() << '\n';

return 0;
}
