# Project 2 - Solving the Schrodinger equation

This repository contains all files and results for project 2 in addition to the report.

### Prerequisites

The code is written in c++. Compiling software is required. The programs are written using Armadillo so one also needs to have the library Armadillo dowloaded.

## Running the programs

All programs are compiled using a "makefile". Compiling is then done through the command
```
make
```

#### 2b

Start by compiling.
Then run the executable with the 3 required commandline arguments, for instance
```
make
./run.x 4 0 1
```
where the first argument is the number of grid points *n*, the second is *rho_0* and the final being *rho_max*. 

#### 2c

Start by compiling. This creates the executable **UnitTest.x**
```
make
./UnitTest.x
```

#### 2d

Similar to **2b** with same commandline arguments. We can now also plot the groundstate energy with
```
make
./run.x 100 0 5
python plot.py 100_5.dat
```
which creates the figure *200_5.pdf*.


#### 2e

The final exercise. Similar to **2b** and **2c** with the addition the command argument *omega*. The file *plot.py* plots the result for 4 different values of *omega*
```
make
./run.x 400 0 5 0.01
./run.x 400 0 5 0.5
./run.x 400 0 5 1
./run.x 400 0 5 5
python plot.py 400_5_0.010000.dat 400_5_0.500000.dat 400_5_1.000000.dat 400_5_5.000000.dat 
```
which creates the figure *interacting.pdf*. Excuse the silly *.dat* file names.



## Authors

* **Metin San** - (https://github.com/MetinSa)

* **Maren Rasmussen** - (https://github.com/mjauren)

* **Markus Leira Asprusten** - (https://github.com/maraspr)
