#include "Shader.h"
#include "NativeProcess.h"

// =================================================================
// Constructor / Destructor
// =================================================================
rcShader* rcShader::Create(const char* path)
{
  rcShader* ret = NativeProcess::Resource::ShaderLoad(path);
  ret->Resource::Init();
  return ret;
}
