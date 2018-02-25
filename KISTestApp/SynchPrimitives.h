#pragma once

#include <windows.h>

////////////////////////////////////////////////////////////////////////////////
// class Mutex - реализация мьютекса в парадигме RAII
class Mutex
{
public:

    Mutex();
    ~Mutex();

    operator HANDLE() const;

private:

    HANDLE m_mutex;
};

////////////////////////////////////////////////////////////////////////////////
// class CriticalSection - реализация критической секции в парадигме RAII
class CriticalSection
{
public:

    CriticalSection();
    ~CriticalSection();

    void enter();
    void leave();

private:

    CRITICAL_SECTION m_cs;
};

////////////////////////////////////////////////////////////////////////////////
// class CriticalSectionSentry - вход в критическую секцию и выход из нее в парадигме RAII
class CriticalSectionSentry
{
public:

    CriticalSectionSentry(CriticalSection& cs)
        : m_cs(cs)
    {
        m_cs.enter();
    }

    ~CriticalSectionSentry()
    {
        m_cs.leave();
    }

private:

    CriticalSection & m_cs;
};

////////////////////////////////////////////////////////////////////////////////
// class Event - реализация события в парадигме RAII
class Event
{
public:

    // Конструктор
    /*
     * @param bool bManualReset - признак автоматического сброса события
     * @param bool bInitialState - начальное состояние события:
     *      true - установлено, false - сброшено
     */
    Event(bool bManualReset, bool bInitialState);

    // Деструктор
    ~Event();

    // Установить событие
    void    SetEvent();

    // Сбросить событие
    void    ResetEvent();

    // Получить описатель события
    HANDLE  GetHandle() const;

private:

    HANDLE m_hEvent;
};
