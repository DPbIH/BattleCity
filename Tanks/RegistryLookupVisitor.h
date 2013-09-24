#pragma once

#include "GraphicObjectVisitor.h"

class Tank;
class Bullet;
class Obstacle;
class GraphicObjectBase;

class RegistryLookupVisitor
	: public GraphicObjectVisitor
{
public:
	RegistryLookupVisitor();
	void SetLookupPos( unsigned int x, unsigned int y );

	void Visit( Bullet* bullet );
	void Visit( Tank* tank );
	void Visit( Obstacle* obstacle );

	GraphicObjectBase* GetResult();

private:
	void DoVisit( GraphicObjectBase* obj );

	 unsigned int x_, y_;
	 GraphicObjectBase* foundObj_;
};