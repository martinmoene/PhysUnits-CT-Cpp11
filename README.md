PhysUnits C++11 (compile-time)
==============================

[![Language](https://img.shields.io/badge/language-C++-blue.svg)](https://isocpp.org/) [![Standard](https://img.shields.io/badge/c%2B%2B-11-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization) [![License](https://img.shields.io/badge/license-BSL-blue.svg)](https://opensource.org/licenses/BSL-1.0) [![Build Status master](https://img.shields.io/travis/martinmoene/PhysUnits-CT-Cpp11/master.svg?label=master)](https://travis-ci.org/martinmoene/PhysUnits-CT-Cpp11/branches) [![Version](https://badge.fury.io/gh/martinmoene%2FPhysUnits-CT-Cpp11.svg)](https://github.com/martinmoene/PhysUnits-CT-Cpp11/releases) [![download](https://img.shields.io/badge/latest%20version%20%20-download-blue.svg)](https://github.com/martinmoene/PhysUnits-CT-Cpp11/archive/master.zip) [![hunter](https://img.shields.io/badge/hunter-PhysUnits-blue.svg)](https://docs.hunter.sh/en/latest/packages/pkg/PhysUnits.html)

A small C++11 header-only library for compile-time dimensional analysis and unit/quantity manipulation and conversion.

This library is based on the quantity compile-time library by Michael S. Kenniston[1] and expanded and adapted for C++11 by Martin Moene.

**Contents**
- [Hello quantity](#hello-quantity)
- [Other libraries](#other-libraries)
- [Dependencies](#dependencies)
- [Limitations](#limitations)
- [Error handling](#error-handling)
- [Definition of terms](#definition-of-terms)
- [Dimensions, units and literals](#dimensions-units-and-literals)
- [Include files](#include-files)
- [Configuration](#configuration)  
- [Types and declarations](#types-and-declarations)
- [Operations and expressions](#operations-and-expressions)
- [Convenience functions](#convenience-functions)
- [Output variations](#output-variations)
- [Reported to work with](#reported-to-work-with)
- [Performance](#performance)
- [Ideas for improvement](#ideas-for-improvement)
- [References](#references)

Hello quantity
--------------
```C++
#include "phys/units/quantity.hpp"

using namespace phys::units;
using namespace phys::units::literals;

int main()
{
    quantity<speed_d> speed = 45_km / hour;
}
```

Other libraries
---------------
- Search GitHub for [unit dimension language:C++](https://github.com/search?utf8=%E2%9C%93&q=unit+dimension+language%3AC%2B%2B&type=Repositories).
- [PhysUnits-CT](https://github.com/martinmoene/PhysUnits-CT) - C++98 companion of this library.
- [PhysUnits-RT](https://github.com/martinmoene/PhysUnits-RT) - C++98 Run-time companion of this library.
- [Boost.Units](http://www.boost.org/doc/libs/1_51_0/libs/units/) - Zero-overhead dimensional analysis and unit/quantity manipulation and conversion in C++.
- [SI](https://github.com/bernedom/SI) - A header only C++ library that provides type safety and user defined literal. Dominik Berner.
- [units](https://github.com/mpusz/units) - A Physical Units Library for C++ providing compile-time dimensional analysis and unit/quantity manipulation. Mateusz Pusz.
- [units](https://github.com/nholthaus/units) - A compile-time, header-only, dimensional analysis and unit conversion library built on C++14 with no dependencies. Nic Holthaus.
- [units](https://github.com/tonypilz/units) - A lightweight compile-time, header-only, dimensional analysis and unit conversion library built on C++11 with no dependencies. Tony Pilz.
- [units](https://github.com/legento/units) - C++ compile time dimensional analysis. Oliver Esser.  
- [Units](https://github.com/VincentDucharme/Units) - C++ Library for managing values with units. Vincent Ducharme.
- [DimensionalAnalysis
](https://github.com/njoy/DimensionalAnalysis) - A compact C++ header-only library providing compile-time dimensional analysis and unit awareness. Austin McCartney.
- [units_literals
](https://github.com/acecil/units_literals) - User defined literals for Boost.Units.
- [unitscpp](http://code.google.com/p/unitscpp/) - A lightweight C++ library for physical calculation with units.
- Python packages [Numericalunits](http://pypi.python.org/pypi/numericalunits), [Pint](http://pypi.python.org/pypi/Pint) and [Units](http://pypi.python.org/pypi/units), mentioned in [3].

Dependencies
--------------
This library has no dependencies other than the standard C++ library.

Limitations
-----------
This library only supports the use of the <em>SI unit system</em>.

This library only supports <em>integral powers</em> of the dimensions.

Error handling
--------------
Error handling with respect to mixing incompatible dimensions occurs at compile-time.

Definition of terms
-------------------
Adapted from Boost.Units:
- <b>Base dimension</b>: A base dimension is loosely defined as a measurable entity of interest; in conventional dimensional analysis, base dimensions include length ([L]), mass ([M]), time ([T]), etc.. Base dimensions are essentially a tag type and provide no dimensional analysis functionality themselves.
- <b>Dimension</b>: A collection of zero or more base dimensions, each potentially raised to a different rational power. For example, length = [L]^1, area = [L]^2, velocity = [L]^1/[T]^1, and energy = [M]^1 [L]^2/[T]^2 are all dimensions.
- <b>Base unit</b>: A base unit represents a specific measure of a dimension. For example, while length is an abstract measure of distance, the meter is a concrete base unit of distance. Conversions are defined using base units. Much like base dimensions, base units are a tag type used solely to define units and do not support dimensional analysis algebra.
- <b>Unit</b>: A set of base units raised to rational exponents, e.g. m^1, kg^1, m^1/s^2.
- <b>System</b>: A unit system is a collection of base units representing all the measurable entities of interest for a specific problem. For example, the SI unit system defines seven base units : length ([L]) in meters, mass ([M]) in kilograms, time ([T]) in seconds, current ([I]) in amperes, temperature ([theta]) in kelvin, amount ([N]) in moles, and luminous intensity ([J]) in candelas. All measurable entities within the SI system can be represented as products of various integer or rational powers of these seven base units.
- <b>Quantity</b>: A quantity represents a concrete amount of a unit. Thus, while the meter is the base unit of length in the SI system, 5.5 meters is a quantity of length in that system.

Dimensions, units and literals
------------------------------
The seven fundamental SI [2] *dimensions* are length, mass, time interval, electric current, thermodynamic temperature, quantity of substance and luminous intensity. The base *units* are meter (m), kilogram (kg), second (s), ampere (A), mole (mol) and candela (cd).

The library defines dimensions such as `length_d` and `mass_d` and it defines quantities that represent their units as `meter` and `kilogram`. The library also defines [user-defined literal suffixes](https://en.wikipedia.org/wiki/C%2B%2B11#User-defined_literals) with prefixes ranging from yocto (1e-24L) through yotta (1e+24). Thus you can write quantity literals such as `1_ns` and ` 42.195_km`.

To use literals of non-base units, include the file `io.hpp` or `io_symbols.hpp`, or one or more of the following files named quantity_io_ *unit* .hpp where *unit* is becquerel, celsius, coulomb, farad, gray, henry, hertz, joule, lumen, lux, newton, ohm, pascal, radian, siemens, sievert, speed, steradian, tesla, volt, watt, weber.

Include files
-------------
- io.hpp - include all io-related include files.
- io_output.hpp - provide basic stream output in base dimensions.
- io_output_eng.hpp - provide stream output in [engineering notation](http://en.wikipedia.org/wiki/Engineering_notation), using [metric prefixes](http://en.wikipedia.org/wiki/Metric_prefix).
- io_symbols.hpp - include all files quantity_io_ *unit* .hpp
- other_units.hpp - units that are *not* approved for use with SI.
- physical_constants.hpp - Planck constant, speed of light etc.
- quantity.hpp - quantity, SI dimensions and units, base unit literals.
- quantity_io_ *unit* .hpp - name, symbol and literals for *unit*.

Configuration
-------------
-D<b>PHYS_UNITS_REP_TYPE</b>=double  
Define this to the <em>representation or value type</em> for the magnitude of quantity. Default is `double`.
You can change the type for all uses within a translation unit by defining `PHYS_UNITS_REP_TYPE` before inclusion of header quantity.hpp.

-D<b>PHYS_UNITS_COLLAPSE_TO_REP</b>=1  
The library can collapse dimensionless results to the representation type or continue with type `quantity<dimensionless_d>`. Define `PHYS_UNITS_COLLAPSE_TO_REP` to 0 to allow dimensionless quantities. Default is 1.

Types and declarations
----------------------
```C++
#include "phys/units/quantity.hpp"

using namespace phys::units;

quantity<mass_d> q_rep;           // magnitude has type Rep (PHYS_UNITS_REP_TYPE)
quantity<mass_d, float> q_float;  // magnitude has type float
```
The default <em>representation or value type</em> `Rep` for the magnitude of quantity is `double`. You can change the type for all uses within a translation unit by defining `PHYS_UNITS_REP_TYPE` before inclusion of header quantity.hpp.

Operations and expressions
--------------------------

- `N` is an integer constant
- `num` is an int, long, float, double, etc.
- `quantity1` and `quantity2` have different dimensions
- quantities with different magnitude types can be mixed

|Operation     |Operand Type(s)            |Result Type |
|--------------|---------------------------|------------|
|Construction  |`quantity()`               |`quantity`  |
|              |`quantity( quantity )`     |`quantity`  |
|Assignment    |`quantity = quantity`      |`quantity &`|
|Addition &    |`quantity += quantity`     |`quantity &`|
| Subtraction  |`quantity -= quantity`     |`quantity &`|
|              |`+quantity`                |`quantity`  |
|              |`-quantity`                |`quantity`  |
|              |`quantity + quantity`      |`quantity`  |
|              |`quantity - quantity`      |`quantity`  |
|Multiplication|`quantity *= num`          |`quantity &`|
|              |`quantity * num`           |`quantity`  |
|              |`num * quantity`           |`quantity`  |
|              |`quantity1 * quantity1`    |`quantity2` |
|              |`quantity1 * quantity2`    |`num` or `quantity3` |
|Division      |`quantity /= num`          |`quantity &`|
|              |`quantity / num`           |`quantity`  |
|              |`num / quantity1`          |`quantity2` |
|              |`quantity / quantity`      |`num`       |
|              |`quantity1 / quantity2`    |`quantity3` |
|Powers        |`nth_power<N>( quantity1 )`|`num` if N=0, `quantity1` if  N=1, `quantity2` otherwise|
|              |`square( quantity1 )`      |`quantity2` |
|              |`cube( quantity1 )`        |`quantity2` |
|Roots         |`nth_root<N>( quantity1 )` |`quantity2`, iff dimensions of quantity1 are all even multiples of N|
|              |`sqrt( quantity1 )`        |`quantity2`, iff dimensions of quantity1 are all even multiples of 2|
|Conversion    |`quantity1.to( quantity2 )`|`num` or `quantity3` (quantity1/quantity2)|
|Zero          |`quantity.zero()`          |`quantity` with magnitude 0|

Convenience functions
---------------------
The following convenience functions are provided.

In namespace `phys::units`:
- `DX dimension( quantity<DX, ...> const & q )` - the quantity's dimension.
- `X magnitude( quantity<..., X> const & q )` - the quantity's magnitude.
- `std::string to_magnitude( quantity<...> const & q )` - the quantity's magnitude represented as string.
- `std::string to_unit_name( quantity<...> const & q )` - the quantity's unit name, e.g. 'hertz'.
- `std::string to_unit_symbol( quantity<...> const & q )` - the quantity's unit symbol, e.g. 'Hz'.
- `std::string to_string( long double const value )` - the value of a long double represented as string.

In namespace `phys::units::io`:
- `std::string to_string( quantity<...> const & q )` - the quantity represented as string in scientific notation.
- `std::ostream & operator<<( std::ostream & os, quantity<...> const & q )` - output the quantity to a stream in scientific notation.

In namespace `phys::units::io::eng`:
- `std::string to_string( quantity<...> const & q )` - the quantity represented as string in engineering notation.
- `std::ostream & operator<<( std::ostream & os, quantity<...> const & q )` - output the quantity to a stream in engineering notation.

Output variations
-----------------
The following example shows the quantity type in the computation of work from force and distance and the printing of the result on standard output.
```C++
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
To get the presentation in base dimensions, you should not include `quantity_io_joule`, `io_symbols.hpp` or `io.hpp`.

Reported to work with
---------------------
- GCC 4.8.1
- Clang 3.2

Performance
-------------

```
Relative running time (lower is better)

Compiler        Option : double : quantity
-----------------------+--------+-------------
GCC 4.8.1         -O0  :  1     :  7
GCC 4.8.1         -O2  :  1     :  1
Clang 3.2         -O0  :  .     :  .
Clang 3.2         -O2  :  .     :  .

Measured on a AMD Athlon 64 X2 Dual Core Processor 5600+, 64kB L1 Data, 64kB L1 Instruction, 512kB L2, 3.2 GB RAM
```

Ideas for improvement
-----------------------
Allow to specify a conversion offset between two units, e.g. to make conversion between 'C and K possible (see Boost.Units).

References
----------
[1] Michael Kenniston. [The Quantity Library](http://home.xnet.com/~msk/quantity/quantity.html). ([Rationale](http://home.xnet.com/%7Emsk/quantity/quantity.html), Quantity [folder](http://www.xnet.com/%7Emsk/quantity)). 16 July 2001, rev 0.4.

[2] Ambler Thompson and Barry N. Taylor. [Guide for the Use of the International System of Units (SI)](http://physics.nist.gov/cuu/pdf/sp811.pdf). NIST Special Publication 811 2008 Edition.

[3] Gaston Hillar. [Quantities and Units in Python](http://www.drdobbs.com/jvm/quantities-and-units-in-python/240161101). Dr. Dobb's. 10 September 2013.
