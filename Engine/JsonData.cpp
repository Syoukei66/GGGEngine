#include "JsonData.h"
#include "NativeMethod.h"

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
  std::string str = NativeMethod::IO().TextFile_Read(path);
  this->root_ = parser.Parse(str.c_str());
}

void JsonData::Write(const char* path)
{
  if (this->root_)
  {
    return;
  }
  std::string str = this->root_->ToString();
  NativeMethod::IO().TextFile_Write(path, str);
}
