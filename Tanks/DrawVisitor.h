#pragma once

#include "GraphicObjectVisitor.h"


class Tank;
class Bullet;
class Terrain;
class GraphicObjectBase;
class Renderer;

class DrawVisitor
	: public GraphicObjectVisitor
{
public:
	DrawVisitor(Renderer* renderer);
	void Visit( Tank* );
	void Visit( Bullet* );
	void Visit( Terrain* );
	void Visit( Mine* );

private:
	Renderer* renderer_;

};