#pragma once

#include <boost/noncopyable.hpp>

class Tank;
class Bullet;
class Obstacle;

class GraphicObjectVisitor
	: boost::noncopyable
{
public:
	GraphicObjectVisitor();
	virtual ~GraphicObjectVisitor() = 0 {}
	virtual void Visit( Tank* ) = 0;
	virtual void Visit( Bullet* ) = 0;
	virtual void Visit( Obstacle* ) = 0;

	bool InterruptionRequested();
	void RequestInterruption();

private:
	bool interruptionRequested_;

};