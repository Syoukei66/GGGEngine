#include "JsonData.h"
#include "../Core/NativeProcess.h"

// =================================================================
// Constructor / Destructor
// =================================================================
JsonData::JsonData()
  : root_(nullptr)
{}

JsonData::~JsonData()
{
  this->root_->Release();
}

void JsonData::Read(const char* path)
{
  JsonParser parser = JsonParser();
  std::string str = NativeProcess::IO::TextFile_Read(path);
  this->root_ = parser.Parse(str.c_str());
}

void JsonData::Write(const char* path)
{
  if (this->root_)
  {
    return;
  }
  std::string str = this->root_->ToString();
  NativeProcess::IO::TextFile_Write(path, str);
}
