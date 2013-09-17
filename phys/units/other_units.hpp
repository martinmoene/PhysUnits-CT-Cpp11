/**
 * \file other_units.hpp
 *
 * \brief   Units not approved for use with SI.
 * \author  Michael S. Kenniston
 * \date    16 July 2001
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
 * This file contains the definitions of units that are *NOT* approved
 * for use with SI, as specified by SP811.  These units should not
 * be used with any new work.  However, they may be needed for
 * handling and converting legacy data.
 */

#ifndef PHYS_UNITS_OTHER_UNITS_HPP_INCLUDED
#define PHYS_UNITS_OTHER_UNITS_HPP_INCLUDED

#include "phys/units/quantity.hpp"

namespace phys { namespace units {

constexpr quantity< electric_current_d >     abampere           { Rep( 1e+1L ) * ampere };
constexpr quantity< electric_charge_d >      abcoulomb          { Rep( 1e+1L ) * coulomb };
constexpr quantity< capacitance_d >          abfarad            { Rep( 1e+9L ) * farad };
constexpr quantity< inductance_d >           abhenry            { Rep( 1e-9L ) * henry };
constexpr quantity< electric_conductance_d > abmho              { Rep( 1e+9L ) * siemens };
constexpr quantity< electric_resistance_d >  abohm              { Rep( 1e-9L ) * ohm };
constexpr quantity< electric_potential_d >   abvolt             { Rep( 1e-8L ) * volt };
constexpr quantity< area_d >                 acre               { Rep( 4.046873e+3L ) * square( meter ) };
constexpr quantity< volume_d >               acre_foot          { Rep( 1.233489e+3L ) * cube( meter ) };
constexpr quantity< length_d >               astronomical_unit  { Rep( 1.495979e+11L ) * meter };
constexpr quantity< pressure_d >             atmosphere_std     { Rep( 1.01325e+5L ) * pascal };
constexpr quantity< pressure_d >             atmosphere_tech    { Rep( 9.80665e+4L ) * pascal };

constexpr quantity< volume_d >               barrel             { Rep( 1.589873e-1L ) * cube( meter ) };
constexpr quantity< electric_current_d >     biot               { Rep( 1e+1L ) * ampere };
constexpr quantity< energy_d >               btu                { Rep( 1.05587e+3L ) * joule };
constexpr quantity< energy_d >               btu_it             { Rep( 1.055056e+3L ) * joule };
constexpr quantity< energy_d >               btu_th             { Rep( 1.054350e+3L ) * joule };
constexpr quantity< energy_d >               btu_39F            { Rep( 1.05967e+3L ) * joule };
constexpr quantity< energy_d >               btu_59F            { Rep( 1.05480e+3L ) * joule };
constexpr quantity< energy_d >               btu_60F            { Rep( 1.05468e+3L ) * joule };
constexpr quantity< volume_d >               bushel             { Rep( 3.523907e-2L ) * cube( meter ) };

constexpr quantity< energy_d >               calorie            { Rep( 4.19002L ) * joule };
constexpr quantity< energy_d >               calorie_it         { Rep( 4.1868L ) * joule };
constexpr quantity< energy_d >               calorie_th         { Rep( 4.184L ) * joule };
constexpr quantity< energy_d >               calorie_15C        { Rep( 4.18580L ) * joule };
constexpr quantity< energy_d >               calorie_20C        { Rep( 4.18190L ) * joule };
constexpr quantity< mass_d >                 carat_metric       { Rep( 2e-4L ) * kilogram };
constexpr quantity< length_d >               chain              { Rep( 2.011684e+1L ) * meter };
constexpr quantity< thermal_insulance_d >    clo                { Rep( 1.55e-1L ) * square( meter ) * kelvin / watt };
constexpr quantity< pressure_d >             cm_mercury         { Rep( 1.333224e+3L ) * pascal };
constexpr quantity< volume_d >               cord               { Rep( 3.624556L ) * cube( meter ) };
constexpr quantity< volume_d >               cup                { Rep( 2.365882e-4L ) * cube( meter ) };

constexpr quantity< dimensions< 2, 0, 0 >>   darcy              { Rep( 9.869233e-13L ) * square( meter ) };
constexpr quantity< time_interval_d >        day_sidereal       { Rep( 8.616409e+4L ) * second };
constexpr quantity< dimensions< 1, 0, 1, 1>> debye              { Rep( 3.335641e-30L ) * coulomb * meter };
constexpr quantity< thermodynamic_temperature_d > degree_fahrenheit{ Rep( 5.555556e-1L ) * kelvin };
constexpr quantity< thermodynamic_temperature_d > degree_rankine   { Rep( 5.555556e-1L ) * kelvin };
constexpr quantity< dimensions< -1, 1, 0 >>  denier             { Rep( 1.111111e-7L ) * kilogram / meter };
constexpr quantity< force_d >                dyne               { Rep( 1e-5L ) * newton };

constexpr quantity< energy_d >               erg                { Rep( 1e-7L ) * joule };

constexpr quantity< electric_charge_d >      faraday            { Rep( 9.648531e+4L ) * coulomb };
constexpr quantity< length_d >               fathom             { Rep( 1.828804L ) * meter };
constexpr quantity< length_d >               fermi              { Rep( 1e-15L ) * meter };
constexpr quantity< length_d >               foot               { Rep( 3.048e-1L ) * meter };
constexpr quantity< energy_d >               foot_pound_force   { Rep( 1.355818L ) * joule };
constexpr quantity< energy_d >               foot_poundal       { Rep( 4.214011e-2L ) * joule };
constexpr quantity< length_d >               foot_us_survey     { Rep( 3.048006e-1L ) * meter };
constexpr quantity< illuminance_d >          footcandle         { Rep( 1.076391e+1L ) * lux };
constexpr quantity< illuminance_d >          footlambert        { Rep( 3.426259L ) * candela / square( meter ) };
constexpr quantity< time_interval_d >        fortnight          { Rep( 14 ) * day }; // from OED
constexpr quantity< electric_charge_d >      franklin           { Rep( 3.335641e-10L ) * coulomb };
constexpr quantity< length_d >               furlong            { Rep( 2.01168e+2L ) * meter }; // from OED

constexpr quantity< volume_d >               gallon_imperial    { Rep( 4.54609e-3L ) * cube( meter ) };
constexpr quantity< volume_d >               gallon_us          { Rep( 3.785412e-3L ) * cube( meter ) };
constexpr quantity< magnetic_flux_density_d > gamma             { Rep( 1e-9L ) * tesla };
constexpr quantity< mass_d >                 gamma_mass         { Rep( 1e-9L ) * kilogram };
constexpr quantity< magnetic_flux_density_d > gauss             { Rep( 1e-4L ) * tesla };
constexpr quantity< electric_current_d >     gilbert            { Rep( 7.957747e-1L ) * ampere };
constexpr quantity< volume_d >               gill_imperial      { Rep( 1.420653e-4L ) * cube( meter ) };
constexpr quantity< volume_d >               gill_us            { Rep( 1.182941e-4L ) * cube( meter ) };
constexpr Rep                                gon                { Rep( 9e-1L ) * degree_angle };
constexpr quantity< mass_d >                 grain              { Rep( 6.479891e-5L ) * kilogram };

constexpr quantity< power_d >                horsepower         { Rep( 7.456999e+2L ) * watt };
constexpr quantity< power_d >                horsepower_boiler  { Rep( 9.80950e+3L ) * watt };
constexpr quantity< power_d >                horsepower_electric{ Rep( 7.46e+2L ) * watt };
constexpr quantity< power_d >                horsepower_metric  { Rep( 7.354988e+2L ) * watt };
constexpr quantity< power_d >                horsepower_uk      { Rep( 7.4570e+2L ) * watt };
constexpr quantity< power_d >                horsepower_water   { Rep( 7.46043e+2L ) * watt };
constexpr quantity< time_interval_d >        hour_sidereal      { Rep( 3.590170e+3L ) * second };
constexpr quantity< mass_d >                 hundredweight_long { Rep( 5.080235e+1L ) * kilogram };
constexpr quantity< mass_d >                 hundredweight_short{ Rep( 4.535924e+1L ) * kilogram };

constexpr quantity< length_d >               inch               { Rep( 2.54e-2L ) * meter };
constexpr quantity< pressure_d >             inches_mercury     { Rep( 3.386389e+3L ) * pascal };

constexpr quantity< wave_number_d >          kayser             { Rep( 1e+2 ) / meter };
constexpr quantity< force_d >                kilogram_force     { Rep( 9.80665 ) * newton };
constexpr quantity< force_d >                kilopond           { Rep( 9.80665 ) * newton };
constexpr quantity< force_d >                kip                { Rep( 4.448222e+3L ) * newton };

constexpr quantity< volume_d >               lambda_volume      { Rep( 1e-9L ) * cube( meter ) };
constexpr quantity< illuminance_d >          lambert            { Rep( 3.183099e+3L ) * candela / square( meter ) };
constexpr quantity< heat_density_d >         langley            { Rep( 4.184e+4L ) * joule / square( meter ) };
constexpr quantity< length_d >               light_year         { Rep( 9.46073e+15L ) * meter };

constexpr quantity< magnetic_flux_d >        maxwell            { Rep( 1e-8L ) * weber };
constexpr quantity< electric_conductance_d > mho                { siemens };
constexpr quantity< length_d >               micron             { micro * meter };
constexpr quantity< length_d >               mil                { Rep( 2.54e-5L ) * meter };
constexpr Rep                                mil_angle          { Rep( 5.625e-2L ) * degree_angle };
constexpr quantity< area_d >                 mil_circular       { Rep( 5.067075e-10L ) * square( meter ) };
constexpr quantity< length_d >               mile               { Rep( 1.609344e+3L ) * meter };
constexpr quantity< length_d >               mile_us_survey     { Rep( 1.609347e+3L ) * meter };
constexpr quantity< time_interval_d >        minute_sidereal    { Rep( 5.983617e+1L ) * second };

constexpr quantity< dimensions< -1, 0, 0, 1 > >oersted          { Rep( 7.957747e+1L ) * ampere / meter };
constexpr quantity< mass_d >                 ounce_avdp         { Rep( 2.834952e-2L ) * kilogram };
constexpr quantity< volume_d >               ounce_fluid_imperial{ Rep( 2.841306e-5L ) * cube( meter ) };
constexpr quantity< volume_d >               ounce_fluid_us     { Rep( 2.957353e-5L ) * cube( meter ) };
constexpr quantity< force_d >                ounce_force        { Rep( 2.780139e-1L ) * newton };
constexpr quantity< mass_d >                 ounce_troy         { Rep( 3.110348e-2L ) * kilogram };

constexpr quantity< length_d >               parsec             { Rep( 3.085678e+16L ) * meter };
constexpr quantity< volume_d >               peck               { Rep( 8.809768e-3L ) * cube( meter ) };
constexpr quantity< mass_d >                 pennyweight        { Rep( 1.555174e-3L ) * kilogram };
constexpr quantity< substance_permeability_d >  perm_0C         { Rep( 5.72135e-11L ) * kilogram / pascal / second / square( meter ) };
constexpr quantity< substance_permeability_d >  perm_23C        { Rep( 5.74525e-11L ) * kilogram / pascal / second / square( meter ) };
constexpr quantity< illuminance_d >          phot               { Rep( 1e+4L ) * lux };
constexpr quantity< length_d >               pica_computer      { Rep( 4.233333e-3L ) * meter };
constexpr quantity< length_d >               pica_printers      { Rep( 4.217518e-3L ) * meter };
constexpr quantity< volume_d >               pint_dry           { Rep( 5.506105e-4L ) * cube( meter ) };
constexpr quantity< volume_d >               pint_liquid        { Rep( 4.731765e-4L ) * cube( meter ) };
constexpr quantity< length_d >               point_computer     { Rep( 3.527778e-4L ) * meter };
constexpr quantity< length_d >               point_printers     { Rep( 3.514598e-4L ) * meter };
constexpr quantity< dynamic_viscosity_d >    poise              { Rep( 1e-1L ) * pascal * second };
constexpr quantity< mass_d >                 pound_avdp         { Rep( 4.5359237e-1L ) * kilogram };
constexpr quantity< force_d >                pound_force        { Rep( 4.448222L ) * newton };
constexpr quantity< mass_d >                 pound_troy         { Rep( 3.732417e-1L ) * kilogram };
constexpr quantity< force_d >                poundal            { Rep( 1.382550e-1L ) * newton };
constexpr quantity< pressure_d >             psi                { Rep( 6.894757e+3L ) * pascal };

constexpr quantity< energy_d >               quad               { Rep( 1e+15L ) * btu_it };
constexpr quantity< volume_d >               quart_dry          { Rep( 1.101221e-3L ) * cube( meter ) };
constexpr quantity< volume_d >               quart_liquid       { Rep( 9.463529e-4L ) * cube( meter ) };

constexpr Rep                                revolution         { Rep( 2 ) * pi };
constexpr quantity< dimensions< 1, -1, 1 > > rhe                { Rep( 1e+1L ) / pascal / second };
constexpr quantity< length_d >               rod                { Rep( 5.029210L ) * meter };
constexpr quantity< angular_velocity_d >     rpm                { Rep( 1.047198e-1L ) / second };

constexpr quantity< time_interval_d >        second_sidereal    { Rep( 9.972696e-1L ) * second };
constexpr quantity< time_interval_d >        shake              { Rep( 1e-8L ) * second };
constexpr quantity< mass_d >                 slug               { Rep( 1.459390e+1L ) * kilogram };
constexpr quantity< electric_current_d >     statampere         { Rep( 3.335641e-10L ) * ampere };
constexpr quantity< electric_charge_d >      statcoulomb        { Rep( 3.335641e-10L ) * coulomb };
constexpr quantity< capacitance_d >          statfarad          { Rep( 1.112650e-12L ) * farad };
constexpr quantity< inductance_d >           stathenry          { Rep( 8.987552e+11L ) * henry };
constexpr quantity< electric_conductance_d > statmho            { Rep( 1.112650e-12L ) * siemens };
constexpr quantity< electric_resistance_d >  statohm            { Rep( 8.987552e+11L ) * ohm };
constexpr quantity< electric_potential_d >   statvolt           { Rep( 2.997925e+2L ) * volt };
constexpr quantity< volume_d >               stere              { cube( meter ) };
constexpr quantity< illuminance_d >          stilb              { Rep( 1e+4L ) * candela / square( meter ) };
constexpr quantity< kinematic_viscosity_d >  stokes             { Rep( 1e-4L ) * square( meter ) / second };

constexpr quantity< volume_d >               tablespoon         { Rep( 1.478676e-5L ) * cube( meter ) };
constexpr quantity< volume_d >               teaspoon           { Rep( 4.928922e-6L ) * cube( meter ) };
constexpr quantity< dimensions< -1, 1, 0 > > tex                { Rep( 1e-6L ) * kilogram / meter };
constexpr quantity< energy_d >               therm_ec           { Rep( 1.05506e+8L ) * joule };
constexpr quantity< energy_d >               therm_us           { Rep( 1.054804e+8L ) * joule };
constexpr quantity< mass_d >                 ton_assay          { Rep( 2.916667e-2L ) * kilogram };
constexpr quantity< force_d >                ton_force          { Rep( 8.896443e+3L ) * newton };
constexpr quantity< mass_d >                 ton_long           { Rep( 1.016047e+3L ) * kilogram };
constexpr quantity< heat_flow_rate_d >       ton_refrigeration  { Rep( 3.516853e+3L ) * watt };
constexpr quantity< volume_d >               ton_register       { Rep( 2.831685L ) * cube( meter ) };
constexpr quantity< mass_d >                 ton_short          { Rep( 9.071847e+2L ) * kilogram };
constexpr quantity< energy_d >               ton_tnt            { Rep( 4.184e+9L ) * joule };
constexpr quantity< pressure_d >             torr               { Rep( 1.333224e+2L ) * pascal };

constexpr quantity< magnetic_flux_d >        unit_pole          { Rep( 1.256637e-7L ) * weber };

constexpr quantity< time_interval_d >        week               { Rep( 604800L ) * second }; // 7 days

constexpr quantity< length_d >               x_unit             { Rep( 1.002e-13L ) * meter };

constexpr quantity< length_d >               yard               { Rep( 9.144e-1L ) * meter };
constexpr quantity< time_interval_d >        year_sidereal      { Rep( 3.155815e+7L ) * second };
constexpr quantity< time_interval_d >        year_std           { Rep( 3.1536e+7L ) * second }; // 365 days
constexpr quantity< time_interval_d >        year_tropical      { Rep( 3.155693e+7L ) * second };

}} // namespace phys::units

#endif // PHYS_UNITS_OTHER_UNITS_HPP_INCLUDED

/*
 * end of file
 */
