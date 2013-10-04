#pragma once

#include "Bullet.h"
#include "Tank.h"
#include "Obstacle.h"
#include "GraphicObjectBase.h"

#include <boost/shared_ptr.hpp>

class GraphicObjectsFactory
{
public:
	typedef boost::shared_ptr<GraphicObjectsFactory> Ptr;

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