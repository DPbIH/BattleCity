#pragma once

#include "GraphicObjectBase.h"

class Obstacle
	: public GraphicObjectBase
{
public:
	typedef boost::shared_ptr<Obstacle> Ptr;

	void Accept( GraphicObjectVisitor& visitor );

protected:
	void DrawImpl(Renderer* renderer);

};