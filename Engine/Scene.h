#ifndef HAL_ENGINE_SCENE_SCENE_H_
#define HAL_ENGINE_SCENE_SCENE_H_

#include <vector>

#include "GameObject2D.h"
#include "GameObject3D.h"
#include "InputManager.h"
#include "UpdateEvent.h"
#include "SceneTransitioner.h"

#include "ResourcePool.h"

class Camera;

// =================================================================
// Scene
// Sceneを切り替えた場合、リソースのロード、アンロードが行われます。
// リソースの確保はSceneのOnLoad(),OnUnload()内で行ってください。
// =================================================================
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
  void Load(IResourceLoadingListener* listener);
  void Unload();
  void Show(ISceneShowListener* listener);
  void ShowFinish();
  void Hide(ISceneHideListener* listener);
  void HideFinish();

  void Draw();
  void Draw2DLayers(GameObject2DRenderState* state);
  void Draw3DLayers(GameObject3DRenderState* state);

  inline void AddChild(GameObject2D* child)
  {
    this->root2d_->AddChild(child);
  }
  inline void RemoveChild(GameObject2D* child)
  {
    this->root2d_->RemoveChild(child);
  }
  inline void AddChild(GameObject3D* child)
  {
    this->root3d_->AddChild(child);
  }
  inline void RemoveChild(GameObject3D* child)
  {
    this->root3d_->RemoveChild(child);
  }
  inline void ClearChildren()
  {
    this->root2d_->ClearChildren();
    this->root3d_->ClearChildren();
  }

  inline void AddCamera(Camera* camera)
  {
    this->cameras_.push_back(camera);
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

  virtual void PreUpdate() {}
  virtual void Update() {}
  virtual void PostUpdate() {}

  virtual void OnInputEvent() {}

  void OnUpdateEvent();

protected:
  virtual void OnLoad(IResourceLoadReserver* resource) = 0;
  virtual void OnSetup() = 0;
  virtual void OnUnload() = 0;
  virtual void OnShow(ISceneShowListener* listener) = 0;
  virtual void OnShowFinish() {}
  virtual void OnHide(ISceneHideListener* listener) = 0;
  virtual void OnHideFinish() {}

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline GameObject2D* GetRoot2d()
  {
    return this->root2d_;
  }
  inline GameObject3D* GetRoot3d()
  {
    return this->root3d_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  GameObject2D* root2d_;
  GameObject3D* root3d_;

  std::vector<Camera*> cameras_;
};

#endif//HAL_ENGINE_SCENE_SCENE_H_
