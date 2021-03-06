#pragma once
#ifndef JETBYTE_TOOLS_WIN32_EXPANDABLE_BUFFER_INCLUDED__
#define JETBYTE_TOOLS_WIN32_EXPANDABLE_BUFFER_INCLUDED__
///////////////////////////////////////////////////////////////////////////////
// File: ExpandableBuffer.h
///////////////////////////////////////////////////////////////////////////////
//
// Copyright 1998 JetByte Limited.
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

#include <functional>   // for std::swap

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools::Win32
///////////////////////////////////////////////////////////////////////////////

namespace JetByteTools {
namespace Win32 {

///////////////////////////////////////////////////////////////////////////////
// TExpandableBuffer
///////////////////////////////////////////////////////////////////////////////

/// A template class for an expandable buffer, that is a buffer that can be
/// expanded and which will, if expanded, maintain its contents.
/// \ingroup Templates
/// \ingroup CPlusPlusTools

template <class T> class TExpandableBuffer
{
   public :

      /// Create a buffer of the specified initialSize. If the size is 0 then
      /// the buffer must be resized or expanded before use.
      explicit TExpandableBuffer(
         size_t initialSize = 0);

      TExpandableBuffer(
         const TExpandableBuffer &rhs);

      ~TExpandableBuffer();

      TExpandableBuffer &operator=(
         const TExpandableBuffer &rhs);

      /// Access the buffer.

      T *GetBuffer() const;

      /// Access the buffer.

      operator T *() const;

      /// Obtain the size of the buffer

      size_t GetSize() const;

      /// Make the buffer bigger, but do not copy the previous contents to
      /// the new buffer. Return the new size.

      //lint -esym(534, JetByteTools::Win32::TExpandableBuffer<*>::Resize) (Ignoring return value of function)
      size_t Resize(
         size_t newSize);

      /// Make the buffer bigger and copy the previous contents to the new
      /// buffer. Return the new size.

      //lint -esym(534, JetByteTools::Win32::TExpandableBuffer<*>::Expand) (Ignoring return value of function)
      size_t Expand(
         size_t newSize);

      /// Remove the actual memory used to store the date from the buffer. The
      /// buffer is left with a buffer of size 0. The caller is responsible for
      /// destroying the memory returned, using delete [], once they've finished
      /// with it

      T *ReleaseBuffer();

      /// Swap the internal storage and state from this buffer with the supplied
      /// buffer

      void Swap(
         TExpandableBuffer &rhs);

   private :

      T *m_pBuffer;

      size_t m_logicalSize;

      size_t m_physicalSize;
};

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction
///////////////////////////////////////////////////////////////////////////////

template <class T>
TExpandableBuffer<T>::TExpandableBuffer(
   const size_t initialSize)
   :  m_pBuffer(nullptr),
      m_logicalSize(0),
      m_physicalSize(0)
{
   Resize(initialSize);
}

template <class T>
TExpandableBuffer<T>::TExpandableBuffer(
   const TExpandableBuffer<T> &rhs)
   :  m_pBuffer(nullptr),
      m_logicalSize(0),
      m_physicalSize(0)
{
   Resize(rhs.m_logicalSize);

   for (size_t i = 0; i < m_logicalSize; i++)
   {
      m_pBuffer[i] = rhs.m_pBuffer[i];
   }
}

template <class T>
TExpandableBuffer<T>::~TExpandableBuffer()
{
   delete[] m_pBuffer;
}

template <class T>
TExpandableBuffer<T> &TExpandableBuffer<T>::operator=(
   const TExpandableBuffer<T> &rhs)
{
   if (this != &rhs)
   {
      Resize(rhs.m_logicalSize);

      for (size_t i = 0; i < m_logicalSize; i++)
      {
         m_pBuffer[i] = rhs.m_pBuffer[i];
      }
   }

   return *this;
}

///////////////////////////////////////////////////////////////////////////////
// Access functions
///////////////////////////////////////////////////////////////////////////////

template <class T>
T *TExpandableBuffer<T>::GetBuffer() const
{
   return m_pBuffer;
}

template <class T>
TExpandableBuffer<T>::operator T *() const
{
   return GetBuffer();
}

template <class T>
size_t TExpandableBuffer<T>::GetSize() const
{
   return m_logicalSize;
}

template <class T>
T *TExpandableBuffer<T>::ReleaseBuffer()
{
   T *pBuffer = m_pBuffer;

   m_pBuffer = nullptr;
   m_logicalSize = 0;
   m_physicalSize = 0;

   return pBuffer;
}

template <class T>
void TExpandableBuffer<T>::Swap(
   TExpandableBuffer<T> &rhs)
{
   std::swap(m_pBuffer, rhs.m_pBuffer);
   std::swap(m_logicalSize, rhs.m_logicalSize);
   std::swap(m_physicalSize, rhs.m_physicalSize);
}

///////////////////////////////////////////////////////////////////////////////
// Make the buffer bigger
///////////////////////////////////////////////////////////////////////////////

template <class T>
size_t TExpandableBuffer<T>::Resize(
   const size_t newSize)
{
   if (m_physicalSize < newSize)
   {
      auto *pNewBuffer = new T[newSize];

      delete[] m_pBuffer;

      m_pBuffer = pNewBuffer;

      m_logicalSize = newSize;
      m_physicalSize = newSize;
   }
   else
   {
      m_logicalSize = newSize;
   }

   return m_logicalSize;
}

template <class T>
size_t TExpandableBuffer<T>::Expand(
   const size_t newSize)
{
   if (m_physicalSize < newSize)
   {
      auto *pNewBuffer = new T[newSize];

      if (m_pBuffer)
      {
         for (size_t i = 0; i < m_logicalSize; i++)
         {
            pNewBuffer[i] = m_pBuffer[i];
         }

         delete[] m_pBuffer;
      }

      m_pBuffer = pNewBuffer;

      m_logicalSize = newSize;
      m_physicalSize = newSize;
   }
   else
   {
      m_logicalSize = newSize;
   }

   return m_logicalSize;
}

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools::Win32
///////////////////////////////////////////////////////////////////////////////

} // End of namespace Win32
} // End of namespace JetByteTools

#endif // JETBYTE_TOOLS_WIN32_EXPANDABLE_BUFFER_INCLUDED__

///////////////////////////////////////////////////////////////////////////////
// End of file: ExpandableBuffer.h
///////////////////////////////////////////////////////////////////////////////
