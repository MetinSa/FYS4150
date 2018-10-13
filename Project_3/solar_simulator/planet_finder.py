from astroquery.jplhorizons import Horizons
from datetime import date, timedelta as td
import numpy as np



def getpositions(id, id_type = "majorbody"):
	today = date.today()
	obj = Horizons(id_type=id_type, id=id, location='500@0', 
			epochs={'start': today.__str__(), 'stop':(today + td(1)).__str__() ,'step':'2d'})

	table = obj.vectors()

	return table["targetname"].item().split()[0], (table["x"].item(), table["y"].item(), table["z"].item()), (table["vx"].item(), table["vy"].item(), table["vz"].item())



def getplanets(lisst):
	r = np.zeros((len(lisst), 3))
	v = np.zeros((len(lisst), 3))
	names = []
	for i in range(len(lisst)):
		name, r_, v_ = getpositions(lisst[i])
		names.append(name)
		r[i] = r_
		v[i] = v_
	return names, r, v

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
	names, r, v = getplanets(["10", "199", "299", "399", "499", "599", "699", "799", "899", "999"]) 					
	mass = [1, 1.66012e-7, 2.44781e-6, 3.003467e-6, 3.22713e-7, 9.5458e-4, 2.85812e-4, 4.36576e-5, 5.15028e-5, 6.583e-9]

	savetofile("file.txt", names, r, v, mass)
	