#pragma once

class rcSprite;
class rcModel;

namespace GameObjectFactory
{
// =================================================================
// GameObject2D
// =================================================================
static GameObject2D* Create(const SharedRef<rcSprite>& sprite);

// =================================================================
// GameObject3D
// =================================================================
static GameObject3D* Create(const SharedRef<rcModel>& model);

}