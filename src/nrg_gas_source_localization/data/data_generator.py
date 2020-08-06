import json
import sys

import numpy as np

source="one"
params="a"

wind_path="C:/Users/Jack/OneDrive/UT SPRING 2020/LAB/code/data_sets/sim_params/"+params+"_params.json"
source_path="C:/Users/Jack/OneDrive/UT SPRING 2020/LAB/code/data_sets/"+source+"_source/source.json"
data_out="C:/Users/Jack/OneDrive/UT SPRING 2020/LAB/code/data_sets/"+source+"_source/"+params+"_data.json"

def Deb(msg = None):
  	print(f"Debug {sys._getframe().f_back.f_lineno}: {msg if msg is not None else ''}")

with open(wind_path) as json_file:
	wind_d = json.load(json_file)

with open(source_path) as json_file:
	source_d = json.load(json_file)

#wind params
azimuth=wind_d["wind_params"]["azimuth"]
speed=wind_d["wind_params"]["speed"]
stability=wind_d["wind_params"]["stability"]
#source params
sources=[]
for key in source_d["sources"]:
	sources.append(tuple(source_d["sources"][key]["position"])+(source_d["sources"][key]["rate"],))
sources=np.array(sources)

def concentration(xg, yg, zg, sources):
		#for each individual source the global test point (x,y,z) coordinate needs to be transformed into the local source plume frame  
		#then the concentration at any global point can be calculated and summed from all individual sources

		#unfortunately I have to to use try: execpt: blocks to handle fact that the input source array can have 1 element and be 1D or multiple elements and be 2D

		test_point= np.array([xg,yg,zg])

		try:
			test_point= test_point-sources[:,0:3]	#translation
		except IndexError:	#runs if "sources" is a 1D array instead of a 2D array
			test_point= test_point-sources[0:3]

		R= np.array([[np.cos(azimuth), -np.sin(azimuth), 0], [np.sin(azimuth), np.cos(azimuth), 0 ], [0, 0, 1]])	#rotation matrix where positive angle is counter-clockwise rotation
		test_point= np.dot(test_point,R )	#rotation 

		try:
			x= test_point[:,0]	#local to each source
			y= test_point[:,1]	#local to each source
			z= test_point[:,2]	#local to each source
		except IndexError:	#runs if "sources" is a 1D array instead of a 2D array
			x= test_point[0]	#local to each source
			y= test_point[1]	#local to each source
			z= test_point[2]	#local to each source
		try:
			rate= sources[:,3]
		except IndexError:	#runs if "sources" is a 1D array instead of a 2D array
			rate= sources[3]

		ya, yb, yc= stability["sigy"][0], stability["sigy"][1], stability["sigy"][2]
		za, zb, zc= stability["sigz"][0], stability["sigz"][1], stability["sigz"][2]
		
		sigy= ya*x*(1+yb*x)**(-yc)
		sigz= za*x*(1+zb*x)**(-zc)
		C_xyz= ((rate/speed)/(2*np.pi*sigy*sigz))*np.exp(-y**2/(2*sigy**2))*np.exp(-z**2/(2*sigz**2))*(x>0.0)	#if it is behind the source wrt the wind set equal to zero
		C_xyz= C_xyz*(C_xyz>.01)

		try:
			C_xyz= sum(C_xyz)
		except TypeError:	#runs if "sources" is a 1D array instead of a 2D array
			C_xyz=C_xyz     

		return(C_xyz)


#generate robot data
robot_data=[]
discretization=0.5 #meters
x=wind_d["frame"]["x"][0]
for i in range(int((wind_d["frame"]["x"][1]-wind_d["frame"]["x"][0])/discretization)):
	x=x+discretization
	y=np.sin(x/10)*20
	z=0
	C_xyz=concentration(x,y,z,sources)
	wind_speed=0
	wind_azimuth=0
	robot_data_i=[x, y, z, C_xyz, speed, azimuth]
	robot_data.append(robot_data_i)


with open(data_out, 'w') as outfile:
    json.dump(robot_data, outfile)


