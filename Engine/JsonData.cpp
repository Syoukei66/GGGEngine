#include "JsonData.h"
#include "NativeMethod.h"

// =================================================================
// Constructor / Destructor
// =================================================================
JsonData::JsonData(const char* path)
{
  JsonParser parser = JsonParser();
  std::string str =  NativeMethod::IO().TextFile_Read(path);
  this->root_ = parser.Parse(str.c_str());
}

JsonData::~JsonData()
{
  delete this->root_;
}
