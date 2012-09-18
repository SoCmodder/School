###############################################################################
## -->Makefile<--
###############################################################################

###############################################################################
##
## Instructor :  Dr. Franck Xia
## Class      :  CS236 Fall 2003
## Assignment :  Program 4
## Programmer :  Franck Xia
## Filename   :  Makefile
##
###############################################################################

###############################################################################
## This makefile will build an executable for the assignment
## Important Note:
#  You might need to change on line about "OBJECTS = ...
#    to include all your class files (*.cpp).
###############################################################################

CXX = /umr/bin/g++
CXXFLAGS = -g -Wno-deprecated
OBJECTS = driver.o CToken.o CToken_List.o Err_Msg.o scanner.o parser.o

.SUFFIXES: .cpp

.cpp.o: $<
	@echo "Compiling $@"
	@${CXX} -c ${CXXFLAGS} $< -o $@

default: all

all: driver

driver: ${OBJECTS}
	@echo "Compiling driver"
	@${CXX} ${CXXFLAGS} ${OBJECTS} -o $@
	@echo "Everything worked"
	@echo ""

clean:
	-@rm core > /dev/null 2>&1
	-@rm driver > /dev/null 2>&1
	-@rm ${OBJECTS} > /dev/null 2>&1
	
# Dependency lists for the various source files
Err_Msg.cpp	:: Err_Msg.h
CToken.cpp	:: CToken.h 
CToken_List.cpp	:: CToken_List.h CToken.h Err_Msg.h
scanner.cpp	:: scanner.h CToken_List.h CToken.h
parser.cpp	:: parser.h scanner.h CToken_List.h CToken.h
driver.cpp	:: parser.h scanner.h CToken.h CToken_List.h Err_Msg.h
