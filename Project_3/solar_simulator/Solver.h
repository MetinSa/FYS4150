#ifndef SOLVER_H
#define SOLVER_H

class Solver
{
public:
  int totalObjects;
  std::vector<PlanetaryBody> allObjects;
  std::vector<Gravity> gravityForces;

  // Constructor
  Solver();

  // Functions
  void add(PlanetaryBody newObject);
  void setupForces();
  void forwardEuler(int N, double Tfinal);
  void dumptofile();

};

#endif // SOLVER_H
