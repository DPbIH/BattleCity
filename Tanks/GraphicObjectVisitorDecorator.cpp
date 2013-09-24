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

void GraphicObjectVisitorDecorator::Visit( Obstacle* obstacle )
{
	decorated_->Visit(obstacle);
}