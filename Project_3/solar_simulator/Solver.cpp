#include "functions.h"


Solver::Solver()
{
  totalObjects = 0;
}

void Solver::add(PlanetaryBody newObject)
{
  totalObjects += 1;                     // Total numver of objects
  allObjects.push_back(newObject);       // Vector containing all objects
}



void Solver::setupForces()
{
  // Computing the gravitational forces between all objects
  for (int i = 0; i < totalObjects-1; i++)
  {
    for (int j = i+1; j < totalObjects; j++)
    {
      gravityForces.push_back(Gravity(&allObjects[i], &allObjects[j]));
    }
  }
}



void Solver::forwardEuler(int N, double Tfinal)
{
  double dt = Tfinal/N;
  double t = 0;

  while (t <= Tfinal){
    for (int i = 0; i < gravityForces.size(); i++){
      gravityForces[i].calculateForce();
    };

    for (int i=0; i < totalObjects; i++){
      vec3 acceleration = allObjects[i].force/allObjects[i].mass;
      allObjects[i].velocity += acceleration * dt;
      allObjects[i].position += allObjects[i].velocity * dt;
      allObjects[i].resetF();
    };

    // Writing information to file instead of saving the arrays
		dumptofile();
		t += dt;
  }
}


void Solver::dumptofile()
{

	// Writing the position of the planets to file instead of saving the information in arrays

	std::string path = "output/";
	std::ofstream outfile;
	outfile.open(path+"output.txt", std::ios_base::app);

	for (int i = 0; i < totalObjects; i++)
	{
		outfile << allObjects[i].position[0] << " " << allObjects[i].position[1] << " " << allObjects[i].position[2] << " ";
	}
	outfile << std::endl;
}
