from numpy import exp
from scipy.special import gamma

def GammaDistribution(m0, m, lmbda):
    """
    Returns the Gamma distribution for the
    given lambda-value (saving criterion).
    """
    # Define parameter n and rescaled variable x_n
    n = 1 + (3*lmbda)/(1 - lmbda)
    x = m/m0
    a_n = n**n/gamma(n)
    
    return a_n*x**(n-1) * exp(-n*x)
