#include "ShaderResource.h"

const ShaderResource* ShaderResource::DynamicLoad(const char* path)
{
  return nullptr;
}

// =================================================================
// Constructor / Destructor
// =================================================================
ShaderResource::ShaderResource(const char* path)
  : FileResource("ShaderData", path)
{
}

// =================================================================
// Methods
// =================================================================
INativeShader* ShaderResource::NativeLoadProcess(const std::string& path)
{
  return INativeShader::Create(path.c_str());
}
