#pragma once

#include <boost/thread.hpp>
#include "GraphicObjectBase.h"

class Bullet
	: public GraphicObjectBase
{
public:
	typedef boost::shared_ptr<Bullet> Ptr;

	~Bullet();
	void Fly( Direction direction );
	void Accept( GraphicObjectVisitor& visitor );

protected:
	void DrawImpl(Renderer* renderer);

private:
	void StartFlyThread();
	void InterruptFlyThread();
	void FlyThreadProc();

	boost::thread flyThread_;
	mutable Direction direction_;
};