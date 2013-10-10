#pragma once

#include "GraphicObjectVisitor.h"

class GraphicObjectsRegistry;
class GraphicObjectBase;

class RegistryGarbageCollector
	: public GraphicObjectVisitor
{
public:
	RegistryGarbageCollector(GraphicObjectsRegistry* registry);
	void Visit( Tank* );
	void Visit( Bullet* );
	void Visit( Terrain* );
	void Visit( Mine* );

private:
	void DoVisit( GraphicObjectBase* obj );

	GraphicObjectsRegistry* registry_;

};