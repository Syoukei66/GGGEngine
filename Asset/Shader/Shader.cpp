#include "Shader.h"

// =================================================================
// Factory Method
// =================================================================
UniqueRef<rcShader> rcShader::CreateFromFile(const char* path)
{
  return NativeProcess::Resource::ShaderLoad(path);
}
