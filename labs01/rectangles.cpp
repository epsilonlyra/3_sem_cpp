#include<iostream>
#include<string>


unsigned long long  tenpower(unsigned long long  a){

    unsigned long long result = 1;

    for (int i = 0; i < a; i++){
        result *= 10;
    }

    return result;
}

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


unsigned long long get_coordinate (std :: string expression, int iterator, char stop_condition){

    int reverse_iterator = iterator - 1;

    unsigned long long x = 0;;

    while(true){

        if (expression[reverse_iterator] == stop_condition){
            break;
        }

        unsigned long long digit = (expression[reverse_iterator]);
        unsigned long long order = tenpower(iterator - 1 - reverse_iterator);

        x = order * (digit - 48); // magical number

        reverse_iterator--;
    }

    return x;
}

Rectangle Get_Rectangle (std :: string expression, int begin_iter){

    int iterator = begin_iter;

    while(true){
        if (expression[iterator] == ','){
            break;
        }

        iterator++;
    }

    unsigned long long x = get_coordinate(expression, iterator, '(');

     while(true){
        if (expression[iterator] == ')'){
            break;
        }
        iterator++;
    }

    unsigned long long y = get_coordinate(expression, iterator, ',');

    return Rectangle(Point(x, y));
}

Rectangle calc_expression(std :: string expression, int begin_iter){

    int iterator = begin_iter;
    if (int(expression[iterator]) != 0){

        Rectangle temp = Get_Rectangle(expression, iterator);
    }

    Rectangle temp = Get_Rectangle(expression, iterator);

    bool found_plus = false;
    bool found_mult = false;

    while(!found_plus || !found_mult){

        if (int(expression[iterator] == 0)){
            return temp;
        }

        if (expression[iterator] == '+'){
            found_plus = true;
            break;
        }
        if (expression[iterator] == '*'){
            found_mult = true;
            break;
        }

        iterator++;
    }



    while(true){

    if (expression[iterator] == '('){
        break;
    }

    iterator++;
    }

    if (found_plus){
        return temp + calc_expression(expression, iterator);
    }

    else{
        Rectangle temp_two = Get_Rectangle(expression, iterator);

        while (true){
            if (expression[iterator] == ')'){
                break;
            }
        iterator++;
        }
        return temp * temp_two + calc_expression(expression, iterator + 1);





}
}

int main(){
std :: string expression;
std :: getline(std :: cin, expression);


Rectangle a = calc_expression(expression, 0);
a.print();

//temp.print();



return 0;
}
