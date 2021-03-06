#pragma once
#ifndef JETBYTE_TOOLS_WIN32_AUTO_RESET_EVENT_INCLUDED__
#define JETBYTE_TOOLS_WIN32_AUTO_RESET_EVENT_INCLUDED__
///////////////////////////////////////////////////////////////////////////////
// File: AutoResetEvent.h
///////////////////////////////////////////////////////////////////////////////
//
// Copyright 1997 JetByte Limited.
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

#include "Event.h"

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools::Win32
///////////////////////////////////////////////////////////////////////////////

namespace JetByteTools {
namespace Win32 {

///////////////////////////////////////////////////////////////////////////////
// CAutoResetEvent
///////////////////////////////////////////////////////////////////////////////

/// A class that wraps the operating system
/// <a href="http://msdn2.microsoft.com/en-us/library/ms682655.aspx">Event API</a>
/// and exposes just the interface for an auto reset event.
/// \ingroup Synchronization
/// \ingroup KernelObjects

class CAutoResetEvent : public IWaitable
{
   public :

      /// Create an anonymous CAutoResetEvent object for in-process use.

      explicit CAutoResetEvent(
         CEvent::InitialState initialState = CEvent::NonSignaled,
         SECURITY_ATTRIBUTES *pSecurityAttributes = nullptr);

      /// Create a new named CAutoResetEvent object or connect to an existing
      /// one with the same name, for cross-process use.

      explicit CAutoResetEvent(
         const IKernelObjectName &name,
         SECURITY_ATTRIBUTES *pSecurityAttributes = nullptr,
         CEvent::InitialState initialState = CEvent::NonSignaled);

      /// Create a new named CAutoResetEvent object or connect to an existing
      /// one with the same name, for cross-process use. Use the CreationFlags
      /// to force creation only or connection only if required.

      CAutoResetEvent(
         const IKernelObjectName &name,
         CEvent::CreationFlags creationFlags,
         SECURITY_ATTRIBUTES *pSecurityAttributes = nullptr,
         CEvent::InitialState initialState = CEvent::NonSignaled);


      CAutoResetEvent(
         const CAutoResetEvent &rhs) = delete;

      CAutoResetEvent &operator=(
         const CAutoResetEvent &rhs) = delete;

      /// Set the event to the signalled state.

      void Set();

      /// Pulse the event. Releases one waiting thread and resets the event.

      void Pulse();

      // Implement IWaitable

      HANDLE GetWaitHandle() const override;

      void Wait() const override;

      bool Wait(
         Milliseconds timeout) const override;

   private :

      CEvent m_event;
};

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools::Win32
///////////////////////////////////////////////////////////////////////////////

} // End of namespace Win32
} // End of namespace JetByteTools

#endif // JETBYTE_TOOLS_WIN32_AUTO_RESET_EVENT_INCLUDED__

///////////////////////////////////////////////////////////////////////////////
// End of file: AutoResetEvent.h
///////////////////////////////////////////////////////////////////////////////
