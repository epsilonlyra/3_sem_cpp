#include "test_complex.hpp"

int test_complex() {

Complex test_number (2, 1);

Complex test_number_2 (-2, -1);

Complex test_number_3(2, 1);

double real_number = 4;

TestRunner elena;
//constuctor
Assertion_equality_Functor test_functor = {test_number.Real(), 2};
elena.RunTest(test_functor,  "check Real value of the constructed example");

test_functor =  {test_number.Imaginary(), 1};
elena.RunTest(test_functor,  "check Imaginary value of the constructed example");

//sum
test_functor = {(test_number + test_number_2).Real(), 0};
elena.RunTest(test_functor,  "check Real value of the sum");

test_functor = {(test_number + test_number_2).Imaginary(), 0};
elena.RunTest(test_functor,  "check Imaginary value of the sum");

//difference
test_functor = {(test_number - test_number_2).Real(), 4};
elena.RunTest(test_functor,  "check Real value of the difference");

test_functor = {(test_number - test_number_2).Imaginary(), 2};
elena.RunTest(test_functor,  "check Imaginary value of the difference");

//multiplication
test_functor = {(test_number * test_number_2).Real(), -3};
elena.RunTest(test_functor,  "check Real value of the product");

test_functor = {(test_number - test_number_2).Imaginary(), 2};
elena.RunTest(test_functor,  "check Imaginary value of the product");

//addition by a real
test_functor = {(test_number  + real_number).Real(), 6};
elena.RunTest(test_functor,  "check Real value of the sum with real ");

test_functor = {(test_number + real_number).Imaginary(), 1};
elena.RunTest(test_functor,  "check Imaginary value of the sum with real");



//non equality check
Assertion_equality_Functor<bool, bool> test_functor_logical = {!(test_number == test_number_2)};
elena.RunTest(test_functor_logical,  "non Equality check");

//equality chek
test_functor_logical = {(test_number == test_number_3)};
elena.RunTest(test_functor_logical,  "Equality check");

return 0;
}
