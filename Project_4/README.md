# Project 4 - The Ising Model

 ### Prerequisites

The code is written in c++ and is parallelized with MPI. Compiling software and MPI are needed. The makefile uses c++17 as standard version. Libraries required are armadillo, lapack and blas.

## Running the main program

The main program is compiled using a "makefile". Compiling is then done through the command
```
make
```
This will create a run.x executable. The executable takes in the following arguments in order: Lattice dimension, 10^N MC cycles, starting temperature, final temperature, number of temperature steps, savefilename. An example is 
```
./mpirun -n 2 ./run.x 20 5 2.0 2.4 100 savefile
```
where -n 2 means that the program is split up into 2 processes.
If one only wants to study a single temperature, put the final temperature argument to 0 and number of temperature steps to 1.

## Tools

The tools used to analyze the resulting data are written in python. These should be studied individually to understand their use and how they are executed.

## Authors

* **Metin San** 

*Only me this time*
