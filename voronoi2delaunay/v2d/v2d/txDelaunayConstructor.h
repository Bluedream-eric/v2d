#pragma once
#include <vector>


#include <boost/polygon/voronoi.hpp>
typedef boost::polygon::default_voronoi_builder VB_BOOST;
typedef boost::polygon::voronoi_diagram<double> VD_BOOST;

class txDelaunayConstructor
{
public:
	txDelaunayConstructor(VB_BOOST &vb, VD_BOOST &vd);
	~txDelaunayConstructor(void);

	std::vector<size_t> &GetIndexes() { return indexes; };

private:

	VB_BOOST &mVB;
	VD_BOOST &mVD;
	std::vector<size_t> indexes;
};

