#include "..\..\NativeObjectFactory.h"
#include "..\..\NativeObjectFactory.h"
#include "..\..\NativeObjectFactory.h"
#include <NativeObjectFactory.h>

#include "NativeIndexBuffer.h"
#include "NativeMatrix.h"
#include "NativeMatrixStack.h"
#include "NativeVertexBuffer.h"
#include "NativeTexture.h"
#include "NativeRenderTexture.h"
#include "NativeModel_x.h"
#include "NativeShader.h"
#include "NativeSound.h"

INativeMatrix* NativeObjectFactory::CreateMatrix()
{
  return new NativeMatrix();
}

INativeMatrix* NativeObjectFactory::CreateMatrix(NativeMatrixInstance* instance)
{
  return new NativeMatrix(instance);
}

const INativeMatrix& NativeObjectFactory::GetIdentityMatrix()
{
  static NativeMatrix identity = NativeMatrix();
  return identity;
}

INativeMatrixStack* NativeObjectFactory::CreateMatrixStack()
{
  return new NativeMatrixStack();
}

INativeVertexBuffer* NativeObjectFactory::CreateVertexBuffer(T_UINT16 vertex_count, T_UINT16 polygon_count, Vertex::VertexType vertex_type)
{
  return new NativeVertexBuffer(vertex_count, polygon_count, vertex_type);
}

INativeIndexBuffer* NativeObjectFactory::CreateIndexBuffer(T_UINT32 indexes_count)
{
  return new NativeIndexBuffer(indexes_count);
}

INativeTexture* NativeObjectFactory::CreateTexture(const char* path)
{
  return new NativeTexture(path);
}

INativeRenderTexture* NativeObjectFactory::CreateRenderTexture(T_UINT16 width, T_UINT16 height, INativeRenderTexture::Format format)
{
  return new NativeRenderTexture(width, height, format);
}

INativeSound* NativeObjectFactory::CreateSound(const char* path)
{
  return new NativeSound(path);
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
