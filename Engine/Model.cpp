#include "Model.h"
#include "NativeMethod.h"

Model::Model(const char* path)
  : lighting_enabled_(true)
{
  this->model_ = NativeMethod::Model().Model_Load(path);
}

Model::~Model()
{
  NativeMethod::Model().Model_Unload(this->model_);
}

void Model::NativeDraw(GameObject3DRenderState* state)
{
  NativeMethod::Graphics().Graphics_SetLightingEnabled(this->lighting_enabled_);
  NativeMethod::Model().Model_Draw(this->model_);
}