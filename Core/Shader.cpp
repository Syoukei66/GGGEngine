#include "Shader.h"
#include "NativeProcess.h"

// =================================================================
// Factory Method
// =================================================================
rcShader* rcShader::CreateFromFile(const char* path)
{
  rcShader* ret = NativeProcess::Resource::ShaderLoad(path);
  ret->Resource::Init();
  return ret;
}
