# General makefile for c++ - choose PROG =   name of given program

# Here we define compiler option, libraries and the  target
CPPflags = c++ -O3

# Here we define the library functions we nee
LIB = -larmadillo -llapack -lblas

# Here we define the name of the executable
PROG = run.x


${PROG} :			main.o  vec3.o PlanetaryBody.o Gravity.o SolarSystem.o Solver.o SmallObject.o
					${CPPflags} main.o vec3.o PlanetaryBody.o Gravity.o SolarSystem.o Solver.o SmallObject.o -o ${PROG} ${LIB}

main.o :			main.cpp functions.h
					${CPPflags} -c main.cpp

vec3.o :			vec3.cpp vec3.h
					${CPPflags} -c vec3.cpp

PlanetaryBody.o :	PlanetaryBody.cpp PlanetaryBody.h
					${CPPflags} -c PlanetaryBody.cpp

Gravity.o :			Gravity.cpp Gravity.h
					${CPPflags} -c Gravity.cpp

SolarSystem.o :		SolarSystem.cpp SolarSystem.h
					${CPPflags} -c SolarSystem.cpp

Solver.o :  		Solver.cpp Solver.h
					${CPPflags} -c Solver.cpp
					
SmallObject.o : 	SmallObject.cpp SmallObject.h
					${CPPflags} -c SmallObject.cpp	        	
