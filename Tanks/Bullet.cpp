#include "stdafx.h"
#include "GraphicObjectVisitor.h"
#include "Renderer.h"
#include "Bullet.h"

Bullet::Bullet()
{
	damagePoints_ = 10;
}

Bullet::~Bullet()
{
	InterruptFlyThread();
}

void Bullet::DrawImpl(Renderer* renderer)
{
	renderer->Render(this);
}

void Bullet::Fly( GlobalDeclarations::Direction direction )
{
	direction_ = direction;
	StartFlyThread();
}

void Bullet::StartFlyThread()
{
	flyThread_ = boost::thread(&Bullet::FlyThreadProc, this);
}

void Bullet::InterruptFlyThread()
{
	flyThread_.interrupt();
}

void Bullet::FlyThreadProc()
{
	static const unsigned int flyDistance = 20;
	static const int delta = 1;
	static const unsigned int timeout = 30;

	for( unsigned int i = 0; i < flyDistance; ++i )
	{
		Move( delta, direction_ );
		Sleep(100);
	}

	IsGarbage(true);
}

void Bullet::Accept( GraphicObjectVisitor& visitor )
{
	visitor.Visit(this);
}

void* Bullet::get_type_static()
{
	static int type=0;
	return &type;
}

void* Bullet::get_type()
{
	return get_type_static();
}