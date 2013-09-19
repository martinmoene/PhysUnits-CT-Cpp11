/**
 * \file test_quantity_io_io.cpp
 *
 * \brief   lest tests for quantity library.
 * \author  Martin Moene
 * \date    16 September 2013
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
#include "phys/units/io_output_eng.hpp"
#include "phys/units/io_symbols.hpp"

#include "test_util.hpp"  // include before lest.hpp

#ifndef USE_HAMLEST
# include "lest.hpp"
#else
# include "hamlest.hpp"
  using namespace lest::match;
#endif

using namespace phys::units;

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

    "quantity base unit literal names", []
    {
        EXPECT( to_unit_name( meter    ) == "meter" );
        EXPECT( to_unit_name( kilogram ) == "kilogram" );
        EXPECT( to_unit_name( second   ) == "second" );
        EXPECT( to_unit_name( ampere   ) == "ampere" );
        EXPECT( to_unit_name( kelvin   ) == "kelvin" );
        EXPECT( to_unit_name( mole     ) == "mole" );
        EXPECT( to_unit_name( candela  ) == "candela" );
    },

    "quantity base unit literal symbols", []
    {
        EXPECT( to_unit_symbol( meter    ) == "m" );
        EXPECT( to_unit_symbol( kilogram ) == "kg" );
        EXPECT( to_unit_symbol( second   ) == "s" );
        EXPECT( to_unit_symbol( ampere   ) == "A" );
        EXPECT( to_unit_symbol( kelvin   ) == "K" );
        EXPECT( to_unit_symbol( mole     ) == "mol" );
        EXPECT( to_unit_symbol( candela  ) == "cd" );
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
