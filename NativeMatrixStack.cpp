#include "NativeMatrixStack.h"

#include "NativeObjectFactory.h"

INativeMatrixStack* INativeMatrixStack::Create()
{
  return NativeObjectFactory::CreateMatrixStack();
}
