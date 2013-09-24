#pragma once

#include "CriticalSection.h" //For backward compatibility
#include <boost/thread/once.hpp>


	namespace sync
	{
		//-------------------------------------
		template<class SyncObjT>
		class ObjectLevelLockable{  // Object level blocking
		public:
			friend class LockT;

			ObjectLevelLockable(){}

			template< typename T >
			ObjectLevelLockable( T val )
				:m_syncObj( val )
			{}

			template< typename T, typename T2 >
			ObjectLevelLockable( T val, T2 val2 )
				:m_syncObj( val, val2 )
			{}

			template<class LocableT>
			class LockT
			{
			public:
				LockT( const LocableT &c )
					: m_lackable(c)
				{
					m_lackable.m_syncObj.Enter();
				};

				template<class ParamT>
				LockT( const LocableT &c, ParamT param )
					: m_lackable(c)
				{
					m_lackable.m_syncObj.Enter( param );
				};

				~LockT()
				{
					m_lackable.m_syncObj.Leave();
				};

			private:
				LocableT const &m_lackable;

				LockT(const LockT &c);
				LockT& operator=(const LockT &c);
			};

			typedef LockT< ObjectLevelLockable > Lock;
		private:
			mutable SyncObjT m_syncObj;
		};
		//-------------------------------------

		template <class SyncObjT>
		class ClassLevelLockable
		{
		public:
			class Lock;
			friend class Lock;

			class Lock
			{
			public:
				Lock()
				{
					boost::call_once(InitSyncObj, sm_initFlag);
					sm_syncObj->Enter();
				}

				explicit Lock(const ClassLevelLockable&)
				{
					boost::call_once(InitSyncObj, sm_initFlag);
					sm_syncObj->Enter();
				}

				~Lock()
				{
					sm_syncObj->Leave();
				}

			private:
				Lock(const Lock&);
				Lock& operator=(const Lock&);
			};

		private:
			static void InitSyncObj()
			{
				sm_syncObj = new SyncObjT();
				atexit(DoneSyncObj);
			}

			static void DoneSyncObj()
			{
				delete sm_syncObj;
			}

			static SyncObjT* sm_syncObj;
			static boost::once_flag sm_initFlag;
		};

		template <class SyncObjT> typename SyncObjT* ClassLevelLockable<SyncObjT>::sm_syncObj = nullptr;
		template <class SyncObjT> boost::once_flag ClassLevelLockable<SyncObjT>::sm_initFlag = BOOST_ONCE_INIT;
		//-------------------------------------

		typedef sync::ObjectLevelLockable< sync::CriticalSection > CSlock;
	}



