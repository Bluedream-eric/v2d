// v2d.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <numeric>
#include <vector>
#include <utility>

#include <boost/random/mersenne_twister.hpp>
#include <boost/timer.hpp>

#include <boost/polygon/voronoi.hpp>
typedef boost::polygon::default_voronoi_builder VB_BOOST;
typedef boost::polygon::voronoi_diagram<double> VD_BOOST;

#include "txDelaunayConstructor.h"
#include "txV2DUtil.h"

#include "txConstrcutCSVdata.h"

const int RANDOM_SEED = 27;



void run_boost()
{
	boost::mt19937 gen(RANDOM_SEED);

	VB_BOOST vb;
	VD_BOOST vd;
	//vb.insert_point(1,1);
	//vb.insert_point(2,1);
	//vb.insert_point(2,3);
	//vb.insert_point(1,2);
	//vb.insert_point(3,2);
	
	int numpoints = 5000;

	int coordscale = 1;

	std::vector<int> psites;
	psites.reserve(numpoints*2);
	for (int i=0; i<numpoints; i++) {
		int p0 = static_cast<int>(gen());
		int p1 = static_cast<int>(gen());
		p0/=coordscale;
		p1/=coordscale;
		psites.push_back(p0);
		psites.push_back(p1);
		vb.insert_point(p0,p1);
	}
	vb.construct(&vd);
	txDelaunayConstructor debuilder(vb, vd);
	OutPutDelaunayTrianglOFF(psites,debuilder.GetIndexes(),"delaunay10000.off");
}


int _tmain(int argc, _TCHAR* argv[])
{
	//run_boost();

	// Construct Delaunay from csv file
	txConstrcutCSVdata csv("di.csv");
	csv.DumpOFFFile("diDelaunay.off");


	return 0;
}


