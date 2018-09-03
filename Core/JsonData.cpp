#include "JsonData.h"
#include "../Core/NativeProcess.h"

// =================================================================
// Factory Method
// =================================================================
rcJsonData* rcJsonData::CreateFromFile(const char* path)
{
  rcJsonData* ret = new rcJsonData(path);
  ret->Resource::Init();
  return ret;
}

// =================================================================
// Constructor / Destructor
// =================================================================
rcJsonData::rcJsonData(const char* path)
{
  JsonParser parser = JsonParser();
  std::string str = NativeProcess::IO::TextFile_Read(path);
  this->root_ = parser.Parse(str.c_str());
}

rcJsonData::~rcJsonData()
{
  this->root_->Release();
}

// =================================================================
// Methods
// =================================================================
void rcJsonData::Write(const char* path)
{
  if (this->root_)
  {
    return;
  }
  std::string str = this->root_->ToString();
  NativeProcess::IO::TextFile_Write(path, str);
}
