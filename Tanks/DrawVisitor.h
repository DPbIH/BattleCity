#pragma once

#include "GraphicObjectVisitor.h"


class Tank;
class Bullet;
class Obstacle;
class GraphicObjectBase;
class Renderer;

class DrawVisitor
	: public GraphicObjectVisitor
{
public:
	DrawVisitor(Renderer* renderer);
	void Visit( Tank* );
	void Visit( Bullet* );
	void Visit( Obstacle* );

private:
	Renderer* renderer_;

};