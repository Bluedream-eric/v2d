#include "StdAfx.h"
#include "txV2DUtil.h"


void OutPutDelaunayTrianglOFF(std::vector<int> &points, std::vector<size_t> &indexes, char *filename)
{
	FILE *f = fopen(filename, "w");

	fprintf(f,"OFF\n");

	fprintf(f,"%d\t%d\t%d\n", points.size()/2, indexes.size()/3, 0);

	for (size_t i=0; i<points.size()/2; i++) {
		fprintf(f,"%d\t%d\t%d\n", points[i*2], points[i*2+1], 0);
	}

	for (size_t i=0; i<indexes.size()/3; i++) {
		fprintf(f,"%d\t%d\t%d\t%d\n", 3,
			indexes[i*3],
			indexes[i*3+1],
			indexes[i*3+2]);
	}

	fclose(f);
}
