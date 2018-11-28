from numpy import exp

def GibbsDistribution(m0, m):

	"""
	Returns the gibbs distribution

	"""
	# Constant beta
	beta = 1/m0

	return beta*exp(-beta*m)