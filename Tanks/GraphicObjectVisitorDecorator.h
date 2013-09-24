#pragma once

#include "GraphicObjectVisitor.h"

class GraphicObjectVisitorDecorator
	: public GraphicObjectVisitor
{
public:
	GraphicObjectVisitorDecorator( GraphicObjectVisitor* decorated );
	virtual ~GraphicObjectVisitorDecorator() = 0 {}
	virtual void Visit( Tank* tank );
	virtual void Visit( Bullet* bullet );
	virtual void Visit( Obstacle* obstacle );

protected:
	GraphicObjectVisitor* decorated_;

};