#include "Model.h"
#include "EngineAsset.h"

Model::Model(const FbxResource& data)
  : ModelNode(data.GetContents()->GetRootData())
  , data_(data)
{
}

Model::~Model()
{
}

// =================================================================
// Method
// =================================================================
