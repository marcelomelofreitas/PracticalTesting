///////////////////////////////////////////////////////////////////////////////
// File: CallbackTimerWheel.cpp
///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2010 JetByte Limited.
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

#include "JetByteTools\Admin\Admin.h"

#include "CallbackTimerWheel.h"
#include "TickCountProvider.h"
#include "Exception.h"
#include "ToString.h"
#include "NullCallbackTimerQueueMonitor.h"
#include "TickCountProvider.h"

#pragma hdrstop

///////////////////////////////////////////////////////////////////////////////
// Using directives
///////////////////////////////////////////////////////////////////////////////

using std::min;

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools::Win32
///////////////////////////////////////////////////////////////////////////////

namespace JetByteTools {
namespace Win32 {

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

static const Milliseconds s_defaultTimerGranularity = 15;

///////////////////////////////////////////////////////////////////////////////
// File level statics
///////////////////////////////////////////////////////////////////////////////

static const CTickCountProvider s_tickProvider;

static CNullCallbackTimerQueueMonitor s_monitor;

///////////////////////////////////////////////////////////////////////////////
// Static helper functions
///////////////////////////////////////////////////////////////////////////////

static size_t CalculateNumberOfTimers(
   const Milliseconds maximumTimeout,
   const Milliseconds timerGranularity);

///////////////////////////////////////////////////////////////////////////////
// CCallbackTimerWheel::Handle
///////////////////////////////////////////////////////////////////////////////

class CCallbackTimerWheel::TimerData
{
   public :

      TimerData();

      TimerData(
         CCallbackTimerWheel::Timer &timer,
         const CCallbackTimerWheel::UserData userData);

      bool DeleteAfterTimeout() const;

      bool CancelTimer();

      void UpdateData(
         CCallbackTimerWheel::Timer &timer,
         const CCallbackTimerWheel::UserData userData);

      void SetTimer(
         TimerData **ppPrevious,
         TimerData *pNext);

      bool HasTimedOut() const;

      void SetDeleteAfterTimeout();

      TimerData *OnTimer();

      void Unlink();

      void AddTimedOutTimers(
         TimerData *pTimers);

      TimerData *PrepareForHandleTimeout();

      TimerData *HandleTimeout();

      TimerData *TimeoutHandlingComplete();

   private :

      TimerData **m_ppPrevious;

      TimerData *m_pNext;

      TimerData *m_pNextTimedout;

      struct Data
      {
         Data();

         Data(
            CCallbackTimerWheel::Timer &timer,
            CCallbackTimerWheel::UserData userData);

         void Clear();

         CCallbackTimerWheel::Timer *pTimer;

         CCallbackTimerWheel::UserData userData;
      };

      TimerData * OnTimer(
         const Data &data);

      Data m_active;

      Data m_timedout;

      bool m_processingTimeout;

      bool m_deleteAfterTimeout;

      /// No copies do not implement
      TimerData(const TimerData &rhs);
      /// No copies do not implement
      TimerData &operator=(const TimerData &rhs);
};

///////////////////////////////////////////////////////////////////////////////
// CCallbackTimerWheel
///////////////////////////////////////////////////////////////////////////////

CCallbackTimerWheel::CCallbackTimerWheel(
   const Milliseconds maximumTimeout)
   :  m_monitor(s_monitor),
      m_maximumTimeout(maximumTimeout),
      m_timerGranularity(s_defaultTimerGranularity),
      m_numTimers(CalculateNumberOfTimers(m_maximumTimeout, m_timerGranularity)),
      m_tickCountProvider(s_tickProvider),
      m_currentTime(m_tickCountProvider.GetTickCount()),
      m_pTimersStart(CreateTimerWheel(m_numTimers)),
      m_pTimersEnd(m_pTimersStart + m_numTimers),
      m_pNow(m_pTimersStart),
      m_pFirstTimerSetHint(0),
      m_numTimersSet(0),
      m_handlingTimeouts(InvalidTimeoutHandleValue)
{

}

CCallbackTimerWheel::CCallbackTimerWheel(
   IMonitorCallbackTimerQueue &monitor,
   const Milliseconds maximumTimeout)
   :  m_monitor(monitor),
      m_maximumTimeout(maximumTimeout),
      m_timerGranularity(s_defaultTimerGranularity),
      m_numTimers(CalculateNumberOfTimers(m_maximumTimeout, m_timerGranularity)),
      m_tickCountProvider(s_tickProvider),
      m_currentTime(m_tickCountProvider.GetTickCount()),
      m_pTimersStart(CreateTimerWheel(m_numTimers)),
      m_pTimersEnd(m_pTimersStart + m_numTimers),
      m_pNow(m_pTimersStart),
      m_pFirstTimerSetHint(0),
      m_numTimersSet(0),
      m_handlingTimeouts(InvalidTimeoutHandleValue)
{

}

CCallbackTimerWheel::CCallbackTimerWheel(
   const Milliseconds maximumTimeout,
   const Milliseconds timerGranularity)
   :  m_monitor(s_monitor),
      m_maximumTimeout(maximumTimeout),
      m_timerGranularity(timerGranularity),
      m_numTimers(CalculateNumberOfTimers(m_maximumTimeout, m_timerGranularity)),
      m_tickCountProvider(s_tickProvider),
      m_currentTime(m_tickCountProvider.GetTickCount()),
      m_pTimersStart(CreateTimerWheel(m_numTimers)),
      m_pTimersEnd(m_pTimersStart + m_numTimers),
      m_pNow(m_pTimersStart),
      m_pFirstTimerSetHint(0),
      m_numTimersSet(0),
      m_handlingTimeouts(InvalidTimeoutHandleValue)
{

}

CCallbackTimerWheel::CCallbackTimerWheel(
   IMonitorCallbackTimerQueue &monitor,
   const Milliseconds maximumTimeout,
   const Milliseconds timerGranularity)
   :  m_monitor(monitor),
      m_maximumTimeout(maximumTimeout),
      m_timerGranularity(timerGranularity),
      m_numTimers(CalculateNumberOfTimers(m_maximumTimeout, m_timerGranularity)),
      m_tickCountProvider(s_tickProvider),
      m_currentTime(m_tickCountProvider.GetTickCount()),
      m_pTimersStart(CreateTimerWheel(m_numTimers)),
      m_pTimersEnd(m_pTimersStart + m_numTimers),
      m_pNow(m_pTimersStart),
      m_pFirstTimerSetHint(0),
      m_numTimersSet(0),
      m_handlingTimeouts(InvalidTimeoutHandleValue)
{

}

CCallbackTimerWheel::CCallbackTimerWheel(
   const Milliseconds maximumTimeout,
   const IProvideTickCount &tickCountProvider)
   :  m_monitor(s_monitor),
      m_maximumTimeout(maximumTimeout),
      m_timerGranularity(s_defaultTimerGranularity),
      m_numTimers(CalculateNumberOfTimers(m_maximumTimeout, m_timerGranularity)),
      m_tickCountProvider(tickCountProvider),
      m_currentTime(m_tickCountProvider.GetTickCount()),
      m_pTimersStart(CreateTimerWheel(m_numTimers)),
      m_pTimersEnd(m_pTimersStart + m_numTimers),
      m_pNow(m_pTimersStart),
      m_pFirstTimerSetHint(0),
      m_numTimersSet(0),
      m_handlingTimeouts(InvalidTimeoutHandleValue)
{

}

CCallbackTimerWheel::CCallbackTimerWheel(
   IMonitorCallbackTimerQueue &monitor,
   const Milliseconds maximumTimeout,
   const IProvideTickCount &tickCountProvider)
   :  m_monitor(monitor),
      m_maximumTimeout(maximumTimeout),
      m_timerGranularity(s_defaultTimerGranularity),
      m_numTimers(CalculateNumberOfTimers(m_maximumTimeout, m_timerGranularity)),
      m_tickCountProvider(tickCountProvider),
      m_currentTime(m_tickCountProvider.GetTickCount()),
      m_pTimersStart(CreateTimerWheel(m_numTimers)),
      m_pTimersEnd(m_pTimersStart + m_numTimers),
      m_pNow(m_pTimersStart),
      m_pFirstTimerSetHint(0),
      m_numTimersSet(0),
      m_handlingTimeouts(InvalidTimeoutHandleValue)
{

}

CCallbackTimerWheel::CCallbackTimerWheel(
   const Milliseconds maximumTimeout,
   const Milliseconds timerGranularity,
   const IProvideTickCount &tickCountProvider)
   :  m_monitor(s_monitor),
      m_maximumTimeout(maximumTimeout),
      m_timerGranularity(timerGranularity),
      m_numTimers(CalculateNumberOfTimers(m_maximumTimeout, m_timerGranularity)),
      m_tickCountProvider(tickCountProvider),
      m_currentTime(m_tickCountProvider.GetTickCount()),
      m_pTimersStart(CreateTimerWheel(m_numTimers)),
      m_pTimersEnd(m_pTimersStart + m_numTimers),
      m_pNow(m_pTimersStart),
      m_pFirstTimerSetHint(0),
      m_numTimersSet(0),
      m_handlingTimeouts(InvalidTimeoutHandleValue)
{

}

CCallbackTimerWheel::CCallbackTimerWheel(
   IMonitorCallbackTimerQueue &monitor,
   const Milliseconds maximumTimeout,
   const Milliseconds timerGranularity,
   const IProvideTickCount &tickCountProvider)
   :  m_monitor(monitor),
      m_maximumTimeout(maximumTimeout),
      m_timerGranularity(timerGranularity),
      m_numTimers(CalculateNumberOfTimers(m_maximumTimeout, m_timerGranularity)),
      m_tickCountProvider(tickCountProvider),
      m_currentTime(m_tickCountProvider.GetTickCount()),
      m_pTimersStart(CreateTimerWheel(m_numTimers)),
      m_pTimersEnd(m_pTimersStart + m_numTimers),
      m_pNow(m_pTimersStart),
      m_pFirstTimerSetHint(0),
      m_numTimersSet(0),
      m_handlingTimeouts(InvalidTimeoutHandleValue)
{

}

CCallbackTimerWheel::~CCallbackTimerWheel()
{
   for (Handles::iterator it = m_handles.begin(); it != m_handles.end(); ++it)
   {
      TimerData *pData = *it;

      delete pData;

#if (JETBYTE_PERF_TIMER_WHEEL_MONITORING == 1)

      m_monitor.OnTimerDeleted();

#endif
   }

   delete [] m_pTimersStart;
}

Milliseconds CCallbackTimerWheel::GetNextTimeout()
{
   Milliseconds nextTimeout = INFINITE;

   // We need to work out the time difference between now and the first timer that is set.

   if (!m_pFirstTimerSetHint)
   {
      m_pFirstTimerSetHint = GetFirstTimerSet();
   }

   if (m_pFirstTimerSetHint)
   {
      // A timer is set! Calculate the timeout in ms

      nextTimeout = static_cast<Milliseconds>(((m_pFirstTimerSetHint >= m_pNow ? (m_pFirstTimerSetHint - m_pNow) : (m_pTimersEnd - m_pNow + m_pFirstTimerSetHint - m_pTimersStart)) + 1) * m_timerGranularity);

      const Milliseconds now = m_tickCountProvider.GetTickCount();

      if (now != m_currentTime)
      {
         // Time has moved on, adjust the next timeout to take into account the difference between now and
         // the timer wheel's view of the current time...

         const Milliseconds timeDiff = (now > m_currentTime ? now - m_currentTime : m_currentTime - now);

         if (timeDiff > nextTimeout)
         {
            nextTimeout = 0;
         }
         else
         {
            nextTimeout -= timeDiff;
         }
      }

      if (nextTimeout > m_maximumTimeout)
      {
         throw CException(
            _T("CCallbackTimerWheel::GetNextTimeout()"), 
            _T("Next timeout: ") + ToString(nextTimeout) + _T(" is larger than max: ") + ToString(m_maximumTimeout));
      }
   }

   return nextTimeout;
}

CCallbackTimerWheel::TimerData **CCallbackTimerWheel::GetFirstTimerSet() const
{
   TimerData **pFirstTimer = 0;

   if (m_numTimersSet != 0)
   {
      // Scan forwards from now to the end of the array...

      for (TimerData **p = m_pNow; !pFirstTimer && p < m_pTimersEnd; ++p)
      {
         if (*p)
         {
            pFirstTimer = p;
         }
      }

      if (!pFirstTimer)
      {
         // We havent yet found our first timer, now scan from the start of the array to
         // now...

         for (TimerData **p = m_pTimersStart; !pFirstTimer && p < m_pNow; ++p)
         {
            if (*p)
            {
               pFirstTimer = p;
            }
         }
      }

      if (!pFirstTimer)
      {
         throw CException(_T("CCallbackTimerWheel::GetFirstTimerSet()"), _T("Unexpected, no timer set but count = ") + ToString(m_numTimersSet));
      }
   }

   return pFirstTimer;
}

void CCallbackTimerWheel::HandleTimeouts()
{
   const Milliseconds now = m_tickCountProvider.GetTickCount();

   TimerData *pTimers = 0;

   while (m_numTimersSet && (0 != (pTimers = GetTimersToProcess(now))))
   {
      while (pTimers)
      {
         TimerData *pTimer = pTimers;

         pTimers = pTimer->OnTimer();

#if (JETBYTE_PERF_TIMER_WHEEL_MONITORING == 1)

         m_monitor.OnTimer();

#endif

         if (pTimer->DeleteAfterTimeout())
         {
            m_handles.erase(pTimer);

            delete pTimer;

#if (JETBYTE_PERF_TIMER_WHEEL_MONITORING == 1)

            m_monitor.OnTimerDeleted();

#endif
         }

         --m_numTimersSet;
      }
   }
}

IManageTimerQueue::TimeoutHandle CCallbackTimerWheel::BeginTimeoutHandling()
{
   if (m_handlingTimeouts != InvalidTimeoutHandleValue)
   {
      throw CException(
         _T("CCallbackTimerWheel::BeginTimeoutHandling()"),
         _T("Already handling timeouts, you need to call EndTimeoutHandling()?"));
   }

   TimeoutHandle timeoutHandle = InvalidTimeoutHandleValue;

   TimerData *pTimers = GetAllTimersToProcess(m_tickCountProvider.GetTickCount());

   if (pTimers)
   {
      timeoutHandle = reinterpret_cast<TimeoutHandle>(pTimers);

      m_handlingTimeouts = timeoutHandle;
   }

   return timeoutHandle;
}

void CCallbackTimerWheel::HandleTimeout(
   IManageTimerQueue::TimeoutHandle &handle)
{
   if (m_handlingTimeouts != handle)
   {
// The following warning is generated when /Wp64 is set in a 32bit build. At present I think
// it's due to some confusion, and even if it isn't then it's not that crucial...
#pragma warning(push, 4)
#pragma warning(disable: 4244)
      throw CException(
         _T("CCallbackTimerWheel::HandleTimeout()"),
         _T("Invalid timeout handle: ") + ToString(handle));
#pragma warning(pop)
   }

   TimerData *pTimers = reinterpret_cast<TimerData *>(handle);

   while (pTimers)
   {
      pTimers = pTimers->HandleTimeout();

#if (JETBYTE_PERF_TIMER_WHEEL_MONITORING == 1)

         m_monitor.OnTimer();

#endif

   }
}

void CCallbackTimerWheel::EndTimeoutHandling(
   IManageTimerQueue::TimeoutHandle &handle)
{
   if (m_handlingTimeouts != handle)
   {
// The following warning is generated when /Wp64 is set in a 32bit build. At present I think
// it's due to some confusion, and even if it isn't then it's not that crucial...
#pragma warning(push, 4)
#pragma warning(disable: 4244)
      throw CException(
         _T("CCallbackTimerWheel::EndTimeoutHandling()"),
         _T("Invalid timeout handle: ") + ToString(handle));
#pragma warning(pop)
   }

   m_handlingTimeouts = InvalidTimeoutHandleValue;

   TimerData *pTimers = reinterpret_cast<TimerData *>(handle);

   TimerData *pDeadTimer = 0;

   while (pTimers)
   {
      if (pTimers->DeleteAfterTimeout())
      {
         pDeadTimer = pTimers;
      }

      pTimers = pTimers->TimeoutHandlingComplete();

      if (pDeadTimer)
      {
         delete pDeadTimer;

#if (JETBYTE_PERF_TIMER_WHEEL_MONITORING == 1)

         m_monitor.OnTimerDeleted();

#endif

         pDeadTimer = 0;
      }
   }
}

CCallbackTimerWheel::Handle CCallbackTimerWheel::CreateTimer()
{
   TimerData *pData = new TimerData();

   return OnTimerCreated(pData);
}

CCallbackTimerWheel::Handle CCallbackTimerWheel::OnTimerCreated(
   TimerData *pData)
{
   m_handles.insert(pData);

#if (JETBYTE_PERF_TIMER_WHEEL_MONITORING == 1)

   m_monitor.OnTimerCreated();

#endif

   return reinterpret_cast<Handle>(pData);
}

Milliseconds CCallbackTimerWheel::CalculateTimeout(
   const Milliseconds timeout)
{
   const Milliseconds now = m_tickCountProvider.GetTickCount();

   if (m_numTimersSet == 0)
   {
      m_currentTime = now;

      m_pNow = m_pTimersStart;
   }

   const Milliseconds actualTimeout = timeout + (now - m_currentTime);

   if (actualTimeout > m_maximumTimeout)
   {
      throw CException(
         _T("CCallbackTimerWheel::CalculateTimeout()"),
         _T("Timeout is too long. Max is: ") + ToString(m_maximumTimeout) + _T(" tried to set: ") + ToString(actualTimeout) + _T(" (") + ToString(timeout) + _T(")"));
   }

   return actualTimeout;
}

bool CCallbackTimerWheel::SetTimer(
   const Handle &handle,
   Timer &timer,
   const Milliseconds timeout,
   const UserData userData)
{
   Milliseconds actualTimeout = CalculateTimeout(timeout);

   TimerData &data = ValidateHandle(handle);

   const bool wasPending = data.CancelTimer();

   data.UpdateData(timer, userData);

   InsertTimer(actualTimeout, data, wasPending);

#if (JETBYTE_PERF_TIMER_WHEEL_MONITORING == 1)

   m_monitor.OnTimerSet(wasPending);

#endif

   return wasPending;
}

void CCallbackTimerWheel::SetTimer(
   IQueueTimers::Timer &timer,
   const Milliseconds timeout,
   const IQueueTimers::UserData userData)
{
   Milliseconds actualTimeout = CalculateTimeout(timeout);

   TimerData *pData = new TimerData(timer, userData);

   OnTimerCreated(pData);

   InsertTimer(actualTimeout, *pData);

#if (JETBYTE_PERF_TIMER_WHEEL_MONITORING == 1)

   m_monitor.OnOneOffTimerSet();

#endif
}

void CCallbackTimerWheel::InsertTimer(
   const Milliseconds timeout,
   TimerData &data,
   const bool wasPending)
{
   const size_t timerOffset = timeout / m_timerGranularity;

   TimerData **ppTimer = GetTimerAtOffset(timerOffset);

   data.SetTimer(ppTimer, *ppTimer);

   m_pFirstTimerSetHint = 0;

   if (!wasPending)
   {
      if (0 == ++m_numTimersSet)
      {
         // number of timers set counter has wrapped!

         throw CException(_T("CCallbackTimerWheel::InsertTimer()"), _T("Too many timers set!"));
      }
   }
}

bool CCallbackTimerWheel::CancelTimer(
   const Handle &handle)
{
   TimerData &data = ValidateHandle(handle);

   const bool wasPending = data.CancelTimer();

   if (wasPending)
   {
      OnTimerCancelled();
   }

#if (JETBYTE_PERF_TIMER_WHEEL_MONITORING == 1)

   m_monitor.OnTimerCancelled(wasPending);

#endif

   return wasPending;
}

void CCallbackTimerWheel::OnTimerCancelled()
{
   --m_numTimersSet;

   m_pFirstTimerSetHint = 0;
}

bool CCallbackTimerWheel::DestroyTimer(
   Handle &handle)
{
   TimerData &data = ValidateHandle(handle);

   const bool wasPending = data.CancelTimer();

   m_handles.erase(&data);

   handle = InvalidHandleValue;

#if (JETBYTE_PERF_TIMER_WHEEL_MONITORING == 1)

   m_monitor.OnTimerDestroyed(wasPending);

#endif

   if (data.HasTimedOut())
   {
      data.SetDeleteAfterTimeout();
   }
   else
   {
      delete &data;

#if (JETBYTE_PERF_TIMER_WHEEL_MONITORING == 1)

   m_monitor.OnTimerDeleted();

#endif

   }

   if (wasPending)
   {
      OnTimerCancelled();
   }

   return wasPending;
}

bool CCallbackTimerWheel::DestroyTimer(
   const Handle &handle)
{
   Handle handle_ = handle;

   return DestroyTimer(handle_);
}

Milliseconds CCallbackTimerWheel::GetMaximumTimeout() const
{
   return m_maximumTimeout;
}

bool CCallbackTimerWheel::DispatchesWithoutLock() const
{
   return true;
}

CCallbackTimerWheel::TimerData &CCallbackTimerWheel::ValidateHandle(
   const Handle &handle) const
{
   TimerData *pData = reinterpret_cast<TimerData *>(handle);

   Handles::const_iterator it = m_handles.find(pData);

   if (it == m_handles.end())
   {
// The following warning is generated when /Wp64 is set in a 32bit build. At present I think
// it's due to some confusion, and even if it isn't then it's not that crucial...
#pragma warning(push, 4)
#pragma warning(disable: 4244)
      throw CException(
         _T("CCallbackTimerWheel::ValidateHandle()"),
         _T("Invalid timer handle: ") + ToString(handle));
#pragma warning(pop)
   }

   if (pData->DeleteAfterTimeout())
   {
// The following warning is generated when /Wp64 is set in a 32bit build. At present I think
// it's due to some confusion, and even if it isn't then it's not that crucial...
#pragma warning(push, 4)
#pragma warning(disable: 4244)
      throw CException(
         _T("CCallbackTimerWheel::ValidateHandle()"),
         _T("Invalid timer handle: ") + ToString(handle));
#pragma warning(pop)
   }

   return *pData;
}

CCallbackTimerWheel::TimerData *CCallbackTimerWheel::GetAllTimersToProcess(
   const Milliseconds now)
{
   TimerData *pTimers = 0;

   TimerData *pLastTimer = 0;

   // Round 'now' down to the timer granularity

   const Milliseconds thisTime = ((now / m_timerGranularity) * m_timerGranularity);

   while (m_numTimersSet && m_currentTime != thisTime)
   {
      TimerData **ppTimers = GetTimerAtOffset(0);

      TimerData *pTheseTimers = *ppTimers;

      if (pTheseTimers)
      {
         pTheseTimers->Unlink();

         if (!pTimers)
         {
            pTimers = pTheseTimers;
         }

         if (pLastTimer)
         {
            pLastTimer->AddTimedOutTimers(pTheseTimers);
         }

         pLastTimer = PrepareTimersForHandleTimeout(pTheseTimers);
      }

      // Step along the wheel...

      m_pNow++;

      if (m_pNow >= m_pTimersEnd)
      {
         m_pNow = m_pTimersStart + (m_pNow - m_pTimersEnd);
      }

      m_currentTime += m_timerGranularity;
   }

   m_currentTime = thisTime;

   if (pTimers)
   {
      m_pFirstTimerSetHint = 0;
   }

   return pTimers;
}

CCallbackTimerWheel::TimerData *CCallbackTimerWheel::PrepareTimersForHandleTimeout(
   TimerData *pTimers)
{
   TimerData *pLastTimer = pTimers;

   while (pTimers)
   {
      pLastTimer = pTimers;

      pTimers = pTimers->PrepareForHandleTimeout();

      m_numTimersSet--;
   }

   return pLastTimer;
}

CCallbackTimerWheel::TimerData *CCallbackTimerWheel::GetTimersToProcess(
   const Milliseconds now)
{
   TimerData *pTimers = 0;

   // Round 'now' down to the timer granularity

   const Milliseconds thisTime = ((now / m_timerGranularity) * m_timerGranularity);

   while (!pTimers && m_currentTime != thisTime)
   {
      TimerData **ppTimers = GetTimerAtOffset(0);

      pTimers = *ppTimers;

      if (pTimers)
      {
         pTimers->Unlink();
      }

      // Step along the wheel...

      m_pNow++;

      if (m_pNow >= m_pTimersEnd)
      {
         m_pNow = m_pTimersStart + (m_pNow - m_pTimersEnd);
      }

      m_currentTime += m_timerGranularity;
   }

   if (pTimers)
   {
      m_pFirstTimerSetHint = 0;
   }

   return pTimers;
}

CCallbackTimerWheel::TimerData **CCallbackTimerWheel::GetTimerAtOffset(
   const size_t offset) const
{
   TimerData **pNext = m_pNow + offset;

   if (pNext >= m_pTimersEnd)
   {
      pNext = m_pTimersStart + (pNext - m_pTimersEnd);
   }

   return pNext;
}

CCallbackTimerWheel::TimerData **CCallbackTimerWheel::CreateTimerWheel(
   const size_t numTimers)
{
   CCallbackTimerWheel::TimerData **ppTimers = new CCallbackTimerWheel::TimerData*[numTimers];

   memset(ppTimers, 0, sizeof(CCallbackTimerWheel::TimerData*) * numTimers);

   return ppTimers;
}

///////////////////////////////////////////////////////////////////////////////
// CCallbackTimerWheel::TimerData
///////////////////////////////////////////////////////////////////////////////

CCallbackTimerWheel::TimerData::TimerData()
   :  m_ppPrevious(0),
      m_pNext(0),
      m_pNextTimedout(0),
      m_processingTimeout(false),
      m_deleteAfterTimeout(false)
{

}

CCallbackTimerWheel::TimerData::TimerData(
   CCallbackTimerWheel::Timer &timer,
   CCallbackTimerWheel::UserData userData)
   :  m_ppPrevious(0),
      m_pNext(0),
      m_pNextTimedout(0),
      m_active(timer, userData),
      m_processingTimeout(false),
      m_deleteAfterTimeout(true)
{

}

bool CCallbackTimerWheel::TimerData::DeleteAfterTimeout() const
{
   return m_deleteAfterTimeout;
}

bool CCallbackTimerWheel::TimerData::CancelTimer()
{
   bool timerWasSet = false;

   if (m_ppPrevious)
   {
      if (m_pNext)
      {
         m_pNext->m_ppPrevious = m_ppPrevious;
      }

      *m_ppPrevious = m_pNext;

      m_ppPrevious = 0;
      m_pNext = 0;

      m_active.Clear();

      timerWasSet = true;
   }

   return timerWasSet;
}

bool CCallbackTimerWheel::TimerData::HasTimedOut() const
{
   return m_processingTimeout;
}

void CCallbackTimerWheel::TimerData::SetDeleteAfterTimeout()
{
   m_deleteAfterTimeout = true;
}

void CCallbackTimerWheel::TimerData::UpdateData(
   CCallbackTimerWheel::Timer &timer,
   CCallbackTimerWheel::UserData userData)
{
   if (m_deleteAfterTimeout)
   {
      throw CException(
         _T("CCallbackTimerWheel::TimerData::UpdateData()"),
         _T("Internal Error: Can't update one shot timers or timers pending deletion"));
   }

   m_active.pTimer = &timer;

   m_active.userData = userData;
}

void CCallbackTimerWheel::TimerData::SetTimer(
   TimerData **ppPrevious,
   TimerData *pNext)
{
   if (m_ppPrevious)
   {
      throw CException(
         _T("CCallbackTimerWheel::TimerData::SetTimer()"),
         _T("Internal Error: Timer is already set"));
   }

   m_ppPrevious = ppPrevious;

   m_pNext = pNext;

   if (m_pNext)
   {
      m_pNext->m_ppPrevious = &m_pNext;
   }

   *ppPrevious = this;
}

CCallbackTimerWheel::TimerData *CCallbackTimerWheel::TimerData::OnTimer()
{
   m_ppPrevious = 0;

   return OnTimer(m_active);
}

CCallbackTimerWheel::TimerData *CCallbackTimerWheel::TimerData::OnTimer(
   const Data &data)
{
   if (!data.pTimer)
   {
      throw CException(
         _T("CCallbackTimerWheel::TimerData::OnTimer()"),
         _T("Internal Error: Timer not set"));
   }

   data.pTimer->OnTimer(data.userData);

   return m_processingTimeout ? m_pNextTimedout : m_pNext;
}

void CCallbackTimerWheel::TimerData::Unlink()
{
   if (m_ppPrevious)
   {
      *m_ppPrevious = 0;

      m_ppPrevious = 0;
   }
}

void CCallbackTimerWheel::TimerData::AddTimedOutTimers(
   TimerData *pTimers)
{
   m_pNextTimedout = pTimers;
}

CCallbackTimerWheel::TimerData *CCallbackTimerWheel::TimerData::PrepareForHandleTimeout()
{
   m_processingTimeout = true;

   m_timedout = m_active;

   m_active.Clear();

   m_pNextTimedout = m_pNext;

   m_pNext = 0;

   m_ppPrevious = 0;

   return m_pNextTimedout;
}

CCallbackTimerWheel::TimerData *CCallbackTimerWheel::TimerData::HandleTimeout()
{
   TimerData *pNextTimedout = OnTimer(m_timedout);

   m_timedout.Clear();

   return pNextTimedout;
}

CCallbackTimerWheel::TimerData *CCallbackTimerWheel::TimerData::TimeoutHandlingComplete()
{
   m_processingTimeout = false;

   TimerData *pNext = m_pNextTimedout;

   m_pNextTimedout = 0;

   return pNext;
}

///////////////////////////////////////////////////////////////////////////////
// CCallbackTimerWheel::TimerData::Data
///////////////////////////////////////////////////////////////////////////////

CCallbackTimerWheel::TimerData::Data::Data()
   :  pTimer(0),
      userData(0)
{

}

CCallbackTimerWheel::TimerData::Data::Data(
   Timer &timer,
   UserData userData_)
   :  pTimer(&timer),
      userData(userData_)
{

}

void CCallbackTimerWheel::TimerData::Data::Clear()
{
   pTimer = 0;
   userData = 0;
}

///////////////////////////////////////////////////////////////////////////////
// Static helper functions
///////////////////////////////////////////////////////////////////////////////

static size_t CalculateNumberOfTimers(
   const Milliseconds maximumTimeout,
   const Milliseconds timerGranularity)
{
   return (maximumTimeout / timerGranularity) + 1;
}

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools::Win32
///////////////////////////////////////////////////////////////////////////////

} // End of namespace Win32
} // End of namespace JetByteTools

///////////////////////////////////////////////////////////////////////////////
// End of file: CallbackTimerWheel.cpp
///////////////////////////////////////////////////////////////////////////////