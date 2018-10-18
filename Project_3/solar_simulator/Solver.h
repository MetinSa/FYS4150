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
  void printPreIntegration(double dt, double Tfinal, std::string name);
  void printPostIntegration(double totalTime);

};

#endif // SOLVER_H
