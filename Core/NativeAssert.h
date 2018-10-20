#pragma once

#include "NativeLogger.h"

namespace Assertion
{
FORCE_INLINE void Assert(bool cause, const char* message)
{
#ifdef _DEBUG
  if (!cause) Log::Assert(message);
#endif
}
}

#define NATIVE_ASSERT(Cause, Message) Assertion::Assert((bool)(Cause), Message);
