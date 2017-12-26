#pragma once

#include "NativeMatrix.h"
#include "NativeTexture.h"
#include "NativeMatrixStack.h"

namespace NativeObjectFactory
{

INativeMatrix* CreateMatrix();
INativeMatrix* CreateMatrix(NativeMatrixInstance* instance);
INativeMatrixStack* CreateMatrixStack();
INativeTexture* CreateTexture(const char* path);

};