#include "test_rational.hpp"

int test_rational() {

Rational test_number;

Rational test_number_simple (7, 2);

Rational test_number_null_num (0, 7);

Rational test_number_negative_denom(1, -3);

Rational test_number_to_simplify (2, 10);


TestRunner kolya;

// default constuctor
Assertion_equality_Functor test_functor = {test_number.Numerator(), 0};
kolya.RunTest(test_functor,  "check Numerator value of the default constructed example");

test_functor =  {test_number.Denominator(), 1};
kolya.RunTest(test_functor,  "check Denominator value of the default constructed example");

//simple fractions
test_functor =  {test_number_simple.Numerator(), 7};
kolya.RunTest(test_functor,  "check Numerator value of the simple fraction");

test_functor =  {test_number_simple.Denominator(), 2};
kolya.RunTest(test_functor,  "check Denominator value of the simple fraction");

//null numerator
test_functor =  {test_number_null_num.Numerator(), 0};
kolya.RunTest(test_functor,  "check Numerator value of the  Null numerator fraction ");

test_functor =  {test_number_null_num.Denominator(), 1};
kolya.RunTest(test_functor,  "check Denominator value of the Null numerator fraction ");


//negative denominator
test_functor =  {test_number_negative_denom.Numerator(), -1};
kolya.RunTest(test_functor,  "check Numerator value of the  Negative denominator ");

test_functor =  {test_number_negative_denom.Denominator(), 3};
kolya.RunTest(test_functor,  "check Denominator value of the Negative denominator  ");

//simplify
test_functor =  {test_number_to_simplify.Numerator(), 1};
kolya.RunTest(test_functor,  "check Numerator value of the Simplified fraction ");

test_functor =  {test_number_to_simplify.Denominator(), 5};
kolya.RunTest(test_functor,  "check Denominator value of the Simplified fraction");


return 0;
}
