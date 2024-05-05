#pragma once

template <typename T1, typename T2 = T1>
concept impl_basic_op = requires(T1 a, T2 b)
{
    +a;
    +b;
    -a;
    -b;
    a + b;
    b + a;
    a - b;
    b - a;
    a* b;
    b* a;
    a / b;
    b / a;
};

template <typename T1, typename T2 = T1>
concept impl_modulo = requires(T1 a, T2 b)
{
    a % b;
    b % a;
};

template <typename T1, typename T2 = T1>
concept impl_bitwise_op = requires(T1 a, T2 b)
{
    ~a;
    ~b;
    a& b;
    b& a;
    a | b;
    b | a;
    a ^ b;
    b ^ a;
    a << b;
    b << a;
    a >> b;
    b >> a;
};

template <typename T1, typename T2>
concept impl_arith_op =
    impl_basic_op<T1, T2> && impl_bitwise_op<T1, T2> && impl_modulo<T1, T2>;
