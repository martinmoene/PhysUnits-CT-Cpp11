/**
 * \file io_output_engineering.hpp
 *
 * \brief   Engineering IO for quantity library.
 * \author  Martin Moene
 * \date    7 September 2013
 * \since   1.0
 *
 * Copyright 2013 Universiteit Leiden. All rights reserved.
 *
 * Based on the following question and answer on StackOverflow:
 * Convert float number to string with engineering notation (with SI prefixe) in Python [closed].
 * Asked by working4coins, http://stackoverflow.com/users/2051311/working4coins
 * Answered by scls, http://stackoverflow.com/users/1609077/scls
 * http://stackoverflow.com/questions/15733772/convert-float-number-to-string-with-engineering-notation-with-si-prefixe-in-py
 *
 * This code is provided as-is, with no warrantee of correctness.
 *
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef PHYS_UNITS_QUANTITY_IO_ENGINEERING_HPP_INCLUDED
#define PHYS_UNITS_QUANTITY_IO_ENGINEERING_HPP_INCLUDED

#include "phys/units/quantity_io.hpp"

#include <cmath>
#include <iomanip>
#include <limits>
#include <sstream>

/*
 * Note: micro, µ, may not work everywhere, so you can define a glyph yourself:
 */
#ifndef ENG_FORMAT_MICRO_GLYPH
# define ENG_FORMAT_MICRO_GLYPH "u"
#endif

/// namespace phys.

namespace phys {

/// namespace units.

namespace units {

/// namespace detail.

namespace detail {

char const * const prefixes[/*exp*/][2][9] =
{
    {
        {   "",   "m",   ENG_FORMAT_MICRO_GLYPH
                            ,   "n",    "p",    "f",    "a",    "z",    "y", },
        {   "",   "k",   "M",   "G",    "T",    "P",    "E",    "Z",    "Y", },
    },
    {
        { "e0", "e-3", "e-6", "e-9", "e-12", "e-15", "e-18", "e-21", "e-24", },
        { "e0",  "e3",  "e6",  "e9",  "e12",  "e15",  "e18",  "e21",  "e24", },
    },
};

template<typename T, size_t N>
constexpr size_t dimenson_of( T(&)[N] )
{
    return N;
}

constexpr int prefix_count = dimenson_of( prefixes[false][false]  );

inline int sign( int const value )
{
    return value == 0 ? +1 : value / std::abs( value );
}

inline bool iszero( double const value )
{
    return FP_ZERO == std::fpclassify( value );
}

inline long degree_of( double const value )
{
    return iszero( value ) ? 0 : std::lrint( std::floor( std::log10( std::abs( value ) ) / 3) );
}

inline int precision( double const scaled, int const digits )
{
    return iszero( scaled ) ? digits - 1 : digits - std::log10( std::abs( scaled ) ) - 2 * std::numeric_limits<double>::epsilon();
}

inline std::string prefix_or_exponent( bool const exponential, int const degree )
{
    return std::string( exponential || 0 == degree ? "" : " " ) + prefixes[ exponential ][ sign(degree) > 0 ][ std::abs( degree ) ];
}

inline std::string exponent( int const degree )
{
    std::ostringstream os;
    os << "e" << 3 * degree;
    return os.str();
}

inline std::string bracket( std::string const unit )
{
	return std::string::npos != unit.find_first_of( "+- " ) ? "(" + unit + ")" : unit;
}

} // anonymous namespace

/**
 * convert real number to prefixed or exponential notation, optionally followed by a unit.
 */
inline std::string
to_engineering_string( double const value, int const digits = 3, bool exponential = false, bool const showpos = false, std::string const unit = "" )
{
    using namespace detail;

    if      ( std::isnan( value ) ) return "NaN";
    else if ( std::isinf( value ) ) return "INFINITE";

    const int degree = degree_of( value );

    std::string factor;

    if ( std::abs( degree ) < prefix_count )
    {
        factor = prefix_or_exponent( exponential, degree );
    }
    else
    {
        exponential = true;
        factor = exponent( degree );
    }

    std::ostringstream os;

    const double scaled = value * std::pow( 1000.0, -degree );

    const std::string space = ( 0 == degree || exponential ) && unit.length() ? " ":"";

    os << std::fixed << (showpos ? std::showpos : std::noshowpos) << std::setprecision( precision(scaled, digits) ) << scaled << factor << space << bracket( unit );

    return os.str();
}

namespace io {
namespace eng {

template< typename Dims, typename T >
std::string to_string( quantity<Dims, T> const & q, int const digits = 3, bool const exponential = false, bool const showpos = false )
{
   return to_engineering_string( q.magnitude(), digits, exponential, showpos, to_unit_symbol( q ) );
}

template< typename Dims, typename T >
inline std::ostream & operator<<( std::ostream & os, quantity< Dims, T > const & q )
{
   return os << to_string( q );
}

} // namespace eng
} // namespace io

}} // namespace phys::units

#endif // PHYS_UNITS_QUANTITY_IO_ENGINEERING_HPP_INCLUDED

/*
 * end of file
 */

