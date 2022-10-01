#include<iostream>

template <typename Field,  size_t M, size_t N> // M - number of rows, N - number of columns
class Matrix {
    public:
        Field Mat[M][N];
    public:

    Matrix () {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                Mat[i][j] = 0;
            }
        }
    }

    Matrix(const Field array[N * M]) {
        for (int i = 0; i < M; i++){
            for (int j = 0; j < N; j++){
                Mat[i][j] = array[N * i + j];
            }
        }
    }

    void print() {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++){
                std :: cout << Mat[i][j] << ' ';
            }
            std :: cout << '\n';
        }
        std :: cout <<'\n';
    }

    Matrix operator+ (const Matrix &other){
        Matrix Sum;
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                Sum.Mat[i][j] = Mat[i][j] + other.Mat[i][j];
            }
        }
        return Sum;
    }

    Matrix operator- (const Matrix &other){
        Matrix Sum;
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                Sum.Mat[i][j] = Mat[i][j] - other.Mat[i][j];
            }
        }
        return Sum;
    }

};

template<typename Field, size_t M, size_t N, size_t K>
Matrix<Field, M, K> operator*(const Matrix<Field, M, N>& lha, const Matrix<Field, N, K>& rha) {
    Matrix<Field, M, K> Mult;

     for (int i = 0; i < M; i++) {
        for (int j = 0; j < K; j++) {
            for (int k = 0; k < N; k++){
                Mult.Mat[i][j] += lha.Mat[i][k] * rha.Mat[k][j];
            }
        }
    }

    return Mult;
}


int main() {
int A[]  = {1, 1, -1, 9, 6, 5, 2, 3};
int B[] = {1, 0, 3, 8, -4, 9, 6, 7};

Matrix<int, 4, 2> El(A);
Matrix<int, 2, 4> Kol (B);
El.print();
Kol.print();

auto Phil = El * Kol;
Phil.print();
return 0;
}
