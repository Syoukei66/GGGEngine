#include "NativeShader.h"
#include "NativeObjectFactory.h"

INativeShader* INativeShader::Create(const char* path)
{
  return NativeObjectFactory::CreateShader(path);
}

