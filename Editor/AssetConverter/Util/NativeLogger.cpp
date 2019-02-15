#include <Windows.h>
#include <string>
#include <Core/Util/Logger.h>

void Log::Out(Level level, const char* message)
{
  std::string str = message;
  std::cout << Log::LEVEL_NAMES[static_cast<T_UINT32>(level)] << " : " << message << std::endl;
  OutputDebugString((str + "\n").c_str());
}