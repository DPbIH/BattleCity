#pragma once

#include "GraphicObjectBase.h"

class Tank:
	public GraphicObjectBase
{
public:
	typedef boost::shared_ptr<Tank> Ptr;

	Tank();
	void Fire();
	void Skid();
	bool IsSkidding();
	void Reload();

	void Accept( GraphicObjectVisitor& visitor );
	static void* get_type_static();
	void* get_type();

private:
	void DrawImpl(Renderer* renderer);

	bool isSkidding_;
	size_t bulletsCounter_;
	size_t loadsCounter_;

};