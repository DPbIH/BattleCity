#include "stdafx.h"
#include "GraphicObjectVisitor.h"
#include "Renderer.h"
#include "Terrain.h"

Terrain::Terrain( TerrainType type )
	: type_(type)
{
	switch(type_)
	{
	case Ice:
	case Grass:
		damageable_   = false;
		health_       = 0;
		damagePoints_ = 0;
		break;

	case Rock:
		damageable_   = true;
		health_       = 100;
		damagePoints_ = 0;
		break;
	}
}

void Terrain::Accept( GraphicObjectVisitor& visitor )
{
	visitor.Visit(this);
}

void Terrain::DrawImpl(Renderer* renderer)
{
	renderer->Render(this);
}

void* Terrain::get_type_static()
{
	static int type=0;
	return &type;
}

void* Terrain::get_type()
{
	return get_type_static();
}

Terrain::TerrainType Terrain::Type() const
{
	return type_;
}