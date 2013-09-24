#pragma once

#include "Coordinates.h"
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

enum Direction { South, North, East, West };

class Renderer;
class GraphicObjectVisitor;

class GraphicObjectBase
	: boost::noncopyable
{
public:
	typedef boost::shared_ptr<GraphicObjectBase> Ptr;

	GraphicObjectBase();
	virtual ~GraphicObjectBase() = 0 {}

	void Draw( Renderer* renderer );
	void Move( size_t delta, Direction direction );
	bool IsGarbage();
	void IsGarbage( bool isGarbage );
	bool Hidden();
	void Hide();
	void Show();
	virtual void Accept( GraphicObjectVisitor& visitor ) = 0;
	Coordinates GetCoordinates() const;
	void SetCoordinates( const Coordinates& newPosition );
	void SetCoordinates( size_t newX, size_t newY );

protected:
	Direction lastMoveDirection_;
	Coordinates coords_;

private:
	virtual void DrawImpl( Renderer* renderer ) = 0;
	virtual void HandleCollision( GraphicObjectBase* ){}

	bool isGarbage_;
	bool isHidden_;

};