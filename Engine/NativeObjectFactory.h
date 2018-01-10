#pragma once

#include "NativeMatrix.h"
#include "NativeTexture.h"
#include "NativeMatrixStack.h"
#include "NativeModel.h"

namespace NativeObjectFactory
{

INativeMatrix* CreateMatrix();
INativeMatrix* CreateMatrix(NativeMatrixInstance* instance);
INativeMatrixStack* CreateMatrixStack();
INativeTexture* CreateTexture(const char* path);
INativeModel* CreateModel(const char* directory_path, const char* name, const char* extension);

};