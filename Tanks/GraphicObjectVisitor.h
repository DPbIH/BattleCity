#pragma once

#include <boost/noncopyable.hpp>

class Tank;
class Bullet;
class Terrain;
class Mine;

class GraphicObjectVisitor
	: boost::noncopyable
{
public:
	GraphicObjectVisitor();
	virtual ~GraphicObjectVisitor() = 0 {}
	virtual void Visit( Tank* ) = 0;
	virtual void Visit( Bullet* ) = 0;
	virtual void Visit( Mine* ) = 0;
	virtual void Visit( Terrain* ) = 0;

	bool InterruptionRequested();
	void RequestInterruption();

private:
	bool interruptionRequested_;

};