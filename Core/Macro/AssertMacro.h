#pragma once

#ifdef NDEBUG
  #define GG_ASSERT(...)
  #define GG_ASSERT_IS_NULL(...)
  #define GG_ASSERT_NO_ENTRY(...)
#else
  #define GG_ASSERT(Cause, Message) do\
  {\
    if ((bool)(Cause) == false)\
    {\
      Log::Assert(Message);\
      __debugbreak();\
    }\
  } while (0)
  #define GG_ASSERT_IS_NULL(Ptr) do\
  {\
    if (Ptr == nullptr)\
    {\
      Log::Assert(#Ptr "がnullptrでした。");\
      __debugbreak();\
    }\
  } while (0)
  #define GG_ASSERT_NO_ENTRY() do\
  {\
    Log::Assert("想定していないコードが実行されました。");\
    __debugbreak();\
  } while (0)
#endif
