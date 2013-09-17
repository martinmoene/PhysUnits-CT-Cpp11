#
# ./projects/gcc/Test/Makefile.win32.gcc
#
:: Created by Martin on 17 September 2013.
# Copyright 2012 Universiteit Leiden. All rights reserved.
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#

RM = rm

INCDIR = ../../../
HDRDIR = $(INCDIR)/phys/units/
SRCDIR = ../../Test/

HEADERS = \
	io.hpp \
	io_output.hpp \
	io_output_eng.hpp \
	other_units.hpp \
	physical_constants.hpp \
	quantity.hpp \
	quantity_io.hpp \
	quantity_io_ampere.hpp \
	quantity_io_becquerel.hpp \
	quantity_io_candela.hpp \
	quantity_io_celsius.hpp \
	quantity_io_coulomb.hpp \
	quantity_io_dimensionless.hpp \
	quantity_io_engineering.hpp \
	quantity_io_farad.hpp \
	quantity_io_gray.hpp \
	quantity_io_henry.hpp \
	quantity_io_hertz.hpp \
	quantity_io_joule.hpp \
	quantity_io_kelvin.hpp \
	quantity_io_kilogram.hpp \
	quantity_io_lumen.hpp \
	quantity_io_lux.hpp \
	quantity_io_meter.hpp \
	quantity_io_newton.hpp \
	quantity_io_ohm.hpp \
	quantity_io_pascal.hpp \
	quantity_io_radian.hpp \
	quantity_io_second.hpp \
	quantity_io_siemens.hpp \
	quantity_io_sievert.hpp \
	quantity_io_speed.hpp \
	quantity_io_steradian.hpp \
	quantity_io_symbols.hpp \
	quantity_io_tesla.hpp \
	quantity_io_volt.hpp \
	quantity_io_watt.hpp \
	quantity_io_weber.hpp \
	test_util.hpp

OBJS = \
	test_quantity.o

vpath %.hpp $(HDRDIR)
vpath %.cpp $(SRCDIR)

CC = g++
CXXFLAGS = -Wall -Wextra -Weffc++ -std=c++11 -I$(INCDIR)

%.o: %.cpp $(HEADERS)

%.exe: %.o
	$(CC) -o $*.exe $^

all : test_quantity.exe
	./test_quantity.exe

test_quantity.exe : $(OBJS)

clean:
	-$(RM) *.bak *.o

distclean: clean
	-$(RM) *.exe

#
# end of file
#
