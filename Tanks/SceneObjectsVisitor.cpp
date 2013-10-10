#include "stdafx.h"
#include "Scene.h"
#include "Tank.h"
#include "Bullet.h"
#include "Terrain.h"
#include "Mine.h"
#include "GraphicObjectBase.h"
#include "SceneObjectsVisitor.h"

#define VISIT_SCENE_OBJECT(obj)				\
	if( CheckObjectBelongsToScene((obj)) )	\
	{										\
		base_t::Visit( (obj) );				\
	}										\

SceneObjectsVisitor::SceneObjectsVisitor( Scene* scene, GraphicObjectVisitor* decorated )
	: GraphicObjectVisitorDecorator(decorated)
	, scene_(scene)
{
	assert( scene );
}

void SceneObjectsVisitor::Visit( Tank* tank )
{
	VISIT_SCENE_OBJECT(tank);
}

void SceneObjectsVisitor::Visit( Bullet* bullet )
{
	VISIT_SCENE_OBJECT(bullet);
}

void SceneObjectsVisitor::Visit( Terrain* terrain )
{
	VISIT_SCENE_OBJECT(terrain);
}

void SceneObjectsVisitor::Visit( Mine* mine )
{
	VISIT_SCENE_OBJECT(mine);
}

bool SceneObjectsVisitor::CheckObjectBelongsToScene( GraphicObjectBase* obj )
{
	return scene_->CheckSceneCoversLevelMapCoord( obj->GetCoordinates() );
}