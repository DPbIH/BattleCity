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
	void BuildObstacle( const Coordinates& coord );
	void BuildEnemy( const Coordinates& coord );
	void BuildPlayer( const Coordinates& coord );
	Level::Ptr GetLevel();

private:
	GraphicObjectsFactory::Ptr factory_;
	Level::Ptr level_;
};