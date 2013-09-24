#pragma once


namespace sync
{
	class CriticalSectionLock
	{
	public:
		CriticalSectionLock( PCRITICAL_SECTION cs );

		void Enter() const;
		void Leave() const;
	private:
		mutable PCRITICAL_SECTION critSectPtr_;

		CriticalSectionLock(const CriticalSectionLock &);
		CriticalSectionLock & operator=(const CriticalSectionLock &);
	};

	class CriticalSection
		:public CriticalSectionLock
	{
	public:
		CriticalSection();
		~CriticalSection();

	private:
		mutable CRITICAL_SECTION critSect_;

		CriticalSection(const CriticalSection &);
		CriticalSection & operator=(const CriticalSection &);
	};
}
