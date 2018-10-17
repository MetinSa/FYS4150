#ifndef SOLVER_H
#define SOLVER_H

class Solver
{
public:
  int totalObjects;
  SolarSystem* system; 

  // Constructor
  Solver();

  // Functions
  void add(PlanetaryBody newObject);
  void setupForces();
  void forwardEuler(int N, double Tfinal);
  void dumptofile();

};

#endif // SOLVER_H
