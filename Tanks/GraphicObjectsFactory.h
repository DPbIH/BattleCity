#pragma once

#include "Bullet.h"
#include "Tank.h"
#include "Terrain.h"
#include "Mine.h"
#include "GraphicObjectBase.h"

#include <boost/shared_ptr.hpp>

class GraphicObjectsFactory
{
public:
	typedef boost::shared_ptr<GraphicObjectsFactory> Ptr;

	virtual ~GraphicObjectsFactory();
	Bullet::Ptr CreateBullet();
	Tank::Ptr CreateTank();
	Terrain::Ptr CreateTerrain( Terrain::TerrainType type );
	Mine::Ptr CreateMine();

private:
	virtual Bullet::Ptr CreateBulletImpl();
	virtual Tank::Ptr CreateTankImpl();
	virtual Terrain::Ptr CreateTerrainImpl( Terrain::TerrainType type );
	virtual Mine::Ptr CreateMineImpl();
	void OnNewGraphicObject( const GraphicObjectBase::Ptr& newObj );

};