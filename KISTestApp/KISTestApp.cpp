// KISTestApp.cpp : Defines the entry point for the console application.

#include "stdafx.h"

#include <chrono>
#include <thread>
#include <vector>

#include "RequestOperations.h"

//----------------------------------------------------------------------------//
// Получение события и укладывание в очередь
void GetAndPushRequest(Stopper& stopper, RequestsQueue* requestsQueue)
{
    while (!stopper.GetStopState())
    {
        if (Request* request = GetRequest(stopper))
        {
            if (!requestsQueue->push(stopper, request))
            {
                DeleteRequest(request);
            }
        }
    }
}

//----------------------------------------------------------------------------//
// Извлечение и обработка события
void PopAndProcessRequest(Stopper& stopper, RequestsQueue* requestsQueue)
{
    while (!stopper.GetStopState())
    {
        if (Request* request = requestsQueue->pop(stopper))
        {
            ProcessRequest(request, stopper);
        }
    }
}

//----------------------------------------------------------------------------//
int main()
{
    Stopper         stopper;

    // Время работы приложения
    const std::chrono::seconds kWorkTime{ 30 };

    // Максимальная длина очереди
    const size_t    kMaxQueueLength = 1024;

    // Очередь сообщений
    std::unique_ptr<RequestsQueue> requestsQueue = std::make_unique<RequestsQueue>(kMaxQueueLength);

    // Определим количество ядер
    const size_t kHardwareThreadsCount = std::thread::hardware_concurrency();

    // 1) Организовать в несколько потоков (переменное число, но не менее двух) приём запросов,
    //    для этого класть в одну очередь задания, возвращаемые функцией GetRequest.
    // 2) Запустить несколько обрабатывающих запросы потоков (переменное число, но не менее двух),
    //    которые должны обрабатывать поступающие из очереди задания с помощью ProcessRequest.
    const size_t kInputThreadsCountMin = 2;
    const size_t kThreadsCount = max(kHardwareThreadsCount / 2, kInputThreadsCountMin);
    std::vector<std::thread> threads;
    threads.reserve(kThreadsCount * 2);
    for (size_t index = 0; index < kThreadsCount; ++index)
    {
        threads.push_back(std::thread([&]() { GetAndPushRequest(stopper, requestsQueue.get()); }));
    }
    for (size_t index = 0; index < kThreadsCount; ++index)
    {
        threads.push_back(std::thread([&]() { PopAndProcessRequest(stopper, requestsQueue.get()); }));
    }

    // 3) Поработать в течение 30 секунд.
    std::this_thread::sleep_for(kWorkTime);
    stopper.SetStopState();

    // 4) Корректно остановить все потоки. Если остались необработанные задания, не обрабатывать их и корректно удалить.
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
    requestsQueue.reset();

    // 5) Завершить программу.
    return 0;
}
