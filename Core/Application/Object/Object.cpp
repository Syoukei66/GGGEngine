#include "Object.h"

// =================================================================
// Setter / Getter
// =================================================================
size_t GGObject::GetMemorySize() const
{
  std::string message = "����`��MemorySize���Q�Ƃ���܂���(";
  message.append(this->GetObjectName());
  message.append(")");
  Log::Error(message.c_str());
  return 0;
}

size_t GGObject::GetVideoMemorySize() const
{
  std::string message = "����`��VideoMemorySize���Q�Ƃ���܂���(";
  message.append(this->GetObjectName());
  message.append(")");
  Log::Error(message.c_str());
  return 0;
}
