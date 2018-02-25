#include "stdafx.h"
#include "Request.h"

std::atomic<int> Request::s_nRequestGlobalIndex = { 0 };

//----------------------------------------------------------------------------//
Request::Request()
    : m_nRequestIndex(s_nRequestGlobalIndex++)
{
}

//----------------------------------------------------------------------------//
Request::~Request()
{
}

//----------------------------------------------------------------------------//
