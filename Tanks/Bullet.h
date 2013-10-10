#pragma once

#include <boost/thread.hpp>
#include "GlobalDeclarations.h"
#include "GraphicObjectBase.h"

class Bullet
	: public GraphicObjectBase
{
public:
	typedef boost::shared_ptr<Bullet> Ptr;

	~Bullet();
	void Fly( GlobalDeclarations::Direction direction );
	void Accept( GraphicObjectVisitor& visitor );

	static void* get_type_static();
	void* get_type();

protected:
	void DrawImpl(Renderer* renderer);

private:
	void StartFlyThread();
	void InterruptFlyThread();
	void FlyThreadProc();

	boost::thread flyThread_;
	mutable GlobalDeclarations::Direction direction_;
};