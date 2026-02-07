# Copyright 2026-2026 by Martin Moene
#
# https://github.com/martinmoene/physunits-CT-Cpp11
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(
  PhysUnits    VERSION 1.3.0
  LANGUAGES    C CXX
)

# unit_name is used by test/CMakeLists.txt:

set( unit_name "physunits" )

message( STATUS "Project '${PROJECT_NAME}', version: '${PROJECT_VERSION}'")

# Toplevel or subproject:

if ( CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME )
    set( physunits_IS_TOPLEVEL_PROJECT TRUE )
else()
    set( physunits_IS_TOPLEVEL_PROJECT FALSE )
endif()

# If toplevel project, enable building and performing of tests, disable building of examples:

option( PHYS_UNITS_OPT_BUILD_TESTS    "Build and perform physunits tests" ${physunits_IS_TOPLEVEL_PROJECT} )
option( PHYS_UNITS_OPT_BUILD_EXAMPLES "Build PhysUnits examples" OFF )  # not present

# Library:

add_library(PhysUnits INTERFACE)
target_include_directories(PhysUnits INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include>
)
target_compile_features(PhysUnits INTERFACE
  cxx_constexpr
)

add_library(PhysUnits::PhysUnits ALIAS PhysUnits)

# Install and exports:

include(GNUInstallDirs)

install(TARGETS PhysUnits EXPORT PhysUnitsConfig)
install(
  DIRECTORY phys
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT PhysUnitsConfig NAMESPACE PhysUnits:: DESTINATION share/PhysUnits/cmake)
export(TARGETS PhysUnits NAMESPACE PhysUnits:: FILE PhysUnitsConfig.cmake)

export(PACKAGE PhysUnits)

# If requested, build and perform tests, build examples:

if ( PHYS_UNITS_OPT_BUILD_TESTS )
    enable_testing()
    add_subdirectory( test )
endif()

# End of file
