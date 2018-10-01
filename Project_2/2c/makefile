# General makefile for c++ - choose PROG =   name of given program

# Here we define compiler option, libraries and the  target
CPPflags = c++

# Here we define the library functions we nee
LIB = -larmadillo -llapack -lblas

# Here we define the name of the executable
PROG = UnitTest.x

${PROG} :	   	test-main.o  test-functions.o functions.o
			${CPPflags} test-main.o test-functions.o functions.o ${LIB} -o ${PROG}

test-main.o :		test-main.cpp 
		        	${CPPflags} -c test-main.cpp

test-functions.o :	test-functions.cpp
		        	${CPPflags} -c test-functions.cpp

functions.o :		functions.cpp 
		        	${CPPflags} -c functions.cpp