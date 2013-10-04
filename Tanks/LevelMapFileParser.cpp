#include "stdafx.h"
#include <fstream>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include "LevelMapFileParser.h"

const char Enemy    = 'e';
const char Player   = 'p';
const char Obstacle = '#';

LevelMapFileParser::LevelMapFileParser( const LevelBuilder::Ptr& builder )
	: builder_(builder)
{
	assert(builder_);
}

void LevelMapFileParser::Parse( const char* fileName )
{
	OnParseBegin();
	ParseImpl( fileName );
	OnParseEnd();
}

void LevelMapFileParser::ParseImpl( const char* fileName )
{
	ContentBufT content = ReadFileToBuffer(fileName);
	ProcessContent( content );
}

LevelMapFileParser::ContentBufT LevelMapFileParser::ReadFileToBuffer( const char* fileName )
{
	std::ifstream file(fileName);
	if( ! file )
	{
		throw std::exception( "level map file cannot be read" );
	}

	file.seekg(0,std::ios::end);
	std::streampos length = file.tellg();
	file.seekg(0,std::ios::beg);
	ContentBufT buffer( static_cast<ContentBufT::size_type>(length) );
	file.read( &buffer[0], length );
	file.close();

	return buffer;
}

void LevelMapFileParser::ProcessContent( ContentBufT content )
{
	std::vector<ContentBufT> tokens;
	boost::split( tokens, content, boost::is_any_of("\n") );
	size_t x(0), y(0);

	std::vector<ContentBufT>::reverse_iterator rit = tokens.rbegin();
	for( ; rit != tokens.rend(); ++rit )
	{
		ContentBufT& token = *rit;
		for each( auto val in token )
		{
			ProcessEntry( val, Coordinates(x, y) );
			++x;
		}

		x = 0;
		++y;
	}
}

void LevelMapFileParser::ProcessEntry( char entry, const Coordinates& coord )
{
	switch(entry)
	{
	case Obstacle:
		OnNewObstacle(coord);
		break;

	case Enemy:
		OnNewEnemy(coord);
		break;

	case Player:
		OnNewPlayer(coord);
		break;

	default:
		break;
	}
}

void LevelMapFileParser::OnParseBegin()
{
	builder_->BuildLevel();
}

void LevelMapFileParser::OnNewObstacle( const Coordinates& coord)
{
	builder_->BuildObstacle(coord);
}

void LevelMapFileParser::OnNewEnemy( const Coordinates& coord)
{
	builder_->BuildEnemy(coord);
}

void LevelMapFileParser::OnNewPlayer( const Coordinates& coord)
{
	builder_->BuildPlayer(coord);
}

void LevelMapFileParser::OnParseEnd()
{
}