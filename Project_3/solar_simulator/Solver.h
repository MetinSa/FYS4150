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
  void forwardEuler(double dt, double Tfinal);
  void velocityVerlet(double dt, double Tfinal);
  void updateGravity();

};

#endif // SOLVER_H
