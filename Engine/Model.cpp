#include "Model.h"
#include "NativeMethod.h"
#include "GameObject3DRenderState.h"
#include "EngineAsset.h"

Model::Model(const ModelData& data)
  : data_(data)
{
  //this->SetMaterial(EngineAsset::Material::MODEL);
}

Model::~Model()
{
}

void Model::NativeDraw(GameObject3DRenderState* state)
{
  this->data_.GetContents()->Draw(state);
}
