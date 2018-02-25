#pragma once

#include <queue>
#include <functional>

#include "Request.h"
#include "Stopper.h"

////////////////////////////////////////////////////////////////////////////////
// class RequestsQueue - очередь заданий
class RequestsQueue
{
public:

    // Конструктор
    /*
     * @param size_t maxSize - максимально допустимое количество элементов в очереди
     *      Если 0 - длина очереди не ограниченна.
     */
    RequestsQueue(size_t maxSize);

    // Положить задание в очередь
    /*
     * @param Stopper stopSignal - признак необходимости завершения работы
     * @param Request* request - добавляемое в очередь задание
     * @return bool - true, если задание было добавлено в очередь,
     *      false - иначе (например в случае, если в процессе добавления задания
     *          был установлен признак завершения работы приложения
     * ВНИМАНИЕ: если очередь имеет ограниченную длину и заполнена, то
     *           возврат из функции будет выполнен только в случае выполнения
     *           добавления элемента в очередь или в случае установки признака
     *           завершения работы приложения
     */
    bool        push(Stopper stopSignal, Request* request);

    // Получить задание из очереди
    /*
     * @param Stopper stopSignal - признак необходимости завершения работы
     * @return Request* - указатель на задание, извлеченное из очереди.
     * ВНИМАНИЕ: возврат из функции будет выполнен только в случае получения задания
     *           или в случае установки признака завершения работы приложения - в этом
     *              случае будет возвращен нулевой указатель (nullptr)
     */
     Request*    pop (Stopper stopSignal);

    // Обработка и удаление всех элементов очереди заданий
    /**
     * Внимание: функция не является потокобезопасной и работает без синхронизаций
     *
     * @param const std::function<void(Request*)>& fnc - функция для предварительной
     *      обработки удаляемого задания
     */
    void        processAndEraseThreadUnsafe(const std::function<void(Request*)>& fnc);

private:

    const size_t    m_maxSize;

    using RQueue = std::queue<Request*>;
    RQueue          m_queue;

    CriticalSection m_criticalSection;
    Event           m_mutex_not_empty;
    Event           m_mutex_not_full;
};

