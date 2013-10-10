#pragma once

#include "Coordinates.h"
#include "GraphicObjectsFactory.h"
#include "LevelBuilder.h"
#include <vector>

class LevelMapFileParser
{
public:
	LevelMapFileParser( const LevelBuilder::Ptr& builder );

	void Parse( const char* fileName );

private:
	typedef std::vector<char> ContentBufT;

	void ParseImpl( const char* fileName );
	ContentBufT ReadFileToBuffer( const char* fileName );
	void ProcessContent( ContentBufT content );
	void ProcessEntry( char entry, const Coordinates& coord );

	void OnParseBegin();
	void OnNewRock( const Coordinates& coord);
	void OnNewGrass( const Coordinates& coord);
	void OnNewIce( const Coordinates& coord);
	void OnNewEnemy( const Coordinates& coord);
	void OnNewPlayer( const Coordinates& coord);
	void OnNewMine( const Coordinates& coord);
	void OnParseEnd();

	const LevelBuilder::Ptr builder_;

};