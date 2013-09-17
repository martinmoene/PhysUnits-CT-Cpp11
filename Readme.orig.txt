 
               README for Quantity Library

quantity.html   - Overview of the library, and instructions on
                  how to use it.

rationale.html  - Why it was designed the way it was.

quantity.hpp
quantity_io.hpp
physical_constants.hpp
other_units.hpp - The actual source files that make up the library.
                There are no cpp files; this is currently a header-only
                library.

    The following programs are not part of the library, but they are
    supplied with it.  Each is compiled with "cc -I. xxx.cpp" or
    the local equivalent.

regrtest1.cpp   - Regression test, to ensure that the library is
                working correctly on your system.  This program
                reports its own results.  All 414 tests should pass.

regrtest2.cpp
regrtest2.pl    - Regression test to make sure things that should
                be caught as errors at compile-time really are.
                The perl script is used to drive the compilations
                and make sure they fail.  All 53 results should be
                reported as "pass".

user_example.hpp
demo.cpp        - Sample program to demonstrate how to use the
                library.

perf-test.cpp   - Simple performance test to see how well your
                compiler optimizes away all the dimension-checking
                at run-time.  Remember to turn on optimization with
                the appropriate command-line flag.  If things are
                working optimally, all three timings should be
                aproximately equal.

    Porting status:  All regression tests pass on:

        WinNT / MSVC 6
        WinNT / g++ 2.95.3-4 (Cygwin)
        SunOS / g++ 2.95.2

