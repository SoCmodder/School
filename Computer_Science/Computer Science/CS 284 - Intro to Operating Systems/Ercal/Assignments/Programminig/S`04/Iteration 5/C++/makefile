###########################################################################
# -->Makefile<--
###########################################################################

###########################################################################
#
# Programmer :  Rob Wiehage
# Assignment :  Program 4
#
# Instructor :  Dr. Michael Hilgers
# Course     :  CS236 Winter 2001
# Semester   :  Fall 2001
#
###########################################################################

###########################################################################
# This makefile will build an executable for the assignment.
###########################################################################

###########################################################################
# This file originally created and used as the comments above indicate.
# On January 31, 2004, Matt Johnson copied this file from the website
# of Clayton Price for use in CS 328.
# A few modifications have been made, but the file is for the most part
# unaltered.
###########################################################################

.PHONY: all clean

CXX = /usr/bin/g++
#CXX = /umr/bin/g++
CXXFLAGS = -g -Wall -W -pedantic-errors -O3 -funroll-loops 

# The following 2 lines only work with gnu make.
# It's much nicer than having to list them out,
# and less error prone.
SOURCES = $(wildcard *.cpp)
HEADERS = $(wildcard *.h)

# With Sun's make it has to be done like this, instead of
# using wildcards.
# Well, I haven't figured out another way yet.
# SOURCES = signal.cpp tokentype.cpp token.cpp tokenlist.cpp mshell.cpp
# HEADERS = signal.h tokentype.h token.h tokenlist.h

# Looks like it can be done like this, but won't work for gmake.
# SOURCES:sh = ls *.cpp
# HEADERS:sh = ls *.h

OBJECTS = $(SOURCES:%.cpp=%.o)

default: mshell

%.o: %.cpp
	@echo "Compiling $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

mshell: $(OBJECTS)
	@echo "Building $@"
	@$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@
	@echo ""
	@echo "Everything worked :-) "
	@echo ""

clean:
	-@rm -f core
	-@rm -f mshell
	-@rm -f $(OBJECTS)

del:
	-@rm -f *~

# Automatically generate dependencies and include them in Makefile
depend: $(SOURCES) $(HEADERS)
	@echo "Generating dependencies"
	@$(CXX) -MM *.cpp > $@


-include depend
# Put a dash in front of include when using gnu make.
# It stops gmake from warning us that the file
# doesn't exist yet, even though it will be properly
# made and included when all is said and done.
