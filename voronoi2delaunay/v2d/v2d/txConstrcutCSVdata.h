#pragma once
#include <vector>


class txConstrcutCSVdata
{
public:
	typedef struct txPoint3D{
		double x, y, z;
	}txPoint3D;

	typedef struct txPoint3I{
		long x, y, z;
	} txPoint3I;

public:
	txConstrcutCSVdata(char *csvf);
	~txConstrcutCSVdata(void);

	void DumpOFFFile(char *offf);

private:
	void ConstructDelaunay();


private:
	std::vector<txPoint3D> m_Points;
	std::vector<txPoint3I> m_PointsI;
	double m_Scale;

	std::vector<size_t> m_Indices;
};

