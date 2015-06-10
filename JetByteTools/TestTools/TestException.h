#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef JETBYTE_TOOLS_TEST_TEST_EXCEPTION_INCLUDED__
#define JETBYTE_TOOLS_TEST_TEST_EXCEPTION_INCLUDED__
///////////////////////////////////////////////////////////////////////////////
// File: TestException.h 
///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2003 JetByte Limited.
//
// JetByte Limited grants you ("Licensee") a non-exclusive, royalty free, 
// licence to use, modify and redistribute this software in source and binary 
// code form, provided that i) this copyright notice and licence appear on all 
// copies of the software; and ii) Licensee does not utilize the software in a 
// manner which is disparaging to JetByte Limited.
//
// This software is provided "as is" without a warranty of any kind. All 
// express or implied conditions, representations and warranties, including
// any implied warranty of merchantability, fitness for a particular purpose
// or non-infringement, are hereby excluded. JetByte Limited and its licensors 
// shall not be liable for any damages suffered by licensee as a result of 
// using, modifying or distributing the software or its derivatives. In no
// event will JetByte Limited be liable for any lost revenue, profit or data,
// or for direct, indirect, special, consequential, incidental or punitive
// damages, however caused and regardless of the theory of liability, arising 
// out of the use of or inability to use software, even if JetByte Limited 
// has been advised of the possibility of such damages.
//
// This software is not designed or intended for use in on-line control of 
// aircraft, air traffic, aircraft navigation or aircraft communications; or in 
// the design, construction, operation or maintenance of any nuclear 
// facility. Licensee represents and warrants that it will not use or 
// redistribute the Software for such purposes. 
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Lint options
//
//lint -save
//
///////////////////////////////////////////////////////////////////////////////

#pragma warning(disable : 4786)

#include "JetByteTools\Win32Tools\Exception.h"

#include <string>

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools::Email::Test
///////////////////////////////////////////////////////////////////////////////

namespace JetByteTools {
namespace Test {

///////////////////////////////////////////////////////////////////////////////
// CTestException
///////////////////////////////////////////////////////////////////////////////

class CTestException : public JetByteTools::Win32::CException
{
   public :

      CTestException(
         const JetByteTools::Win32::_tstring &where, 
         const JetByteTools::Win32::_tstring &message);
};

#define THROW_ON_FAILURE(w, t) do{if(!(t)){throw CTestException(w, _T("Test Failed:")## _T(#t));}}while(0)

#define THROW_ON_NO_EXCEPTION(w, e) do{try{e();throw CTestException(w, _T("No Exception from: ")## _T(#e) ## _T("()"));}catch(CTestException &){throw;}catch(...){}}while(0)

#define THROW_ON_NO_EXCEPTION_1(w, e, p) do{try{e(p);throw CTestException(w, _T("No Exception from: ")## _T(#e) ## _T("(") ## _T(#p) ## _T(")"));}catch(CTestException &){throw;}catch(...){}}while(0)

#define THROW_ON_NO_EXCEPTION_2(w, e, p1, p2) do{try{e(p1, p2);throw CTestException(w, _T("No Exception from: ")## _T(#e) ## _T("(") ## _T(#p1) ## _T(", ") ## _T(#p2) ## _T(")"));}catch(CTestException &){throw;}catch(...){}}while(0)

#define THROW_ON_NO_EXCEPTION_3(w, e, p1, p2, p3) do{try{e(p1, p2, p3);throw CTestException(w, _T("No Exception from: ")## _T(#e) ## _T("(") ## _T(#p1) ## _T(", ") ## _T(#p2) ## _T(", ") ## _T(#p3) ## _T(")"));}catch(CTestException &){throw;}catch(...){}}while(0)

#define THROW_ON_NO_EXCEPTION_4(w, e, p1, p2, p3, p4) do{try{e(p1, p2, p3, p4);throw CTestException(w, _T("No Exception from: ")## _T(#e) ## _T("(") ## _T(#p1) ## _T(", ") ## _T(#p2) ## _T(", ") ## _T(#p3) ## _T(", ") ## _T(#p4) ## _T(")"));}catch(CTestException &){throw;}catch(...){}}while(0)

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools::Test
///////////////////////////////////////////////////////////////////////////////

} // End of namespace Test
} // End of namespace JetByteTools 

///////////////////////////////////////////////////////////////////////////////
// Lint options
//
//lint -restore
//
///////////////////////////////////////////////////////////////////////////////

#endif // JETBYTE_TOOLS_TEST_TEST_EXCEPTION_INCLUDED__

///////////////////////////////////////////////////////////////////////////////
// End of file: TestException.h
///////////////////////////////////////////////////////////////////////////////