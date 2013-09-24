#pragma once

#include "GraphicObjectVisitor.h"
#include "Coordinates.h"

class Tank;
class Bullet;
class Obstacle;
class GraphicObjectBase;

class RegistryLookupVisitor
	: public GraphicObjectVisitor
{
public:
	RegistryLookupVisitor();
	void SetLookupPos( const Coordinates& pos );

	void Visit( Bullet* bullet );
	void Visit( Tank* tank );
	void Visit( Obstacle* obstacle );

	GraphicObjectBase* GetResult();

private:
	void DoVisit( GraphicObjectBase* obj );

	 Coordinates lookupPos_;
	 GraphicObjectBase* foundObj_;
};