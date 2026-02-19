//
// Copyright (c) 2026-2026 Martin Moene
//
// https://github.com/martinmoene/PhysUnits-CT-Cpp11
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// #define USE_HAMLEST
// #define TEST_COMPILE_TIME
// #define PHYS_UNITS_COLLAPSE_TO_REP  0

#include "physunits-main.t.hpp"

#include <iostream>
#include <regex>

#ifndef  physunits_COMPILE_TIME_TEST
# define physunits_COMPILE_TIME_TEST  0
#endif

#define dimension_of(a)  ( sizeof(a) / sizeof(0[a]) )

using namespace phys::units;
using namespace phys::units::literals;

const int mag = 123;

#ifdef TEST_COMPILE_TIME

#if PHYS_UNITS_COLLAPSE_TO_REP

CASE("quantity: Cannot be dimensionless" " [compile-time][quantity]")
{
    constexpr quantity<dimensionless_d> dimensionless_quantity( detail::magnitude_tag, 1.23 );
}

#else // PHYS_UNITS_COLLAPSE_TO_REP

CASE("quantity: Can be dimensionless" " [compile-time][quantity]")
{
    constexpr quantity<dimensionless_d> dimensionless_quantity( detail::magnitude_tag, 1.23 );
}
#endif // PHYS_UNITS_COLLAPSE_TO_REP

CASE("quantity: Can be default-constructed (non-initialized)" " [compile-time][quantity]")
{
    quantity<mass_d> mass;
}

CASE("quantity: Cannot be constructed from scalar" " [compile-time][quantity]")
{
    quantity<mass_d> mass = mag;
}

CASE("quantity: Cannot be copy-constructed from different dimension" " [compile-time][dimension]")
{
    quantity<mass_d  > mass( detail::magnitude_tag, mag );
    quantity<length_d> length( mass );
}

CASE("quantity: quantity must be dimensionless when used in cast (regardless destination)" " [compile-time][dimension]")
{
    double d = meter;
}

CASE("quantity: dimension powers must be even multiples" " [compile-time][function]")
{
    nth_root<2>( meter * meter / second );
}

#else // TEST_COMPILE_TIME

//
// Construction:
//

CASE("quantity: Can be magnitude-constructed" " [construction]")
{
    quantity<mass_d, int> mass( detail::magnitude_tag, mag );

    EXPECT( mass.magnitude() == mag );
    EXPECT( mass.dimension() == mass_d{} );
}

CASE("quantity: Can be copy-constructed" " [construction]")
{
    quantity<mass_d, int> mass1( detail::magnitude_tag, mag );
    quantity<mass_d, int> mass2( mass1 );

    EXPECT( mass2.magnitude() == mag );
    EXPECT( mass2.magnitude() == mass1.magnitude() );
    EXPECT( mass2.dimension() == mass1.dimension() );
}

CASE("quantity: Can be conversion copy-constructed" " [construction]")
{
    quantity<mass_d,int > mass1( detail::magnitude_tag, mag );
    quantity<mass_d,long> mass2( mass1 );

    EXPECT( mass2.magnitude() == mag );
    EXPECT( mass2.magnitude() == mass1.magnitude() );
    EXPECT( mass2.dimension() == mass1.dimension() );
}

CASE("quantity: Can be copy-assigned" " [assignment]")
{
    quantity<mass_d, int> mass1( detail::magnitude_tag, mag + 1 );
    quantity<mass_d, int> mass2( detail::magnitude_tag, mag + 2 );

    mass2 = mass1;

    EXPECT( mass2.magnitude() == mass1.magnitude() );
    EXPECT( mass2.dimension() == mass1.dimension() );
}

CASE("quantity: Can be conversion copy-assigned" " [assignment]")
{
    quantity<mass_d,int > mass1( detail::magnitude_tag, mag + 1 );
    quantity<mass_d,long> mass2( detail::magnitude_tag, mag + 2 );

    mass2 = mass1;

    EXPECT( mass2.magnitude() == mass1.magnitude() );
    EXPECT( mass2.dimension() == mass1.dimension() );
}

//
// Arithmetic:
//

quantity<area_d> a1;
quantity<area_d> a2( meter * meter );

#if 0
CASE("quantity: Can be copy-constructed" " [construction]")
{
    EXPECT( s( a2 ) == "1.000000 m+2" );
}

CASE("quantity: assignment" " [assignment]")
{
    a1 = 3 * meter * meter;
    a2 = 4 * meter * meter;
    EXPECT( s( a1 ) == "3.000000 m+2" );
    EXPECT( s( a2 ) == "4.000000 m+2" );
}
#endif

CASE("quantity: Adds" " [arithmetic]")
{
    a1 = 5 * meter * meter;
    a2 = 6 * meter * meter;
    a1 += a2;
    EXPECT( s( a1      ) == "11.000000 m+2" );
    EXPECT( s( a1 + a2 ) == "17.000000 m+2" );
}

CASE("quantity: Subtracts" " [arithmetic]")
{
    a1 = 9 * meter * meter;
    a2 = 7 * meter * meter;
    a1 -= a2;
    EXPECT( s(  a1     ) ==  "2.000000 m+2" );
    EXPECT( s( -a1     ) == "-2.000000 m+2" );
    EXPECT( s( a1 - a2 ) == "-5.000000 m+2" );
    EXPECT( s( a2 - a1 ) ==  "5.000000 m+2" );
}

CASE("quantity: Multiplies" " [arithmetic]")
{
    quantity<speed_d >  s1( 8 * meter / second );
    quantity<speed_d >  s2( 20 * meter / second );
    quantity<length_d> len( 4 * meter );

    s1 *= 2;
    EXPECT( s( s1       ) ==  "16.000000 m s-1"   );
    EXPECT( s( s1 * s2  ) == "320.000000 m+2 s-2" );
    EXPECT( s( s1 * len ) ==  "64.000000 m+2 s-1" );
    EXPECT( s( s1 * 3   ) ==  "48.000000 m s-1"   );
    EXPECT( s(  5 * s1  ) ==  "80.000000 m s-1"   );
}

CASE("quantity: Divides" " [arithmetic]")
{
    quantity<speed_d        > s2( 20 * meter / second );
    quantity<time_interval_d>  t(  5 * second );

    s2 /= 5;
    EXPECT( s( s2      ) == "4.000000 m s-1" );
    EXPECT( s( s2 / s2 ) == "1.000000"       );
    EXPECT( s( s2 / t  ) == "0.800000 m s-2" );
    EXPECT( s( s2 / 8  ) == "0.500000 m s-1" );
    EXPECT( s(  8 / s2 ) == "2.000000 m-1 s" );
}

//
// Comparison:
//

constexpr quantity<length_d> meter2 = 2 * meter;

CASE("quantity: Compares equal" " [comparison]")
{
    EXPECT( meter == meter );
}

CASE("quantity: Compares unequal" " [comparison]")
{
    EXPECT( meter  != meter2 );
    EXPECT( meter2 != meter  );
}

CASE("quantity: Compares less-than" " [comparison]")
{
    EXPECT( meter < meter2 );
}

CASE("quantity: Compares less-equal" " [comparison]")
{
    EXPECT( meter <= meter  );
    EXPECT( meter <= meter2 );
}

CASE("quantity: Compares greater-than" " [comparison]")
{
    EXPECT( meter2 > meter );
}

CASE("quantity: Compares greater-equal" " [comparison]")
{
    EXPECT( meter  >= meter );
    EXPECT( meter2 >= meter );
}

CASE("quantity: Compares, more extensive" " [comparison]")
{
    constexpr quantity<power_d> neg2( -2 * watt );
    constexpr quantity<power_d> neg1( -1 * watt );
    constexpr quantity<power_d>    z(  0 * watt );
    constexpr quantity<power_d> pos1( +1 * watt );
    constexpr quantity<power_d> pos2( +2 * watt );

    EXPECT( ( neg1 == neg1 ) == true );
    EXPECT( ( neg1 != neg1 ) == false );
    EXPECT( ( neg1 <= neg1 ) == true );
    EXPECT( ( neg1 >= neg1 ) == true );
    EXPECT( ( neg1 <  neg1 ) == false );
    EXPECT( ( neg1 >  neg1 ) == false );

    EXPECT( ( z == z ) == true );
    EXPECT( ( z != z ) == false );
    EXPECT( ( z <= z ) == true );
    EXPECT( ( z >= z ) == true );
    EXPECT( ( z <  z ) == false );
    EXPECT( ( z >  z ) == false );

    EXPECT( ( pos1 == pos1 ) == true );
    EXPECT( ( pos1 != pos1 ) == false );
    EXPECT( ( pos1 <= pos1 ) == true );
    EXPECT( ( pos1 >= pos1 ) == true );
    EXPECT( ( pos1 <  pos1 ) == false );
    EXPECT( ( pos1 >  pos1 ) == false );

    EXPECT( ( z == neg1 ) == false );
    EXPECT( ( z != neg1 ) == true );
    EXPECT( ( z <= neg1 ) == false );
    EXPECT( ( z >= neg1 ) == true );
    EXPECT( ( z <  neg1 ) == false );
    EXPECT( ( z >  neg1 ) == true );

    EXPECT( ( z == pos1 ) == false );
    EXPECT( ( z != pos1 ) == true );
    EXPECT( ( z <= pos1 ) == true );
    EXPECT( ( z >= pos1 ) == false );
    EXPECT( ( z <  pos1 ) == true );
    EXPECT( ( z >  pos1 ) == false );

    EXPECT( ( neg1 == z ) == false );
    EXPECT( ( neg1 != z ) == true );
    EXPECT( ( neg1 <= z ) == true );
    EXPECT( ( neg1 >= z ) == false );
    EXPECT( ( neg1 <  z ) == true );
    EXPECT( ( neg1 >  z ) == false );

    EXPECT( ( pos1 == z ) == false );
    EXPECT( ( pos1 != z ) == true );
    EXPECT( ( pos1 <= z ) == false );
    EXPECT( ( pos1 >= z ) == true );
    EXPECT( ( pos1 <  z ) == false );
    EXPECT( ( pos1 >  z ) == true );

    EXPECT( ( neg1 == neg2 ) == false );
    EXPECT( ( neg1 != neg2 ) == true );
    EXPECT( ( neg1 <= neg2 ) == false );
    EXPECT( ( neg1 >= neg2 ) == true );
    EXPECT( ( neg1 <  neg2 ) == false );
    EXPECT( ( neg1 >  neg2 ) == true );

    EXPECT( ( neg2 == neg1 ) == false );
    EXPECT( ( neg2 != neg1 ) == true );
    EXPECT( ( neg2 <= neg1 ) == true );
    EXPECT( ( neg2 >= neg1 ) == false );
    EXPECT( ( neg2 <  neg1 ) == true );
    EXPECT( ( neg2 >  neg1 ) == false );

    EXPECT( ( neg1 == pos1 ) == false );
    EXPECT( ( neg1 != pos1 ) == true );
    EXPECT( ( neg1 <= pos1 ) == true );
    EXPECT( ( neg1 >= pos1 ) == false );
    EXPECT( ( neg1 <  pos1 ) == true );
    EXPECT( ( neg1 >  pos1 ) == false );

    EXPECT( ( pos1 == neg1 ) == false );
    EXPECT( ( pos1 != neg1 ) == true );
    EXPECT( ( pos1 <= neg1 ) == false );
    EXPECT( ( pos1 >= neg1 ) == true );
    EXPECT( ( pos1 <  neg1 ) == false );
    EXPECT( ( pos1 >  neg1 ) == true );

    EXPECT( ( pos1 == pos2 ) == false );
    EXPECT( ( pos1 != pos2 ) == true );
    EXPECT( ( pos1 <= pos2 ) == true );
    EXPECT( ( pos1 >= pos2 ) == false );
    EXPECT( ( pos1 <  pos2 ) == true );
    EXPECT( ( pos1 >  pos2 ) == false );

    EXPECT( ( pos2 == pos1 ) == false );
    EXPECT( ( pos2 != pos1 ) == true );
    EXPECT( ( pos2 <= pos1 ) == false );
    EXPECT( ( pos2 >= pos1 ) == true );
    EXPECT( ( pos2 <  pos1 ) == false );
    EXPECT( ( pos2 >  pos1 ) == true );
}

//
// Convenience functions:
//

template< typename T >
int to_int( T value ) 
{ 
    return static_cast<int>(value);
}

CASE("quantity: Provides convenience functions: dimension(), magnitude()" " [function]")
{
    constexpr quantity<length_d> length = 2 * meter;

    EXPECT(        dimension( length )  == length_d{} );
    EXPECT( to_int(magnitude( length )) == 2          );
}

CASE("quantity: Provides power functions: nth_power<N>()" " [function]")
{
    // general powers

    quantity<force_d> f1( 2 * newton );

    EXPECT( s( nth_power<10>( f1 ) ) == "1024.000000 m+10 kg+10 s-20" );
    EXPECT( s( nth_power< 4>( f1 ) ) ==   "16.000000 m+4 kg+4 s-8" );
    EXPECT( s( nth_power< 3>( f1 ) ) ==    "8.000000 m+3 kg+3 s-6" );
    EXPECT( s( nth_power< 2>( f1 ) ) ==    "4.000000 m+2 kg+2 s-4" );
    EXPECT( s( nth_power< 1>( f1 ) ) ==    "2.000000 m kg s-2" );
    EXPECT( s( nth_power< 0>( f1 ) ) ==    "1.000000" );
    EXPECT( s( nth_power<-1>( f1 ) ) ==    "0.500000 m-1 kg-1 s+2" );
    EXPECT( s( nth_power<-2>( f1 ) ) ==    "0.250000 m-2 kg-2 s+4" );

    // special powers

    EXPECT( s( square( f1 ) ) == "4.000000 m+2 kg+2 s-4" );
    EXPECT( s( cube(   f1 ) ) == "8.000000 m+3 kg+3 s-6" );
}

CASE("quantity: Provides root functions: nth_root<N>()" " [function]")
{
    // general roots

    quantity<dimensions< 4, 0, 0 > > hv( 10000 * meter * meter * meter * meter );

    EXPECT( s( nth_root< 4>( hv ) ) == "10.000000 m" );
    EXPECT( s( nth_root< 2>( hv ) ) == "100.000000 m+2" );
    EXPECT( s( nth_root< 1>( hv ) ) == "10000.000000 m+4" );
    EXPECT( s( nth_root<-1>( hv ) ) == "0.000100 m-4" );
    EXPECT( s( nth_root<-2>( hv ) ) == "0.010000 m-2" );
    EXPECT( s( nth_root<-4>( hv ) ) == "0.100000 m-1" );

    // special roots

    EXPECT( s( sqrt( hv ) ) == "100.000000 m+2" );

    quantity<power_d> p1( 3 * watt );
    quantity<power_d> p2( 4 * watt );

    EXPECT( s( sqrt( square( p1 ) + square( p2 ) ) ) == "5.000000 m+2 kg s-3" );

    quantity<frequency_d> freq( 25 / second );
    quantity<dimensions< 0, 0, -1, 2> > thing( 9 * ampere * ampere / second );

    EXPECT( s( sqrt( freq * thing ) ) == "15.000000 s-1 A" );
}

CASE("quantity: Provides various functions: abs()" " [function]")
{
    quantity<length_d> m( meter );
    // abs
    EXPECT( s( abs(  m ) ) == "1.000000 m" );
    EXPECT( s( abs( +m ) ) == "1.000000 m" );
    EXPECT( s( abs( -m ) ) == "1.000000 m" );
}

//
// Prefixes, yocto..yotta:
//

CASE("quantity: Provides prefixes: yotto..yotta" " [prefix]")
{
    EXPECT( std::regex_match( e( yocto ), std::regex("1\\.0e-0*24") ) );
    EXPECT( std::regex_match( e( zepto ), std::regex("1\\.0e-0*21" ) ) );
    EXPECT( std::regex_match( e( atto  ), std::regex("1\\.0e-0*18" ) ) );
    EXPECT( std::regex_match( e( femto ), std::regex("1\\.0e-0*15" ) ) );
    EXPECT( std::regex_match( e( pico  ), std::regex("1\\.0e-0*12" ) ) );
    EXPECT( std::regex_match( e( nano  ), std::regex("1\\.0e-0*09" ) ) );
    EXPECT( std::regex_match( e( micro ), std::regex("1\\.0e-0*06" ) ) );
    EXPECT( std::regex_match( e( milli ), std::regex("1\\.0e-0*03" ) ) );
    
    EXPECT( std::regex_match( e( kilo  ), std::regex( "1\\.0e\\+00?3" ) ) );
    EXPECT( std::regex_match( e( mega  ), std::regex( "1\\.0e\\+00?6" ) ) );
    EXPECT( std::regex_match( e( giga  ), std::regex( "1\\.0e\\+00?9" ) ) );
    EXPECT( std::regex_match( e( tera  ), std::regex( "1\\.0e\\+0?12" ) ) );
    EXPECT( std::regex_match( e( peta  ), std::regex( "1\\.0e\\+0?15" ) ) );
    EXPECT( std::regex_match( e( exa   ), std::regex( "1\\.0e\\+0?18" ) ) );
    EXPECT( std::regex_match( e( zetta ), std::regex( "1\\.0e\\+0?21" ) ) );
    EXPECT( std::regex_match( e( yotta ), std::regex( "1\\.0e\\+0?24" ) ) );
}

//
// User-defined literals:
//

CASE("quantity: Provides cooked literals of base units: _kg, _m, _s, _A, _K, _cd" " [literal]")
{
    EXPECT( s( 1._kg ) == "1.000000 kg" );
    EXPECT( s( 1._m  ) == "1.000000 m"  );
    EXPECT( s( 1._s  ) == "1.000000 s"  );
    EXPECT( s( 1._A  ) == "1.000000 A"  );
    EXPECT( s( 1._K  ) == "1.000000 K"  );
    EXPECT( s( 1._cd ) == "1.000000 cd" );
}

CASE("quantity: Provides cooked literals for duration variations: _min, _hour, _day" " [literal]")
{
    EXPECT( s( 1._min  ) ==    "60.000000 s" );
    EXPECT( s( 1._hour ) ==  "3600.000000 s" );
    EXPECT( s( 1._day  ) == "86400.000000 s" );
}

CASE("quantity: Provides cooked literals prefix variations: _y.._Y" " [literal]")
{
    using namespace phys::units::io::eng;

    EXPECT( to_string( 1._Ys ) == "1.00 Ys" );
    EXPECT( to_string( 1._Zs ) == "1.00 Zs" );
    EXPECT( to_string( 1._Es ) == "1.00 Es" );
    EXPECT( to_string( 1._Ps ) == "1.00 Ps" );
    EXPECT( to_string( 1._Ts ) == "1.00 Ts" );
    EXPECT( to_string( 1._Gs ) == "1.00 Gs" );
    EXPECT( to_string( 1._Ms ) == "1.00 Ms" );
    EXPECT( to_string( 1._ks ) == "1.00 ks" );
    EXPECT( to_string( 1._hs ) ==  "100 s"  );
    EXPECT( to_string( 1._das) == "10.0 s"  );
    EXPECT( to_string( 1._s  ) == "1.00 s"  );
    EXPECT( to_string( 1._ds ) ==  "100 ms" );
    EXPECT( to_string( 1._cs ) == "10.0 ms" );
    EXPECT( to_string( 1._ms ) == "1.00 ms" );
    EXPECT( to_string( 1._us ) == "1.00 us" );
    EXPECT( to_string( 1._ns ) == "1.00 ns" );
    EXPECT( to_string( 1._ps ) == "1.00 ps" );
    EXPECT( to_string( 1._fs ) == "1.00 fs" );
    EXPECT( to_string( 1._as ) == "1.00 as" );
    EXPECT( to_string( 1._zs ) == "1.00 zs" );
    EXPECT( to_string( 1._ys ) == "1.00 ys" );
}

CASE("quantity: Provides cooked literals: defects: _mA" " [literal]")
{
    // prefix smaller than 1 with integral type
    EXPECT( s( 20_mA ) == "0.020000 A" );
}

//
// Base units:
//

CASE("quantity: Provides base units: meter..candela" " [units]")
{
    EXPECT( s( meter    ) == "1.000000 m" );
    EXPECT( s( metre    ) == "1.000000 m" );
    EXPECT( s( kilogram ) == "1.000000 kg" );
    EXPECT( s( second   ) == "1.000000 s" );
    EXPECT( s( ampere   ) == "1.000000 A" );
    EXPECT( s( kelvin   ) == "1.000000 K" );
    EXPECT( s( mole     ) == "1.000000 mol" );
    EXPECT( s( candela  ) == "1.000000 cd" );
}

//
// Rest of units as specified in SP811:
//

CASE("quantity: Provides the rest of the standard dimensional types as specified in SP811: absorbed_dose_d..wave_number_d" " [units]")
{
    EXPECT( s( quantity< absorbed_dose_d >::zero() ) == "0.000000 m+2 s-2" );
    EXPECT( s( quantity< absorbed_dose_rate_d >::zero() ) == "0.000000 m+2 s-3" );
    EXPECT( s( quantity< acceleration_d >::zero() ) == "0.000000 m s-2" );
    EXPECT( s( quantity< activity_of_a_nuclide_d >::zero() ) == "0.000000 s-1" );
    EXPECT( s( quantity< angular_velocity_d >::zero() ) == "0.000000 s-1" );
    EXPECT( s( quantity< angular_acceleration_d >::zero() ) == "0.000000 s-2" );
    EXPECT( s( quantity< area_d >::zero() ) == "0.000000 m+2" );
    EXPECT( s( quantity< capacitance_d >::zero() ) == "0.000000 m-2 kg-1 s+4 A+2" );
    EXPECT( s( quantity< concentration_d >::zero() ) == "0.000000 m-3 mol" );
    EXPECT( s( quantity< current_density_d >::zero() ) == "0.000000 m-2 A" );
    EXPECT( s( quantity< dose_equivalent_d >::zero() ) == "0.000000 m+2 s-2" );
    EXPECT( s( quantity< dynamic_viscosity_d >::zero() ) == "0.000000 m-1 kg s-1" );
    EXPECT( s( quantity< electric_charge_d >::zero() ) == "0.000000 s A" );
    EXPECT( s( quantity< electric_charge_density_d >::zero() ) == "0.000000 m-3 s A" );
    EXPECT( s( quantity< electric_conductance_d >::zero() ) == "0.000000 m-2 kg-1 s+3 A+2" );
    EXPECT( s( quantity< electric_field_strenth_d >::zero() ) == "0.000000 m kg s-3 A-1" );
    EXPECT( s( quantity< electric_flux_density_d >::zero() ) == "0.000000 m-2 s A" );
    EXPECT( s( quantity< electric_potential_d >::zero() ) == "0.000000 m+2 kg s-3 A-1" );
    EXPECT( s( quantity< electric_resistance_d >::zero() ) == "0.000000 m+2 kg s-3 A-2" );
    EXPECT( s( quantity< energy_d >::zero() ) == "0.000000 m+2 kg s-2" );
    EXPECT( s( quantity< energy_density_d >::zero() ) == "0.000000 m-1 kg s-2" );
    EXPECT( s( quantity< exposure_d >::zero() ) == "0.000000 kg-1 s A" );
    EXPECT( s( quantity< force_d >::zero() ) == "0.000000 m kg s-2" );
    EXPECT( s( quantity< frequency_d >::zero() ) == "0.000000 s-1" );
    EXPECT( s( quantity< heat_capacity_d >::zero() ) == "0.000000 m+2 kg s-2 K-1" );
    EXPECT( s( quantity< heat_density_d >::zero() ) == "0.000000 kg s-2" );
    EXPECT( s( quantity< heat_density_flow_rate_d >::zero() ) == "0.000000 kg s-3" );
    EXPECT( s( quantity< heat_flow_rate_d >::zero() ) == "0.000000 m+2 kg s-3" );
    EXPECT( s( quantity< heat_flux_density_d >::zero() ) == "0.000000 kg s-3" );
    EXPECT( s( quantity< heat_transfer_coefficient_d >::zero() ) == "0.000000 kg s-3 K-1" );
    EXPECT( s( quantity< illuminance_d >::zero() ) == "0.000000 m-2 cd" );
    EXPECT( s( quantity< inductance_d >::zero() ) == "0.000000 m+2 kg s-2 A-2" );
    EXPECT( s( quantity< irradiance_d >::zero() ) == "0.000000 kg s-3" );
    EXPECT( s( quantity< kinematic_viscosity_d >::zero() ) == "0.000000 m+2 s-1" );
    EXPECT( s( quantity< luminance_d >::zero() ) == "0.000000 m-2 cd" );
    EXPECT( s( quantity< luminous_flux_d >::zero() ) == "0.000000 cd" );
    EXPECT( s( quantity< magnetic_field_strength_d >::zero() ) == "0.000000 m-1 A" );
    EXPECT( s( quantity< magnetic_flux_d >::zero() ) == "0.000000 m+2 kg s-2 A-1" );
    EXPECT( s( quantity< magnetic_flux_density_d >::zero() ) == "0.000000 kg s-2 A-1" );
    EXPECT( s( quantity< magnetic_permeability_d >::zero() ) == "0.000000 m kg s-2 A-2" );
    EXPECT( s( quantity< mass_density_d >::zero() ) == "0.000000 m-3 kg" );
    EXPECT( s( quantity< mass_flow_rate_d >::zero() ) == "0.000000 kg s-1" );
    EXPECT( s( quantity< molar_energy_d >::zero() ) == "0.000000 m+2 kg s-2 mol-1" );
    EXPECT( s( quantity< molar_entropy_d >::zero() ) == "0.000000 m+2 kg s-2 A-1 mol-1" );
    EXPECT( s( quantity< moment_of_force_d >::zero() ) == "0.000000 m+2 kg s-2" );
    EXPECT( s( quantity< permittivity_d >::zero() ) == "0.000000 m-3 kg-1 s+4 A+2" );
    EXPECT( s( quantity< power_d >::zero() ) == "0.000000 m+2 kg s-3" );
    EXPECT( s( quantity< pressure_d >::zero() ) == "0.000000 m-1 kg s-2" );
    EXPECT( s( quantity< radiance_d >::zero() ) == "0.000000 kg s-3" );
    EXPECT( s( quantity< radiant_intensity_d >::zero() ) == "0.000000 m+2 kg s-3" );
    EXPECT( s( quantity< specific_volume_d >::zero() ) == "0.000000 m+3 kg-1" );
    EXPECT( s( quantity< speed_d >::zero() ) == "0.000000 m s-1" );
    EXPECT( s( quantity< specific_energy_d >::zero() ) == "0.000000 m+2 s-2" );
    EXPECT( s( quantity< specific_heat_capacity_d >::zero() ) == "0.000000 m+2 s-2 K-1" );
    EXPECT( s( quantity< specific_volume_d >::zero() ) == "0.000000 m+3 kg-1" );
    EXPECT( s( quantity< substance_permeability_d >::zero() ) == "0.000000 m-1 s" );
    EXPECT( s( quantity< surface_tension_d >::zero() ) == "0.000000 kg s-2" );
    EXPECT( s( quantity< thermal_conductivity_d >::zero() ) == "0.000000 m kg s-3 K-1" );
    EXPECT( s( quantity< thermal_diffusivity_d >::zero() ) == "0.000000 m+2 s-1" );
    EXPECT( s( quantity< thermal_insulance_d >::zero() ) == "0.000000 kg-1 s+3 K" );
    EXPECT( s( quantity< thermal_resistance_d >::zero() ) == "0.000000 m-2 kg-1 s+3 K" );
    EXPECT( s( quantity< thermal_resistivity_d >::zero() ) == "0.000000 m-1 kg-1 s+3 K" );
    EXPECT( s( quantity< torque_d >::zero() ) == "0.000000 m+2 kg s-2" );
    EXPECT( s( quantity< volume_d >::zero() ) == "0.000000 m+3" );
    EXPECT( s( quantity< volume_flow_rate_d >::zero() ) == "0.000000 m+3 s-1" );
    EXPECT( s( quantity< wave_number_d >::zero() ) == "0.000000 m-1" );
}

//
// Derived SI units as specified in SP811:
//

CASE("quantity: Provides the derived SI units as specified in SP811: radian..sievert" " [units]")
{
    EXPECT( s( radian ) == "1.000000" );
    EXPECT( s( steradian ) == "1.000000" );
    EXPECT( s( hertz ) == "1.000000 s-1" );
    EXPECT( s( newton ) == "1.000000 m kg s-2" );
#ifndef pascal // MSVC
    EXPECT( s( pascal ) == "1.000000 m-1 kg s-2" );
#endif
    EXPECT( s( joule ) == "1.000000 m+2 kg s-2" );
    EXPECT( s( watt ) == "1.000000 m+2 kg s-3" );
    EXPECT( s( coulomb ) == "1.000000 s A" );
    EXPECT( s( volt ) == "1.000000 m+2 kg s-3 A-1" );
    EXPECT( s( farad ) == "1.000000 m-2 kg-1 s+4 A+2" );
    EXPECT( s( ohm ) == "1.000000 m+2 kg s-3 A-2" );
    EXPECT( s( siemens ) == "1.000000 m-2 kg-1 s+3 A+2" );
    EXPECT( s( weber ) == "1.000000 m+2 kg s-2 A-1" );
    EXPECT( s( tesla ) == "1.000000 kg s-2 A-1" );
    EXPECT( s( henry ) == "1.000000 m+2 kg s-2 A-2" );
    EXPECT( s( degree_celsius ) == "1.000000 K" );
    EXPECT( s( lumen ) == "1.000000 cd" );
    EXPECT( s( lux ) == "1.000000 m-2 cd" );
    EXPECT( s( becquerel ) == "1.000000 s-1" );
    EXPECT( s( gray ) == "1.000000 m+2 s-2" );
    EXPECT( s( sievert ) == "1.000000 m+2 s-2" );
}

//
// Rest of units approved with SI as specified in SP811:
//

CASE("quantity: Provides the rest of the units approved for use with SI as specified in SP811: angstrom..tonne" " [units]")
{
    EXPECT( s( 1e+10 * angstrom ) == "1.000000 m" );
    EXPECT( s( are ) == "100.000000 m+2" );
    EXPECT( s( 1e-5 * bar ) == "1.000000 m-1 kg s-2" );
    EXPECT( s( 1e+28 * barn ) == "1.000000 m+2" );
    EXPECT( s( 1e-10 * curie ) == "3.700000 s-1" );
    EXPECT( s( day ) == "86400.000000 s" );
    EXPECT( s( 1e+2 * degree_angle ) == "1.745329" );
    EXPECT( s( 1e+2 * gal ) == "1.000000 m s-2" );
    EXPECT( s( 1e-4 * hectare ) == "1.000000 m+2" );
    EXPECT( s( hour ) == "3600.000000 s" );
    EXPECT( s( 1e+1 * knot ) == "5.144444 m s-1" );
    EXPECT( s( 1e+3 * liter ) == "1.000000 m+3" );
    EXPECT( s( 1e+3 * litre ) == "1.000000 m+3" );
    EXPECT( s( minute ) == "60.000000 s" );
    EXPECT( s( 1e+4 * minute_angle ) == "2.908882" );
    EXPECT( s( 1e-3 * mile_nautical ) == "1.852000 m" );
    EXPECT( s( 1e+2 * rad ) == "1.000000 m+2 s-2" );
    EXPECT( s( 1e+2 * rem ) == "1.000000 m+2 s-2" );
    EXPECT( s( 1e+4 * roentgen ) == "2.580000 kg-1 s A" );
    EXPECT( s( 1e+6 * second_angle ) == "4.848137" );
    EXPECT( s( ton_metric ) == "1000.000000 kg" );
    EXPECT( s( tonne ) == "1000.000000 kg" );
}

//
// Other units:
//

CASE("quantity: Provides yet other units: abampere..year_tropical" " [units]")
{
    EXPECT( s( abampere ) == "10.000000 A" );
    EXPECT( s( abcoulomb ) == "10.000000 s A" );
    EXPECT( s( 1e-9 * abfarad ) == "1.000000 m-2 kg-1 s+4 A+2" );
    EXPECT( s( 1e+9 * abhenry ) == "1.000000 m+2 kg s-2 A-2" );
    EXPECT( s( 1e-9 * abmho ) == "1.000000 m-2 kg-1 s+3 A+2" );
    EXPECT( s( 1e+9 * abohm ) == "1.000000 m+2 kg s-3 A-2" );
    EXPECT( s( 1e+8 * abvolt ) == "1.000000 m+2 kg s-3 A-1" );
    EXPECT( s( 1e-3 * acre ) == "4.046873 m+2" );
    EXPECT( s( 1e-3 * acre_foot ) == "1.233489 m+3" );
    EXPECT( s( 1e-11 * astronomical_unit ) == "1.495979 m" );
    EXPECT( s( 1e-5 * atmosphere_std ) == "1.013250 m-1 kg s-2" );
    EXPECT( s( 1e-4 * atmosphere_tech ) == "9.806650 m-1 kg s-2" );
    EXPECT( s( 1e+1 * barrel ) == "1.589873 m+3" );
    EXPECT( s( 1e-1 * biot ) == "1.000000 A" );
    EXPECT( s( 1e-3 * btu ) == "1.055870 m+2 kg s-2" );
    EXPECT( s( 1e-3 * btu_it ) == "1.055056 m+2 kg s-2" );
    EXPECT( s( 1e-3 * btu_th ) == "1.054350 m+2 kg s-2" );
    EXPECT( s( 1e-3 * btu_39F ) == "1.059670 m+2 kg s-2" );
    EXPECT( s( 1e-3 * btu_59F ) == "1.054800 m+2 kg s-2" );
    EXPECT( s( 1e-3 * btu_60F ) == "1.054680 m+2 kg s-2" );
    EXPECT( s( 1e+2 * bushel ) == "3.523907 m+3" );
    EXPECT( s( calorie ) == "4.190020 m+2 kg s-2" );
    EXPECT( s( calorie_it ) == "4.186800 m+2 kg s-2" );
    EXPECT( s( calorie_th ) == "4.184000 m+2 kg s-2" );
    EXPECT( s( calorie_15C ) == "4.185800 m+2 kg s-2" );
    EXPECT( s( calorie_20C ) == "4.181900 m+2 kg s-2" );
    EXPECT( s( 1e+4 * carat_metric ) == "2.000000 kg" );
    EXPECT( s( 1e-1 * chain ) == "2.011684 m" );
    EXPECT( s( 1e+1 * clo ) == "1.550000 kg-1 s+3 K" );
    EXPECT( s( 1e-3 * cm_mercury ) == "1.333224 m-1 kg s-2" );
    EXPECT( s( cord ) == "3.624556 m+3" );
    EXPECT( s( 1e+4 * cup ) == "2.365882 m+3" );
    EXPECT( s( 1e+13 * darcy ) == "9.869233 m+2" );
    EXPECT( s( 1e-4 * day_sidereal ) == "8.616409 s" );
    EXPECT( s( 1e+30 * debye ) == "3.335641 m s A" );
    EXPECT( s( 1e+1 * degree_fahrenheit ) == "5.555556 K" );
    EXPECT( s( 1e+1 * degree_rankine ) == "5.555556 K" );
    EXPECT( s( 1e+7 * denier ) == "1.111111 m-1 kg" );
    EXPECT( s( 1e+5 * dyne ) == "1.000000 m kg s-2" );
    EXPECT( s( 1e+7 * erg ) == "1.000000 m+2 kg s-2" );
    EXPECT( s( 1e-4 * faraday ) == "9.648531 s A" );
    EXPECT( s( fathom ) == "1.828804 m" );
    EXPECT( s( 1e+15 * fermi ) == "1.000000 m" );
    EXPECT( s( 1e+1 * foot ) == "3.048000 m" );
    EXPECT( s( foot_pound_force ) == "1.355818 m+2 kg s-2" );
    EXPECT( s( 1e+2 * foot_poundal ) == "4.214011 m+2 kg s-2" );
    EXPECT( s( 1e+1 * foot_us_survey ) == "3.048006 m" );
    EXPECT( s( 1e-1 * footcandle ) == "1.076391 m-2 cd" );
    EXPECT( s( footlambert ) == "3.426259 m-2 cd" );
    EXPECT( s( 1e-6 * fortnight ) == "1.209600 s" );
    EXPECT( s( 1e+10 * franklin ) == "3.335641 s A" );
    EXPECT( s( 1e-2 * furlong ) == "2.011680 m" );
    EXPECT( s( 1e+3 * gallon_imperial ) == "4.546090 m+3" );
    EXPECT( s( 1e+3 * gallon_us ) == "3.785412 m+3" );
    EXPECT( s( 1e+9 * phys::units::gamma ) == "1.000000 kg s-2 A-1" );	// gamma clashes in clang
    EXPECT( s( 1e+9 * gamma_mass ) == "1.000000 kg" );
    EXPECT( s( 1e+4 * gauss ) == "1.000000 kg s-2 A-1" );
    EXPECT( s( 1e+1 * gilbert ) == "7.957747 A" );
    EXPECT( s( 1e+4 * gill_imperial ) == "1.420653 m+3" );
    EXPECT( s( 1e+4 * gill_us ) == "1.182941 m+3" );
    EXPECT( s( 1e+2 * gon ) == "1.570796" );
    EXPECT( s( 1e+5 * grain ) == "6.479891 kg" );
    EXPECT( s( 1e-2 * horsepower ) == "7.456999 m+2 kg s-3" );
    EXPECT( s( 1e-3 * horsepower_boiler ) == "9.809500 m+2 kg s-3" );
    EXPECT( s( 1e-2 * horsepower_electric ) == "7.460000 m+2 kg s-3" );
    EXPECT( s( 1e-2 * horsepower_metric ) == "7.354988 m+2 kg s-3" );
    EXPECT( s( 1e-2 * horsepower_uk ) == "7.457000 m+2 kg s-3" );
    EXPECT( s( 1e-2 * horsepower_water ) == "7.460430 m+2 kg s-3" );
    EXPECT( s( 1e-3 * hour_sidereal ) == "3.590170 s" );
    EXPECT( s( 1e-1 * hundredweight_long ) == "5.080235 kg" );
    EXPECT( s( 1e-1 * hundredweight_short ) == "4.535924 kg" );
    EXPECT( s( 1e+2 * inch ) == "2.540000 m" );
    EXPECT( s( 1e-3 * inches_mercury ) == "3.386389 m-1 kg s-2" );
    EXPECT( s( 1e-2 * kayser ) == "1.000000 m-1" );
    EXPECT( s( kilogram_force ) == "9.806650 m kg s-2" );
    EXPECT( s( kilopond ) == "9.806650 m kg s-2" );
    EXPECT( s( 1e-3 * kip ) == "4.448222 m kg s-2" );
    EXPECT( s( 1e+9 * lambda_volume ) == "1.000000 m+3" );
    EXPECT( s( 1e-3 * lambert ) == "3.183099 m-2 cd" );
    EXPECT( s( 1e-4 * langley ) == "4.184000 kg s-2" );
    EXPECT( s( 1e-15 * light_year ) == "9.460730 m" );
    EXPECT( s( 1e+8 * maxwell ) == "1.000000 m+2 kg s-2 A-1" );
    EXPECT( s( mho ) == "1.000000 m-2 kg-1 s+3 A+2" );
    EXPECT( s( 1e+6 * micron ) == "1.000000 m" );
    EXPECT( s( 1e+5 * mil ) == "2.540000 m" );
    EXPECT( s( 1e+4 * mil_angle ) == "9.817477" );
    EXPECT( s( 1e+10 * mil_circular ) == "5.067075 m+2" );
    EXPECT( s( 1e-3 * mile ) == "1.609344 m" );
    EXPECT( s( 1e-3 * mile_us_survey ) == "1.609347 m" );
    EXPECT( s( 1e-1 * minute_sidereal ) == "5.983617 s" );
    EXPECT( s( 1e-1 * oersted ) == "7.957747 m-1 A" );
    EXPECT( s( 1e+2 * ounce_avdp ) == "2.834952 kg" );
    EXPECT( s( 1e+5 * ounce_fluid_imperial ) == "2.841306 m+3" );
    EXPECT( s( 1e+5 * ounce_fluid_us ) == "2.957353 m+3" );
    EXPECT( s( 1e+1 * ounce_force ) == "2.780139 m kg s-2" );
    EXPECT( s( 1e+2 * ounce_troy ) == "3.110348 kg" );
    EXPECT( s( 1e-16 * parsec ) == "3.085678 m" );
    EXPECT( s( 1e+3 * peck ) == "8.809768 m+3" );
    EXPECT( s( 1e+3 * pennyweight ) == "1.555174 kg" );
    EXPECT( s( 1e+11 * perm_0C ) == "5.721350 m-1 s" );
    EXPECT( s( 1e+11 * perm_23C ) == "5.745250 m-1 s" );
    EXPECT( s( 1e-4 * phot ) == "1.000000 m-2 cd" );
    EXPECT( s( 1e+3 * pica_computer ) == "4.233333 m" );
    EXPECT( s( 1e+3 * pica_printers ) == "4.217518 m" );
    EXPECT( s( 1e+4 * pint_dry ) == "5.506105 m+3" );
    EXPECT( s( 1e+4 * pint_liquid ) == "4.731765 m+3" );
    EXPECT( s( 1e+4 * point_printers ) == "3.514598 m" );
    EXPECT( s( 1e+1 * poise ) == "1.000000 m-1 kg s-1" );
    EXPECT( s( 1e+1 * pound_avdp ) == "4.535924 kg" );
    EXPECT( s( pound_force ) == "4.448222 m kg s-2" );
    EXPECT( s( 1e+1 * pound_troy ) == "3.732417 kg" );
    EXPECT( s( 1e+1 * poundal ) == "1.382550 m kg s-2" );
    EXPECT( s( 1e-3 * psi ) == "6.894757 m-1 kg s-2" );
    EXPECT( s( 1e-18 * quad ) == "1.055056 m+2 kg s-2" );
    EXPECT( s( 1e+3 * quart_dry ) == "1.101221 m+3" );
    EXPECT( s( 1e+4 * quart_liquid ) == "9.463529 m+3" );
    EXPECT( s( revolution ) == "6.283185" );
    EXPECT( s( 1e-1 * rhe ) == "1.000000 m kg-1 s" );
    EXPECT( s( rod ) == "5.029210 m" );
    EXPECT( s( 1e+1 * rpm ) == "1.047198 s-1" );
    EXPECT( s( 1e+1 * second_sidereal ) == "9.972696 s" );
    EXPECT( s( 1e+8 * shake ) == "1.000000 s" );
    EXPECT( s( 1e-1 * slug ) == "1.459390 kg" );
    EXPECT( s( 1e+10 * statampere ) == "3.335641 A" );
    EXPECT( s( 1e+10 * statcoulomb ) == "3.335641 s A" );
    EXPECT( s( 1e+12 * statfarad ) == "1.112650 m-2 kg-1 s+4 A+2" );
    EXPECT( s( 1e-11 * stathenry ) == "8.987552 m+2 kg s-2 A-2" );
    EXPECT( s( 1e+12 * statmho ) == "1.112650 m-2 kg-1 s+3 A+2" );
    EXPECT( s( 1e-11 * statohm ) == "8.987552 m+2 kg s-3 A-2" );
    EXPECT( s( 1e-2 * statvolt ) == "2.997925 m+2 kg s-3 A-1" );
    EXPECT( s( stere ) == "1.000000 m+3" );
    EXPECT( s( 1e-4 * stilb ) == "1.000000 m-2 cd" );
    EXPECT( s( 1e+4 * stokes ) == "1.000000 m+2 s-1" );
    EXPECT( s( 1e+5 * tablespoon ) == "1.478676 m+3" );
    EXPECT( s( 1e+6 * teaspoon ) == "4.928922 m+3" );
    EXPECT( s( 1e+6 * tex ) == "1.000000 m-1 kg" );
    EXPECT( s( 1e-8 * therm_ec ) == "1.055060 m+2 kg s-2" );
    EXPECT( s( 1e-8 * therm_us ) == "1.054804 m+2 kg s-2" );
    EXPECT( s( 1e+2 * ton_assay ) == "2.916667 kg" );
    EXPECT( s( 1e-3 * ton_force ) == "8.896443 m kg s-2" );
    EXPECT( s( 1e-3 * ton_long ) == "1.016047 kg" );
    EXPECT( s( 1e-3 * ton_refrigeration ) == "3.516853 m+2 kg s-3" );
    EXPECT( s( ton_register ) == "2.831685 m+3" );
    EXPECT( s( 1e-2 * ton_short ) == "9.071847 kg" );
    EXPECT( s( 1e-9 * ton_tnt ) == "4.184000 m+2 kg s-2" );
    EXPECT( s( 1e-2 * torr ) == "1.333224 m-1 kg s-2" );
    EXPECT( s( 1e+7 * unit_pole ) == "1.256637 m+2 kg s-2 A-1" );
    EXPECT( s( 1e-5 * week ) == "6.048000 s" );
    EXPECT( s( 1e+13 * x_unit ) == "1.002000 m" );
    EXPECT( s( 1e+1 * yard ) == "9.144000 m" );
    EXPECT( s( 1e-7 * year_sidereal ) == "3.155815 s" );
    EXPECT( s( 1e-7 * year_std ) == "3.153600 s" );
    EXPECT( s( 1e-7 * year_tropical ) == "3.155693 s" );
}

#endif // #else TEST_COMPILE_TIME

// g++ -std=c++11 -I../include -o physunits.t.exe physunits.t.cpp && physunits.t.exe
// cl -EHsc -I../include physunits.t.cpp && physunits.t.exe
