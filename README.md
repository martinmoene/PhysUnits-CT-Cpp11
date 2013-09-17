PhysUnits-CT-C++11
==================

A C++11 header-only library for compile-time dimensional analysis and unit/quantity manipulation and conversion.

This library is based on the quantity compile-time library by Michael S. Kenniston[1] and expanded and adapted for C++11 by Martin Moene.

Example
---------
```C++
#include "phys/units/quantity.hpp"

using namespace phys::units;

int main()
{
    quantity<speed_d> speed = 45._km / hour;
}
```
Note: GCC requires that a floating point literal precedes the unit literal.

<h2>Other libraries</h2>
- [PhysUnits-CT](https://github.com/martinmoene/PhysUnits-CT) - C++98 companion of this library.
- [PhysUnits-RT](https://github.com/martinmoene/PhysUnits-RT) - C++98 Run-time companion of this library.
- [Boost.Units](http://www.boost.org/doc/libs/1_51_0/libs/units/) - Zero-overhead dimensional analysis and unit/quantity manipulation and conversion in C++.
- [unitscpp](http://code.google.com/p/unitscpp/) - A lightweight C++ library for physical calculation with units.
- Python packages [Numericalunits](http://pypi.python.org/pypi/numericalunits), [Pint](http://pypi.python.org/pypi/Pint) and [Units](http://pypi.python.org/pypi/units), mentioned in [3].

Usage
-------
### Definition of terms

Adapted from Boost.Units:
- <b>Base dimension</b>: A base dimension is loosely defined as a measurable entity of interest; in conventional dimensional analysis, base dimensions include length ([L]), mass ([M]), time ([T]), etc.. Base dimensions are essentially a tag type and provide no dimensional analysis functionality themselves.
- <b>Dimension</b>: A collection of zero or more base dimensions, each potentially raised to a different rational power. For example, length = [L]^1, area = [L]^2, velocity = [L]^1/[T]^1, and energy = [M]^1 [L]^2/[T]^2 are all dimensions.
- <b>Base unit</b>: A base unit represents a specific measure of a dimension. For example, while length is an abstract measure of distance, the meter is a concrete base unit of distance. Conversions are defined using base units. Much like base dimensions, base units are a tag type used solely to define units and do not support dimensional analysis algebra.
- <b>Unit</b>: A set of base units raised to rational exponents, e.g. m^1, kg^1, m^1/s^2.
- <b>System</b>: A unit system is a collection of base units representing all the measurable entities of interest for a specific problem. For example, the SI unit system defines seven base units : length ([L]) in meters, mass ([M]) in kilograms, time ([T]) in seconds, current ([I]) in amperes, temperature ([theta]) in kelvin, amount ([N]) in moles, and luminous intensity ([J]) in candelas. All measurable entities within the SI system can be represented as products of various integer or rational powers of these seven base units.
- <b>Quantity</b>: A quantity represents a concrete amount of a unit. Thus, while the meter is the base unit of length in the SI system, 5.5 meters is a quantity of length in that system.

### Limitations
This library only supports the use of the <em>SI unit system</em>.

This library only supports <em>integral powers</em> of the dimensions.

The <em>representation or value type</em> in the implementation of quantity is fixed and cannot be defined separately for each quantity. However you can change the type for all uses within a translation unit by defining `PHYS_UNITS_REP_TYPE` before inclusion of header quantity.hpp. Default this type is `double`.

### Output

The following example shows the quantity type in the computation of work from force and distance and the printing of the result on standard output.
```C++
#include <iostream>

#include "phys/units/io.hpp"
#include "phys/units/quantity.hpp"

using namespace phys::units;
using namespace phys::units::io;

quantity<energy_d>
work( const quantity<force_d> & F, const quantity<length_d> & dx )
{
    return F * dx; // Defines the relation: work = force * distance.
}

int main()
{
    // Test calculation of work.
    quantity<force_d>       F { 2.0_N         };  // Define a quantity of force.
    quantity<length_d>      dx{ 2.0_m         };  // and a distance,
    quantity<energy_d>      E { work( F, dx ) };  // and calculate the work done.

    std::cout << "F  = " << F  << std::endl
              << "dx = " << dx << std::endl
              << "E  = " << E  << std::endl;
}
```

The output produced is:
```
F  = 2 N
dx = 2 m
E  = 4 J
```

The following example demonstrates printing in default floating point notation and in [engineering notation](http://en.wikipedia.org/wiki/Engineering_notation), using [metric prefixes](http://en.wikipedia.org/wiki/Metric_prefix).
```C++
#include <iostream>

#include "phys/units/io.hpp"
#include "phys/units/quantity.hpp"

using namespace phys::units;

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
```
The output produced is:
```
R = 4700 Ohm
R = 4.70 kOhm
```
See namespaces `io` and `io::eng` for further information.

Instead of unit names such as J, you can also obtain the unit expressed in base dimensions.
```C++
#include <iostream>

#include "phys/units/quantity.hpp"
#include "phys/units/quantity_io.hpp"

using namespace phys::units;
using namespace phys::units::io;

int main()
{
    std::cout << "J = " << joule << std::endl;
}
```
The output produced is:
```
J = m+2 kg s-2
```

### Convenience functions

There are several convenience functions, such as:
- `std::string to_magnitude( quantity<...> const & q )` - the quantity's magnitude represented as string
- `std::string to_unit_name( quantity<...> const & q )` - the quantity's unit name, e.g. 'hertz'
- `std::string to_unit_symbol( quantity<...> const & q )` - the quantity's unit symbol, e.g. 'Hz'
- `std::string to_string( long double const value )` - the value of a long double represented as string

In namespace `io`:
- `std::string to_string( quantity<...> const & q )` - the quantity represented as string in scientific notation
- `std::ostream & operator<<( std::ostream & os, quantity<...> const & q )` - output the quantity to a stream in scientific notation

In namespace `io::eng`:
- `std::string to_string( quantity<...> const & q )` - the quantity represented as string in engineering notation
- `std::ostream & operator<<( std::ostream & os, quantity<...> const & q )` - output the quantity to a stream in engineering notation

### Error handling
Error handling with respect to mixing incompatible dimensions occurs at compile-time.

### Mixing run-time and compile-time libraries
Although this library seems to be in the `phys::units` namespace, it does so through *using* the `ct` namespace in the global namespace. So this library actually lives in the `ct::phys::units` namespace. When you want to mix this library with its compile-time companion, the `ct` namespace must be applied. This can be accomplished by defining `PHYS_UNITS_IN_CT_NAMESPACE`.

Dependencies
--------------
This library has no dependencies other than the standard C++ libraries.

Performance
-------------
TBD
```
Relative running time (lower is better)

Compiler        Option : double : quantity
-----------------------+--------+-------------
GCC 4.8.1         -O2  :  1     :  . (1)
Clang 3.2         -O2  :  .     :  . (1.x)

Measured on a AMD Athlon 64 X2 Dual Core Processor 5600+, 64kB L1 Data, 64kB L1 Instruction, 512kB L2, 3.2 GB RAM
```

Compilers known to work
-------------------------
- GCC 4.8.1
- Clang 3.2

Ideas for improvement
-----------------------
Allow to specify a conversion offset between two units, e.g. to make conversion between 'C and K possible (see Boost.Units).

It may be nice if you can obtain a quantity in a unit representation of your choice, e.g. in kWh in stead of J [m+2 kg s-2]. See G.S. Novak. [Conversion of units of measurement (PDF)](http://reference.kfupm.edu.sa/content/c/o/conversion_of_units_of_measurement__42431.pdf)". 1 August 1997.

### References
[1] Michael Kenniston. [The Quantity Library](http://home.xnet.com/~msk/quantity/quantity.html). ([Rationale](http://home.xnet.com/%7Emsk/quantity/quantity.html), Quantity [folder](http://www.xnet.com/%7Emsk/quantity)). 16 July 2001, rev 0.4.

[2] Ambler Thompson and Barry N. Taylor. [Guide for the Use of the International System of Units (SI)](http://physics.nist.gov/cuu/pdf/sp811.pdf). NIST Special Publication 811 2008 Edition.

[3] Gaston Hillar. [Quantities and Units in Python](http://www.drdobbs.com/jvm/quantities-and-units-in-python/240161101). Dr. Dobb's. 10 September 2013.

[![Build Status](https://travis-ci.org/martinmoene/PhysUnits-CT-Cpp11.png?branch=master)](https://travis-ci.org/martinmoene/PhysUnits-CT-Cpp11)
