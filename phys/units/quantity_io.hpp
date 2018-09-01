/**
 * \file quantity_io.hpp
 *
 * \brief   IO for quantity library.
 * \author  Michael S. Kenniston, Martin Moene
 * \date    10 September 2013
 * \since   0.4
 *
 * Copyright 2013 Universiteit Leiden. All rights reserved.
 *
 * Copyright (c) 2001 by Michael S. Kenniston.  For the most
 * recent version check www.xnet.com/~msk/quantity.  Permission is granted
 * to use this code without restriction so long as this copyright
 * notice appears in all source files.
 *
 * This code is provided as-is, with no warrantee of correctness.
 *
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef PHYS_UNITS_QUANTITY_IO_HPP_INCLUDED
#define PHYS_UNITS_QUANTITY_IO_HPP_INCLUDED

#include "phys/units/quantity.hpp"

#include <algorithm>
#include <iosfwd>
#include <map>
#include <stdexcept>
#include <string>
#include <sstream>

/// namespace phys.

namespace phys {

/// namespace units.

namespace units {

/// quantity error base class (not used by quantity itself).

struct quantity_error : public std::runtime_error
{
    quantity_error( std::string const text )
        : std::runtime_error( text )  { }
};

/// prefix error, e.g. when prefix is unrecognized.

struct prefix_error : public quantity_error
{
    prefix_error( std::string const text )
        : quantity_error( text ) { }
};

/// return factor for given prefix.

inline Rep prefix( std::string const prefix_ )
{
    std::map<std::string, Rep> table
    {
        { "m", milli },
        { "k", kilo  },
        { "u", micro },
        { "M", mega  },
        { "n", nano  },
        { "G", giga  },
        { "p", pico  },
        { "T", tera  },
        { "f", femto },
        { "P", peta  },
        { "a", atto  },
        { "E", exa   },
        { "z", zepto },
        { "Z", zetta },
        { "y", yocto },
        { "Y", yotta },
        { "h", hecto },
        { "da", deka },
        { "d", deci  },
        { "c", centi },
    };

    auto pos = table.find( prefix_ );

    if ( pos == table.end() )
    {
        throw prefix_error( "quantity: unrecognized prefix '" + prefix_ + "'" );
    }

    return pos->second;
}

/**
 * Provide SI units-and-exponents in as close to NIST-specified format as possible with plain ascii.
 *
 * Made presentation customizable by specialization of template.
 * Adapted by Martin Moene, 21 February 2012.
 */
template <typename Dims>
struct unit_info
{
    /// true if base dimension.

    static bool single()
    {
        return Dims::is_base;
    }

    /// provide unit's name.

    static std::string name()
    {
        return symbol();
    }

    /// provide unit's symbol.

    static std::string symbol()
    {
        std::ostringstream os;

        bool first = true;

        emit_dim( os, "m",   Dims::dim1, first );
        emit_dim( os, "kg",  Dims::dim2, first );
        emit_dim( os, "s",   Dims::dim3, first );
        emit_dim( os, "A",   Dims::dim4, first );
        emit_dim( os, "K",   Dims::dim5, first );
        emit_dim( os, "mol", Dims::dim6, first );
        emit_dim( os, "cd",  Dims::dim7, first );

        return os.str();
    }

    /// emit a single dimension.

    static void emit_dim( std::ostream & os, const char * label, int exp, bool & first )
    {
        if( exp == 0 )
            return;

        if ( first )
            first = false;
        else
            os << " ";

        os << label;

        if( exp > 1 )
            os << "+";

        if( exp != 1 )
            os << exp;
    }
};

}} // namespace phys::units

#include "quantity_io_meter.hpp"
#include "quantity_io_kilogram.hpp"
#include "quantity_io_second.hpp"
#include "quantity_io_ampere.hpp"
#include "quantity_io_mole.hpp"
#include "quantity_io_candela.hpp"

/*
 * User must choose celsius or kelvin, either by defining
 * QUANTITY_USE_CELSIUS or QUANTITY_USE_KELVIN, or by
 * including the desired include file.
 */
#if defined(QUANTITY_USE_CELSIUS) && defined(QUANTITY_USE_KELVIN)
# error At most define one of QUANTITY_USE_CELSIUS, QUANTITY_USE_KELVIN
#endif
#ifdef QUANTITY_USE_CELSIUS
# include "quantity_io_celsius.hpp"
#endif
#ifdef QUANTITY_USE_KELVIN
# include "quantity_io_kelvin.hpp"
#endif

namespace phys { namespace units {

/// magnitude as string.

template< typename  Dims, typename T >
std::string to_magnitude( quantity<Dims, T> const & q )
{
    std::ostringstream os;
    os << q.magnitude();
    return os.str();
}

/// unit name.

template< typename Dims, typename T >
std::string to_unit_name( quantity<Dims, T> const & /* q  */)
{
    return unit_info<Dims>::name();
}

/// unit symbol.

template< typename Dims, typename T >
std::string to_unit_symbol( quantity<Dims, T> const & /* q */)
{
    return unit_info<Dims>::symbol();
}

/// string representation of value.

inline std::string to_string( long double const value )
{
    std::ostringstream os;
    os << value;
    return os.str();
}

/// namespace io.

namespace io {

/// stream quantity.

template< typename Dims, typename T >
std::ostream & operator<<( std::ostream & os, quantity<Dims, T> const & q )
{
    return os << q.magnitude() << (Dims::is_all_zero ? "":" ") << to_unit_symbol( q );
}

/// quantity string representation.

template< typename Dims, typename T >
std::string to_string( quantity<Dims, T> const & q )
{
    std::ostringstream os;
    os << q;
    return os.str();
}

} // namespace io

}} // namespace phys::units

#endif // PHYS_UNITS_QUANTITY_IO_HPP_INCLUDED

/*
 * end of file
 */
