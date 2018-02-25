#include "stdafx.h"

#include "RequestOperations.h"

//----------------------------------------------------------------------------//
Request* GetRequest(Stopper stopSignal)
{
    if (stopSignal.GetStopState())
        return nullptr;

    Request* request = nullptr;

    try
    {
        request = new Request();
        std::cout << "New request: ID = " << request->ID() << ", ptr = 0x" << request << ", thread = " << std::this_thread::get_id() << ";\n";
    }
    catch (std::bad_alloc&)
    {
        std::cout << "No memory: thread = " << std::this_thread::get_id() << ";\n";
    }

    return request;
}

//----------------------------------------------------------------------------//
// ������������ ������, �� ������ �� �������, ��������� ��������� ��������, ����
// ������ stopSignal ��������� �� ������������� ���������
void ProcessRequest(Request* request, Stopper stopSignal)
{
    if (!stopSignal.GetStopState())
    {
        // ���������� ��������� �������
        std::cout << "Process request: ID = " << request->ID() << ", thread = " << std::this_thread::get_id() << ";\n";
    }

    // �������� �������
    DeleteRequest(request);
}

//----------------------------------------------------------------------------//
// �������� �������
void DeleteRequest(Request* request)
{
    std::cout << "Delete request: ID = " << request->ID() << ", ptr = 0x" << request << ", thread = " << std::this_thread::get_id() << ";\n";

    delete request;
}

//----------------------------------------------------------------------------//
