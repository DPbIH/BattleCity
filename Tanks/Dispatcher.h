#pragma once

#include "stdafx.h"

#include <map>
#include <boost/shared_ptr.hpp>

#include "Dispatchable.h"

class Dispatcher
{
	struct BaseFunction
	{
		virtual ~BaseFunction(){}
		virtual void operator()( Dispatchable & obj1, Dispatchable & obj2 ) {}
	};

	template <class DerivedT1, class DerivedT2>
	struct Function : public BaseFunction
	{
		typedef void (*Callback)(DerivedT1 &,DerivedT2 &);
		Callback f;

		Function(Callback f_):f(f_) {}
		virtual void operator()(Dispatchable & obj1, Dispatchable & obj2) { f((DerivedT1&)obj1,(DerivedT2&)obj2); }
	};

	typedef boost::shared_ptr<BaseFunction> BaseFunctionPtr;
	typedef std::pair<void*, void*> Key;
	typedef std::map<Key, BaseFunctionPtr> DispatchMap;

	DispatchMap dispatch_map;
	bool symmetric; // is f(obj1,obj2)==f(obj2,obj1) ?

public:

	Dispatcher(bool s = true ):symmetric(s) {}

	template <class DerivedT1, class DerivedT2>
	void Add(typename Function<DerivedT1,DerivedT2>::Callback f)
	{
		Key type(DerivedT1::get_type_static(),DerivedT2::get_type_static());
		dispatch_map[type].reset (new Function<DerivedT1,DerivedT2>(f) );
	}

	void Call(Dispatchable & obj1, Dispatchable & obj2, bool check_symmetric=true)
	{
		DispatchMap::iterator it;
		Key type(obj1.get_type(),obj2.get_type());

		it=dispatch_map.find(type);
		if (it==dispatch_map.end())
		{
			if (symmetric && check_symmetric)
			{
				return Call(obj2,obj1,false);
			}
			else
			{
				return;
			}
		}

		(*it->second)(obj1,obj2);
	}
};