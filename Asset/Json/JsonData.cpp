#include "JsonData.h"
#include "JsonParser.h"

#include <Core/Util/FileUtil.h>

// =================================================================
// Factory Method
// =================================================================
UniqueRef<rcJsonData> rcJsonData::CreateFromFile(const char* path)
{
  return UniqueRef<rcJsonData>(new rcJsonData(path));
}

// =================================================================
// Constructor / Destructor
// =================================================================
rcJsonData::rcJsonData(const char* path)
{
  JsonParser parser = JsonParser();
  std::string str = FileUtil::TextFile_Read(path);
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
  FileUtil::TextFile_Write(path, str);
}
