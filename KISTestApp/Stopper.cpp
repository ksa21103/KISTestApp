#include "stdafx.h"
#include "Stopper.h"

Event Stopper::m_stopEvent(true, false);

//----------------------------------------------------------------------------//
void Stopper::SetStopState()
{
    m_stopEvent.SetEvent();
}

//----------------------------------------------------------------------------//
bool Stopper::GetStopState() const
{
    return ::WaitForSingleObject(m_stopEvent.GetHandle(), 0) == WAIT_OBJECT_0;
}

//----------------------------------------------------------------------------//
HANDLE Stopper::GetHandle() const
{
    return m_stopEvent.GetHandle();
}

//----------------------------------------------------------------------------//
