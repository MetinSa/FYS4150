 # Project 3 - Simulating the Solar System

 ### Prerequisites

The code is written in c++. Compiling software is required. The makefile uses c++17. Libraries required are armadillo, lapack and blas.

## Running the programs

All programs are compiled using a "makefile". Compiling is then done through the command
```
make
```
Similarely the object files can be cleared through 
```
make clean
```

#### Using the framework

Start by chosing a planetary system of interest. Locate **SystemFinder.py** in the *PlanetarySystems* folder. Running
```
python PlanetarySystems.py
```
will return *planets.txt* containg a default planetary system. In general it should be used as following
```
python PlanetarySystems.py -f Systemo.txt
```