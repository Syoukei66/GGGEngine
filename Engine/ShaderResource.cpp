#include "ShaderResource.h"
#include "UserResourcePool.h"

ShaderResource* ShaderResource::DynamicLoad(const char* path)
{
  return UserResourcePool::GetInstance().DynamicLoad<ShaderResource>(path);
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
