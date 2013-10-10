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

Terrain::Ptr GraphicObjectsFactory::CreateTerrain( Terrain::TerrainType type )
{
	Terrain::Ptr terrain = CreateTerrainImpl( type );
	OnNewGraphicObject( terrain );

	return terrain;
}

Mine::Ptr GraphicObjectsFactory::CreateMine()
{
	Mine::Ptr mine = CreateMineImpl();
	OnNewGraphicObject( mine );

	return mine;
}

Bullet::Ptr GraphicObjectsFactory::CreateBulletImpl()
{
	return Bullet::Ptr( new Bullet );
}

Tank::Ptr GraphicObjectsFactory::CreateTankImpl()
{
	return Tank::Ptr( new Tank );
}

Terrain::Ptr GraphicObjectsFactory::CreateTerrainImpl( Terrain::TerrainType type )
{
	return Terrain::Ptr( new Terrain( type ) );
}

Mine::Ptr GraphicObjectsFactory::CreateMineImpl()
{
	return Mine::Ptr( new Mine );
}

void GraphicObjectsFactory::OnNewGraphicObject( const GraphicObjectBase::Ptr& newObj )
{
	GORegistry().Add( newObj->UID(), newObj );
}
