#pragma once

#include "GraphicObjectBase.h"

class Tank:
	public GraphicObjectBase
{
public:
	typedef boost::shared_ptr<Tank> Ptr;

	void Fire();
	void Accept( GraphicObjectVisitor& visitor );

protected:
	void DrawImpl(Renderer* renderer);

};