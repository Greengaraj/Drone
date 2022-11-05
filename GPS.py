from math import radians, cos, sin, asin, sqrt
def distance(Longitude1, Longitude2, Breadth1, Breadth2):

    Breadth1 = radians(Breadth1)
    Breadth2 = radians(Breadth2)
    Longitude1 = radians(Longitude1)
    Longitude2 = radians(Longitude2)
      
    # Distance calculation using the Haversin formula
    dlon = Breadth2 - Breadth1
    dlat = Longitude2 - Longitude1
    a = sin(dlat / 2)**2 + cos(Longitude1) * cos(Longitude2) * sin(dlon / 2)**2
 
    c = 2 * asin(sqrt(a))

    r = 6371	# The radius of the earth in kilometers
  
    return(c * r)

Longitude1 = 55.110485	# Longitude of the current point
Breadth1 = 37.962350	# Latitude of the current point
Longitude2 = 55.108175	# The longitude of the destination point
Breadth2 = 37.975712	# Latitude of the destination point
print(round(distance(Longitude1, Longitude2, Breadth1, Breadth2), 2), "km")