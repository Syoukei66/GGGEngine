#include "CameraManager.h"

CameraManager::CameraManager(Scene* scene)
  : scene_(scene)
{
}

CameraManager::~CameraManager()
{
}

void CameraManager::SetupCameras()
{
  for (std::vector<Camera*>::iterator itr = this->cameras_.begin(); itr != this->cameras_.end(); ++itr)
  {
    (*itr)->SetupCamera();
  }
}

