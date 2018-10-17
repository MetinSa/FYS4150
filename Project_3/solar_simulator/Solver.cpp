#include "functions.h"



Solver::Solver(SolarSystem &input_system)
{
  system = &input_system;
  totalObjects = system->objects.size();

  // Write position-values to file
  system->writeheader();
  system->dumptofile();

  system->objects[2].velocity;

}



void Solver::forwardEuler(int N, double Tfinal)
{
  double dt = Tfinal/N;
  double t = 0;

  system->writeheader();
  system->dumptofile();

  // For each time step dt
  while (t <= Tfinal){
    // For each object in solar system
    for (int i = 0; i < system->gravityForces.size(); i++){
      system->gravityForces[i].calculateForce();
    };

    for (int i=0; i < totalObjects; i++){
      vec3 acceleration = system->objects[i].force/system->objects[i].mass;
      system->objects[i].velocity += acceleration * dt;
      system->objects[i].position += system->objects[i].velocity * dt;
      system->objects[i].resetF();
    };

    // Writing information to file instead of saving the arrays
		system->dumptofile();
		t += dt;
  }
}
