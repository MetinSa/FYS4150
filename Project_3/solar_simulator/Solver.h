#ifndef SOLVER_H
#define SOLVER_H

class Solver
{
public:
  int totalObjects;
  SolarSystem* system;

  // Constructor
  Solver(SolarSystem &input_system);

  // Functions
  void forwardEuler(int N, double Tfinal);

};

#endif // SOLVER_H
