#include "EngineBehavior.h"
#include "Scene/MeshViewScene.h"

void EngineBehavior::SetupApplicationOption(ApplicationOption& option)
{
}

void EngineBehavior::SetupMainActivityOption(ActivityOption& option)
{
}

void EngineBehavior::SetupEngineOption(EngineOption& option)
{
}

SharedRef<Scene> EngineBehavior::FirstScene()
{
  return new MeshViewScene();
}
