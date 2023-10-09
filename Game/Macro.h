#pragma once


#include "stdafx.h"

#define ERR(str) Error::finish(str, T(__FUNCTION__), __LINE__);