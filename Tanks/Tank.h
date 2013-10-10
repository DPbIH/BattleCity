#pragma once

#include "GraphicObjectBase.h"

class Tank:
	public GraphicObjectBase
{
public:
	typedef boost::shared_ptr<Tank> Ptr;

	void Fire();
	void Accept( GraphicObjectVisitor& visitor );

	void Skid(){}
	bool IsSkidding(){return false;}

	static void* get_type_static();
	void* get_type();

protected:
	void DrawImpl(Renderer* renderer);

};