#include <Core/NativeLogger.h>
#include <Windows.h>
#include <string>

void Log::Out(Level level, const char* message)
{
  std::string str = message;
  OutputDebugString((str + "\n").c_str());
}