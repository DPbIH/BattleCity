#pragma once

#include "Coordinates.h"

class GraphicObjectBase;

namespace Helpers
{
	GraphicObjectBase* FindGraphicObjectByPosition( const Coordinates& pos );
}