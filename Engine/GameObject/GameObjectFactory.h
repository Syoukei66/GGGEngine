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
GameObject2D* Create(const SharedRef<rcSprite>& sprite);

// =================================================================
// GameObject3D
// =================================================================
GameObject3D* Create(const SharedRef<rcCharacterModel>& model, const CharacterNodeData& node);
GameObject3D* Create(const SharedRef<rcCharacterModel>& model);
GameObject3D* Create(const SharedRef<rcStaticModel>& model);

}