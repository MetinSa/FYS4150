# General makefile for c++ - choose PROG =   name of given program

# Here we define compiler option, libraries and the  target
CPPflags = c++ -O3

# Here we define the library functions we nee
LIB = -larmadillo -llapack -lblas

# Here we define the name of the executable
PROG = run.x


${PROG} :	  		main.o  vec3.o PlanetaryBody.o Gravity.o
					${CPPflags} main.o vec3.o PlanetaryBody.o Gravity.o -o ${PROG} ${LIB}

main.o :			main.cpp 
		        	${CPPflags} -c main.cpp

vec3.o :			vec3.cpp
		        	${CPPflags} -c vec3.cpp

PlanetaryBody.o :	PlanetaryBody.cpp
		        	${CPPflags} -c PlanetaryBody.cpp

Gravity.o :			Gravity.cpp
		        	${CPPflags} -c Gravity.cpp
