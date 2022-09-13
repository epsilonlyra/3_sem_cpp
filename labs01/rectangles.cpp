#include<iostream>

struct Point{

    unsigned long long const x, y;

    Point (unsigned long long x, unsigned long long y) : x(x), y(y) {}

    Point minx (Point const &rha) const {
        return Point (rha.x < x ? rha.x : x, y);
    }

    Point maxx (Point const &rha) const {
        return Point (rha.x > x ? rha.x : x, y);
    }

    Point maxy (Point const &rha) const {
        return Point (x, rha.y > y ? rha.y : y);
    }

    Point miny (Point const &rha) const {
        return Point (x, rha.y < y ? rha.y : y);
    }

    void print() const{
        std :: cout << "("<< x << "," << y << ")";
    }

};

class Rectangle {

   public:
        Rectangle(Point const & point) : point(point) {}

        Rectangle() : Rectangle (Point(0, 0)) {}

        void print() const{
            point.print();
        }

        Rectangle operator+(const Rectangle &rha ) const{

            Rectangle bigx = Rectangle (point.maxx(rha.point));

            Rectangle bigy = Rectangle (bigx.point.maxy(rha.point));

            return bigy;
        }

        Rectangle operator*(const Rectangle &rha ) const{

            Rectangle smallx = Rectangle (point.minx(rha.point));

            Rectangle smally = Rectangle (smallx.point.miny(rha.point));

            return smally;
        }


    private:
        Point point;

};

int main(){

Point A = Point(5, 6);
Point B = Point (7, 4);

Rectangle a = Rectangle(A);
Rectangle b = Rectangle(B);

Rectangle c = a * b;

c.print();

return 0;
}
