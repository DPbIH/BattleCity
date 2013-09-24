#pragma once

struct Coordinates
{
	Coordinates();
	Coordinates( size_t x, size_t y );
	Coordinates( const Coordinates& other );
	Coordinates& operator=( const Coordinates& other );
	Coordinates& operator+( const Coordinates& other );
	Coordinates& operator-( const Coordinates& other );
	Coordinates& operator<( const Coordinates& other );
	size_t X, Y;
};

bool operator==( const Coordinates& lhs, const Coordinates& rhs );