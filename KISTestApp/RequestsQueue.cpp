#include "stdafx.h"

#include <array>

#include "RequestsQueue.h"

void DeleteRequest(Request* request);

//----------------------------------------------------------------------------//
RequestsQueue::RequestsQueue(size_t maxSize)
    : m_maxSize(maxSize),
      m_mutex_not_empty(true, false),
      m_mutex_not_full(true, true)
{
}

//----------------------------------------------------------------------------//
RequestsQueue::~RequestsQueue()
{
    while (!m_queue.empty())
    {
        if (Request* request = m_queue.front())
        {
            DeleteRequest(request);
        }
        m_queue.pop();
    }
}

//----------------------------------------------------------------------------//
bool RequestsQueue::push(Stopper stopSignal, Request* request)
{
    const std::array<HANDLE, 2> handles{ stopSignal.GetHandle(), m_mutex_not_full.GetHandle() };

    bool bProcessed(false);
    while (!bProcessed)
    {
        switch (::WaitForMultipleObjects(handles.size(), handles.data(), FALSE, INFINITE))
        {
        case WAIT_OBJECT_0:
            return false;

        case WAIT_OBJECT_0 + 1:
            {
                CriticalSectionSentry csSentry(m_criticalSection);

                if (m_maxSize == 0 || m_queue.size() < m_maxSize)
                {
                    m_queue.push(request);

                    bProcessed = true;

                    m_mutex_not_empty.SetEvent();

                    if (m_maxSize > 0 && m_queue.size() >= m_maxSize)
                    {
                        m_mutex_not_full.ResetEvent();
                    }
                }
            }
            break;
        }
    }

    return true;
}

//----------------------------------------------------------------------------//
Request* RequestsQueue::pop(Stopper stopSignal)
{
    Request* result = nullptr;

    const std::array<HANDLE, 2> handles{ stopSignal.GetHandle(), m_mutex_not_empty.GetHandle() };

    while (result == nullptr)
    {
        switch (::WaitForMultipleObjects(handles.size(), handles.data(), FALSE, INFINITE))
        {
        case WAIT_OBJECT_0:
            return nullptr;

        case WAIT_OBJECT_0 + 1:
            {
                CriticalSectionSentry csSentry(m_criticalSection);

                if (!m_queue.empty())
                {
                    result = m_queue.front();
                    m_queue.pop();

                    m_mutex_not_full.SetEvent();

                    if (m_queue.empty())
                    {
                        m_mutex_not_empty.ResetEvent();
                    }
                }
            }
            break;
        }
    }

    return result;
}

//----------------------------------------------------------------------------//
