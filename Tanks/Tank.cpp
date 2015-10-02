#include "StdAfx.h"
#include "Renderer.h"
#include "GraphicObjectVisitor.h"
#include "GraphicObjectsFactory.h"
#include "Bullet.h"
#include "Tank.h"

size_t loadsDefaultCount         = 5;
size_t bulletsInLoadDefaultCount = 20;
size_t defaultHealthLevel        = 100;

Tank::Tank()
{
	isSkidding_     = false;
	loadsCounter_   = loadsDefaultCount;
	bulletsCounter_ = bulletsInLoadDefaultCount;
	health_         = defaultHealthLevel;
	destructible_   = true;
}

void Tank::Fire()
{
	if( ! bulletsCounter_ )
	{
		return;
	}

	--bulletsCounter_;
	GraphicObjectsFactory goFactory;
	Bullet::Ptr bullet = goFactory.CreateBullet();
	bullet->SetCoordinates( coords_ );
	bullet->Fly( lastMoveDirection_ );
}

void Tank::Skid()
{
	isSkidding_ = true;
}

bool Tank::IsSkidding()
{
	return isSkidding_;
}

void Tank::Reload()
{
	if( ! loadsCounter_ )
	{
		return;
	}

	--loadsCounter_;
	bulletsCounter_ = bulletsInLoadDefaultCount;
}

void Tank::DrawImpl(Renderer* renderer)
{
	renderer->Render(this);
}

void Tank::Accept( GraphicObjectVisitor& visitor )
{
	visitor.Visit(this);
}

void* Tank::get_type_static()
{
	static int type=0;
	return &type;
}

void* Tank::get_type()
{
	return get_type_static();
}