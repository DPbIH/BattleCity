#pragma once

#include <boost/thread.hpp>
#include "GlobalDeclarations.h"
#include "GraphicObjectBase.h"

class Bullet
	: public GraphicObjectBase
{
public:
	typedef boost::shared_ptr<Bullet> Ptr;

	Bullet();
	~Bullet();
	void Fly( GlobalDeclarations::Direction direction );
	void Accept( GraphicObjectVisitor& visitor );

	static void* get_type_static();
	void* get_type();

private:
	void DrawImpl(Renderer* renderer);
	void StartFlyThread();
	void InterruptFlyThread();
	void FlyThreadProc();

	boost::thread flyThread_;
	mutable GlobalDeclarations::Direction direction_;

	size_t lifeCyclesCounter_;
};