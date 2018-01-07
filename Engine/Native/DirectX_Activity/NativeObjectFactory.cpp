#include "..\..\NativeObjectFactory.h"
#include <NativeObjectFactory.h>

#include "NativeMatrix.h"
#include "NativeMatrixStack.h"
#include "NativeTexture.h"
#include "NativeModel.h"

INativeMatrix* NativeObjectFactory::CreateMatrix()
{
  return new NativeMatrix();
}

INativeMatrix* NativeObjectFactory::CreateMatrix(NativeMatrixInstance* instance)
{
  return new NativeMatrix(instance);
}

INativeMatrixStack* NativeObjectFactory::CreateMatrixStack()
{
  return new NativeMatrixStack();
}

INativeTexture* NativeObjectFactory::CreateTexture(const char* path)
{
  return new NativeTexture(path);
}

INativeModel* NativeObjectFactory::CreateModel(const char* directory_path, const char* name)
{
  return new NativeModel_x(directory_path, name);
}
