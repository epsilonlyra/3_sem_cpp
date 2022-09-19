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

        x += order * (digit - 48); // magical number

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

Rectangle calc_expression_plus(std :: string expression, int begin_iter){
    /*
    Add consecutive rectangles
    */

    int iterator = begin_iter;

    if (int(expression[iterator] == 0)){
            return Rectangle();
    }

    Rectangle temp = Get_Rectangle(expression, iterator);

    bool found_plus = false;

    while(!found_plus){

        if (int(expression[iterator] == 0)){
            return temp;
        }

        if (expression[iterator] == '+'){
            int counter_left_bracket = 0;

            int iterator_two = iterator;

            while(true){
                if (expression[iterator_two] == '('){
                    counter_left_bracket++;
                }

                if (counter_left_bracket > 1){
                    found_plus = true;
                    break;

                }

                if (expression[iterator_two] == '*'){
                    return temp;
                }

                iterator_two++;
            }

        }

        if (expression[iterator] == '*'){
            return Rectangle();
        }

        iterator++;
    }


    while(true){

        if (expression[iterator] == '('){
            break;
        }

        iterator++;
    }

    return temp + calc_expression_plus(expression, iterator);
}

Rectangle calc_expression_mult(std :: string expression, int begin_iter){
     /*
    Multiply consecutive rectangles
    */

    int iterator = begin_iter;

    if (int(expression[iterator] == 0)){
            return Rectangle(Point(999999, 999999)); // some big number
        }

    Rectangle temp = Get_Rectangle(expression, iterator);

    bool found_mult = false;

    while(!found_mult){

        if (int(expression[iterator] == 0)){
            return temp;
        }

        if (expression[iterator] == '*'){
            found_mult = true;
            break;
        }

        if (int(expression[iterator] == '+')){
            return temp;
        }

        iterator++;
    }


    while(true){

        if (expression[iterator] == '('){
            break;
        }

        iterator++;
    }

    return temp * calc_expression_mult(expression, iterator);
}

Rectangle calc_expression(std :: string expression, int begin_iter){

    bool found_plus = false;
    bool found_mult = false;

    int iterator = begin_iter;

    while(!found_plus && !found_mult){

        if (int(expression[iterator] == 0)){
            break;

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

    if (found_plus){

        found_mult = false;

        while(!found_mult){

            if (int(expression[iterator] == 0)){
                break;
            }

            if (expression[iterator] == '*'){
                found_mult = true;
                break;
            }

            iterator++;
        }


        if (found_mult){

            while(true){
                if (expression[iterator] == '('){
                    break;
                }
                iterator--;
            }

            return calc_expression_plus(expression, begin_iter) + calc_expression(expression, iterator);
        }

        return calc_expression_plus(expression, begin_iter);

    }

    else if (found_mult){

        found_plus = false;

        while(!found_plus){

            if (int(expression[iterator] == 0)){
                break;
            }

            if (expression[iterator] == '+'){
                found_plus = true;
                break;
            }

            iterator++;

        }

        if (found_plus){

            while(true){
                if (expression[iterator] == '('){
                    break;
                }
                iterator++;
            }
            return calc_expression_mult(expression, begin_iter) + calc_expression(expression, iterator);
        }

        return calc_expression_mult(expression, begin_iter);
    }

    else{
        return calc_expression_plus(expression, begin_iter);
    }
}

int main(){
std :: string expression;
std :: getline(std :: cin, expression);

Rectangle temp = calc_expression(expression, 0);
temp.print();

return 0;
}
