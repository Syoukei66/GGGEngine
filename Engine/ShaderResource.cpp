#include "ShaderResource.h"
#include "UserResourcePool.h"

ShaderAsset* ShaderAsset::DynamicLoad(const char* path)
{
  return UserResourcePool::GetInstance().DynamicLoad<ShaderAsset>(path);
}

// =================================================================
// Constructor / Destructor
// =================================================================
ShaderAsset::ShaderAsset(const char* path)
  : FileResource("ShaderData", path)
{
}

// =================================================================
// Methods
// =================================================================
INativeShader* ShaderAsset::NativeLoadProcess(const std::string& path)
{
  return INativeShader::Create(path.c_str());
}
