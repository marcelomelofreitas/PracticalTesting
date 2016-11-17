#pragma once
#ifndef JETBYTE_TOOLS_CALLBACK_TIMER_QUEUE_EX_INCLUDED__
#define JETBYTE_TOOLS_CALLBACK_TIMER_QUEUE_EX_INCLUDED__
///////////////////////////////////////////////////////////////////////////////
// File: CallbackTimerQueueEx.h
///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2008 JetByte Limited.
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

#include "IManageTimerQueue.h"

#include "IntrusiveMultiMap.h"
#include "IntrusiveSet.h"

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools::Win32
///////////////////////////////////////////////////////////////////////////////

namespace JetByteTools {
namespace Win32 {

///////////////////////////////////////////////////////////////////////////////
// Classes defined in other files...
///////////////////////////////////////////////////////////////////////////////

class IProvideTickCount64;
class IMonitorCallbackTimerQueue;

///////////////////////////////////////////////////////////////////////////////
// CCallbackTimerQueueEx
///////////////////////////////////////////////////////////////////////////////

/// A class that manages a group of timers that implement IQueueTimers::Timer
/// and which have their IQueueTimers::Timer::OnTimer() method called when the
/// timer expires. You must manually manage the handling and processing of
/// timeouts by calling IManageTimerQueue::BeginTimeoutHandling() every
/// IManageTimerQueue::GetNextTimeout() milliseconds.
/// See <a href="http://www.lenholgate.com/archives/000342.html">here</a> for
/// more details.
/// Note: the maximum timeout that you can set is 4294967294ms as 0xFFFFFFF is
/// reserved as 'INFINITE' i.e. a timer that never expires. Internally the code
/// uses an unsigned 64 bit counter which will wrap in around 584942417.4 years
/// from the creation of the timer queue. You cannot set a timer that crosses
/// this wrap point and an exception will be thrown. GetMaximumTimeout() does
/// not report the reducing maximum timeout as the wrap point approaches, it
/// will always return 4294967294ms.
/// \ingroup Timers

class CCallbackTimerQueueEx : public IManageTimerQueue
{
   public :

      /// Create a timer queue.

      CCallbackTimerQueueEx();

      /// Create a timer queue and monitor it with the supplied monitor.

      explicit CCallbackTimerQueueEx(
         IMonitorCallbackTimerQueue &monitor);

      /// Create a timer queue that uses the provdided instance of
      /// IProvideTickCount64 to obtain its tick counts rather than getting
      /// them directly from the system.

      explicit CCallbackTimerQueueEx(
         const IProvideTickCount64 &tickProvider);

      /// Create a timer queue that uses the provdided instance of
      /// IProvideTickCount64 to obtain its tick counts rather than getting
      /// them directly from the system. Monitor it with the supplied monitor.

      CCallbackTimerQueueEx(
         IMonitorCallbackTimerQueue &monitor,
         const IProvideTickCount64 &tickProvider);

      virtual ~CCallbackTimerQueueEx();

      // Implement IManageTimerQueue

      virtual Milliseconds GetNextTimeout();

      virtual bool BeginTimeoutHandling();

      virtual void HandleTimeout();

      virtual void EndTimeoutHandling();

      // Implement IQueueTimers
      // We need to fully specify the IQueueTimers types to get around a bug in
      // doxygen 1.5.2

      virtual IQueueTimers::Handle CreateTimer();

      virtual bool SetTimer(
         const IQueueTimers::Handle &handle,
         IQueueTimers::Timer &timer,
         const Milliseconds timeout,
         const IQueueTimers::UserData userData);

      virtual bool CancelTimer(
         const IQueueTimers::Handle &handle);

      virtual bool DestroyTimer(
         IQueueTimers::Handle &handle);

      virtual bool DestroyTimer(
         const IQueueTimers::Handle &handle);

      virtual void SetTimer(
         IQueueTimers::Timer &timer,
         const Milliseconds timeout,
         const IQueueTimers::UserData userData);

      virtual Milliseconds GetMaximumTimeout() const;

   private :

      class TimerDataSetNodeAccessor;

      class TimerData;

      class TimerDataIntrusiveMultiMapNodeKeyAccessor
      {
         public :

            static ULONGLONG GetKeyFromT(
               const TimerData *pNode);
      };

      class TimerDataIntrusiveMultiMapNodeAccessor
      {
         public :

            static CIntrusiveMultiMapNode * GetNodeFromT(
               const TimerData *pData);

            static TimerData *GetTFromNode(
               const CIntrusiveMultiMapNode *pNode);

            static TimerData *GetTFromNode(
               const CIntrusiveRedBlackTreeNode *pNode);
      };

      typedef TIntrusiveMultiMap<
         TimerData,
         ULONGLONG,
         TimerDataIntrusiveMultiMapNodeKeyAccessor,
         std::less<ULONGLONG>,
         TimerDataIntrusiveMultiMapNodeAccessor> TimerQueue;

      typedef TIntrusiveSet<TimerData> ActiveHandles;

      TimerData *ValidateHandle(
         const Handle &handle);

      //lint -e{1411} (Member with different signature hides virtual member --- Eff. C++ 3rd Ed. item 33)
      bool CancelTimer(
         TimerData *pData);

      void InsertTimer(
         TimerData * const pData,
         const Milliseconds timeout);

      void InsertTimer(
         TimerData * const pData,
         const ULONGLONG absoluteTimeout);

      TimerQueue m_queue;

      ActiveHandles m_activeHandles;

      const IProvideTickCount64 &m_tickProvider;

      IMonitorCallbackTimerQueue &m_monitor;

      const Milliseconds m_maxTimeout;

      bool m_handlingTimeouts;

      TimerData *m_pTimeoutsToBeHandled;

      /// No copies do not implement
      CCallbackTimerQueueEx(const CCallbackTimerQueueEx &rhs);
      /// No copies do not implement
      CCallbackTimerQueueEx &operator=(const CCallbackTimerQueueEx &rhs);
};

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools::Win32
///////////////////////////////////////////////////////////////////////////////

} // End of namespace Win32
} // End of namespace JetByteTools

#endif // JETBYTE_TOOLS_CALLBACK_TIMER_QUEUE_EX_INCLUDED__

///////////////////////////////////////////////////////////////////////////////
// End of file: CallbackTimerQueueEx.h
///////////////////////////////////////////////////////////////////////////////
