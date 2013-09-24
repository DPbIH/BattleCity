#pragma once

#include <boost/noncopyable.hpp>

class Command
	: boost::noncopyable
{
public:
	virtual ~Command (){};
	virtual void Execute () = 0;
};