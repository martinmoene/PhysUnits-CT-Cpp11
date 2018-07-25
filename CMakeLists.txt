cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(PhysUnits VERSION 1.1.0 LANGUAGES C CXX)

add_library(PhysUnits INTERFACE)
target_include_directories(PhysUnits INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include>
)
target_compile_features(PhysUnits INTERFACE
  cxx_constexpr
)

add_library(PhysUnits::PhysUnits ALIAS PhysUnits)

# Install and exports
include(GNUInstallDirs)

install(TARGETS PhysUnits EXPORT PhysUnitsConfig)
install(
  DIRECTORY phys
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT PhysUnitsConfig NAMESPACE PhysUnits:: DESTINATION share/PhysUnits/cmake)
export(TARGETS PhysUnits NAMESPACE PhysUnits:: FILE PhysUnitsConfig.cmake)

export(PACKAGE PhysUnits)

