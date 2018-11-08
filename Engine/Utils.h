#pragma once

#include <Core/Application/Platform/API/Input/InputAPI.h>
#include <Core/Application/Event/UpdateEventState.h>
#include <Engine/Component/Modifier/EntityModifierManager.h>

namespace HalEngine
{

static GG_INLINE InputState* Input(T_UINT8 player_id)
{
  return Application::GetPlatform()->GetInputAPI()->GetState(player_id);
}

namespace Time
{
//–ß‚è’l‚Í•b
static GG_INLINE T_FLOAT DeltaTime()
{
  return Application::GetUpdateEventState().GetDeltaTime();
}
} // namespace Time

namespace GGAssetObject
{

}

}// namespace HalEngine