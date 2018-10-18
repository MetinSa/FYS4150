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
    // For each Large object in solar system
    updateGravity();

    for (int i=0; i < totalObjects; i++){
    	vec3 acceleration = system->objects[i].force/system->objects[i].mass;
    	system->objects[i].velocity += acceleration * dt;
    	system->objects[i].position += system->objects[i].velocity * dt;
    	system->objects[i].resetF();
    };

    // For each small object in solar system
    for (int i=0; i < system->smallobjects.size(); i++){
    	system->smallobjects[i].calcA();
    	vec3 acceleration = system->smallobjects[i].acceleration;
    	system->smallobjects[i].velocity += acceleration * dt;
    	system->smallobjects[i].position += system->smallobjects[i].velocity * dt;
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
    // For each Large object in solar system
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

    // For each small object in solar system
    vec3 smallacceleration;
    for (int i = 0; i < system->smallobjects.size(); i++)
    {
    	system->smallobjects[i].calcA();
    	smallacceleration = system->smallobjects[i].acceleration;
    	system->smallobjects[i].position += system->smallobjects[i].velocity * dt + smallacceleration*(dt*dt)/2;
    	system->smallobjects[i].calcA();
    	system->smallobjects[i].velocity += (smallacceleration + system->smallobjects[i].acceleration) * dt/2;
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
