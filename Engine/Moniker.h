#pragma once

#include "InputManager.h"
#include "UpdateEvent.h"
#include "EntityModifierManager.h"

namespace HalEngine
{

inline InputState* Input(T_UINT8 player_id)
{
  return InputManager::GetInstance()->GetState(player_id);
}

namespace Time
{
//�߂�l�͕b
inline T_FLOAT DeltaTime()
{
  return UpdateEventState::GetInstance()->GetDeltaTime() / 1000.0f;
}

//�߂�l�͕b
inline T_FLOAT ElapsedTimeSinceSceneCreate()
{
  return UpdateEventState::GetInstance()->GetMillisecondsElapsedSinceSceneCreate() / 1000.0f;
}

inline T_UINT32 ElapsedFrameSinceSceneCreate()
{
  return UpdateEventState::GetInstance()->GetFrameElapsedSinceSceneCreate();
}

} // namespace Time

namespace Resource
{

inline EntityModifierManager* GetEntityModifierManager()
{
  return &EntityModifierManager::GetInstance();
}

}

}// namespace HalEngine