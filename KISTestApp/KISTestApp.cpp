// KISTestApp.cpp : Defines the entry point for the console application.

#include "stdafx.h"

#include <chrono>

#include "RequestOperations.h"

////////////////////////////////////////////////////////////////////////////////
// Откуда-то дано:

// Тип Stopper должен быть определён вами и должен представлять собой механизм
// досрочной остановки выполняемого действия (предполагается, что GetRequest и
// ProcessRequest будут его корректно использовать).
// class Stopper;
// class Request { };

// возвращает NULL, если объект stopSignal указывает на необходимость остановки,
// либо указатель на память, которую в дальнейшем требуется удалить
//Request* GetRequest(Stopper stopSignal);

// обрабатывает запрос, но память не удаляет, завершает обработку досрочно, если
// объект stopSignal указывает на необходимость остановки
//void ProcessRequest(Request* request, Stopper stopSignal);

//void DeleteRequest(Request* request);

////////////////////////////////////////////////////////////////////////////////
//1.	С++ 11 использовать можно.
//2.	Решение должно работать на Windows XP.
//3.	Тип Stopper должен быть определён вами и должен представлять собой механизм досрочной остановки выполняемого действия (предполагается, что GetRequest и ProcessRequest будут его корректно использовать).
//4.	Вызов GetRequest может не сразу возвращать задания.
//5.	Вызов ProcessRequest может не мгновенно обрабатывать задание.
//6.	Синхронизационная часть задачи должна использовать Win32 API.

////////////////////////////////////////////////////////////////////////////////
// 1) Организовать в несколько потоков (переменное число, но не менее двух) приём запросов, для этого класть в одну очередь задания, возвращаемые функцией GetRequest.
// 2) Запустить несколько обрабатывающих запросы потоков (переменное число, но не менее двух), которые должны обрабатывать поступающие из очереди задания с помощью ProcessRequest.
// 3) Поработать в течение 30 секунд.
// 4) Корректно остановить все потоки.Если остались необработанные задания, не обрабатывать их и корректно удалить.
// 5) Завершить программу.

// обрабатывает запрос, но память не удаляет, завершает обработку досрочно, если
// объект stopSignal указывает на необходимость остановки
void ProcessRequest(Request* request, Stopper stopSignal);

////////////////////////////////////////////////////////////////////////////////
// Время работы приложения
const std::chrono::seconds kWorkTime{ 30 };

int main()
{
    return 0;
}

