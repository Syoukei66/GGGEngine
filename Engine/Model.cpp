#include "Model.h"
#include "NativeMethod.h"

Model::Model(const ModelData& data)
  : data_(data)
  , lighting_enabled_(true)
{
}

Model::~Model()
{
}

void Model::NativeDraw(GameObject3DRenderState* state)
{
  NativeMethod::Graphics().Graphics_SetLightingEnabled(this->lighting_enabled_);
  this->data_.GetContents()->Draw();
}
