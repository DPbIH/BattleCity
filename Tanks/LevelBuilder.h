#pragma once

#include "Level.h"
#include "GraphicObjectsFactory.h"
#include "Coordinates.h"
#include <boost/shared_ptr.hpp>

class LevelBuilder
{
public:
	typedef boost::shared_ptr<LevelBuilder> Ptr;

	LevelBuilder( const GraphicObjectsFactory::Ptr& factory );
	void BuildLevel();
	void BuildGrass( const Coordinates& coord );
	void BuildIce( const Coordinates& coord );
	void BuildRock( const Coordinates& coord );
	void BuildEnemy( const Coordinates& coord );
	void BuildPlayer( const Coordinates& coord );
	void BuildMine( const Coordinates& coord );
	Level::Ptr GetLevel();

private:
	void BuildTerrain( Terrain::TerrainType type, const Coordinates& coord );

	GraphicObjectsFactory::Ptr factory_;
	Level::Ptr level_;
};