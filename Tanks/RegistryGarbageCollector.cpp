#include "stdafx.h"
#include "Tank.h"
#include "Bullet.h"
#include "Terrain.h"
#include "Mine.h"
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

void RegistryGarbageCollector::Visit( Terrain* terrain )
{
	DoVisit(terrain);
}

void RegistryGarbageCollector::Visit( Mine* mine )
{
	DoVisit(mine);
}

void RegistryGarbageCollector::DoVisit( GraphicObjectBase* obj )
{
	if( obj->IsGarbage() )
	{
		registry_->Remove( obj->UID() );
	}
}