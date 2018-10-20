#include "Shader.h"
#include "NativeProcess.h"

// =================================================================
// Factory Method
// =================================================================
UniqueResource<rcShader> rcShader::CreateFromFile(const char* path)
{
  UniqueResource<rcShader> ret = NativeProcess::Resource::ShaderLoad(path);
  ret->Resource::Init();
  return ret;
}
