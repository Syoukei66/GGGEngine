#include "Object.h"

// =================================================================
// Setter / Getter
// =================================================================
size_t GGObject::GetMemorySize() const
{
  std::string message = "未定義のMemorySizeが参照されました(";
  message.append(this->GetObjectName());
  message.append(")");
  Log::Error(message.c_str());
  return 0;
}

size_t GGObject::GetVideoMemorySize() const
{
  std::string message = "未定義のVideoMemorySizeが参照されました(";
  message.append(this->GetObjectName());
  message.append(")");
  Log::Error(message.c_str());
  return 0;
}
