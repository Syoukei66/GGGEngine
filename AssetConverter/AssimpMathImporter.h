#pragma once

#include <assimp\vector2.h>
#include <assimp\vector3.h>
#include <assimp\color4.h>

#include "../Core/Vector2.h"
#include "../Core/Vector3.h"
#include "../Core/Color.h"

namespace ModelImporter
{

namespace Assimp
{

TVec2f ToTVec2f(const aiVector2D& vec);
TVec3f ToTVec3f(const aiVector3D& vec);
TColor ToTColor(const aiColor4D& col);

} // namespace Assimp

} // namespace ModelImporter