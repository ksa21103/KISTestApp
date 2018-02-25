#include "stdafx.h"

#include "SynchPrimitives.h"

//----------------------------------------------------------------------------//
Mutex::Mutex()
{
    m_mutex = ::CreateMutex(nullptr, FALSE, nullptr);
}

//----------------------------------------------------------------------------//
Mutex::~Mutex()
{
    ::DeleteObject(m_mutex);
}

//----------------------------------------------------------------------------//
Mutex::operator HANDLE() const
{
    return m_mutex;
}

//----------------------------------------------------------------------------//
CriticalSection::CriticalSection()
{
    ::InitializeCriticalSection(&m_cs);
}

//----------------------------------------------------------------------------//
CriticalSection::~CriticalSection()
{
    ::DeleteCriticalSection(&m_cs);
}

//----------------------------------------------------------------------------//
void CriticalSection::enter()
{
    ::EnterCriticalSection(&m_cs);
}

//----------------------------------------------------------------------------//
void CriticalSection::leave()
{
    ::LeaveCriticalSection(&m_cs);
}

//----------------------------------------------------------------------------//
Event::Event(bool bManualReset, bool bInitialState)
{
    m_hEvent = ::CreateEvent(nullptr,
                             bManualReset  ? TRUE : FALSE,
                             bInitialState ? TRUE : FALSE,
                             nullptr);
}

//----------------------------------------------------------------------------//
Event::~Event()
{
    ::DeleteObject(m_hEvent);
}

//----------------------------------------------------------------------------//
void Event::SetEvent()
{
    ::SetEvent(m_hEvent);
}

//----------------------------------------------------------------------------//
void Event::ResetEvent()
{
    ::ResetEvent(m_hEvent);
}

//----------------------------------------------------------------------------//
HANDLE Event::GetHandle() const
{
    return m_hEvent;
}

//----------------------------------------------------------------------------//
