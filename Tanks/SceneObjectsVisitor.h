#pragma once

#include "GraphicObjectVisitorDecorator.h"

class Scene;
class GraphicObjectBase;

class SceneObjectsVisitor
	: public GraphicObjectVisitorDecorator
{
	typedef GraphicObjectVisitorDecorator base_t;

public:
	SceneObjectsVisitor( Scene* scene, GraphicObjectVisitor* decorated );
	virtual void Visit( Tank* tank );
	virtual void Visit( Bullet* bullet );
	virtual void Visit( Terrain* terrain );
	virtual void Visit( Mine* mine );

private:
	bool CheckObjectBelongsToScene( GraphicObjectBase* obj );

	Scene* scene_;
};