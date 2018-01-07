#pragma once

#include "InputManager.h"
#include "UpdateEvent.h"
#include "ResourceManager.h"

namespace HalEngine
{

inline InputState* Input(T_UINT8 player_id)
{
  return InputManager::GetInstance()->GetState(player_id);
}

namespace Time
{
//–ß‚è’l‚Í•b
inline T_FLOAT DeltaTime()
{
  return UpdateEventState::GetInstance()->GetDeltaTime() / 1000.0f;
}

//–ß‚è’l‚Í•b
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

inline ITexture* GetTexture(T_UINT8 pid, T_UINT16 tid)
{
  return ResourceManager::GetInstance()->GetTexturePaletteManager()->Get(pid)->GetTexture(tid);
}

inline const Texture* GetTexture(const char* path)
{
  return ResourceManager::GetInstance()->GetTexturePaletteManager()->DynamicLoad(path);
}

inline const ParticleData* GetParticleData(T_UINT8 id)
{
  return ResourceManager::GetInstance()->GetParticleDataManager()->GetData(id);
}

inline EntityModifierManager* GetEntityModifierManager()
{
  return ResourceManager::GetInstance()->GetEntityModifierManager();
}

inline ModelData* GetModelData(T_UINT8 id)
{
  return ResourceManager::GetInstance()->GetModelDataManager()->Get(id);
}

}// namespace Resource

}// namespace HalEngine