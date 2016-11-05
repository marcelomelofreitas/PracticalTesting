///////////////////////////////////////////////////////////////////////////////
// File: MockTimerQueue.cpp
///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2007 JetByte Limited.
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

#include "MockTimerQueue.h"

#include "JetByteTools\Win32Tools\Utils.h"

#include "JetByteTools\TestTools\TestException.h"

#pragma hdrstop

///////////////////////////////////////////////////////////////////////////////
// Using directives
///////////////////////////////////////////////////////////////////////////////

using JetByteTools::Win32::ToString;

using JetByteTools::Test::CTestException;

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools::Win32::Mock
///////////////////////////////////////////////////////////////////////////////

namespace JetByteTools {
namespace Win32 {
namespace Mock {

///////////////////////////////////////////////////////////////////////////////
// CMockTimerQueue
///////////////////////////////////////////////////////////////////////////////

CMockTimerQueue::CMockTimerQueue(
   const bool dispatchWithoutLock)
   :  m_dispatchWithoutLock(dispatchWithoutLock),
      m_nextTimer(0),
      m_pTimer(0),
      m_userData(0),
      m_maxTimeout(0xFFFFFFFE),
      m_nextTimeout(INFINITE)
{

}

void CMockTimerQueue::SetNextTimeout(
   const Milliseconds nextTimeout)
{
   m_nextTimeout = nextTimeout;
}

bool CMockTimerQueue::WaitForNextTimeout(
   const Milliseconds timeout)
{
   return m_nextTimeoutEvent.Wait(timeout);
}

bool CMockTimerQueue::WaitForOnTimer(
   const Milliseconds timeout)
{
   return m_onTimerEvent.Wait(timeout);
}

void CMockTimerQueue::OnTimer()
{
   if (!m_pTimer)
   {
      throw CTestException(_T("CMockTimerQueue::OnTimer()"), _T("Timer not set"));
   }

   Timer *pTimer = m_pTimer;

   UserData userData = m_userData;

   m_pTimer = 0;
   m_userData = 0;

   pTimer->OnTimer(userData);

   m_onTimerEvent.Set();
}

bool CMockTimerQueue::IsTimerSet() const
{
   return (m_pTimer != 0);
}

Milliseconds CMockTimerQueue::GetNextTimeout()
{
   LogMessage(_T("GetNextTimeout"));

   m_nextTimeoutEvent.Set();

   return m_nextTimeout;
}

void CMockTimerQueue::HandleTimeouts()
{
   LogMessage(_T("HandleTimeouts"));

   if (m_pTimer)
   {
      OnTimer();
   }

   m_nextTimeout = INFINITE;
}

IManageTimerQueue::TimeoutHandle CMockTimerQueue::BeginTimeoutHandling()
{
   LogMessage(_T("BeginTimeoutHandling"));

   return m_pTimer ? reinterpret_cast<IManageTimerQueue::TimeoutHandle>(1) : IManageTimerQueue::InvalidTimeoutHandleValue;
}

void CMockTimerQueue::HandleTimeout(
   IManageTimerQueue::TimeoutHandle &/*handle*/)
{
   LogMessage(_T("HandleTimeout"));

   OnTimer();

   m_nextTimeout = INFINITE;
}

void CMockTimerQueue::EndTimeoutHandling(
   IManageTimerQueue::TimeoutHandle &/*handle*/)
{
   LogMessage(_T("EndTimeoutHandling"));
}

CMockTimerQueue::Handle CMockTimerQueue::CreateTimer()
{
   Handle handle = ::InterlockedIncrement(&m_nextTimer);

   LogMessage(_T("CreateTimer: ") + ToString(handle));

   return handle;
}

#pragma warning(disable: 4100)

bool CMockTimerQueue::SetTimer(
   const Handle &handle, 
   Timer &timer,
   const Milliseconds timeout,
   const UserData userData)
{
   LogMessage(_T("SetTimer: ") + ToString(handle) + _T(": ") + ToString(timeout));

   bool wasPending = (m_pTimer != 0);

   m_pTimer = &timer;

   m_userData = userData;

   m_nextTimeout = 0;

   return wasPending;
}

bool CMockTimerQueue::CancelTimer(
   const Handle &handle)
{
   LogMessage(_T("CancelTimer: ") + ToString(handle));

   const bool wasSet = m_pTimer != 0;

   m_pTimer = 0;
   m_userData = 0;

   return wasSet;
}

bool CMockTimerQueue::DestroyTimer(
   Handle &handle)
{
   LogMessage(_T("DestroyTimer: ") + ToString(handle));
   
   handle = InvalidHandleValue;

   const bool wasSet = m_pTimer != 0;

   m_pTimer = 0;
   m_userData = 0;

   return wasSet;
}

bool CMockTimerQueue::DestroyTimer(
   const Handle &handle)
{
   LogMessage(_T("DestroyTimer: ") + ToString(handle));

   const bool wasSet = m_pTimer != 0;

   m_pTimer = 0;
   m_userData = 0;

   return wasSet;
}

void CMockTimerQueue::SetTimer(
   Timer &timer,
   const Milliseconds timeout,
   const UserData userData)
{
   LogMessage(_T("SetTimer: ") + ToString(timeout));

   m_pTimer = &timer;

   m_userData = userData;
}

Milliseconds CMockTimerQueue::GetMaximumTimeout() const
{
   LogMessage(_T("GetMaximumTimeout"));

   return m_maxTimeout;
}

bool CMockTimerQueue::DispatchesWithoutLock() const
{
   LogMessage(_T("DispatchesWithoutLock"));

   return m_dispatchWithoutLock;
}

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools::Win32::Mock
///////////////////////////////////////////////////////////////////////////////

} // End of namespace Mock
} // End of namespace Win32
} // End of namespace JetByteTools 

///////////////////////////////////////////////////////////////////////////////
// End of file: MockTimerQueue.cpp
///////////////////////////////////////////////////////////////////////////////
