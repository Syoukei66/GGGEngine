#include "NativeMatrix.h"
#include "NativeObjectFactory.h"

INativeMatrix* INativeMatrix::Create()
{
  return NativeObjectFactory::CreateMatrix();
}

INativeMatrix* INativeMatrix::Create(NativeMatrixInstance* instance)
{
  return NativeObjectFactory::CreateMatrix(instance);
}

const INativeMatrix& INativeMatrix::Identity()
{
  return NativeObjectFactory::GetIdentityMatrix();
}