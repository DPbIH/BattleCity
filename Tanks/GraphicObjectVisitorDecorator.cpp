#include "stdafx.h"
#include "GraphicObjectVisitorDecorator.h"

GraphicObjectVisitorDecorator::GraphicObjectVisitorDecorator( GraphicObjectVisitor* decorated )
	: decorated_(decorated)
{
}

void GraphicObjectVisitorDecorator::Visit( Tank* tank )
{
	decorated_->Visit(tank);
}

void GraphicObjectVisitorDecorator::Visit( Bullet* bullet )
{
	decorated_->Visit(bullet);
}

void GraphicObjectVisitorDecorator::Visit( Terrain* terrain )
{
	decorated_->Visit(terrain);
}

void GraphicObjectVisitorDecorator::Visit( Mine* mine )
{
	decorated_->Visit(mine);
}