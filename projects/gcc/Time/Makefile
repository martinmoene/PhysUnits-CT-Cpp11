#
# ./projects/gcc/Test/Makefile
#
# Created by Martin on 17 September 2013.
# Copyright 2012 Universiteit Leiden. All rights reserved.
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#

RM = rm

INCDIR = ../../../
HDRDIR = $(INCDIR)/phys/units/
SRCDIR = ../../Time/

HEADERS = \
	quantity.hpp \
	quantity_io.hpp

vpath %.hpp $(HDRDIR)
vpath %.cpp $(SRCDIR)

CC = g++
CXXFLAGS = -Wall -Wextra -Weffc++ -std=c++11 -I$(INCDIR)

.PHONY: all run_tests clean

all: time_performance_opt.exe time_performance_nonopt.exe run_tests

time_performance_opt.exe: time_performance.cpp $(HEADERS)
	$(CC) $(CXXFLAGS) -O2 $< -o $@

time_performance_nonopt.exe: time_performance.cpp $(HEADERS)
	$(CC) $(CXXFLAGS) $< -o $@

run_tests:
	./time_performance_opt.exe
	./time_performance_nonopt.exe

clean:
	-$(RM) *.bak *.o

distclean: clean
	-$(RM) *.exe

#
# end of file
#
