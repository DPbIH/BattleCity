
#include "StdAfx.h"
#include "CriticalSection.h"



namespace sync
{
	CriticalSectionLock::CriticalSectionLock( PCRITICAL_SECTION cs )
		:critSectPtr_( cs )
	{
	}

	void CriticalSectionLock::Enter() const
	{
		EnterCriticalSection( critSectPtr_ );
	}

	void CriticalSectionLock::Leave() const
	{
		LeaveCriticalSection( critSectPtr_ );
	}

	CriticalSection::CriticalSection()
		:CriticalSectionLock( &critSect_ )
	{
		InitializeCriticalSection( &critSect_ );
	}

	CriticalSection::~CriticalSection()
	{
		DeleteCriticalSection( &critSect_ );
	}
}
