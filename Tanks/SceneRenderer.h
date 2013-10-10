#pragma once

#include "Renderer.h"
#include "Coordinates.h"

class Scene;
class GraphicObjectBase;

class SceneRenderer
	: public Renderer
{
public:
	SceneRenderer( Scene* scene );
	void Render( const Tank* tank );
	void Render( const Bullet* bullet );
	void Render( const Terrain* tank );
	void Render( const Mine* mine );

private:
	void Print( const Coordinates& pos, char ch, WORD color );
	Coordinates GetRenderPositionForObject( const GraphicObjectBase* obj );

	Scene* scene_;

};