#pragma once

class rcSprite;
class rcCharacterModel;
struct CharacterNodeData;
class rcStaticModel;

#include "GameObject.h"

namespace GameObjectFactory
{
SharedRef<GameObject> Create(const SharedRef<rcSprite>& sprite);
SharedRef<GameObject> Create(const SharedRef<rcCharacterModel>& model);
SharedRef<GameObject> Create(const SharedRef<rcStaticModel>& model);
}