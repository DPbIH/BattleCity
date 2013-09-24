#pragma once

#include "Thread.h"

template
	<
		class T,
		class SyncObj = sync::CriticalSection,
			template <class> class ThreadingModel = sync::ClassLevelLockable
	>
class  Singleton
	: private ThreadingModel< SyncObj >
{
public:
	static T& Instance()
	{
		if ( ! m_instance )
		{
			Lock l;
			if ( ! m_instance )
			{
				m_instance = new T();
				atexit( Destruct );
			}
		}

		return *m_instance;
	}

	static void Destruct()
	{
		if ( m_instance )
		{
			Lock l;
			if ( m_instance )
			{
				delete m_instance;
				m_instance = NULL;
			}
		}
	}

protected:
	typedef Singleton SingletonType;

	Singleton(){}
	~Singleton(){}

private:
	static T* m_instance;

	Singleton & operator=(const Singleton &);
	Singleton(const Singleton &);

};

template< class T, class SyncObj, template <class> class ThreadingModel>
typename T* Singleton<T, SyncObj, ThreadingModel>::m_instance = NULL;