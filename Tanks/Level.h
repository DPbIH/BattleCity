#pragma once

#include "Player.h"
#include "Tank.h"
#include "Scene.h"
#include "Terrain.h"
#include "Mine.h"
#include <boost/shared_ptr.hpp>

class Level
{
public:
	typedef boost::shared_ptr<Level> Ptr;

	Level();
	void AddPlayer( const Player::Ptr& player );
	void AddEnemy( const Tank::Ptr& enemy );
	void AddTerrain( const Terrain::Ptr& terrain );
	void AddMine( const Mine::Ptr& mine );
	void RenderScene();
	Player::Ptr Player();

private:
	void InitScene();
	void AddImpl( const GraphicObjectBase::Ptr& go );

	Player::Ptr player_;
	Scene scene;
};