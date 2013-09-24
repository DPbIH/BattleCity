#include "stdafx.h"
#include "GraphicObjectBase.h"
#include "GraphicObjectsRegistry.h"
#include "RegistryLookupVisitor.h"
#include "Helpers.h"

namespace Helpers
{
	GraphicObjectBase* FindGraphicObjectByPosition( unsigned int posX, unsigned int posY )
	{
		RegistryLookupVisitor finder;
		finder.SetLookupPos(posX, posY);
		GORegistry().Accept( finder );

		return finder.GetResult();
	}
}