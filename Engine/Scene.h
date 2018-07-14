#pragma once

#include "SceneTransitioner.h"
#include "CameraManager.h"
#include "RendererManager.h"

class GameObject2D;
class GameObject3D;

class Scene
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Scene();
  virtual ~Scene();

  // =================================================================
  // Method
  // =================================================================
public:
  void AddChild(GameObject* child);
  void RemoveChild(GameObject* child);
  void ClearChildren();

  // =================================================================
  // Event
  // =================================================================
public:
  void Load(IResourceLoadingListener* listener);
  void Unload();
  void Show(ISceneShowListener* listener);
  void ShowFinish();
  void Hide(ISceneHideListener* listener);
  void HideFinish();

  void OnUpdateEvent();
  void Draw();

protected:
  virtual void OnLoad(IResourceLoadReserver* resource) = 0;
  virtual void OnSetup() = 0;
  virtual void OnUnload() = 0;
  virtual void OnShow(ISceneShowListener* listener) = 0;
  virtual void OnShowFinish() {}
  virtual void OnHide(ISceneHideListener* listener) = 0;
  virtual void OnHideFinish() {}
  
  virtual void PreUpdate() {}
  virtual void Update() {}
  virtual void PostUpdate() {}

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline GameObject* GetRoot()
  {
    return this->root_;
  }

  inline CameraManager* GetCameraManager()
  {
    return this->camera_manager_;
  }
  inline const CameraManager* GetCameraManager() const
  {
    return this->camera_manager_;
  }

  inline RendererManager* GetRendererManager()
  {
    return this->renderer_manager_;
  }
  inline const RendererManager* GetRendererManager() const
  {
    return this->renderer_manager_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  bool is_loaded_;

  GameObject* root_;

  CameraManager* camera_manager_;
  RendererManager* renderer_manager_;
};

