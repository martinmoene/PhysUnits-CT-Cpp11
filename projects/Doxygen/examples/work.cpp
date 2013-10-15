#include <iostream>

#include "phys/units/io.hpp"
#include "phys/units/quantity.hpp"

using namespace phys::units;
using namespace phys::units::io;
using namespace phys::units::literals;

quantity<energy_d>
work( const quantity<force_d> & F, const quantity<length_d> & dx )
{
    return F * dx; // Defines the relation: work = force * distance.
}

int main()
{
    // Test calculation of work.
    quantity<force_d>       F { 2_N           };  // Define a quantity of force.
    quantity<length_d>      dx{ 2_m           };  // and a distance,
    quantity<energy_d>      E { work( F, dx ) };  // and calculate the work done.

    std::cout << "F  = " << F  << std::endl
              << "dx = " << dx << std::endl
              << "E  = " << E  << std::endl;
}
