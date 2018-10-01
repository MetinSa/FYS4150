# General makefile for c++ - choose PROG =   name of given program

# Here we define compiler option, libraries and the  target
CPPflags = c++

# Here we define the library functions we nee
LIB = -larmadillo -llapack -lblas

# Here we define the name of the executable
PROG = run.x

${PROG} :	   	main.o  functions.o
			${CPPflags} main.o functions.o  ${LIB} -o ${PROG}

main.o :		main.cpp 
		        	${CPPflags} -c main.cpp

functions.o :	functions.cpp
		        	${CPPflags} -c functions.cpp