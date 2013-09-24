#pragma once

namespace Geo
{
	namespace Linear
	{
		unsigned int SegmentLength( int x1, int x2, int y1 = 0, int y2 = 0, int z1 = 0, int z2 = 0 );
		unsigned int RectangleArea( unsigned int height, unsigned int width );
	}
}