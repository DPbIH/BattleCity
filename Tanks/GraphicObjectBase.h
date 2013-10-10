#pragma once

#include "Dispatchable.h"
#include "GlobalDeclarations.h"
#include "Coordinates.h"
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

class Renderer;
class GraphicObjectVisitor;

class GraphicObjectBase
	: public Dispatchable
	, boost::noncopyable
{
public:
	typedef boost::shared_ptr<GraphicObjectBase> Ptr;

	GraphicObjectBase();
	virtual ~GraphicObjectBase() = 0 {}

	void Draw( Renderer* renderer );
	void Move( size_t delta, GlobalDeclarations::Direction direction );

	bool IsGarbage();
	void IsGarbage( bool isGarbage );
	bool Hidden();
	void Hide();
	void Show();

	void Damage( GraphicObjectBase& other );
	void GetDamaged( size_t damagePoints );
	void Die();
	void Explode();

	Coordinates GetCoordinates() const;
	void SetCoordinates( const Coordinates& newPosition );
	void SetCoordinates( size_t newX, size_t newY );

	virtual void Accept( GraphicObjectVisitor& visitor ) = 0;

	size_t UID();

protected:
	GlobalDeclarations::Direction lastMoveDirection_;
	Coordinates coords_;

	size_t damagePoints_;
	size_t health_;

	bool damageable_;

private:
	virtual void DrawImpl( Renderer* renderer ) = 0;
	void HandleCollision( GraphicObjectBase* other );

	static size_t CreateUID();
	static size_t newInstanceCounter_;

	bool isGarbage_;
	bool isHidden_;

	const size_t uid_;

};