#pragma once

#include <fbxsdk.h>
#include "Mesh.h"

namespace MeshFactory
{
namespace Fbx
{
Mesh* Create(FbxNode* node, bool readonly);
}
}