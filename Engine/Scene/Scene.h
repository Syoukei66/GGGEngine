#pragma once

#include <Core/AssetManager.h>

#include "GameObject2D.h"
#include "GameObject3D.h"
#include "InputManager.h"
#include "UpdateEvent.h"
#include "SceneTransitioner.h"

#include "Camera.h"
#include "Camera2D.h"
#include "Camera3D.h"

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
  void Load();
  void Unload();

  void Show(ISceneShowListener* listener);
  void ShowFinish();

  void Hide(ISceneHideListener* listener);
  void HideFinish();

  void Draw();
  void Draw2DLayers(GameObjectRenderState* state);
  void Draw3DLayers(GameObjectRenderState* state);

  GG_INLINE void AddChild(GameObject2D* child)
  {
    this->root2d_->AddChild(child);
  }
  GG_INLINE void AddChild(GameObject3D* child)
  {
    this->root3d_->AddChild(child);
  }
  GG_INLINE void RemoveChild(GameObject2D* child)
  {
    this->root2d_->RemoveChild(child);
  }
  GG_INLINE void RemoveChild(GameObject3D* child)
  {
    this->root3d_->RemoveChild(child);
  }
  GG_INLINE void ClearChildren()
  {
    this->root2d_->ClearChildren();
    this->root3d_->ClearChildren();
  }

  GG_INLINE void AddCamera(Camera2D* camera)
  {
    this->cameras_.emplace_back(camera);
  }
  GG_INLINE void AddCamera(Camera3D* camera)
  {
    this->cameras_.emplace_back(camera);
  }
  void RemoveCamera(Camera2D* camera)
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
  void RemoveCamera(Camera3D* camera)
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
  GG_INLINE void ClearCamera()
  {
    this->cameras_.clear();
  }

  virtual void PreUpdate() {}
  virtual void Update() {}
  virtual void PostUpdate() {}

  virtual void OnInputEvent() {}

  void OnUpdateEvent();

protected:
  virtual void OnLoad() = 0;
  virtual void OnUnload() = 0;

  virtual void OnShow(ISceneShowListener* listener) = 0;
  virtual void OnShowFinish() {}

  virtual void OnHide(ISceneHideListener* listener) = 0;
  virtual void OnHideFinish() {}

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE GameObject2D* GetRoot2d()
  {
    return this->root2d_;
  }
  GG_INLINE GameObject3D* GetRoot3d()
  {
    return this->root3d_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  bool is_loaded_;

  GameObject2D* root2d_;
  GameObject3D* root3d_;
  std::vector<Camera*> cameras_;
};
