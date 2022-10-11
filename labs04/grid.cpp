#include<iostream>
#include<cstring>
#include<cassert>

template <typename T, int N = 2> // N >= 2

class Grid final {

    public:
        using size_type = unsigned;
        using  plane = Grid<T, N - 1>;

    private:
        plane* level = nullptr;
        size_type z_size = 0;

    public:

        Grid() = default;

        template <typename Head, typename... Tail>
        Grid (Head head, Tail... tail) : level(new plane[head]), z_size(head)  {
            for (size_type z = 0; z < z_size; z++){
               level[z] =  plane(tail...);
            }
        }

        Grid (Grid const &obj) : level(new plane[obj.z_size]), z_size(obj.z_size)  {
           // copy constuctor

           for (size_type z = 0; z < z_size; z ++) {
                level[z] = obj.level[z];
            }
        }

        Grid (Grid &&obj) : level(obj.level), z_size(obj.z_size) {
            // move constructor
            obj.z_size = 0;
            obj.level = nullptr;
        }

        Grid& operator= (Grid &obj) {
            // copy assignment

            Grid tmp(obj);
            for (size_type z = 0; z < z_size; z++) {
                level[z] = obj.level[z];
            }

            z_size = obj.z_size;

            return *this;
        }

        Grid& operator= (Grid &&obj) {
            // move assignment

            if (&obj == this) {
                return *this;
            }

            delete [] level;
            z_size = obj.z_size;

            level = obj.level;

            obj.z_size = 0;

            obj.level = nullptr;

            return *this;
        }

        template <typename Head, typename... Tail>
        T operator() (Head head, Tail... tail) const {
            return level[head](tail...);
        }

        template <typename Head, typename... Tail>
        T& operator() (Head head, Tail... tail)  {
            return level[head](tail...);
        }

        plane& operator[] (int z) {
            return level[z];
        }

        Grid& operator=(T const &t) {

            for (size_type z = 0; z < z_size; z++) {
                level[z] = t;
            }

            return *this;
        }


        ~Grid() {
            delete [] level;
        }

        size_type get_z_size() {
            return z_size;
        }
};

template<typename T>
class Grid<T, 2> final {

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
        using size_type = unsigned;

    private:
        T* data = nullptr;
        size_type  y_size, x_size = 0;

    public:
        Grid (T* data, size_type y_size, size_type x_size) : data(data), y_size(y_size), x_size(x_size) {}

        Grid (T const &t) : Grid(1, 1, t) {}

        Grid() = default;

        Grid (size_type y_size, size_type x_size) : Grid(y_size, x_size, T())  {}

        Grid (size_type y_size, size_type x_size, T const& t) : data(new T[y_size * x_size]), y_size(y_size), x_size(x_size) {
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
             if (&obj == this) {
                return *this;
            }

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

        T& operator() (size_type y_idx, size_type x_idx) {
            return data [y_idx * x_size + x_idx];
        }

        Grid& operator=(T const &t) {

            for (auto it = data, end = data + x_size * y_size; it != end; ++it) {
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

Grid<float, 3>  g3 (2, 3, 4, 1.0f);
assert(1.0f == g3(1, 1, 1));

Grid<float, 2> g2 (2, 5, 2.0f);
assert(2.0f == g2(1, 1));

g3 = 6.0f;

g3[1][1][1] = 2.0f;

g2 = g3[1];
assert(2.0f == g2(1,1));

}
