#include "functions.h"



Solver::Solver(SolarSystem &input_system)
{
  system = &input_system;
  totalObjects = system->objects.size();
}



void Solver::forwardEuler(double dt, double Tfinal)
{
  double t = 0;

  system->writeheader();
  system->dumptofile();

  // For each time step dt
  while (t <= Tfinal){
    // For each object in solar system
    updateGravity();

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

void Solver::velocityVerlet(double dt, double Tfinal)
{
  double t = 0;

  system->writeheader();
  system->dumptofile();



  // For each time step dt
  while (t <= Tfinal){
    // For each object in solar system
    updateGravity();
    std::vector<vec3> acceleration;
    for (int i=0; i < totalObjects; i++){
      acceleration.push_back(system->objects[i].force/system->objects[i].mass);
      system->objects[i].position += system->objects[i].velocity * dt + acceleration[i]*(dt*dt)/2;
      system->objects[i].resetF();
    }

    updateGravity();

    for (int i=0; i < totalObjects; i++){
      vec3 accelerationNew = system->objects[i].force/system->objects[i].mass;
      system->objects[i].velocity += (acceleration[i] + accelerationNew) * dt/2;
      system->objects[i].resetF();
    }


    // Writing information to file instead of saving the arrays
		system->dumptofile();
		t += dt;
  }
}


void Solver::updateGravity()
{
  for (int i = 0; i < system->gravityForces.size(); i++){
    system->gravityForces[i].calculateForce();
  }
}
