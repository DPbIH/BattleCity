#include "stdafx.h"
#include "GraphicObjectBase.h"
#include "GraphicObjectsRegistry.h"
#include "RegistryLookupVisitor.h"
#include "Helpers.h"

namespace Helpers
{
	GraphicObjectBase* FindGraphicObjectByPosition( const Coordinates& pos )
	{
		RegistryLookupVisitor finder;
		finder.SetLookupPos(pos);
		GORegistry().Accept( finder );

		return finder.GetResult();
	}
}