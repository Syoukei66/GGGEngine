#include "Model.h"
#include "NativeMethod.h"
#include "GameObject3DRenderState.h"

Model::Model(const ModelData& data)
  : data_(data)
{
}

Model::~Model()
{
}

void Model::NativeDraw(GameObject3DRenderState* state)
{
  this->data_.GetContents()->Draw(state);
}
