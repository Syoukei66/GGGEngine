#include "Shader.h"

// =================================================================
// Factory Method
// =================================================================
UniqueRef<rcShader> rcShader::CreateFromFile(const char* path)
{
  return Application::GetPlatform()->GetGraphicsAPI()->ShaderLoad(path);
}
