#pragma once

#include "InputManager.h"
#include "UpdateEvent.h"
#include "EntityModifierManager.h"

namespace HalEngine
{

GG_INLINE InputState* Input(T_UINT8 player_id)
{
  return InputManager::Instance().GetState(player_id);
}

namespace Time
{
//–ß‚è’l‚Í•b
GG_INLINE T_FLOAT DeltaTime()
{
  return UpdateEventState::Instance().GetDeltaTime() / 1000.0f;
}

//–ß‚è’l‚Í•b
GG_INLINE T_FLOAT ElapsedTimeSinceSceneCreate()
{
  return UpdateEventState::Instance().GetMillisecondsElapsedSinceSceneCreate() / 1000.0f;
}

GG_INLINE T_UINT32 ElapsedFrameSinceSceneCreate()
{
  return UpdateEventState::Instance().GetFrameElapsedSinceSceneCreate();
}

} // namespace Time

namespace GGAssetObject
{

}

}// namespace HalEngine