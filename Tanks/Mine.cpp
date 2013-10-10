#include "stdafx.h"
#include "GraphicObjectVisitor.h"
#include "Renderer.h"
#include "Mine.h"

Mine::Mine()
{
	damageable_ = false;
	health_ = 0;
	damagePoints_ = 50;
}

void Mine::Accept( GraphicObjectVisitor& visitor )
{
	visitor.Visit(this);
}

void Mine::DrawImpl( Renderer* renderer )
{
	renderer->Render(this);
}

void* Mine::get_type_static()
{
	static int type=0;
	return &type;
}

void* Mine::get_type()
{
	return get_type_static();
}