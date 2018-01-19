#include "Model.h"
#include "NativeMethod.h"
#include "GameObject3DRenderState.h"
#include "EngineAsset.h"

Model::Model(const ModelData& data)
  : data_(data)
{
}

Model::~Model()
{
}

// =================================================================
// Method
// =================================================================
void Model::ManagedDraw(GameObject3DRenderState* state)
{
  this->NativeDraw(state);
}

void Model::NativeDraw(GameObject3DRenderState* state)
{
  this->data_.GetContents()->Draw(state);
}

