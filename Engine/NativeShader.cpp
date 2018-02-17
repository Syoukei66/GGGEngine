#include "NativeShader.h"
#include "NativeObjectFactory.h"

INativeShader* INativeShader::Create(const char* path)
{
  INativeShader* ret = NativeObjectFactory::CreateShader(path);

  std::string full_path = path;
  int path_i = full_path.find_last_of("\\") + 1;
  int ext_i = full_path.find_last_of(".");
  ret->SetName(full_path.substr(path_i, ext_i - path_i));

  return ret;
}
