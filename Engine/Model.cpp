#include "Model.h"
#include "NativeMethod.h"
#include "GameObject3DRenderState.h"
#include "EngineAsset.h"

Model::Model(FbxData& data)
  : ModelNode(data.GetRootData())
  , data_(data)
{
}

Model::~Model()
{
}

// =================================================================
// Method
// =================================================================

