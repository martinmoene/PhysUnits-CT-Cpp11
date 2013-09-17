#
# ./doxygen/examples/Makefile
#
# Created by Martin on 7 September 2013.
# Copyright 2013 Martin Moene. All rights reserved.
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#

CXX = g++
RM  = rm

SOURCES = hello.cpp work.cpp engineering.cpp base.cpp # # exception.cpp extend.cpp input.cpp

PROGRAMS = $(SOURCES:.cpp=)

CXXFLAGS += -Wall -Wextra -Weffc++ -std=c++11 -I../../../

TARGET = compile
all compile: $(PROGRAMS)

#$(PROGAMS): quantity.hpp io.hpp

clean:
	-$(RM) *.bak

distclean: clean
	-$(RM) *.obj *.exe

#
# end of file
#

