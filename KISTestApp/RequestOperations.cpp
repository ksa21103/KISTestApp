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
// обрабатывает запрос, но память не удаляет, завершает обработку досрочно, если
// объект stopSignal указывает на необходимость остановки
void ProcessRequest(Request* request, Stopper stopSignal)
{
    if (!stopSignal.GetStopState())
    {
        // Собственно обработка запроса
        std::cout << "Process request: ID = " << request->ID() << ", thread = " << std::this_thread::get_id() << ";\n";
    }

    // Удаление запроса
    DeleteRequest(request);
}

//----------------------------------------------------------------------------//
// Удаление запроса
void DeleteRequest(Request* request)
{
    std::cout << "Delete request: ID = " << request->ID() << ", ptr = 0x" << request << ", thread = " << std::this_thread::get_id() << ";\n";

    delete request;
}

//----------------------------------------------------------------------------//
