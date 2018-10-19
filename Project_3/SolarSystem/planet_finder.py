from astroquery.jplhorizons import Horizons
from datetime import date, timedelta as td
import numpy as np
import sys



def getpositions(id, id_type = "majorbody"):
	today = date.today()
	obj = Horizons(id_type=id_type, id=id, location='500@0', 
			epochs={'start': today.__str__(), 'stop':(today + td(1)).__str__() ,'step':'2d'})

	table = obj.vectors()

	return table["targetname"].item().split()[0], (table["x"].item(), table["y"].item(), table["z"].item()), (table["vx"].item(), table["vy"].item(), table["vz"].item())



def getplanets(lisst):
	daytoyr = 365
	r = np.zeros((len(lisst), 3))
	v = np.zeros((len(lisst), 3))
	names = []
	for i in range(len(lisst)):
		name, r_, v_ = getpositions(lisst[i])
		names.append(name)
		r[i] = r_
		v[i] = v_
	return names, r, v*daytoyr

def savetofile(file, names, r, v, mass = None):
	text = ""
	rows = ["Name", "x", "y", "z", "vx", "vy", "vz", "mass"]
	for i in range(len(rows)):
		text += rows[i] + " "
		for j in range(len(names)):
			if rows[i] == "Name":
				text += names[j] + " "
			elif rows[i] == "x":
				text += str(r[j,0]) + " "
			elif rows[i] == "y":
				text += str(r[j,1]) + " "
			elif rows[i] == "z":
				text += str(r[j,2]) + " "
			elif rows[i] == "vx":
				text += str(v[j,0]) + " "
			elif rows[i] == "vy":
				text += str(v[j,1]) + " "
			elif rows[i] == "vz":
				text += str(v[j,2]) + " "
			elif rows[i] == "mass":
				if mass:
					text += str(mass[j]) + " "
		text += "\n"							

	with open(file, "w") as fil:
		fil.write(text)
		



if __name__ == "__main__":
	# planets = ["10", "199", "299", "301", "399", "499", "599", "699", "799", "899", "999"]
	# mass = [1, 1.66012e-7, 2.44781e-6, 3.6943e-8, 3.003467e-6, 3.22713e-7, 9.5458e-4, 2.85812e-4, 4.36576e-5, 5.15028e-5, 6.583e-9]

	Planets = {}
	Planets["Sun"] = ["10", 1]
	Planets["Mercury"] = ["199", 1.66012e-7]
	Planets["Venus"] = ["299", 2.44781e-6]
	Planets["Moon"] = ["301", 3.6943e-8]
	Planets["Earth"] = ["399", 3.003467e-6]
	Planets["Mars"] = ["499", 3.22713e-7]
	Planets["Jupiter"] = ["599", 9.5458e-4]
	Planets["Saturn"] = ["699", 2.85812e-4]
	Planets["Uranus"] = ["799", 4.36576e-5]
	Planets["Neptune"] = ["899", 5.15028e-5]
	Planets["Pluto"] = ["999", 6.583e-9]

	planets = []
	mass = []

	if sys.argv[1] == ".":
		for i in range(len(Planets)):
			planets.append(list(Planets.values())[i][0])
			mass.append(list(Planets.values())[i][1])

	else:

		for i in range(len(sys.argv) - 1):

			planets.append(Planets[str(sys.argv[i+1])][0])
			mass.append(Planets[str(sys.argv[i+1])][1])


	names, r, v = getplanets(planets) 					
	print("Please insert name of data file here")
	filename = str(input())

	savetofile(filename, names, r, v, mass)

