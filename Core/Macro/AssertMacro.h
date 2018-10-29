#pragma once

#include <Core/Common/Logger.h>

namespace Assertion
{
static GG_INLINE void Assert(bool cause, const char* message)
{
  if (!cause) Log::Assert(message);
}
}

#ifdef NDEBUG
  #define GG_ASSERT(...)
  #define GG_ASSERT_IS_NULL(...)
  #define GG_ASSERT_NO_ENTRY(...)
#else
  #define GG_ASSERT(Cause, Message) Assertion::Assert((bool)(Cause), Message)
  #define GG_ASSERT_IS_NULL(Ptr) Assertion::Assert(Ptr != nullptr, #Ptr "��nullptr�ł����B")
  #define GG_ASSERT_NO_ENTRY() Assertion::Assert(false, "�z�肵�Ă��Ȃ��R�[�h�����s����܂����B")
#endif
