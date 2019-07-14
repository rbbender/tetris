#include <GLDefs.h>

IGLObject::IGLObject() : m_gl_obj_id(++gl_obj_count) {
	std::cout << "GLObject::CREATED::" << m_gl_obj_id << std::endl;
};

unsigned IGLObject::GetGLObjID() const { return m_gl_obj_id; };

unsigned IGLObject::gl_obj_count = 0;
