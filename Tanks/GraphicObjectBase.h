#pragma once

#include "IMovable.h"
#include "Locatable2D.h"
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

class Renderer;
class GraphicObjectVisitor;

class GraphicObjectBase
	: public IMovable
	, public Locatable2D
	, boost::noncopyable
{
public:
	typedef boost::shared_ptr<GraphicObjectBase> Ptr;

	GraphicObjectBase();
	virtual ~GraphicObjectBase() = 0 {}

	void Draw( Renderer* renderer );
	void Move( int delta, Direction direction );
	void PinTo( unsigned int x, unsigned int y );
	bool IsGarbage();
	void IsGarbage( bool isGarbage );
	bool Hidden();
	void Hide();
	void Show();
	virtual void Accept( GraphicObjectVisitor& visitor ) = 0;

protected:
	Direction lastMoveDirection_;

private:
	virtual void DrawImpl( Renderer* renderer ) = 0;
	virtual void HandleCollision( GraphicObjectBase* ){}

	bool isGarbage_;
	bool isHidden_;

};