#pragma once

enum Direction { North, South, East, West };

class IMovable
{
public:
	virtual void Move( int delta, Direction direction) = 0;
	virtual void PinTo( unsigned int x, unsigned int y ) = 0;
	virtual ~IMovable() = 0 {}
};