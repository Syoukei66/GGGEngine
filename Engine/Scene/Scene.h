#pragma once

#include <Engine/GameObject/GameObject2D.h>
#include <Engine/GameObject/GameObject3D.h>
#include <Engine/Component/Camera/Camera.h>
#include <Engine/Component/Camera/Camera2D.h>
#include <Engine/Component/Camera/Camera3D.h>

class Scene : public GGObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_INIT_FUNC(Scene);

  // =================================================================
  // Methods
  // =================================================================
public:
  void Load();
  void Unload();

  void Show();
  void Hide();

  void Draw(const ActivityContext& context);
  void Draw2DLayers(GameObjectRenderState* state);
  void Draw3DLayers(GameObjectRenderState* state);

  GG_INLINE void AddChild2D(const SharedRef<GameObject2D>& child)
  {
    this->root2d_->AddChild(child);
  }
  GG_INLINE void AddChild(const SharedRef<GameObject3D>& child)
  {
    this->root3d_->AddChild(child);
  }
  GG_INLINE void ClearChildren()
  {
    this->root2d_->ClearChildren();
    this->root3d_->ClearChildren();
  }

  GG_INLINE void AddCamera(const SharedRef<Camera>& camera)
  {
    this->cameras_.emplace_back(camera);
  }
  GG_INLINE void RemoveCamera(const SharedRef<Camera>& camera)
  {
    const auto& itr = std::find(this->cameras_.begin(), this->cameras_.end(), camera);
    if (itr != this->cameras_.end())
    {
      this->cameras_.erase(itr);
    }
  }
  GG_INLINE void ClearCamera()
  {
    this->cameras_.clear();
  }

  virtual void PreUpdate(const ActivityContext& context) {}
  virtual void Update(const ActivityContext& context) {}
  virtual void PostUpdate(const ActivityContext& context) {}

  void OnUpdateEvent(const ActivityContext& context);

protected:
  virtual void OnLoad() = 0;
  virtual void OnUnload() = 0;

  virtual void OnShow() = 0;
  virtual void OnHide() = 0;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE SharedRef<GameObject2D> GetRoot2d()
  {
    return this->root2d_;
  }

  GG_INLINE SharedRef<GameObject3D> GetRoot3d()
  {
    return this->root3d_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  // ÉçÅ[ÉhÇ≥ÇÍÇΩâÒêî
  T_UINT32 load_count_;

  bool is_shown_;

  SharedRef<GameObject2D> root2d_;
  SharedRef<GameObject3D> root3d_;
  std::vector<SharedRef<Camera>> cameras_;
};
