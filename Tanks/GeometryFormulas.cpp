#include "stdafx.h"
#include <cmath>
#include "GeometryFormulas.h"

namespace Geo
{
	namespace Linear
	{
		unsigned int SegmentLength( int x1, int x2, int y1, int y2, int z1, int z2 )
		{
			return static_cast<unsigned int>(sqrt( pow(double(x2-x1),2) + pow(double(y2-y1),2) + pow(double(z2-z1),2) ));
		}

		unsigned int RectangleArea( unsigned int height, unsigned int width )
		{
			return height * width;
		}
	}
}