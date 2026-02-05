//
// Copyright (c) 2026-2026 Martin Moene
//
// https://github.com/martinmoene/PhysUnits-CT-Cpp11
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "physunits-main.t.hpp"

#define physunits_PRESENT( x ) \
    std::cout << #x << ": " << (x) << "\n"

#define physunits_ABSENT( x ) \
    std::cout << #x << ": (undefined)\n"

lest::tests & specification()
{
    static lest::tests tests;
    return tests;
}

CASE( "physunits-lite version" "[.bit][.version]" )
{
    physunits_PRESENT( phys_units_MAJOR );
    physunits_PRESENT( phys_units_MINOR );
    physunits_PRESENT( phys_units_PATCH );
    physunits_PRESENT( phys_units_VERSION );
}

CASE( "physunits-lite configuration" "[.bit][.config]" )
{
    // physunits_PRESENT( physunits_HAVE_STD_BIT );
    // physunits_PRESENT( physunits_USES_STD_BIT );
    // physunits_PRESENT( physunits_BIT_DEFAULT );
    // physunits_PRESENT( physunits_BIT_NONSTD );
    // physunits_PRESENT( physunits_BIT_STD );
    // physunits_PRESENT( physunits_CONFIG_SELECT_BIT );
    // // physunits_PRESENT( physunits_CONFIG_NO_EXCEPTIONS );
    // physunits_PRESENT( physunits_CPLUSPLUS );
}

CASE( "__cplusplus" "[.stdc++]" )
{
    physunits_PRESENT( __cplusplus );

#ifdef _MSVC_LANG
    physunits_PRESENT( _MSVC_LANG );
#else
    physunits_ABSENT(  _MSVC_LANG );
#endif
}

CASE( "Compiler version" "[.compiler]" )
{
// #if physunits_USES_STD_BIT
//     std::cout << "(Compiler version not available: using standard <bit>)\n";
// #else
//     physunits_PRESENT( physunits_COMPILER_CLANG_VERSION );
//     physunits_PRESENT( physunits_COMPILER_GNUC_VERSION );
//     physunits_PRESENT( physunits_COMPILER_MSVC_VERSION );
// #endif
}

CASE( "Presence of C++ language features" "[.stdlanguage]" )
{
// #if physunits_USES_STD_BIT
//     std::cout << "(Presence of C++ language features not available: using standard <bit>)\n";
// #else
// //  physunits_PRESENT( physunits_HAVE_AUTO );
//     // physunits_PRESENT( physunits_HAVE_NULLPTR );
//     // physunits_PRESENT( physunits_HAVE_STATIC_ASSERT );
//     // physunits_PRESENT( physunits_HAVE_DEFAULT_FUNCTION_TEMPLATE_ARG );
// //  physunits_PRESENT( physunits_HAVE_ALIAS_TEMPLATE );
//     physunits_PRESENT( physunits_HAVE_CONSTEXPR_11 );
//     physunits_PRESENT( physunits_HAVE_CONSTEXPR_14 );
//     physunits_PRESENT( physunits_HAVE_ENUM_CLASS );
// //  physunits_PRESENT( physunits_HAVE_ENUM_CLASS_CONSTRUCTION_FROM_UNDERLYING_TYPE );
// //  physunits_PRESENT( physunits_HAVE_EXPLICIT_CONVERSION );
//     // physunits_PRESENT( physunits_HAVE_INITIALIZER_LIST );
// //  physunits_PRESENT( physunits_HAVE_IS_DEFAULT );
// //  physunits_PRESENT( physunits_HAVE_IS_DELETE );
//     physunits_PRESENT( physunits_HAVE_NOEXCEPT );
// #endif
}

CASE( "Presence of C++ library features" "[.stdlibrary]" )
{
// #if physunits_USES_STD_BIT
//     std::cout << "(Presence of C++ library features not available: using standard <bit>)\n";
// #else
//     physunits_PRESENT( physunits_HAVE_TYPE_TRAITS );
//     physunits_PRESENT( physunits_HAVE_TR1_TYPE_TRAITS );
//     physunits_PRESENT( physunits_HAVE_IS_TRIVIAL );
//     physunits_PRESENT( physunits_HAVE_IS_TRIVIALLY_COPYABLE );
//     physunits_PRESENT( physunits_HAVE_IS_COPY_CONSTRUCTIBLE );
//     physunits_PRESENT( physunits_HAVE_IS_MOVE_CONSTRUCTIBLE );
// #endif

#if defined _HAS_CPP0X
    physunits_PRESENT( _HAS_CPP0X );
#else
    physunits_ABSENT(  _HAS_CPP0X );
#endif
}

int main( int argc, char * argv[] )
{
    return lest::run( specification(), argc, argv );
}

#if 0
g++            -I../include -o physunits-lite.t.exe physunits-main.t.cpp && physunits-lite.t.exe --pass
g++ -std=c++98 -I../include -o physunits-lite.t.exe physunits-main.t.cpp && physunits-lite.t.exe --pass
g++ -std=c++03 -I../include -o physunits-lite.t.exe physunits-main.t.cpp && physunits-lite.t.exe --pass
g++ -std=c++0x -I../include -o physunits-lite.t.exe physunits-main.t.cpp && physunits-lite.t.exe --pass
g++ -std=c++11 -I../include -o physunits-lite.t.exe physunits-main.t.cpp && physunits-lite.t.exe --pass
g++ -std=c++14 -I../include -o physunits-lite.t.exe physunits-main.t.cpp && physunits-lite.t.exe --pass
g++ -std=c++17 -I../include -o physunits-lite.t.exe physunits-main.t.cpp && physunits-lite.t.exe --pass

cl -EHsc -I../include -Fephysunits-lite.t.exe physunits-main.t.cpp && physunits-lite.t.exe --pass
#endif

// end of file
