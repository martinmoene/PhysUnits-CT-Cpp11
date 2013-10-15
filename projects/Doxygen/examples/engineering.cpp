#include <iostream>

#include "phys/units/io.hpp"
#include "phys/units/quantity.hpp"

using namespace phys::units;
using namespace phys::units::literals;

int main()
{
    quantity<electric_resistance_d> R{ 4.7_kV / ampere };

    {
        using namespace phys::units::io;
        std::cout << "R = " << R << std::endl;
    }
    {
        using namespace phys::units::io::eng;
        std::cout << "R = " << R << std::endl;
    }
}
