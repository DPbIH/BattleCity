#pragma once

#include "GraphicObjectBase.h"

class Terrain
	: public GraphicObjectBase
{
public:
	enum TerrainType { Ice, Rock, Grass };

	typedef boost::shared_ptr<Terrain> Ptr;

	Terrain( TerrainType type );
	void Accept( GraphicObjectVisitor& visitor );

	static void* get_type_static();
	void* get_type();

	TerrainType Type() const;

protected:
	void DrawImpl(Renderer* renderer);

private:
	TerrainType type_;

};