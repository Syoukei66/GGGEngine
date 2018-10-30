#pragma once

#include <Engine/Input/InputManager.h>
#include <Engine/Event/UpdateEventState.h>
#include <Engine/Component/Modifier/EntityModifierManager.h>

namespace HalEngine
{

GG_INLINE InputState* Input(T_UINT8 player_id)
{
  return InputManager::GetState(player_id);
}

namespace Time
{
//–ß‚è’l‚Í•b
GG_INLINE T_FLOAT DeltaTime()
{
  return UpdateEventState::GetDeltaTime() / 1000.0f;
}

//–ß‚è’l‚Í•b
GG_INLINE T_FLOAT ElapsedTimeSinceSceneCreate()
{
  return UpdateEventState::GetMillisecondsElapsedSinceSceneCreate() / 1000.0f;
}

GG_INLINE T_UINT32 ElapsedFrameSinceSceneCreate()
{
  return UpdateEventState::GetFrameElapsedSinceSceneCreate();
}

} // namespace Time

namespace GGAssetObject
{

}

}// namespace HalEngine