#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef JETBYTE_TOOLS_I_QUEUE_TIMERS_INCLUDED__
#define JETBYTE_TOOLS_I_QUEUE_TIMERS_INCLUDED__
///////////////////////////////////////////////////////////////////////////////
// File: IQueueTimers.h
///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2004 JetByte Limited.
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

#include "JetByteTools\Admin\Types.h"

#include <wtypes.h>

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools::Win32
///////////////////////////////////////////////////////////////////////////////

namespace JetByteTools {
namespace Win32 {

///////////////////////////////////////////////////////////////////////////////
// IQueueTimers
///////////////////////////////////////////////////////////////////////////////

/// An interface representing a class that manages timers that implement the 
/// IQueueTimers::Timer interface and and which have their 
/// IQueueTimers::Timer::OnTimer() method called when the the timer expires. 
/// See <a href="http://www.lenholgate.com/archives/000389.html">here</a>
/// for more details.
/// \ingroup Timers
/// \ingroup Interfaces
/// \ingroup ProtectedDestructors

class IQueueTimers
{
   public :

      /// User data that can be passed to Timer via the OnTimer() call when 
      /// the timeout expires.

      typedef ULONG_PTR UserData;

      /// The Timer interface.
      
      class Timer;

      /// A handle to a timer that has been created. This can be passed to
      /// SetTimer(), CancelTimer() and DestroyTimer() and is created with
      /// CreateTimer().
      
      typedef ULONG_PTR Handle;

      /// The value that represents an invalid handle that cannot be used.
      
      static Handle InvalidHandleValue;

      /// Create a timer and return a Handle to it.
      
      virtual Handle CreateTimer() = 0;

      /// Set a timer that was previously created with CreateTimer().
      /// Returns true if the timer was previously pending for another timeout and
      /// false if the timer was not already pending. Note that calling SetTimer() 
      /// will cause any timers that have expired to be processed before the new
      /// timer is set.
      
      virtual bool SetTimer(
         const Handle &handle, 
         Timer &timer,
         const Milliseconds timeout,
         const UserData userData) = 0;

      /// Cancel a timer that was previously set with SetTimer().
      /// Returns true if the timer was pending and false if the timer was not pending.
      
      virtual bool CancelTimer(
         const Handle &handle) = 0;

      /// Destroy a timer that was previously created with CreateTimer()
      /// and update the variable passed in to contain InvalidHandleValue.
      /// Note that it is not permitted to call DestroyHandle() on a 
      /// handle that contains the InvalidHandleValue value and an exception
      /// is thrown in this case. Returns true if the timer was pending and 
      /// false if the timer was not pending.
      
      virtual bool DestroyTimer(
         Handle &handle) = 0;

      /// Destroy a timer that was previously created with CreateTimer().
      /// Returns true if the timer was pending and false if the timer was not pending.
      
      virtual bool DestroyTimer(
         const Handle &handle) = 0;

      /// Create and set a single use timer.
      /// Note that calling SetTimer() will cause any timers that have expired to be 
      /// processed before the new timer is set.
      
      virtual void SetTimer(
         Timer &timer,
         const Milliseconds timeout,
         const UserData userData) = 0;

      /// Returns the maximum timeout value that can be set. Note that this may differ
      /// between instances of the objects that implement this interface.

      virtual Milliseconds GetMaximumTimeout() const = 0;

   protected :

		/// We never delete instances of this interface; you must manage the 
		/// lifetime of the class that implements it.

      ~IQueueTimers() {}
};

///////////////////////////////////////////////////////////////////////////////
// IQueueTimers::Timer
///////////////////////////////////////////////////////////////////////////////

/// An interface to a timer that can be set with IQueueTimers.

class IQueueTimers::Timer
{
   public :
      
      /// User data that can be passed to Timer via the OnTimer() call when 
      /// the timeout expires.
      
      typedef IQueueTimers::UserData UserData;

      /// Called after the timer expires.
      
      virtual void OnTimer(
         UserData userData) = 0;

   protected :

		/// We never delete instances of this interface; you must manage the 
		/// lifetime of the class that implements it.

      ~Timer() {}
};

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools::Win32
///////////////////////////////////////////////////////////////////////////////

} // End of namespace Win32
} // End of namespace JetByteTools 

#endif // JETBYTE_TOOLS_I_QUEUE_TIMERS_INCLUDED__

///////////////////////////////////////////////////////////////////////////////
// End of file: IQueueTimers.h
///////////////////////////////////////////////////////////////////////////////