#include "../Core/NativeLogger.h"
#include <Windows.h>

void Log::Out(Level level, const char* message)
{
  std::string str = message;
  OutputDebugString((str + "\n").c_str());
}