#pragma once

class Dispatchable
{
public:
	virtual ~Dispatchable() { }
	virtual void * get_type() { return 0; }

};