#include "forward_multiplication.hh"

outer_lambda_type mult_by = [](int lhs) {
    return [lhs](int rhs) { return rhs * lhs; };
};