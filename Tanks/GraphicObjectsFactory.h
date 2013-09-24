#pragma once

#include "Bullet.h"
#include "Tank.h"
#include "Obstacle.h"
#include "GraphicObjectBase.h"

class GraphicObjectsFactory
{
public:
	virtual ~GraphicObjectsFactory();
	Bullet::Ptr CreateBullet();
	Tank::Ptr CreateTank();
	Obstacle::Ptr CreateObstacle();

private:
	virtual Bullet::Ptr CreateBulletImpl();
	virtual Tank::Ptr CreateTankImpl();
	virtual Obstacle::Ptr CreateObstacleImpl();
	void OnNewGraphicObject( const GraphicObjectBase::Ptr& newObj );

};