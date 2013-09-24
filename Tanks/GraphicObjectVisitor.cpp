#include "stdafx.h"
#include "GraphicObjectVisitor.h"

GraphicObjectVisitor::GraphicObjectVisitor()
	: interruptionRequested_(false)
{
}

bool GraphicObjectVisitor::InterruptionRequested()
{
	return interruptionRequested_;
}

void GraphicObjectVisitor::RequestInterruption()
{
	interruptionRequested_ = true;
}