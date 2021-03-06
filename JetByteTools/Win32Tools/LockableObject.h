#pragma once
#ifndef JETBYTE_TOOLS_WIN32_LOCKABLE_OBJECT_INCLUDED__
#define JETBYTE_TOOLS_WIN32_LOCKABLE_OBJECT_INCLUDED__
///////////////////////////////////////////////////////////////////////////////
// File: LockableObject.h
///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2012 JetByte Limited.
//
// This software is provided "as is" without a warranty of any kind. All
// express or implied conditions, representations and warranties, including
// any implied warranty of merchantability, fitness for a particular purpose
// or non-infringement, are hereby excluded. JetByte Limited and its licensors
// shall not be liable for any damages suffered by licensee as a result of
// using the software. In no event will JetByte Limited be liable for any
// lost revenue, profit or data, or for direct, indirect, special,
// consequential, incidental or punitive damages, however caused and regardless
// of the theory of liability, arising out of the use of or inability to use
// software, even if JetByte Limited has been advised of the possibility of
// such damages.
//
///////////////////////////////////////////////////////////////////////////////

#include <wtypes.h>

#include "EmptyBase.h"
#include "ILockableObject.h"
#include "Exception.h"

#if (JETBYTE_LOCKABLE_OBJECT_CHECK_FOR_REENTRANT_USE_GENERATE_CRASH_DUMP == 1)
#include "DebugTrace.h"
#include "MiniDumpGenerator.h"
#endif

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools::Win32
///////////////////////////////////////////////////////////////////////////////

namespace JetByteTools {
namespace Win32 {

///////////////////////////////////////////////////////////////////////////////
// TLockableObject
///////////////////////////////////////////////////////////////////////////////

/// \ingroup Synchronization

template <typename Base>
class TLockableObject : public Base
{
   public :

      typedef TLockableObjectOwner<TLockableObject<Base> > Owner;

      typedef TLockableObjectConditionalOwner<TLockableObject<Base> > ConditionalOwner;

      typedef TLockableObjectPotentialOwner<TLockableObject<Base> > PotentialOwner;

      TLockableObject()
         #if (JETBYTE_LOCKABLE_OBJECT_CHECK_FOR_REENTRANT_USE == 1)
         : m_owningThreadId(0)
         #endif
      {
         #if (JETBYTE_LOCKABLE_OBJECT_USE_CRITICAL_SECTIONS == 0)
         InitializeSRWLock(&m_lock);
         #else
         ::InitializeCriticalSection(&m_lock);
         #endif
      }

      TLockableObject(
         const TLockableObject &rhs) = delete;

      //lint -esym(1509, TLockableObject) Base class destructor not virtual
      #if (JETBYTE_LOCKABLE_OBJECT_USE_CRITICAL_SECTIONS == 1)
      ~TLockableObject()
      {
         ::DeleteCriticalSection(&m_lock);
      }
      #else
      ~TLockableObject() = default;
      #endif

      TLockableObject &operator=(
         const TLockableObject &rhs) = delete;

      bool TryLock()
      {
         #if (JETBYTE_LOCKABLE_OBJECT_CHECK_FOR_REENTRANT_USE == 1)
         #if (JETBYTE_LOCKABLE_OBJECT_USE_CRITICAL_SECTIONS == 0)
            const bool locked = (0 != TryAcquireSRWLockExclusive(&m_lock));
         #else
            const bool locked = (0 != ::TryEnterCriticalSection(&m_lock));
         #endif

         if (locked)
         {
            m_owningThreadId = GetCurrentThreadId();
         }
         else
         {
            CheckForReentrantUse();
         }

         return locked;
         #else
         #if (JETBYTE_LOCKABLE_OBJECT_USE_CRITICAL_SECTIONS == 0)
            return 0 != ::TryAcquireSRWLockExclusive(&m_lock);
         #else
            return 0 != ::TryEnterCriticalSection(&m_lock);
         #endif
         #endif
      }

      void Lock()
      {
         #if (JETBYTE_LOCKABLE_OBJECT_CHECK_FOR_REENTRANT_USE == 1)
         CheckForReentrantUse();
         #endif

         #if (JETBYTE_LOCKABLE_OBJECT_CHECK_FOR_REENTRANT_USE == 1)
         m_owningThreadId = GetCurrentThreadId();
         #endif

         #if (JETBYTE_LOCKABLE_OBJECT_USE_CRITICAL_SECTIONS == 0)
         AcquireSRWLockExclusive(&m_lock);
         #else
         ::EnterCriticalSection(&m_lock);
         #endif
      }

      void Unlock()
      {
         #if (JETBYTE_LOCKABLE_OBJECT_CHECK_FOR_REENTRANT_USE == 1)
         m_owningThreadId = 0;
         #endif

         #if (JETBYTE_LOCKABLE_OBJECT_USE_CRITICAL_SECTIONS == 0)
         ReleaseSRWLockExclusive(&m_lock);
         #else
         ::LeaveCriticalSection(&m_lock);
         #endif
      }

   private :

      #if (JETBYTE_LOCKABLE_OBJECT_USE_CRITICAL_SECTIONS == 0)
      SRWLOCK m_lock;
      #else
      CRITICAL_SECTION m_lock;
      #endif

      #if (JETBYTE_LOCKABLE_OBJECT_CHECK_FOR_REENTRANT_USE == 1)
      DWORD m_owningThreadId;

      void CheckForReentrantUse() const
      {
         if (m_owningThreadId == GetCurrentThreadId())
         {
            #if (JETBYTE_LOCKABLE_OBJECT_CHECK_FOR_REENTRANT_USE_DEBUG_BREAK == 1)
            ::DebugBreak();
            #endif

            #if (JETBYTE_LOCKABLE_OBJECT_CHECK_FOR_REENTRANT_USE_GENERATE_CRASH_DUMP == 1)
            JetByteTools::Win32::OutputEx(_T("WARNING - LockableObject lock recursion detected"));
            JetByteTools::Win32::CMiniDumpGenerator::GenerateDumpHere(_T("LockRecursion"), JetByteTools::Win32::CMiniDumpGenerator::PerDumpTypeMaxDumpLimits);
            #endif

            #if (JETBYTE_LOCKABLE_OBJECT_CHECK_FOR_REENTRANT_USE_EXCEPTION == 1)
            throw CException(
               _T("CLockableObject::CheckForRecursion()"),
               _T("Reentrant use detected."));
            #endif
         }
      }
      #endif
};

class CLockableObject : public TLockableObject<ILockableObject>
{
};

class CSlimLockableObject : public TLockableObject<CEmptyBase>
{
};

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools::Win32
///////////////////////////////////////////////////////////////////////////////

} // End of namespace Win32
} // End of namespace JetByteTools

#endif // JETBYTE_TOOLS_WIN32_LOCKABLE_OBJECT_INCLUDED__

///////////////////////////////////////////////////////////////////////////////
// End of file: LockableObject.h
///////////////////////////////////////////////////////////////////////////////
