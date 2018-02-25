#pragma once

#include <atomic>

////////////////////////////////////////////////////////////////////////////////
// class Request - задание для обработки
class Request
{
public:

	Request();
	virtual ~Request();

    // Получить идентификатор задания
    const int ID() const
        {   return m_nRequestIndex; }

private:

    // Идентификатор задания
    const int               m_nRequestIndex;

    // Счетчик заданий
    static std::atomic<int> s_nRequestGlobalIndex;
};
