#include<iostream>
#include<vector>
#include<cmath>

struct Point {

    Point(double x, double y) : x(x), y(y) {}
    Point() : Point(0, 0) {}

    double x = 0.;
    double y = 0.;


    Point operator+ (const Point &other) const {
        return Point ((this->x + other.x), (this->y + other.y));
    }
    Point operator/ (double factor) const {
        return Point ((this->x / factor), (this->y / factor));
    }


    friend std::ostream& operator<<(std::ostream& out, const Point &point);
};

std::ostream& operator<<(std::ostream& out, const Point &point)
{
    out << '(' << point.x << ',' << point.y << ')';
    return out;
}

double distance(const Point &a, const Point &b) {
    return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}


double Heron(const double &a,const  double &b, const double &c) {

    double s = (a + b + c)/2;

    return sqrt(s * (s - a) * (s - b) * (s - c));
}

void form_vector(std::vector<Point> &storage, Point a, Point b, Point c) {
    storage.clear();
    storage.push_back(a);
    storage.push_back(b);
    storage.push_back(c);
}

class Shape {
    protected:
        std::vector <Point> storage;

        virtual double area() const {
            return 0;
        }

        virtual double perimeter() const {
            return 0;
        }

        virtual Point center() const {
            return Point();
        }
};

class Triangle : public Shape {
    public:
        Triangle (Point a, Point b, Point c) {
           form_vector(storage, a, b, c);
        }

        double area() const override {
            return Heron(
                        distance(storage[0], storage[1]),
                        distance(storage[1], storage[2]),
                        distance(storage[2], storage[0])
                        );
        }

        double perimeter() const override {
            return (distance(storage[0], storage[1]) +
                    distance(storage[1], storage[2]) +
                    distance(storage[2], storage[0])
                    );
        }

        Point center() const  override {
            return (storage[0] + storage[1] + storage[2])/3;
        }
};

class Square : public Shape {


    public:
        Square (Point a, Point b, Point c, Point d) {

            form_vector(storage, a, b, c);
            storage.push_back(d);
        }

        double area() const override {
            std::vector <Point> storage_first;

            std::vector <Point> storage_second;

            Triangle first(storage[0], storage[1], storage[2]);
            Triangle second(storage[0], storage[2], storage[3]);

            return first.area() + second.area();
        }

        double perimeter() const override {
            return (distance(storage[0], storage[1]) +
                    distance(storage[1], storage[2]) +
                    distance(storage[2], storage[3]) +
                    distance(storage[3], storage[0])
                    );
        }

        Point center() const  override {
            return (storage[0] + storage[1] + storage[2] + storage[4])/4;
        }
};

class Line : public Shape {


    public:
        Line (Point a, Point b) {

            form_vector(storage, a, b, Point(0,0));
        }

        double area() const override {
            return 0;
        }

        double perimeter() const override {
            return (distance(storage[0], storage[1]));
        }

        Point center() const  override {
            return (storage[0] + storage[1])/2;
        }
};

int main(){

Line Evgeniy(Point(0,1), Point(0, 0));

std::cout << Evgeniy.perimeter();
return 0;
}
