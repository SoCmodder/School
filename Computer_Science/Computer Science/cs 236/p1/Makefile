#############################################################
#  Makefile for CS236 Programming Languages & Translators   #
#   created by Dr. Franck Xia, CS Dept.                     #
#############################################################

CPP = /umr/bin/g++

# CPPFLAG = -g -Wall -W -pedantic -errors
CPPFLAG = -g -Wno-deprecated

driver:		cppmatrix.o driver.o
		$(CPP) $(CPPFLAG) driver.o cppmatrix.o -o $@

driver.o:	cppmatrix.h cppmatrix.cpp driver.cpp
		$(CPP) $(CPPFLAG) -c driver.cpp 

cppmatrix.o:	cppmatrix.h cppmatrix.cpp
		$(CPP) $(CPPFLAG) -c cppmatrix.cpp 
