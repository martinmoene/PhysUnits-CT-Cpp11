//
// Copyright (c) 2026-2026 Martin Moene
//
// https://github.com/martinmoene/PhysUnits-CT-Cpp11
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef TEST_PHYS_UNITS_H_INCLUDED
#define TEST_PHYS_UNITS_H_INCLUDED

#include "phys/units/quantity.hpp"
#include "phys/units/io_output.hpp"
#include "phys/units/io_output_eng.hpp"
#include "phys/units/other_units.hpp"

#include <iomanip>
#include <sstream>

// Compiler warning suppression for usage of lest:

#ifdef __clang__
# pragma clang diagnostic ignored "-Wstring-conversion"
# pragma clang diagnostic ignored "-Wunused-parameter"
# pragma clang diagnostic ignored "-Wunused-template"
# pragma clang diagnostic ignored "-Wunused-function"
# pragma clang diagnostic ignored "-Wunused-member-function"
#elif defined __GNUC__
# pragma GCC   diagnostic ignored "-Wunused-parameter"
# pragma GCC   diagnostic ignored "-Wunused-function"
#endif

#ifndef USE_HAMLEST
# include "lest_cpp03.hpp"
#else
#error
# include "hamlest.hpp"
  using namespace lest::match;
#endif

#define CASE( name ) lest_CASE( specification(), name )

// Attribute externally visible for -fwhole-program:

#if defined(__GNUC__) && !defined(__clang__)
# define bit_ATTRIBUTE_EXT_VIS  __attribute__((externally_visible))
#else
# define bit_ATTRIBUTE_EXT_VIS
#endif

extern lest::tests & specification() bit_ATTRIBUTE_EXT_VIS;

// define to_string(dimensions<>) before inclusion of lest.hpp:

namespace lest {

template< int D1, int D2, int D3, int D4, int D5, int D6, int D7>
std::string to_string( ::phys::units::dimensions<D1,D2,D3,D4,D5,D6,D7> const & /*dim*/ )
{
    std::ostringstream os;
    os << "<" << D1 << "," << D2 << "," << D3 << "," << D4 << "," << D5 << "," << D6 << "," << D7 << ">";
    return os.str();
}

template <typename D, typename T>
std::string to_string( ::phys::units::quantity<D,T> const & q )
{
    std::ostringstream os;
    os << to_string( q.dimension() ) << "(" << q.magnitude() << ")";
    return os.str();
}

// using ::phys::units::io::operator<<;

template< int D1, int D2, int D3, int D4, int D5, int D6, int D7>
std::ostream & operator<<( std::ostream & os, ::phys::units::dimensions<D1,D2,D3,D4,D5,D6,D7> const & dim )
{
    return os << to_string( dim );
}

template< typename Dims, typename T >
std::ostream & operator<<( std::ostream & os, ::phys::units::quantity<Dims, T> const & q )
{
    return os << to_string( q );
}

} // namespace lest

inline std::string
operator"" _str( char const * text, std::size_t /*num_chars*/ )
{
    return text;
}

inline std::string
s( phys::units::Rep v )
{
    std::ostringstream os;
    os.setf( std::ios::fixed, std::ios::floatfield );
    os << std::setprecision(6) << v;
    return os.str();
}

inline std::string
e( phys::units::Rep v )
{
    std::ostringstream os;
    os.setf( std::ios::scientific, std::ios::floatfield );
    os << std::setprecision(1) << v;
    return os.str();
}

template< typename Dims, typename T >
inline std::string
s( phys::units::quantity<Dims, T> const & q /*, name_symbol const use = name_symbol() */ )
{
    std::ostringstream os;
    os.setf( std::ios::fixed, std::ios::floatfield );
    os << std::setprecision(6) << q.magnitude(); // q.value();

//    if ( q.dimension() != dimensionless_d )
    {
        os << (Dims::is_all_zero ? "":" ") << to_unit_symbol( q /*, use */ );
    }
    return os.str();
}

#endif // TEST_PHYS_UNITS_H_INCLUDED

// end of file
