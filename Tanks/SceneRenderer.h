#pragma once

#include "Renderer.h"

class Scene;
class GraphicObjectBase;

class SceneRenderer
	: public Renderer
{
public:
	SceneRenderer( Scene* scene );
	void Render( const Tank* tank );
	void Render( const Bullet* bullet );
	void Render( const Obstacle* tank );

private:
	void Print( size_t posX, size_t posY, char ch, WORD color );
	void GetRenderPositionForObject( const GraphicObjectBase* obj, size_t& posX, size_t& posY );

	Scene* scene_;

};