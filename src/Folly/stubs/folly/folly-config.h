#pragma once

#ifdef _WIN32

//  Bring in windows.h here, very early in the folly inclusion graph.
//  Doing so avoids a packing/alignment bug that comes up when windows.h
//  is included late.
#include <windows.h>

#endif // _WIN32
