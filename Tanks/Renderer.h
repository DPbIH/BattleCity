#pragma once

class Tank;
class Bullet;
class Obstacle;

class Renderer
{
public:
	virtual ~Renderer() = 0 {}
	virtual void Render( const Tank* tank ) = 0;
	virtual void Render( const Bullet* bullet ) = 0;
	virtual void Render( const Obstacle* tank ) = 0;

};