#pragma once

//  This exists as a workaround for an Mso library build issue.
//
//  Mso doesn't have an official debug build, so their code is built
//  with "release" pre-processor directives. This means no #ifdef DEBUG
//  code is included.
//
//  Our project does have a debug build, and we define macros like DEBUG.
//  This is a problem because the pre-processor gives us "debug" Mso
//  headers to use with "release" Mso libs.
//
//  To work around this, all Mso headers are included via this stub.
//  In here, we switch the pre-processor from "debug" mode to "release"
//  and pull in all Mso headers that we need for the project.

#pragma push_macro("DEBUG")
#undef DEBUG
#pragma push_macro("_DEBUG")
#undef _DEBUG
#pragma push_macro("NDEBUG")
#undef NDEBUG


#include <core/TCntPtr.h>
#include <object/make.h>
#include <object/refCountedObject.h>


#pragma pop_macro("NDEBUG")
#pragma pop_macro("_DEBUG")
#pragma pop_macro("DEBUG")
