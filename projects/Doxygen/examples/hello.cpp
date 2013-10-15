#include "phys/units/quantity.hpp"

using namespace phys::units;
using namespace phys::units::literals;

int main()
{
    quantity<speed_d> speed = 45_km / hour;
}
