#pragma once

class rcSprite;
class rcCharacterModel;
struct CharacterNodeData;
class rcStaticModel;

namespace GameObjectFactory
{
// =================================================================
// GameObject2D
// =================================================================
SharedRef<GameObject2D> Create(const SharedRef<rcSprite>& sprite);

// =================================================================
// GameObject3D
// =================================================================
UniqueRef<GameObject3D> Create(const SharedRef<rcCharacterModel>& model);
SharedRef<GameObject3D> Create(const SharedRef<rcStaticModel>& model);

}