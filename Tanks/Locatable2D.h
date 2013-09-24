#pragma once

class Locatable2D
{
public:
	Locatable2D();
	Locatable2D( unsigned int x, unsigned int y );
	Locatable2D( const Locatable2D& other );
	void SetPos( unsigned int x, unsigned int y );
	void SetX( unsigned int x );
	void SetY( unsigned int y );
	void GetPos( unsigned int& x, unsigned int& y ) const;
	unsigned int GetX() const;
	unsigned int GetY() const;
	bool Intersects( const Locatable2D& other ) const;

private:
	unsigned int x_, y_;

};