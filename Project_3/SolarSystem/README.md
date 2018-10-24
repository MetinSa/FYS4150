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

Start by chosing a planetary system of interest. Locate *SystemFinder.py* in the **PlanetarySystems** folder. The run
```
python PlanetarySystems.py
```
This will return *planets.txt* containg a default planetary system. In general it should be used as following
```
python PlanetarySystems.py -f SystemOfInterest.txt -o Sun Earth Jupiter SomeOtherPlanetOrMoonOrSatelite
```
which will create a *SystemOfInterst.txt* containg the planetary objects: Sun Earth Jupiter or any other body of interest. (*Works for planetary objects compatible with NASA's HORIZONS tool*)

Once this the System text file is aquired, return to the main folder **Project_3**. Now run 
```
make
./run.x SystemOfInterest 10 0.01
```
where 10 is the amount of years you simulate and 0.01 is the stepsize. This will create a binary output file called *SystemOfInterst.bin*. Now, enter the *plottertools* folder. Here you find a set of different plotting tools which allows you to either study the system in 2D, 3D or through an animation or other quantities related to the system such as the energy. 

For instance, run
```
python plotter2D.py SystemOfInterest
```
which will display a 2D simulation of a given system.

## Authors

* **Metin San** - (https://github.com/MetinSa)

* **Maren Rasmussen** - (https://github.com/mjauren)

* **Markus Leira Asprusten** - (https://github.com/maraspr)

