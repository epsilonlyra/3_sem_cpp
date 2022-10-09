#include<iostream>
#include<cstring>
#include<cassert>

template <typename T>

class Grid final {

    class Shevelev {

        friend Grid;

        private :
            Grid& grid;
            int i;

        protected:
            Shevelev(Grid &grid, int i): grid(grid), i(i) {}

        public:
            T& operator[](int j) {
                return grid(i, j);
            }
    };

    public:
        using value_type = T;
        using size_type = unsigned;

    private:
        T* data = nullptr;
        size_type  y_size, x_size = 0;

    public:
        Grid (T* data, size_type y_size, size_type x_size) : data(data), y_size(y_size), x_size(x_size) {}

        Grid (T const &t) : Grid(1, 1) {
            data[1] = t;
        }

        Grid (size_type y_size, size_type x_size) : data(new T[y_size * x_size]), y_size(y_size), x_size(x_size) {
            T t;

            for (auto it = data, end = data + x_size * y_size;it != end; ++it) {
                *it = t;
            }
        }

        Grid (size_type y_size, size_type x_size, T const& t) : Grid(y_size, x_size) {
            for (auto it = data, end = data + x_size * y_size;it != end; ++it) {
                *it = t;
            }
        }

        Grid (Grid const &obj) : Grid(obj.y_size, obj.x_size) {
           // copy constuctor
            memcpy(data, obj.data, y_size *  x_size * sizeof(T));
        }

        Grid (Grid &&obj) : data(obj.data), y_size(obj.y_size), x_size(obj.x_size) {
            // move constructor
            obj.x_size = 0;
            obj.y_size = 0;
            obj.data = nullptr;
        }

        Grid& operator= (Grid &obj) {
            // copy assignment

            Grid tmp(obj);

            std::swap(x_size, tmp.x_size);
            std::swap(y_size, tmp.y_size);
            std::swap(data, tmp.data);

            return *this;
        }

        Grid& operator= (Grid &&obj) {
            // move assignment

            delete [] data;

            y_size = obj.y_size;
            x_size = obj.x_size;
            data = obj.data;

            obj.x_size = 0;
            obj.y_size = 0;
            obj.data = nullptr;

            return *this;
        }

        T operator() (size_type y_idx, size_type x_idx) const {
            return data [y_idx * x_size + x_idx];
        }

        T& operator() (size_type y_idx, size_type x_idx) { // ??????
            return data [y_idx * x_size + x_idx];
        }

        Grid& operator=(T const &t) { // ?

            for (auto it = data, end = data + x_size * y_size;it != end; ++it) {
                *it = t;
            }

            return *this;
        }

        Shevelev operator[](int i) {
            return Shevelev(*this, i);
        }

        size_type get_y_size() const {
            return y_size;
        }

        size_type get_x_size() const {
            return x_size;
        }


        ~Grid() {
            delete [] data;
        }
};


int main() {

using  gsize_t = Grid<int> ::size_type;

Grid<float> g (3, 2, 0.0f);
assert (3 == g.get_y_size());
assert (2 == g.get_x_size());


for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx) {
    for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx) {
        assert (0.0f == g[y_idx][x_idx]);
    }
}

for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx) {
    for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx) {
        g[y_idx][x_idx] = 1.0f;
    }
}

for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx) {
    for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx) {
        assert (g(y_idx, x_idx) == 1.0f);
    }
}


return 0;
}
