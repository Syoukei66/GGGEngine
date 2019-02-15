#pragma once

#include <Core/Application/Platform/API/Input/InputAPI.h>
#include <Core/Application/Event/UpdateEventState.h>
#include <Engine/Component/Modifier/EntityModifierManager.h>

namespace HalEngine
{
namespace Time
{
// –ß‚è’l‚Í•b
static GG_INLINE T_FLOAT DeltaTime()
{
  return Application::GetUpdateEventState().GetDeltaTime();
}
} // namespace Time

namespace GGAssetObject
{

}

}// namespace HalEngine