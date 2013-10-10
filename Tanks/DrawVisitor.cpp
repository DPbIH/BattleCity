#include "stdafx.h"
#include "Tank.h"
#include "Bullet.h"
#include "Terrain.h"
#include "Mine.h"
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

void DrawVisitor::Visit( Terrain* terrain )
{
	terrain->Draw( renderer_ );
}

void DrawVisitor::Visit( Mine* mine )
{
	mine->Draw( renderer_ );
}