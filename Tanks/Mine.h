#pragma once

#include "GraphicObjectBase.h"

class Mine:
	public GraphicObjectBase
{
public:
	typedef boost::shared_ptr<Mine> Ptr;

	Mine();
	void Accept( GraphicObjectVisitor& visitor );
	static void* get_type_static();
	void* get_type();

protected:
	void DrawImpl( Renderer* renderer );

};