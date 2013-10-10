#pragma once

class Tank;
class Bullet;
class Terrain;
class Mine;

class Renderer
{
public:
	virtual ~Renderer() = 0 {}
	virtual void Render( const Tank* tank ) = 0;
	virtual void Render( const Bullet* bullet ) = 0;
	virtual void Render( const Terrain* terrain ) = 0;
	virtual void Render( const Mine* mine ) = 0;

};