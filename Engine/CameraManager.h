#pragma once

#include <vector>

#include "Camera.h"

class Scene;

class CameraManager
{
public:
  CameraManager(Scene* scene);
  ~CameraManager();

public:
  void SetupCameras();

public:
  inline void AddCamera(Camera* camera)
  {
    this->cameras_.emplace_back(camera);
  }
  void RemoveCamera(Camera* camera)
  {
    for (std::vector<Camera*>::iterator itr = this->cameras_.begin(); itr != this->cameras_.end(); ++itr)
    {
      if (camera == (*itr))
      {
        this->cameras_.erase(itr);
        return;
      }
    }
  }
  inline void ClearCamera()
  {
    this->cameras_.clear();
  }

private:
  Scene* scene_;
  std::vector<Camera*> cameras_;

};