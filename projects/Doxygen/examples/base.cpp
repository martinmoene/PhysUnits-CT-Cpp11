#include <iostream>

#include "phys/units/quantity.hpp"
#include "phys/units/quantity_io.hpp"

using namespace phys::units;
using namespace phys::units::io;

int main()
{
    std::cout << "J = " << joule << std::endl;
}
