#include "stdafx.h"
#include "GraphicObjectsRegistry.h"
#include "GraphicObjectsFactory.h"

GraphicObjectsFactory::~GraphicObjectsFactory()
{
}

Bullet::Ptr GraphicObjectsFactory::CreateBullet()
{
	Bullet::Ptr bullet = CreateBulletImpl();
	OnNewGraphicObject( bullet );

	return bullet;
}

Tank::Ptr GraphicObjectsFactory::CreateTank()
{
	Tank::Ptr tank = CreateTankImpl();
	OnNewGraphicObject( tank );

	return tank;
}

Obstacle::Ptr GraphicObjectsFactory::CreateObstacle()
{
	Obstacle::Ptr obstacle = CreateObstacleImpl();
	OnNewGraphicObject( obstacle );

	return obstacle;
}

Bullet::Ptr GraphicObjectsFactory::CreateBulletImpl()
{
	return Bullet::Ptr( new Bullet );
}

Tank::Ptr GraphicObjectsFactory::CreateTankImpl()
{
	return Tank::Ptr( new Tank );
}

Obstacle::Ptr GraphicObjectsFactory::CreateObstacleImpl()
{
	return Obstacle::Ptr( new Obstacle );
}

void GraphicObjectsFactory::OnNewGraphicObject( const GraphicObjectBase::Ptr& newObj )
{
	GORegistry().Add( newObj->UID(), newObj );
}
