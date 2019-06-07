#include <Engine/Director.h>
#define NOMINMAX
#include <windows.h>

void Log::Out(Level level, const char* message)
{
  if (Director::IsIgnoreLog())
  {
    return;
  }
  std::string str = message;
  std::cout << Log::LEVEL_NAMES[static_cast<T_UINT32>(level)] << " : " << message << std::endl;
  OutputDebugString((str + "\n").c_str());
}