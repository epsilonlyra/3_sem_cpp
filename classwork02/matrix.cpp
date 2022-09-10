#include<iostream>
#include<cmath>

class Matrix{

    public:

        Matrix(int arr[], size_t n_elements){
            size = int(sqrt(n_elements));

            mat = new int* [size];

            for (int i = 0; i < size; i++){
                mat[i] = new int [size];
            }

            for (int i = 0; i < size; i++){
                for(int j = 0; j < size; j++){
                    mat[i][j] = arr[size * i + j];
                }
            }
        }

        Matrix(int element, size_t n_elements){
            size = int(sqrt(n_elements));

            mat = new int* [size];

            for (int i = 0; i < size; i++){
                mat[i] = new int [size];
            }

            for (int i = 0; i < size; i++){
                for(int j = 0; j < size; j++){
                    mat[i][j] = element;
                }
            }
        }

        Matrix() : Matrix(1, 1) {}

        void printMatrix(){
            for (int i = 0; i < size; i++){

                for (int j = 0; j < size; j++){
                    std :: cout << mat[i][j] << ' ';
                }

                std :: cout << '\n';
            }

            //std :: cout << '\n';
        }

        int calcDeterminant(){
            if (size == 1){
                return mat[0][0];
            }

            int det = 0;

            for (int i = 0; i < size; i++){

                int *temp_arr = new int [size - 1];
                int position = 0;

                for(int j = 1; j < size; j++){
                    for (int k = 0; k < size; k++){
                        if (k != i){
                            temp_arr[position] = mat[j][k];
                            position++;
                        }
                    }
                }

                Matrix temp_Mat = Matrix(temp_arr, (size - 1) * (size - 1));

                if (i % 2 == 0){
                    det += temp_Mat.calcDeterminant() * mat[0][i];
                }
                else{
                    det -= temp_Mat.calcDeterminant() * mat[0][i];
                }

                delete [] temp_arr;
            }

            return det;
        }

        void calcSquare(){
            int* temp_arr = new int [size * size];

            for (int pos = 0; pos < size * size; pos++){
                temp_arr[pos] = 0;

                int i = pos / size;
                int j = pos % size;

                for (int k = 0; k < size; k++) {
                    temp_arr[pos] += mat[i][k] * mat[k][j];
                }
            }

            Matrix temp_Mat = Matrix (temp_arr, size * size);

           for (int i = 0; i < size; i++){
                for (int j = 0; j < size; j++){
                    this->mat[i][j] = temp_Mat.mat[i][j];
                }
           }

            delete [] temp_arr;
        }

        void Transpose(){
            Matrix base = *this;

            for (int i = 0; i < size; i++){
                for (int j = 0; j < size; j++){
                    this->mat[i][j] = base.mat[j][i];
                }
            }
        }

        ~ Matrix(){
            for (int i = 0; i < size; i++){
                delete [] mat[i];
            }

            delete [] mat;
        }

        Matrix(const Matrix& other){
            size = other.size;

            mat = new int* [size];

            for (int i = 0; i < size; i++){
                    mat[i] = new int [size];
                }

            for (int i = 0; i < size; i++){
                for(int j = 0; j < size; j++){
                    mat[i][j] = other.mat[i][j];
                    }
                }
        }

    private:

        int** mat;
        int size;

};


int main(){

int arr[9] = {1, 2, 3, 4, 5, 6, 7, 8, 91};

Matrix Alexey = Matrix(arr, 9);

std :: cout << Alexey.calcDeterminant() << '\n';



Matrix Petr = Matrix(1, 4);

Alexey.Transpose();

Petr.printMatrix();
Alexey.printMatrix();

return 0;
}
