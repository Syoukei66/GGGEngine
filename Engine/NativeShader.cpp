#include "NativeShader.h"
#include "NativeProcess.h"

INativeShader* INativeShader::Create(const char* path)
{
  INativeShader* ret = NativeProcess::Factory::CreateShader(path);

  std::string full_path = path;
  int path_i = full_path.find_last_of("\\") + 1;
  int ext_i = full_path.find_last_of(".");
  ret->SetName(full_path.substr(path_i, ext_i - path_i));

  return ret;
}
