#include "stdafx.h"
#include "Tank.h"
#include "Bullet.h"
#include "Obstacle.h"
#include "GraphicObjectBase.h"
#include "GraphicObjectsRegistry.h"
#include "RegistryGarbageCollector.h"

RegistryGarbageCollector::RegistryGarbageCollector(GraphicObjectsRegistry* registry)
	: registry_(registry)
{
	assert( registry_ );
}

void RegistryGarbageCollector::Visit( Tank* tank )
{
	DoVisit(tank);
}

void RegistryGarbageCollector::Visit( Bullet* bullet)
{
	DoVisit(bullet);
}

void RegistryGarbageCollector::Visit( Obstacle* obstacle )
{
	DoVisit(obstacle);
}

void RegistryGarbageCollector::DoVisit( GraphicObjectBase* obj )
{
	if( obj->IsGarbage() )
	{
		registry_->Remove( obj->UID() );
	}
}