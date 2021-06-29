#include <iomanip>
#include <iostream>
#include <limits>

// gain confidence on your programming skills and learn about numeric precision

// add new repo
// add epsilon

// time ./pi_taylor 2000000000

// https://en.wikipedia.org/wiki/Kahan_summation_algorithm

// https://www.paulbui.net/wl/Taylor_Series_Pi_and_e

// comparar float y long double con y sin Kahan summation

// repartir el cálculo entre tantos hilos como cores tenga nuestra máquina o 4
// y luego 1024 hilos
// y después comparar con std::reduce y una lambda o función

// first step
// create a function that computes pi with a Taylor series
// for a given number of steps use long long to get the value

// optional implement Bailey, Borwein and Plouffe approach
// https://www.davidhbailey.com//dhbpapers/digits.pdf

using my_float = long double;

auto pi_taylor(size_t steps) -> my_float {

    my_float acc = 0.0f;
    int sign = 1;

    for (size_t i = 0; i < steps; ++i) {
        my_float divider = 2.0f * i + 1.0f;
        acc += static_cast<my_float>(sign) / divider;
       sign = -sign;
    }

    acc*=4.0f;
    return acc;
}

int main(int argc, const char *argv[]) {

    // read the number of steps from the command line
    if (argc != 2) {
        std::cerr << "Invalid syntax: pi_taylor <steps>" << std::endl;
        exit(1);

    }

    size_t steps = std::stoll(argv[1]);
    auto pi = pi_taylor(steps);

    std::cout << "For " << steps << ", pi value: "
        << std::setprecision(std::numeric_limits<long double>::digits10 + 1)
        << pi << std::endl;
}
