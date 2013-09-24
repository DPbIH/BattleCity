#include "StdAfx.h"
#include "Renderer.h"
#include "GraphicObjectVisitor.h"
#include "GraphicObjectsFactory.h"
#include "Bullet.h"
#include "Tank.h"

void Tank::Fire()
{
	GraphicObjectsFactory goFactory;
	Bullet::Ptr bullet = goFactory.CreateBullet();
	bullet->SetCoordinates( coords_ );
	bullet->Fly( lastMoveDirection_ );
}

void Tank::DrawImpl(Renderer* renderer)
{
	renderer->Render(this);
}

void Tank::Accept( GraphicObjectVisitor& visitor )
{
	visitor.Visit(this);
}