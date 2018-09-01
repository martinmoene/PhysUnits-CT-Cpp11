/**
 * \file test_util.hpp
 *
 * \brief   utilities for quantity library tests.
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

#ifndef TEST_UTIL_HPP_INCLUDED
#define TEST_UTIL_HPP_INCLUDED

#include "phys/units/io_output.hpp"

#include <iomanip>
#include <sstream>

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

} // namespace lest

inline std::string
operator "" _str( char const * text, std::size_t /*num_chars*/ )
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

#endif // TEST_UTIL_HPP_INCLUDED
