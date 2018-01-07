#include "NativeModel.h"
#include "NativeObjectFactory.h"

INativeModel* INativeModel::Create(const char* directory_path, const char* name)
{
  return NativeObjectFactory::CreateModel(directory_path, name);
}
