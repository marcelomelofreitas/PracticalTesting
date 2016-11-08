#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef JETBYTE_TOOLS_WIN32_EMPTY_BASE_INCLUDED__
#define JETBYTE_TOOLS_WIN32_EMPTY_BASE_INCLUDED__
///////////////////////////////////////////////////////////////////////////////
// File: EmptyBase.h
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

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools::Win32
///////////////////////////////////////////////////////////////////////////////

namespace JetByteTools {
namespace Win32 {

///////////////////////////////////////////////////////////////////////////////
// CEmptyBase
///////////////////////////////////////////////////////////////////////////////

class CEmptyBase
{
   //lint -esym(1510, CEmptyBase) (base class has no destructor -- Effective C++ #14)
};

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools::Win32
///////////////////////////////////////////////////////////////////////////////

} // End of namespace Win32
} // End of namespace JetByteTools

#endif // JETBYTE_TOOLS_WIN32_EMPTY_BASE_INCLUDED__

///////////////////////////////////////////////////////////////////////////////
// End of file: EmptyBase.h
///////////////////////////////////////////////////////////////////////////////
