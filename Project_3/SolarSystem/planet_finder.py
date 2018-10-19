from astroquery.jplhorizons import Horizons
from datetime import date, timedelta as td
import numpy as np
import sys



def getpositions(id, id_type = "majorbody"):
	today = date.today()
	obj = Horizons(id_type=id_type, id=id, location='500@0', 
			epochs={'start': today.__str__(), 'stop':(today + td(1)).__str__() ,'step':'2d'})

	table = obj.vectors()



	return table["targetname"].item().rsplit(" ", 1)[0], (table["x"].item(), table["y"].item(), table["z"].item()), (table["vx"].item(), table["vy"].item(), table["vz"].item())



def getplanets(lisst):
	daytoyr = 365
	r = np.zeros((len(lisst), 3))
	v = np.zeros((len(lisst), 3))
	names = []
	for i in range(len(lisst)):
		if lisst[i].startswith("S"):
			name, r_, v_ = getpositions(lisst[i][1:], id_type="smallbody")
		elif lisst[i].startswith("I"):
			name, r_, v_ = getpositions(lisst[i][1:], id_type="id")

		elif lisst[i].startswith("n"):
			name, r_, v_ = getpositions(lisst[i][1:], id_type="name")

		else:
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
				text += names[j].replace(" ", "_") + " "
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
	nam = ["Sun", "Mercury", "Venus", "Moon", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Netpune", "Pluto"]
	planets = ["10", "199", "299", "301", "399", "499", "599", "699", "799", "899", "999"]
	mass = [1, 1.66012e-7, 2.44781e-6, 3.6943e-8, 3.003467e-6, 3.22713e-7, 9.5458e-4, 2.85812e-4, 4.36576e-5, 5.15028e-5, 6.583e-9]

	filename = "planets.txt"

	for i in range(len(sys.argv) - 1):
		if sys.argv[i+1] == "-h":
			print("Usage:")
			print("    -h - Print this help page.\n")
			print("    -f - Change filename. Use as '-f %desired filename%'.\n")
			print("    -o - Only include objects given. Must be used at the end of the commandline arguments. ex. '-o Sun Earth Jupiter'")
			print("         Possible objects are Sun, Mercury, Venus, Moon, Earth, Mars, Jupiter, Saturn, Uranus, Netpune and Pluto.")
			print("         This option does not affect manually given objects.\n\n")
			print("    Otherwise add objects as desired. Default id_type is majorbody (planets, large moons and large satelites).")
			print("    To use other id types, prefix the ID-number with 'S' for smallbody, 'I' for global ID and 'n' for name search (might not yield best result).")
			print("    Example: S301, where S is the prefix and 301 is the ID. Also nEarth, where n is the prefix and Earth is the search term.")
			sys.exit()

		if sys.argv[i] == "-f":
			filename = sys.argv[i]
		
		elif sys.argv[i] == "-o":
			for j in range(11)[::-1]:
				if nam[j] not in sys.argv[i+1:]:
					del planets[j]
					del mass[j]

			break

				

		elif sys.argv[i] == "-m":
			mass.append(sys.argv[i+1])
		
		elif sys.argv[i+1] not in ["-f", "-o", "-m"]:
			planets.append(sys.argv[i+1])
			if len(mass) != len(planets):
				mass.append(0)

	names, r, v = getplanets(planets) 					
	
	if not filename.endswith(".txt"):
		filename += ".txt"

	savetofile(filename, names, r, v, mass)
	