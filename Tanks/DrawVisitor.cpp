#include "stdafx.h"
#include "Tank.h"
#include "Bullet.h"
#include "Obstacle.h"
#include "GraphicObjectBase.h"
#include "Renderer.h"
#include "DrawVisitor.h"

DrawVisitor::DrawVisitor( Renderer* renderer )
	: renderer_(renderer)
{
}

void DrawVisitor::Visit( Bullet* bullet )
{
	bullet->Draw( renderer_ );
}

void DrawVisitor::Visit( Tank* tank )
{
	tank->Draw( renderer_ );
}

void DrawVisitor::Visit( Obstacle* obstacle )
{
	obstacle->Draw( renderer_ );
}