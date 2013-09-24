#include "stdafx.h"
#include "GraphicObjectVisitor.h"
#include "Renderer.h"
#include "Obstacle.h"

void Obstacle::Accept( GraphicObjectVisitor& visitor )
{
	visitor.Visit(this);
}

void Obstacle::DrawImpl(Renderer* renderer)
{
	renderer->Render(this);
}