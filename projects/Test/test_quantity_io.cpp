/**
 * \file test_quantity_io.cpp
 *
 * \brief   lest tests for quantity library.
 * \author  Martin Moene
 * \date    19 September 2013
 * \since   1.0
 *
 * Copyright 2013 Universiteit Leiden. All rights reserved.
 * This code is provided as-is, with no warrantee of correctness.
 *
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//#define USE_HAMLEST
//#define TEST_COMPILE_TIME

#include "phys/units/quantity.hpp"
#include "phys/units/io_symbols.hpp"
#include "phys/units/io_output_eng.hpp"

#include "test_util.hpp"  // include before lest.hpp

#ifndef USE_HAMLEST
# include "lest.hpp"
#else
# include "hamlest.hpp"
  using namespace lest::match;
#endif

using namespace phys::units;
using namespace phys::units::literals;

const lest::test output[] =
{
    "quantity output conversions", []
    {
        using namespace phys::units::io;

        EXPECT( to_unit_name  ( meter ) == "meter" );
        EXPECT( to_unit_symbol( meter ) == "m" );
        EXPECT( to_string     ( meter ) == "1 m" );

        EXPECT( to_unit_name  ( 1_m ) == "meter" );
        EXPECT( to_unit_symbol( 1_m ) == "m" );
        EXPECT( to_string(      1_m ) == "1 m" );
    },

    "quantity basic stream output", []
    {
        using namespace phys::units::io;

        std::ostringstream os; os << 1.23_km;

        EXPECT( os.str() == "1230 m" );
    },

    "quantity engineering stream output", []
    {
        using namespace phys::units::io::eng;

        std::ostringstream os; os << 1.23_km;

        EXPECT( os.str() == "1.23 km" );
    },

    "quantity output exceptions", []
    {
        EXPECT_THROWS_AS( prefix( "x" ), prefix_error );
    },

    "quantity base unit names", []
    {
        EXPECT( to_unit_name( meter    ) == "meter" );
        EXPECT( to_unit_name( kilogram ) == "kilogram" );
        EXPECT( to_unit_name( second   ) == "second" );
        EXPECT( to_unit_name( ampere   ) == "ampere" );
        EXPECT( to_unit_name( kelvin   ) == "kelvin" );
        EXPECT( to_unit_name( mole     ) == "mole" );
        EXPECT( to_unit_name( candela  ) == "candela" );
    },

    "quantity base unit symbols", []
    {
        EXPECT( to_unit_symbol( meter    ) == "m" );
        EXPECT( to_unit_symbol( kilogram ) == "kg" );
        EXPECT( to_unit_symbol( second   ) == "s" );
        EXPECT( to_unit_symbol( ampere   ) == "A" );
        EXPECT( to_unit_symbol( kelvin   ) == "K" );
        EXPECT( to_unit_symbol( mole     ) == "mol" );
        EXPECT( to_unit_symbol( candela  ) == "cd" );
    },

    "quantity other unit names", []
    {
// Hz   EXPECT( to_unit_name( becquerel ) == "becquerel" );
        EXPECT( to_unit_name( coulomb   ) == "coulomb" );
        EXPECT( to_unit_name( farad     ) == "farad" );
// Sv   EXPECT( to_unit_name( gray      ) == "gray" );
        EXPECT( to_unit_name( henry     ) == "henry" );
        EXPECT( to_unit_name( hertz     ) == "hertz" );
        EXPECT( to_unit_name( joule     ) == "joule" );
// Cd   EXPECT( to_unit_name( lumen     ) == "lumen" );
        EXPECT( to_unit_name( lux       ) == "lux" );
        EXPECT( to_unit_name( newton    ) == "newton" );
        EXPECT( to_unit_name( ohm       ) == "ohm" );
        EXPECT( to_unit_name( pascal    ) == "pascal" );
// []   EXPECT( to_unit_name( radian    ) == "radian" );
        EXPECT( to_unit_name( siemens   ) == "siemens" );
        EXPECT( to_unit_name( sievert   ) == "sievert" );
// []   EXPECT( to_unit_name( steradian ) == "steradian" );
        EXPECT( to_unit_name( tesla     ) == "tesla" );
        EXPECT( to_unit_name( volt      ) == "volt" );
        EXPECT( to_unit_name( watt      ) == "watt" );
    },

    "quantity other unit symbols", []
    {
// Hz   EXPECT( to_unit_symbol( becquerel ) == "Bq" );
        EXPECT( to_unit_symbol( coulomb   ) == "C" );
        EXPECT( to_unit_symbol( farad     ) == "F" );
// Sv   EXPECT( to_unit_symbol( gray      ) == "Gy" );
        EXPECT( to_unit_symbol( henry     ) == "H" );
        EXPECT( to_unit_symbol( hertz     ) == "Hz" );
        EXPECT( to_unit_symbol( joule     ) == "J" );
// Cd   EXPECT( to_unit_symbol( lumen     ) == "lm" );
        EXPECT( to_unit_symbol( lux       ) == "lx" );
        EXPECT( to_unit_symbol( newton    ) == "N" );
        EXPECT( to_unit_symbol( ohm       ) == "Ohm" );
        EXPECT( to_unit_symbol( pascal    ) == "Pa" );
// []   EXPECT( to_unit_symbol( radian    ) == "rad" );
        EXPECT( to_unit_symbol( siemens   ) == "S" );
        EXPECT( to_unit_symbol( sievert   ) == "Sv" );
// []   EXPECT( to_unit_symbol( steradian ) == "sr" );
        EXPECT( to_unit_symbol( tesla     ) == "T" );
        EXPECT( to_unit_symbol( volt      ) == "V" );
        EXPECT( to_unit_symbol( watt      ) == "W" );
    },

    "quantity other unit literals", []
    {
//      EXPECT( to_unit_symbol( 1_Bq ) == "Bq" );
        EXPECT( to_unit_symbol( 1_C  ) == "C" );
        EXPECT( to_unit_symbol( 1_F  ) == "F" );
//      EXPECT( to_unit_symbol( 1_Gy ) == "Gy" );
        EXPECT( to_unit_symbol( 1_H  ) == "H" );
        EXPECT( to_unit_symbol( 1_Hz ) == "Hz" );
        EXPECT( to_unit_symbol( 1_J  ) == "J" );
// Cd   EXPECT( to_unit_symbol( 1_lm ) == "lm" );
        EXPECT( to_unit_symbol( 1_lx ) == "lx" );
        EXPECT( to_unit_symbol( 1_N  ) == "N" );
        EXPECT( to_unit_symbol( 1_Ohm) == "Ohm" );
        EXPECT( to_unit_symbol( 1_Pa ) == "Pa" );
// []   EXPECT( to_unit_symbol( 1_rad) == "rad" );
        EXPECT( to_unit_symbol( 1_S  ) == "S" );
        EXPECT( to_unit_symbol( 1_Sv ) == "Sv" );
// []   EXPECT( to_unit_symbol( 1_sr ) == "sr" );
        EXPECT( to_unit_symbol( 1_T  ) == "T" );
        EXPECT( to_unit_symbol( 1_V  ) == "V" );
        EXPECT( to_unit_symbol( 1_W  ) == "W" );
    },

};

int main()
{
    const int total = 0
    + lest::run( output )
    ;

    if ( total )
    {
        std::cout << "Grand total of " << total << " failed " << lest::pluralise(total, "test") << "." << std::endl;
    }

    return total;
}

// g++ -Wall -Wextra -Weffc++ -std=c++11 -I../../ -o test_quantity_io.exe test_quantity_io.cpp && test_quantity_io.exe
