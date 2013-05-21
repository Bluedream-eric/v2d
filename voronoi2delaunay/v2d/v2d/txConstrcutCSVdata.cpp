#include "StdAfx.h"
#include "txConstrcutCSVdata.h"
#include <fstream>
#include <string>
#include <sstream>

#include <algorithm>
#include <iomanip>
#include <numeric>
#include <utility>

#include <boost/polygon/voronoi.hpp>
typedef boost::polygon::default_voronoi_builder VB_BOOST;
typedef boost::polygon::voronoi_diagram<double> VD_BOOST;

#include "txDelaunayConstructor.h"
#include "txV2DUtil.h"

void OutPutDelaunayTrianglOFFP(std::vector<txConstrcutCSVdata::txPoint3D> &ptns, std::vector<size_t> &indices, char *f)
{
	FILE *ff = fopen(f,"w");

	fprintf(ff,"OFF\n");

	fprintf(ff,"%d\t%d\t%d\n", ptns.size(), indices.size()/3, 0);

	for (size_t i=0; i<ptns.size(); i++) {
		fprintf(ff, "%f\t%f\t%f\n", ptns[i].x, ptns[i].y, ptns[i].z);
	}

	for (size_t i=0; i<indices.size()/3; i++) {
		fprintf(ff,"%d\t%d\t%d\t%d\n",3,
			indices[i*3],
			indices[i*3+1],
			indices[i*3+2]);
	}

	fclose(ff);
}


txConstrcutCSVdata::txConstrcutCSVdata(char *f)
{
	// hard code the scale to 10
	m_Scale = 10.0;

	std::ifstream infile(f);
	double x, y, z;
	std::string line;
	txPoint3D fP;
	txPoint3D min;
	txPoint3D max;

	std::getline(infile,line);
	std::istringstream isso(line);
	isso>>x>>y>>z;
	min.x = max.x = x;
	min.y = max.y = y;
	min.z = max.z = z;

	fP.x = x; fP.y = y; fP.z = z;
	this->m_Points.push_back(fP);

	while(std::getline(infile,line)) {
		std::istringstream iss(line);
		if(!(iss>>x>>y>>z)) { break;}
		
		fP.x = x; fP.y = y; fP.z = z;
		this->m_Points.push_back(fP);

		min.x = x<min.x?x:min.x;
		min.y = y<min.y?y:min.y;
		min.z = z<min.z?z:min.z;

		max.x = x>max.x?x:max.x;
		max.y = y>max.y?y:max.y;
		max.z = z>max.z?z:max.z;
	}



	// change the double in to integar to make the algorithm more robust!
	m_PointsI.reserve(m_Points.size());
	txPoint3I iP;
	for (size_t i=0; i<m_Points.size(); i++) {
		iP.x = (long) (m_Points[i].x-min.x);
		iP.y = (long) (m_Points[i].y-min.y);
		iP.z = (long) (m_Points[i].z-min.z);
		m_PointsI.push_back(iP);
	}

}


txConstrcutCSVdata::~txConstrcutCSVdata(void)
{
}

void txConstrcutCSVdata::DumpOFFFile(char *offf)
{
	ConstructDelaunay();
	OutPutDelaunayTrianglOFFP(this->m_Points,this->m_Indices,offf);
}

void txConstrcutCSVdata::ConstructDelaunay()
{
	VB_BOOST vb;
	VD_BOOST vd;

	for (size_t i=0; i<m_PointsI.size(); i++) {
		vb.insert_point(m_PointsI[i].x, m_PointsI[i].y);
	}
	vb.construct(&vd);
	txDelaunayConstructor dBuilder(vb,vd);
	m_Indices = dBuilder.GetIndexes();
	m_Indices.reserve(dBuilder.GetIndexes().size());
	for (size_t i=0; i<dBuilder.GetIndexes().size(); i++) {
		m_Indices.push_back(dBuilder.GetIndexes()[i]);
	}
}
