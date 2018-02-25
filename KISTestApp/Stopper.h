#pragma once

#include "SynchPrimitives.h"

////////////////////////////////////////////////////////////////////////////////
// class Stopper - признак завершения работы
class Stopper
{
public:

    // Установить признак завершения работы
    void    SetStopState();

    // Получить признак завершения работы
    bool    GetStopState() const;

    // Получить описатель события, реализующего завершение работы
    HANDLE  GetHandle() const;

private:

    static Event m_stopEvent;
};

