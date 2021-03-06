#pragma once
#ifndef JETBYTE_TOOLS_ADMIN_WARNINGS_INCLUDED__
#define JETBYTE_TOOLS_ADMIN_WARNINGS_INCLUDED__
///////////////////////////////////////////////////////////////////////////////
// File: Warnings.h
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

/// \file Warnings.h
/// This file deals with warning level setting and masking of known safe
/// warnings for either STLPort or native Microsoft STL. It's automatically
/// included in all files because they include Admin.h
/// \ingroup Admin
/// \ingroup Warnings

#pragma warning(disable: 4355)   // 'this': used in base member initializer list

#pragma warning(disable: 4373)   // 'x': virtual function overrides 'y', previous versions of the compiler
                                 // (VS2008 and earlier) did not override when parameters only differed by
                                 // const/volatile qualifiers

#pragma warning(disable: 4201)   // nonstandard extension used : nameless struct/union

#pragma warning(disable: 4503)   // decorated name length exceeded, name was truncated

#pragma warning(disable: 4505)   // unreferenced local function has been removed

#pragma warning(disable: 4510)   // default constructor could not be generated
#pragma warning(disable: 4511)   // copy constructor could not be generated
#pragma warning(disable: 4512)   // assignment operator could not be generated
#pragma warning(disable: 4514)   // unreferenced inline function has been removed
#pragma warning(disable: 4610)   // can never be instantiated - user defined constructor required

#pragma warning(disable: 4702)   // unreachable code
#pragma warning(disable: 4710)   // function 'x' not inlined
#pragma warning(disable: 4786)   // identifier was truncated to '255' characters in the debug information

// Things we need to disable to be able to compile with /Wall

#pragma warning(disable: 4548)   // expression before comma has no effect; expected expression with side-effect
#pragma warning(disable: 4820)   // 'x' bytes padding added after data member 'y'
#pragma warning(disable: 4265)   // class has virtual functions, but destructor is not virtual
#pragma warning(disable: 4668)   // 'x' is not defined as a preprocessor macro, replaceing with '0' for '#if/#elif'
#pragma warning(disable: 4619)   // #pragma warning : there is no warning number 'x'
#pragma warning(disable: 4571)   // catch (...) semantics changed since VC 7.1; SEH are no longer caught
#pragma warning(disable: 4917)   // 'x' : a GUID can only be associated with a class, interface or namespace
#pragma warning(disable: 4365)   // conversion from 'x' to 'y', signed/unsigned mismatch
#pragma warning(disable: 4640)   // 'x' : construction of local static object is not thread-safe
#pragma warning(disable: 4625)   // 'x' : copy constructor could not be generated because a base class copy constructor is inaccessible
#pragma warning(disable: 4626)   // 'x' : assignment operator could not be generated because a base class assignment operator is inaccessible

// This is needed for VS2005 without any platform sdk, basestd.h is full of these..

#pragma warning(disable: 4826)   // Conversion from 'x' to 'y' is sign-extended. This may cause unexpected runtime behavior.
#pragma warning(disable: 4191)   // type cast' : unsafe conversion from 'x' to 'y' Calling this function through the result pointer may cause your program to fail

#pragma warning(disable: 4370)   // layout of class has changed from a previous version of the compiler due to better packing
#pragma warning(disable: 4351)   // new behavior: elements of array 'x' will be default initialized

#pragma warning(disable: 4555)   // expression has no effect; expected expression with side-effect
#pragma warning(disable: 4574)   // 'x' is defined to be '0': did you mean to use '#if x'?

#pragma warning(disable: 4324)   // 'x' : structure was padded due to __declspec(align())

// In atlconv.h, atlalloc.h, etc
#pragma warning(disable: 4987)   // nonstandard extension used: 'throw (...)'

#pragma warning(disable: 4711)   // function 'x' selected for automatic inline expansion

#pragma warning(disable: 4748)   // /GS can not protect parameters and local variables
                                 // from local buffer overrun because optimizations
                                 // are disabled in function

#pragma warning(disable: 4200)   // nonstandard extension used : zero-sized array in struct/union
                                 // Cannot generate copy-ctor or copy-assignment operator when UDT
                                 // contains a zero-sized array

#pragma warning(disable: 4350)   // behavior change: 'x' called instead of 'y'
#pragma warning(disable: 4005)   // 'x' macro redefinition

//#pragma warning(disable: 4615)   // #pragma warning : unknown user warning type
//#pragma warning(disable: 4616)   // warning number 'x' out of range, must be between 'y' and 'z'

#pragma warning(disable: 6322)   // Except block empty.

#pragma warning(disable: 4435)   // 'x' : Object layout under /vd2 will change due to virtual base 'y'

#pragma warning(disable: 28159)  // Consider using another function instead (GetTickCount vs GetTickCount64)
#pragma warning(disable: 26135)  // Missing locking annotation
#pragma warning(disable: 26165)  // Possibly failing to release lock (in atlbase!)
#pragma warning(disable: 26167)  // Possibly releasing unheld lock (in atlbase!)
#pragma warning(disable: 28204)  // Only one of this overload is annotated
#pragma warning(disable: 28251)  // Inconsistent annotation for function
#pragma warning(disable: 28252)  // Inconsistent annotation for function
#pragma warning(disable: 28253)  // Inconsistent annotation for function

#pragma warning(disable: 4091)   // 'typedef ': ignored on left of 'x' when no variable is declared
#pragma warning(disable: 4456)   // declaration of 'x' hides previous local declaration
#pragma warning(disable: 4457)   // declaration of 'x' hides function parameter
#pragma warning(disable: 4458)   // declaration of 'x' hides class member
#pragma warning(disable: 4623)   // 'x': default constructor was implicitly defined as deleted
#pragma warning(disable: 4774)   // 'x' : format string expected in argument 3 is not a string literal
#pragma warning(disable: 5025)   // 'x': move assignment operator was implicitly defined as deleted
#pragma warning(disable: 5026)   // 'x': move constructor was implicitly defined as deleted because a base class move constructor is inaccessible or deleted
#pragma warning(disable: 5027)   // 'x': move assignment operator was implicitly defined as deleted because a base class move assignment operator is inaccessible or deleted

#if _MSC_VER >= 1911
#pragma warning(disable: 4768)   // __declspec attributes before linkage specification are ignored
#pragma warning(disable: 5045)   // Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
#pragma warning(disable: 4868)   // compiler may not enforce left-to-right evaluation order in braced initializer list
#endif

#if _MSC_VER >= 1920
#pragma warning(disable: 5031)   // #pragma warning(pop): likely mismatch, popping warning state pushed in different file (compiling source file 'x')
#pragma warning(disable: 5032)   // #pragma warning(push) with no corresponding #pragma warning(pop) (compiling source file 'x')
#endif

#if _MSC_VER >= 1925
#pragma warning(disable: 5204)   // 'x': class has virtual functions, but its trivial destructor is not virtual; instances of objects derived from this class may not be destructed correctly 
#endif

#endif // JETBYTE_TOOLS_ADMIN_WARNINGS_INCLUDED__

///////////////////////////////////////////////////////////////////////////////
// End of file: Warnings.h
///////////////////////////////////////////////////////////////////////////////
