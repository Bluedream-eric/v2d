#include "StdAfx.h"
#include "txDelaunayConstructor.h"

#include <stdio.h>
#include <stdlib.h>





txDelaunayConstructor::txDelaunayConstructor(VB_BOOST &vb, VD_BOOST &vd)
	:mVB(vb)
	,mVD(vd)
{
	const double degenerationRatio = 1.9;
	indexes.reserve((int)vd.num_vertices()*degenerationRatio);

	for (VD_BOOST::const_vertex_iterator it = vd.vertices().begin();
		it!=vd.vertices().end(); ++it) {
			const VD_BOOST::vertex_type &vertex = *it;
			const VD_BOOST::edge_type *edge = vertex.incident_edge();

			std::vector<int> pntscircle;
			pntscircle.reserve(3);
			do {
				if (edge->is_primary()){
					// do sth
					const VD_BOOST::cell_type *cell = edge->cell();
					pntscircle.push_back(cell->source_index());
				}
				edge = edge->rot_next();
			} while(edge!=vertex.incident_edge());

			// construct delaunay from the points circle
			if (pntscircle.size()==3) {
				indexes.insert(indexes.end(), pntscircle.begin(), pntscircle.end());
			} else {
				int si = pntscircle[0];
				//indexes.push_back(si);
				for ( int i=1; i<pntscircle.size()-1; i++) {
					indexes.push_back(si);
					indexes.push_back(pntscircle[i]);
					indexes.push_back(pntscircle[i+1]);
				}
			}
	}



}


txDelaunayConstructor::~txDelaunayConstructor(void)
{
}
