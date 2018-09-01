/**
 * \file quantity.hpp
 *
 * \brief   Zero-overhead dimensional analysis and unit/quantity manipulation and conversion.
 * \author  Michael S. Kenniston, Martin Moene
 * \date    7 September 2013
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

/*
 * Unless otherwise specified, the definitions of all units in this
 * file are from NIST Special Publication 811, found online at
 * http://physics.nist.gov/Document/sp811.pdf
 * Other sources: OED = Oxford English Dictionary
 */

#ifndef PHYS_UNITS_QUANTITY_HPP_INCLUDED
#define PHYS_UNITS_QUANTITY_HPP_INCLUDED

#include <cmath>
#include <cstdlib>
#include <utility>  // std::declval

// Configuration

#ifndef  PHYS_UNITS_COLLAPSE_TO_REP
# define PHYS_UNITS_COLLAPSE_TO_REP  1
#endif

/// namespace phys.

namespace phys {

/// namespace units.

namespace units {

#ifdef PHYS_UNITS_REP_TYPE
   using Rep = PHYS_UNITS_REP_TYPE;
#else
   using Rep = double;
#endif

/*
 * declare now, define later.
 */
template< typename Dims, typename T = Rep >
class quantity;

/**
 * We could drag dimensions around individually, but it's much more convenient to package them.
 */
template< int D1, int D2, int D3, int D4 = 0, int D5 = 0, int D6 = 0, int D7 = 0 >
struct dimensions
{
    enum
    {
        dim1 = D1,
        dim2 = D2,
        dim3 = D3,
        dim4 = D4,
        dim5 = D5,
        dim6 = D6,
        dim7 = D7,

        is_all_zero =
            D1 == 0 && D2 == 0 && D3 == 0 && D4 == 0 && D5 == 0 && D6 == 0 && D7 == 0,

        is_base =
            1 == (D1 != 0) + (D2 != 0) + (D3 != 0) + (D4 != 0) + (D5 != 0) + (D6 != 0) + (D7 != 0)  &&
            1 ==  D1 + D2 + D3 + D4 + D5 + D6 + D7,
    };

    template< int R1, int R2, int R3, int R4, int R5, int R6, int R7 >
    constexpr bool operator==( dimensions<R1, R2, R3, R4, R5, R6, R7> const & ) const
    {
        return D1==R1 && D2==R2 && D3==R3 && D4==R4 && D5==R5 && D6==R6 && D7==R7;
    }

    template< int R1, int R2, int R3, int R4, int R5, int R6, int R7 >
    constexpr bool operator!=( dimensions<R1, R2, R3, R4, R5, R6, R7> const & rhs ) const
    {
        return !( *this == rhs );
    }
};

/// demensionless 'dimension'.

typedef dimensions< 0, 0, 0 > dimensionless_d;

/// namespace detail.

namespace detail {

/**
 * \brief The "collapse" template is used to avoid quantity< dimensions< 0, 0, 0 > >,
 * i.e. to make dimensionless results come out as type "Rep".
 */
template< typename D, typename T >
struct collapse
{
    typedef quantity< D, T > type;
};

#if defined( PHYS_UNITS_COLLAPSE_TO_REP )

template< typename T >
struct collapse< dimensionless_d, T >
{
    typedef T type;
};

#endif

template< typename D, typename T >
using Collapse = typename collapse<D,T>::type;

// promote types of expression to result type.

template < typename X, typename Y >
using PromoteAdd = decltype( std::declval<X>() + std::declval<Y>() );

template < typename X, typename Y >
using PromoteMul = decltype( std::declval<X>() * std::declval<Y>() );

/*
 * The following batch of structs are type generators to calculate
 * the correct type of the result of various operations.
 */

/**
 * product type generator.
 */
template< typename DX, typename DY, typename T >
struct product
{
    enum
    {
        d1 = DX::dim1 + DY::dim1,
        d2 = DX::dim2 + DY::dim2,
        d3 = DX::dim3 + DY::dim3,
        d4 = DX::dim4 + DY::dim4,
        d5 = DX::dim5 + DY::dim5,
        d6 = DX::dim6 + DY::dim6,
        d7 = DX::dim7 + DY::dim7,
    };

    typedef Collapse< dimensions< d1, d2, d3, d4, d5, d6, d7 >, T > type;
};

template< typename DX, typename DY, typename X, typename Y>
using Product = typename product<DX, DY, PromoteMul<X,Y>>::type;

/**
 * quotient type generator.
 */
template< typename DX, typename DY, typename T >
struct quotient
{
    enum
    {
        d1 = DX::dim1 - DY::dim1,
        d2 = DX::dim2 - DY::dim2,
        d3 = DX::dim3 - DY::dim3,
        d4 = DX::dim4 - DY::dim4,
        d5 = DX::dim5 - DY::dim5,
        d6 = DX::dim6 - DY::dim6,
        d7 = DX::dim7 - DY::dim7,
    };

    typedef Collapse< dimensions< d1, d2, d3, d4, d5, d6, d7 >, T > type;
};

template< typename DX, typename DY, typename X, typename Y>
using Quotient = typename quotient<DX, DY, PromoteMul<X,Y>>::type;

/**
 * reciprocal type generator.
 */
template< typename D, typename T >
struct reciprocal
{
    enum
    {
        d1 = - D::dim1,
        d2 = - D::dim2,
        d3 = - D::dim3,
        d4 = - D::dim4,
        d5 = - D::dim5,
        d6 = - D::dim6,
        d7 = - D::dim7,
    };

    typedef Collapse< dimensions< d1, d2, d3, d4, d5, d6, d7 >, T > type;
};

template< typename D, typename X, typename Y>
using Reciprocal = typename reciprocal<D, PromoteMul<X,Y>>::type;

/**
 * power type generator.
 */
template< typename D, int N, typename T >
struct power
{
    enum
    {
        d1 = N * D::dim1,
        d2 = N * D::dim2,
        d3 = N * D::dim3,
        d4 = N * D::dim4,
        d5 = N * D::dim5,
        d6 = N * D::dim6,
        d7 = N * D::dim7,
    };

    typedef Collapse< dimensions< d1, d2, d3, d4, d5, d6, d7 >, T > type;
};

template< typename D, int N, typename T >
using Power = typename detail::power< D, N, T >::type;

/**
 * root type generator.
 */
template< typename D, int N, typename T >
struct root
{
    enum
    {
        all_even_multiples =
            D::dim1 % N == 0 &&
            D::dim2 % N == 0 &&
            D::dim3 % N == 0 &&
            D::dim4 % N == 0 &&
            D::dim5 % N == 0 &&
            D::dim6 % N == 0 &&
            D::dim7 % N == 0
    };

    enum
    {
        d1 = D::dim1 / N,
        d2 = D::dim2 / N,
        d3 = D::dim3 / N,
        d4 = D::dim4 / N,
        d5 = D::dim5 / N,
        d6 = D::dim6 / N,
        d7 = D::dim7 / N
    };

    typedef Collapse< dimensions< d1, d2, d3, d4, d5, d6, d7 >, T > type;
};

template< typename D, int N, typename T >
using Root = typename detail::root< D, N, T >::type;

/**
 * tag to construct a quantity from a magnitude.
 */
constexpr struct magnitude_tag_t{} magnitude_tag{};

} // namespace detail

/**
 * \brief class "quantity" is the heart of the library. It associates
 * dimensions  with a single "Rep" data member and protects it from
 * dimensionally inconsistent use.
 */
template< typename Dims, typename T /*= Rep */ >
class quantity
{
public:
    typedef Dims dimension_type;

    typedef T value_type;

    typedef quantity<Dims, T> this_type;

    constexpr quantity() : m_value{} { }

    /**
     * public converting initializing constructor;
     * requires magnitude_tag to prevent constructing a quantity from a raw magnitude.
     */
    template <typename X>
    constexpr explicit quantity( detail::magnitude_tag_t, X x )
    : m_value( x ) { }

    /**
     * converting copy-assignment constructor.
     */
    template <typename X >
    constexpr quantity( quantity<Dims, X> const & x )
    : m_value( x.magnitude() ) { }

//    /**
//     * convert to compatible unit, for example: (3._dm).to(meter) gives 0.3;
//     */
//    constexpr value_type to( quantity const & x ) const {  return *this / x; }

    /**
     * convert to given unit, for example: (3._dm).to(meter) gives 0.3;
     */
    template <typename DX, typename X>
    constexpr auto to( quantity<DX,X> const & x ) const -> detail::Quotient<Dims,DX,T,X>
    {
        return *this / x;
    }

    /**
     * the quantity's magnitude.
     */
    constexpr value_type magnitude() const { return m_value; }

    /**
     * the quantity's dimensions.
     */
    constexpr dimension_type dimension() const { return dimension_type{}; }

    /**
     * We need a "zero" of each type -- for comparisons, to initialize running
     * totals, etc.  Note:  0 m != 0 kg, since they are of different dimensionality.
     * zero is really just defined for convenience, since
     * quantity< length_d >::zero == 0 * meter, etc.
     */
    static constexpr quantity zero() { return quantity{ value_type( 0.0 ) }; }
//    static constexpr quantity zero = quantity{ value_type( 0.0 ) };

private:
    /**
     * private initializing constructor.
     */
    constexpr explicit quantity( value_type x ) : m_value{ x } { }

private:
    value_type m_value;

    enum { has_dimension = ! Dims::is_all_zero };

#if defined( PHYS_UNITS_COLLAPSE_TO_REP )
    static_assert( has_dimension, "quantity dimensions must not all be zero" );
#endif

private:
    // friends:

    // arithmetic

    template <typename D, typename X, typename Y>
    friend constexpr quantity<D, X> &
    operator+=( quantity<D, X> & x, quantity<D, Y> const & y );

    template <typename D, typename X>
    friend constexpr quantity<D, X>
    operator+( quantity<D, X> const & x );

    template< typename D, typename X, typename Y >
    friend constexpr quantity <D, detail::PromoteAdd<X,Y>>
    operator+( quantity<D, X> const & x, quantity<D, Y> const & y );

    template <typename D, typename X, typename Y>
    friend constexpr quantity<D, X> &
    operator-=( quantity<D, X> & x, quantity<D, Y> const & y );

    template <typename D, typename X>
    friend constexpr quantity<D, X>
    operator-( quantity<D, X> const & x );

    template< typename D, typename X, typename Y >
    friend constexpr quantity <D, detail::PromoteAdd<X,Y>>
    operator-( quantity<D, X> const & x, quantity<D, Y> const & y );

    template< typename D, typename X, typename Y>
    friend constexpr quantity<D, X> &
    operator*=( quantity<D, X> & x, const Y & y );

    template <typename D, typename X, typename Y>
    friend constexpr quantity<D, detail::PromoteMul<X,Y>>
    operator*( quantity<D, X> const & x, const Y & y );

    template <typename D, typename X, typename Y>
    friend constexpr quantity< D, detail::PromoteMul<X,Y> >
    operator*( const X & x, quantity<D, Y> const & y );

    template <typename DX, typename DY, typename X, typename Y>
    friend constexpr detail::Product<DX, DY, X, Y>
    operator*( quantity<DX, X> const & lhs, quantity< DY, Y > const & rhs );

    template< typename D, typename X, typename Y>
    friend constexpr quantity<D, X> &
    operator/=( quantity<D, X> & x, const Y & y );

    template <typename D, typename X, typename Y>
    friend constexpr quantity<D, detail::PromoteMul<X,Y>>
    operator/( quantity<D, X> const & x, const Y & y );

    template <typename D, typename X, typename Y>
    friend constexpr detail::Reciprocal<D, X, Y>
    operator/( const X & x, quantity<D, Y> const & y );

    template <typename DX, typename DY, typename X, typename Y>
    friend constexpr detail::Quotient<DX, DY, X, Y>
    operator/( quantity<DX, X> const & x, quantity< DY, Y > const & y );

    // absolute value.

    template <typename D, typename X>
    friend constexpr quantity<D,X>
    abs( quantity<D,X> const & x );

    // powers and roots

    template <int N, typename D, typename X>
    friend detail::Power<D, N, X>
    nth_power( quantity<D, X> const & x );

    template <typename D, typename X>
    friend constexpr detail::Power<D, 2, X>
    square( quantity<D, X> const & x );

    template <typename D, typename X>
    friend constexpr detail::Power<D, 3, X>
    cube( quantity<D, X> const & x );

    template <int N, typename D, typename X>
    friend detail::Root<D, N, X>
    nth_root( quantity<D, X> const & x );

    template <typename D, typename X>
    friend detail::Root< D, 2, X >
    sqrt( quantity<D, X> const & x );

    // comparison

    template <typename D, typename X, typename Y>
    friend constexpr bool operator==( quantity<D, X> const & x, quantity<D, Y> const & y );

    template <typename D, typename X, typename Y>
    friend constexpr bool operator!=( quantity<D, X> const & x, quantity<D, Y> const & y );

    template <typename D, typename X, typename Y>
    friend constexpr bool operator<( quantity<D, X> const & x, quantity<D, Y> const & y );

    template <typename D, typename X, typename Y>
    friend constexpr bool operator<=( quantity<D, X> const & x, quantity<D, Y> const & y );

    template <typename D, typename X, typename Y>
    friend constexpr bool operator>( quantity<D, X> const & x, quantity<D, Y> const & y );

    template <typename D, typename X, typename Y>
    friend constexpr bool operator>=( quantity<D, X> const & x, quantity<D, Y> const & y );
};

// Give names to the seven fundamental dimensions of physical reality.

typedef dimensions< 1, 0, 0, 0, 0, 0, 0 > length_d;
typedef dimensions< 0, 1, 0, 0, 0, 0, 0 > mass_d;
typedef dimensions< 0, 0, 1, 0, 0, 0, 0 > time_interval_d;
typedef dimensions< 0, 0, 0, 1, 0, 0, 0 > electric_current_d;
typedef dimensions< 0, 0, 0, 0, 1, 0, 0 > thermodynamic_temperature_d;
typedef dimensions< 0, 0, 0, 0, 0, 1, 0 > amount_of_substance_d;
typedef dimensions< 0, 0, 0, 0, 0, 0, 1 > luminous_intensity_d;

// Addition operators

/// quan += quan

template <typename D, typename X, typename Y>
constexpr quantity<D, X> &
operator+=( quantity<D, X> & x, quantity<D, Y> const & y )
{
    return x.m_value += y.m_value, x;
}

/// + quan

template <typename D, typename X>
constexpr quantity<D, X>
operator+( quantity<D, X> const & x )
{
   return quantity<D, X >( +x.m_value );
}

/// quan + quan

template< typename D, typename X, typename Y >
constexpr quantity <D, detail::PromoteAdd<X,Y>>
operator+( quantity<D, X> const & x, quantity<D, Y> const & y )
{
   return quantity<D, detail::PromoteAdd<X,Y>>( x.m_value + y.m_value );
}

// Subtraction operators

/// quan -= quan

template <typename D, typename X, typename Y>
constexpr quantity<D, X> &
operator-=( quantity<D, X> & x, quantity<D, Y> const & y )
{
    return x.m_value -= y.m_value, x;
}

/// - quan

template <typename D, typename X>
constexpr quantity<D, X>
operator-( quantity<D, X> const & x )
{
   return quantity<D, X >( -x.m_value );
}

/// quan - quan

template< typename D, typename X, typename Y >
constexpr quantity <D, detail::PromoteAdd<X,Y>>
operator-( quantity<D, X> const & x, quantity<D, Y> const & y )
{
   return quantity<D, detail::PromoteAdd<X,Y>>( x.m_value - y.m_value );
}

// Multiplication operators

/// quan *= num

template< typename D, typename X, typename Y>
constexpr quantity<D, X> &
operator*=( quantity<D, X> & x, const Y & y )
{
   return x.m_value *= y, x;
}

/// quan * num

template <typename D, typename X, typename Y>
constexpr quantity<D, detail::PromoteMul<X,Y>>
operator*( quantity<D, X> const & x, const Y & y )
{
   return quantity<D, detail::PromoteMul<X,Y>>( x.m_value * y );
}

/// num * quan

template <typename D, typename X, typename Y>
constexpr quantity< D, detail::PromoteMul<X,Y> >
operator*( const X & x, quantity<D, Y> const & y )
{
   return quantity<D, detail::PromoteMul<X,Y>>( x * y.m_value );
}

/// quan * quan:

template <typename DX, typename DY, typename X, typename Y>
constexpr detail::Product<DX, DY, X, Y>
operator*( quantity<DX, X> const & lhs, quantity< DY, Y > const & rhs )
{
    return detail::Product<DX, DY, X, Y>( lhs.m_value * rhs.m_value );
}

// Division operators

/// quan /= num

template< typename D, typename X, typename Y>
constexpr quantity<D, X> &
operator/=( quantity<D, X> & x, const Y & y )
{
   return x.m_value /= y, x;
}

/// quan / num

template <typename D, typename X, typename Y>
constexpr quantity<D, detail::PromoteMul<X,Y>>
operator/( quantity<D, X> const & x, const Y & y )
{
   return quantity<D, detail::PromoteMul<X,Y>>( x.m_value / y );
}

/// num / quan

template <typename D, typename X, typename Y>
constexpr detail::Reciprocal<D, X, Y>
operator/( const X & x, quantity<D, Y> const & y )
{
   return detail::Reciprocal<D, X, Y>( x / y.m_value );
}

/// quan / quan:

template <typename DX, typename DY, typename X, typename Y>
constexpr detail::Quotient<DX, DY, X, Y>
operator/( quantity<DX, X> const & x, quantity< DY, Y > const & y )
{
    return detail::Quotient<DX, DY, X, Y>( x.m_value / y.m_value );
}

/// absolute value.

template <typename D, typename X>
constexpr quantity<D,X> abs( quantity<D,X> const & x )
{
   return quantity<D,X>( std::abs( x.m_value ) );
}

// General powers

/// N-th power.

template <int N, typename D, typename X>
detail::Power<D, N, X>
nth_power( quantity<D, X> const & x )
{
   return detail::Power<D, N, X>( std::pow( x.m_value, X( N ) ) );
}

// Low powers defined separately for efficiency.

/// square.

template <typename D, typename X>
constexpr detail::Power<D, 2, X>
square( quantity<D, X> const & x )
{
   return x * x;
}

/// cube.

template <typename D, typename X>
constexpr detail::Power<D, 3, X>
cube( quantity<D, X> const & x )
{
   return x * x * x;
}

// General root

/// n-th root.

template <int N, typename D, typename X>
detail::Root<D, N, X>
nth_root( quantity<D, X> const & x )
{
   static_assert( detail::root<D, N, X>::all_even_multiples, "root result dimensions must be integral" );

   return detail::Root<D, N, X>( std::pow( x.m_value, X( 1.0 ) / N ) );
}

// Low roots defined separately for convenience.

/// square root.

template <typename D, typename X>
detail::Root< D, 2, X >
sqrt( quantity<D, X> const & x )
{
   static_assert(
      detail::root<D, 2, X >::all_even_multiples, "root result dimensions must be integral" );

   return detail::Root<D, 2, X>( std::pow( x.m_value, X( 1.0 ) / 2 ) );
}

// Comparison operators

/// equality.

template <typename D, typename X, typename Y>
constexpr bool
operator==( quantity<D, X> const & x, quantity<D, Y> const & y )
{
   return x.m_value == y.m_value;
}

/// inequality.

template <typename D, typename X, typename Y>
constexpr bool
operator!=( quantity<D, X> const & x, quantity<D, Y> const & y )
{
   return x.m_value != y.m_value;
}

/// less-than.

template <typename D, typename X, typename Y>
constexpr bool
operator<( quantity<D, X> const & x, quantity<D, Y> const & y )
{
   return x.m_value < y.m_value;
}

/// less-equal.

template <typename D, typename X, typename Y>
constexpr bool
operator<=( quantity<D, X> const & x, quantity<D, Y> const & y )
{
   return x.m_value <= y.m_value;
}

/// greater-than.

template <typename D, typename X, typename Y>
constexpr bool
operator>( quantity<D, X> const & x, quantity<D, Y> const & y )
{
   return x.m_value > y.m_value;
}

/// greater-equal.

template <typename D, typename X, typename Y>
constexpr bool
operator>=( quantity<D, X> const & x, quantity<D, Y> const & y )
{
   return x.m_value >= y.m_value;
}

/// quantity's dimension.

template <typename DX, typename X>
inline constexpr DX dimension( quantity<DX,X> const & q ) { return q.dimension(); }

/// quantity's magnitude.

template <typename DX, typename X>
inline constexpr X magnitude( quantity<DX,X> const & q ) { return q.magnitude(); }

// The seven SI base units.  These tie our numbers to the real world.

constexpr quantity<length_d                   > meter   { detail::magnitude_tag, 1.0 };
constexpr quantity<mass_d                     > kilogram{ detail::magnitude_tag, 1.0 };
constexpr quantity<time_interval_d            > second  { detail::magnitude_tag, 1.0 };
constexpr quantity<electric_current_d         > ampere  { detail::magnitude_tag, 1.0 };
constexpr quantity<thermodynamic_temperature_d> kelvin  { detail::magnitude_tag, 1.0 };
constexpr quantity<amount_of_substance_d      > mole    { detail::magnitude_tag, 1.0 };
constexpr quantity<luminous_intensity_d       > candela { detail::magnitude_tag, 1.0 };

// The standard SI prefixes.

constexpr long double yotta = 1e+24L;
constexpr long double zetta = 1e+21L;
constexpr long double   exa = 1e+18L;
constexpr long double  peta = 1e+15L;
constexpr long double  tera = 1e+12L;
constexpr long double  giga = 1e+9L;
constexpr long double  mega = 1e+6L;
constexpr long double  kilo = 1e+3L;
constexpr long double hecto = 1e+2L;
constexpr long double  deka = 1e+1L;
constexpr long double  deci = 1e-1L;
constexpr long double centi = 1e-2L;
constexpr long double milli = 1e-3L;
constexpr long double micro = 1e-6L;
constexpr long double  nano = 1e-9L;
constexpr long double  pico = 1e-12L;
constexpr long double femto = 1e-15L;
constexpr long double  atto = 1e-18L;
constexpr long double zepto = 1e-21L;
constexpr long double yocto = 1e-24L;

// Binary prefixes, pending adoption.

constexpr long double kibi = 1024;
constexpr long double mebi = 1024 * kibi;
constexpr long double gibi = 1024 * mebi;
constexpr long double tebi = 1024 * gibi;
constexpr long double pebi = 1024 * tebi;
constexpr long double exbi = 1024 * pebi;
constexpr long double zebi = 1024 * exbi;
constexpr long double yobi = 1024 * zebi;

// The rest of the standard dimensional types, as specified in SP811.

using absorbed_dose_d             = dimensions< 2, 0, -2 >;
using absorbed_dose_rate_d        = dimensions< 2, 0, -3 >;
using acceleration_d              = dimensions< 1, 0, -2 >;
using activity_of_a_nuclide_d     = dimensions< 0, 0, -1 >;
using angular_velocity_d          = dimensions< 0, 0, -1 >;
using angular_acceleration_d      = dimensions< 0, 0, -2 >;
using area_d                      = dimensions< 2, 0, 0 >;
using capacitance_d               = dimensions< -2, -1, 4, 2 >;
using concentration_d             = dimensions< -3, 0, 0, 0, 0, 1 >;
using current_density_d           = dimensions< -2, 0, 0, 1 >;
using dose_equivalent_d           = dimensions< 2, 0, -2 >;
using dynamic_viscosity_d         = dimensions< -1, 1, -1 >;
using electric_charge_d           = dimensions< 0, 0, 1, 1 >;
using electric_charge_density_d   = dimensions< -3, 0, 1, 1 >;
using electric_conductance_d      = dimensions< -2, -1, 3, 2 >;
using electric_field_strenth_d    = dimensions< 1, 1, -3, -1 >;
using electric_flux_density_d     = dimensions< -2, 0, 1, 1 >;
using electric_potential_d        = dimensions< 2, 1, -3, -1 >;
using electric_resistance_d       = dimensions< 2, 1, -3, -2 >;
using energy_d                    = dimensions< 2, 1, -2 >;
using energy_density_d            = dimensions< -1, 1, -2 >;
using exposure_d                  = dimensions< 0, -1, 1, 1 >;
using force_d                     = dimensions< 1, 1, -2 >;
using frequency_d                 = dimensions< 0, 0, -1 >;
using heat_capacity_d             = dimensions< 2, 1, -2, 0, -1 >;
using heat_density_d              = dimensions< 0, 1, -2 >;
using heat_density_flow_rate_d    = dimensions< 0, 1, -3 >;
using heat_flow_rate_d            = dimensions< 2, 1, -3 >;
using heat_flux_density_d         = dimensions< 0, 1, -3 >;
using heat_transfer_coefficient_d = dimensions< 0, 1, -3, 0, -1 >;
using illuminance_d               = dimensions< -2, 0, 0, 0, 0, 0, 1 >;
using inductance_d                = dimensions< 2, 1, -2, -2 >;
using irradiance_d                = dimensions< 0, 1, -3 >;
using kinematic_viscosity_d       = dimensions< 2, 0, -1 >;
using luminance_d                 = dimensions< -2, 0, 0, 0, 0, 0, 1 >;
using luminous_flux_d             = dimensions< 0, 0, 0, 0, 0, 0, 1 >;
using magnetic_field_strength_d   = dimensions< -1, 0, 0, 1 >;
using magnetic_flux_d             = dimensions< 2, 1, -2, -1 >;
using magnetic_flux_density_d     = dimensions< 0, 1, -2, -1 >;
using magnetic_permeability_d     = dimensions< 1, 1, -2, -2 >;
using mass_density_d              = dimensions< -3, 1, 0 >;
using mass_flow_rate_d            = dimensions< 0, 1, -1 >;
using molar_energy_d              = dimensions< 2, 1, -2, 0, 0, -1 >;
using molar_entropy_d             = dimensions< 2, 1, -2, -1, 0, -1 >;
using moment_of_force_d           = dimensions< 2, 1, -2 >;
using permittivity_d              = dimensions< -3, -1, 4, 2 >;
using power_d                     = dimensions< 2, 1, -3 >;
using pressure_d                  = dimensions< -1, 1, -2 >;
using radiance_d                  = dimensions< 0, 1, -3 >;
using radiant_intensity_d         = dimensions< 2, 1, -3 >;
using speed_d                     = dimensions< 1, 0, -1 >;
using specific_energy_d           = dimensions< 2, 0, -2 >;
using specific_heat_capacity_d    = dimensions< 2, 0, -2, 0, -1 >;
using specific_volume_d           = dimensions< 3, -1, 0 >;
using substance_permeability_d    = dimensions< -1, 0, 1 >;
using surface_tension_d           = dimensions< 0, 1, -2 >;
using thermal_conductivity_d      = dimensions< 1, 1, -3, 0, -1 >;
using thermal_diffusivity_d       = dimensions< 2, 0, -1 >;
using thermal_insulance_d         = dimensions< 0, -1, 3, 0, 1 >;
using thermal_resistance_d        = dimensions< -2, -1, 3, 0, 1 >;
using thermal_resistivity_d       = dimensions< -1, -1, 3, 0, 1 >;
using torque_d                    = dimensions< 2, 1, -2 >;
using volume_d                    = dimensions< 3, 0, 0 >;
using volume_flow_rate_d          = dimensions< 3, 0, -1 >;
using wave_number_d               = dimensions< -1, 0, 0 >;

// Handy values.

constexpr Rep pi      { Rep( 3.141592653589793238462L ) };
constexpr Rep percent { Rep( 1 ) / 100 };

//// Not approved for use alone, but needed for use with prefixes.
constexpr quantity< mass_d                  > gram         { kilogram / 1000 };

// The derived SI units, as specified in SP811.

constexpr Rep                                 radian       { Rep( 1 ) };
constexpr Rep                                 steradian    { Rep( 1 ) };
constexpr quantity< force_d                 > newton       { meter * kilogram / square( second ) };
constexpr quantity< pressure_d              > pascal       { newton / square( meter ) };
constexpr quantity< energy_d                > joule        { newton * meter };
constexpr quantity< power_d                 > watt         { joule / second };
constexpr quantity< electric_charge_d       > coulomb      { second * ampere };
constexpr quantity< electric_potential_d    > volt         { watt / ampere };
constexpr quantity< capacitance_d           > farad        { coulomb / volt };
constexpr quantity< electric_resistance_d   > ohm          { volt / ampere };
constexpr quantity< electric_conductance_d  > siemens      { ampere / volt };
constexpr quantity< magnetic_flux_d         > weber        { volt * second };
constexpr quantity< magnetic_flux_density_d > tesla        { weber / square( meter ) };
constexpr quantity< inductance_d            > henry        { weber / ampere };
constexpr quantity< thermodynamic_temperature_d > degree_celsius   { kelvin };
constexpr quantity< luminous_flux_d         > lumen        { candela * steradian };
constexpr quantity< illuminance_d           > lux          { lumen / meter / meter };
constexpr quantity< activity_of_a_nuclide_d > becquerel    { 1 / second };
constexpr quantity< absorbed_dose_d         > gray         { joule / kilogram };
constexpr quantity< dose_equivalent_d       > sievert      { joule / kilogram };
constexpr quantity< frequency_d             > hertz        { 1 / second };

// The rest of the units approved for use with SI, as specified in SP811.
// (However, use of these units is generally discouraged.)

constexpr quantity< length_d                > angstrom     { Rep( 1e-10L ) * meter };
constexpr quantity< area_d                  > are          { Rep( 1e+2L ) * square( meter ) };
constexpr quantity< pressure_d              > bar          { Rep( 1e+5L ) * pascal };
constexpr quantity< area_d                  > barn         { Rep( 1e-28L ) * square( meter ) };
constexpr quantity< activity_of_a_nuclide_d > curie        { Rep( 3.7e+10L ) * becquerel };
constexpr quantity< time_interval_d         > day          { Rep( 86400L ) * second };
constexpr Rep                                 degree_angle { pi / 180 };
constexpr quantity< acceleration_d          > gal          { Rep( 1e-2L ) * meter / square( second ) };
constexpr quantity< area_d                  > hectare      { Rep( 1e+4L ) * square( meter ) };
constexpr quantity< time_interval_d         > hour         { Rep( 3600 ) * second };
constexpr quantity< speed_d                 > knot         { Rep( 1852 ) / 3600 * meter / second };
constexpr quantity< volume_d                > liter        { Rep( 1e-3L ) * cube( meter ) };
constexpr quantity< time_interval_d         > minute       { Rep( 60 ) * second };
constexpr Rep                                 minute_angle { pi / 10800 };
constexpr quantity< length_d                > mile_nautical{ Rep( 1852 ) * meter };
constexpr quantity< absorbed_dose_d         > rad          { Rep( 1e-2L ) * gray };
constexpr quantity< dose_equivalent_d       > rem          { Rep( 1e-2L ) * sievert };
constexpr quantity< exposure_d              > roentgen     { Rep( 2.58e-4L ) * coulomb / kilogram };
constexpr Rep                                 second_angle { pi / 648000L };
constexpr quantity< mass_d                  > ton_metric   { Rep( 1e+3L ) * kilogram };

// Alternate (non-US) spellings:

constexpr quantity< length_d                > metre        { meter };
constexpr quantity< volume_d                > litre        { liter };
constexpr Rep                                 deca         { deka };
constexpr quantity< mass_d                  > tonne        { ton_metric };

// cooked literals for base units;
// these could also have been created with a script.

#define QUANTITY_DEFINE_SCALING_LITERAL( sfx, dim, factor ) \
    constexpr quantity<dim, long double> operator "" _ ## sfx(unsigned long long x) \
    { \
        return quantity<dim, long double>( detail::magnitude_tag, factor * x ); \
    } \
    constexpr quantity<dim, long double> operator "" _ ## sfx(long double x) \
    { \
        return quantity<dim, long double>( detail::magnitude_tag, factor * x ); \
    }

#define QUANTITY_DEFINE_SCALING_LITERALS( pfx, dim, fact ) \
    QUANTITY_DEFINE_SCALING_LITERAL( Y ## pfx, dim, fact * yotta ) \
    QUANTITY_DEFINE_SCALING_LITERAL( Z ## pfx, dim, fact * zetta ) \
    QUANTITY_DEFINE_SCALING_LITERAL( E ## pfx, dim, fact * exa   ) \
    QUANTITY_DEFINE_SCALING_LITERAL( P ## pfx, dim, fact * peta  ) \
    QUANTITY_DEFINE_SCALING_LITERAL( T ## pfx, dim, fact * tera  ) \
    QUANTITY_DEFINE_SCALING_LITERAL( G ## pfx, dim, fact * giga  ) \
    QUANTITY_DEFINE_SCALING_LITERAL( M ## pfx, dim, fact * mega  ) \
    QUANTITY_DEFINE_SCALING_LITERAL( k ## pfx, dim, fact * kilo  ) \
    QUANTITY_DEFINE_SCALING_LITERAL( h ## pfx, dim, fact * hecto ) \
    QUANTITY_DEFINE_SCALING_LITERAL( da## pfx, dim, fact * deka  ) \
    QUANTITY_DEFINE_SCALING_LITERAL(      pfx, dim, fact * 1     ) \
    QUANTITY_DEFINE_SCALING_LITERAL( d ## pfx, dim, fact * deci  ) \
    QUANTITY_DEFINE_SCALING_LITERAL( c ## pfx, dim, fact * centi ) \
    QUANTITY_DEFINE_SCALING_LITERAL( m ## pfx, dim, fact * milli ) \
    QUANTITY_DEFINE_SCALING_LITERAL( u ## pfx, dim, fact * micro ) \
    QUANTITY_DEFINE_SCALING_LITERAL( n ## pfx, dim, fact * nano  ) \
    QUANTITY_DEFINE_SCALING_LITERAL( p ## pfx, dim, fact * pico  ) \
    QUANTITY_DEFINE_SCALING_LITERAL( f ## pfx, dim, fact * femto ) \
    QUANTITY_DEFINE_SCALING_LITERAL( a ## pfx, dim, fact * atto  ) \
    QUANTITY_DEFINE_SCALING_LITERAL( z ## pfx, dim, fact * zepto ) \
    QUANTITY_DEFINE_SCALING_LITERAL( y ## pfx, dim, fact * yocto )


#define QUANTITY_DEFINE_LITERALS( pfx, dim ) \
    QUANTITY_DEFINE_SCALING_LITERALS( pfx, dim, 1 )

/// literals

namespace literals {

QUANTITY_DEFINE_SCALING_LITERALS( g, mass_d, 1e-3 )

QUANTITY_DEFINE_LITERALS( m  , length_d )
QUANTITY_DEFINE_LITERALS( s  , time_interval_d )
QUANTITY_DEFINE_LITERALS( A  , electric_current_d )
QUANTITY_DEFINE_LITERALS( K  , thermodynamic_temperature_d )
QUANTITY_DEFINE_LITERALS( mol, amount_of_substance_d )
QUANTITY_DEFINE_LITERALS( cd , luminous_intensity_d )

} // namespace literals

}} // namespace phys::units

#endif // PHYS_UNITS_QUANTITY_HPP_INCLUDED

/*
 * end of file
 */
