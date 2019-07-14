#pragma once
#include <vector>
#include <iostream>

typedef std::vector<unsigned> TCoords;
typedef TCoords::iterator TCoordsIt;
typedef TCoords::const_iterator TCoordsCIt;

class IGLObject {
	static unsigned gl_obj_count;
protected:
	unsigned m_gl_obj_id;
public:
	IGLObject();
	unsigned GetGLObjID() const;
};
