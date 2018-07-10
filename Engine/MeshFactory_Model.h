#pragma once

#include "Mesh.h"
#include "ModelData.h"

namespace MeshFactory
{
namespace Model
{  
//TODO: 現状Node毎にメッシュを作成しているが、
//      パフォーマンス向上/インスタンシングの為に
//      頂点バッファなどを共有したメッシュを用意する必要がある。
Mesh* Create(ModelData* model, ModelNodeData* node, bool readonly);
}
}