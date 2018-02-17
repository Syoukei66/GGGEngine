#include "ModelData.h"
#include "Director.h"
#include "UserResourcePool.h"

ModelData* ModelData::DynamicLoad(const char* path)
{
  return UserResourcePool::GetInstance().DynamicLoad<ModelData>(path);
}

// =================================================================
// Constructor / Destructor
// =================================================================
ModelData::ModelData(const char* path)
  : FileResource("ModelData", path)
{}

// =================================================================
// Methods
// =================================================================
INativeModel* ModelData::NativeLoadProcess(const std::string& path)
{
  std::string directory_path = std::string();
  std::string file_name = std::string();
  std::string extension = std::string();
  std::string buf = std::string();

  const char* p = path.c_str();
  while (*p != '\0')
  {
    buf.append(p, 1);
    if (file_name.length() == 0)
    {
      if (*p == '/')
      {
        directory_path.append(buf);
        buf.clear();
        ++p;
        continue;
      }
      if (*p == '.')
      {
        file_name.append(buf);
        buf.clear();
        ++p;
        continue;
      }
    }
    ++p;
  }
  file_name.append(buf);
  extension.append(buf);

  return INativeModel::Create(directory_path.c_str(), file_name.c_str(), extension.c_str());
}
