#include "..\..\NativeObjectFactory.h"
#include "..\..\NativeObjectFactory.h"
#include <NativeObjectFactory.h>

#include "NativeIndexBuffer.h"
#include "NativeMatrix.h"
#include "NativeMatrixStack.h"
#include "NativeVertexBuffer.h"
#include "NativeTexture.h"
#include "NativeModel_x.h"
#include "NativeShader.h"

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

INativeVertexBuffer* CreateVertexBuffer(T_UINT16 vertex_count, INativeProcess_Graphics::VertexType vertex_type)
{
  return new NativeVertexBuffer(vertex_count, vertex_type);
}

INativeIndexBuffer* CreateIndexBuffer(T_UINT32 indexes_count)
{
  return new NativeIndexBuffer(indexes_count);
}

INativeTexture* NativeObjectFactory::CreateTexture(const char* path)
{
  return new NativeTexture(path);
}

INativeModel* NativeObjectFactory::CreateModel(const char* directory_path, const char* name, const char* extension)
{
  if (!strcmp(extension, "x"))
  {
    return new NativeModel_x(directory_path, name);
  }
  return nullptr;
}

INativeShader* NativeObjectFactory::CreateShader(const char* path)
{
  return new NativeShader(path);
}
