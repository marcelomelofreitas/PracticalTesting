///////////////////////////////////////////////////////////////////////////////
// File: PrecompiledHeader.cpp
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

/// \file JetByteTools\Win32Tools\PrecompiledHeader.cpp
/// This file is compiled to produce the precompiled header in builds which use 
/// it.
/// \ingroup Precomp

#include "JetByteTools\Admin\Admin.h"

#include <wtypes.h>

#include "AutoResetEvent.h"
#include "CallbackTimerQueue.h"
#include "CallbackTimerQueueEx.h"
#include "CriticalSection.h"
#include "DebugTrace.h"
#include "Event.h"
#include "Exception.h"
#include "ICriticalSection.h"
#include "IKernelObjectName.h"
#include "IProvideTickCount.h"
#include "IQueueTimers.h"
#include "IRunnable.h"
#include "IWaitable.h"
#include "SEHException.h"
#include "SimpleMessageLog.h"
#include "StringConverter.h"
#include "Thread.h"
#include "ThreadedCallbackTimerQueue.h"
#include "TickCountProvider.h"
#include "TickCount64Provider.h"
#include "tstring.h"
#include "Utils.h"
#include "Win32Exception.h"

// There's an issue with VS2002 where the ordering of includes is important
// with regards to the secure CRT stuff, until I spend the time to get it
// right, keep this at the end of the precompiled header..
#include "JetByteTools\Admin\SecureCRT.h"

#include "JetByteTools\C++Tools\ExpandableBuffer.h"

#pragma hdrstop

///////////////////////////////////////////////////////////////////////////////
// End of file: PrecompiledHeader.cpp
///////////////////////////////////////////////////////////////////////////////
