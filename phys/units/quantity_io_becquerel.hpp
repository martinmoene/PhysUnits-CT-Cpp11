/**
 * \file quantity_io_becquerel.hpp
 *
 * \brief   becquerel, activity_of_a_nuclide_d
 * \author  Martin Moene
 * \date    7 September 2013
 * \since   1.0
 *
 * Copyright 2013 Universiteit Leiden. All rights reserved.
 * This code is provided as-is, with no warrantee of correctness.
 *
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef PHYS_UNITS_QUANTITY_IO_BECQUEREL_HPP_INCLUDED
#define PHYS_UNITS_QUANTITY_IO_BECQUEREL_HPP_INCLUDED

#include "phys/units/quantity_io.hpp"

namespace phys { namespace units {

/**
 * becquerel, [Bq].
 */
template<>
struct unit_info< activity_of_a_nuclide_d >
{
    static bool        single() { return true; }
    static std::string name()   { return "becquerel"; }
    static std::string symbol() { return "Bq"; }
};

namespace literals {

QUANTITY_DEFINE_LITERALS( Bq, activity_of_a_nuclide_d )

}
}} // namespace phys::units

#endif // PHYS_UNITS_QUANTITY_IO_BECQUEREL_HPP_INCLUDED

/*
 * end of file
 */
