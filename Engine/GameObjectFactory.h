#pragma once

#include "GameObject2D.h"
#include "GameObject3D.h"
#include "Texture.h"

namespace GameObjectFactory
{

GameObject2D* CreateSprite(const Texture& texture);
GameObject2D* CreateAnimatedSprite(const Texture& texture, T_UINT8 x_num, T_UINT8 y_num);

}