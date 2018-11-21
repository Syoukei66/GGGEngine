#pragma once

#include <Engine/Component/GameComponent.h>
#include <Engine/Component/Renderer/Renderer.h>
#include <Engine/GameObject/Transform/Transform.h>

class GameObjectRenderState;

class GameObject : public GGObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
public:
  GG_INIT_FUNC(GameObject);
  GG_DESTRUCT_FUNC(GameObject);

  // =================================================================
  // Methods
  // =================================================================
public:
  void AddChild(const SharedRef<GameObject>& child);
  void RemoveSelf();
  void ClearChildren();

  // =================================================================
  // Events
  // =================================================================
public:
  void Draw(GameObjectRenderState* state);

  void ManagedPreUpdate();
  void ManagedUpdate();
  void ManagedPostUpdate();

  void FireOnPositionChanged();
  void FireOnScaleChanged();
  void FireOnRotationChanged();

protected:
  virtual void PreUpdate() {}
  virtual void Update() {}
  virtual void PostUpdate() {}

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE bool HasParent() const
  {
    return this->parent_ != nullptr;
  }
  GG_INLINE WeakRef<GameObject> GetParent() const
  {
    return this->parent_;
  }

  GG_INLINE void SetEnabled(bool enabled)
  {
    this->enabled_ = enabled;
  }
  GG_INLINE bool IsEnabled() const
  {
    return this->enabled_;
  }

  GG_INLINE void SetRenderer(Renderer* renderer)
  {
    this->renderer_ = renderer;
  }
  GG_INLINE Renderer* GetRenderer() const
  {
    return this->renderer_;
  }

  // =================================================================
  // delegate to Transform
  // =================================================================
  GG_INLINE const Matrix4x4& GetMatrix() const
  {
    return this->transform_->GetMatrix();
  }

  GG_INLINE const Matrix4x4& GetTranslateMatrix() const
  {
    return this->transform_->GetTranslateMatrix();
  }

  GG_INLINE const Matrix4x4& GetRotationMatrix() const
  {
    return this->transform_->GetRotationMatrix();
  }

  GG_INLINE const Matrix4x4& GetScaleMatrix() const
  {
    return this->transform_->GetScaleMatrix();
  }

  GG_INLINE const Matrix4x4& GetWorldMatrix() const
  {
    return this->transform_->GetWorldMatrix();
  }

  // =================================================================
  // delegate to Renderer
  // =================================================================
  GG_INLINE void SetLayerId(T_UINT8 layer_id)
  {
    this->renderer_->SetLayerId(layer_id);
  }
  GG_INLINE T_UINT8 GetLayerId() const
  {
    this->renderer_->GetLayerId();
  }
  GG_INLINE void SetMaterial(const SharedRef<rcMaterial>& material, T_UINT16 index = 0)
  {
    this->renderer_->SetMaterial(material, index);
  }
  GG_INLINE SharedRef<const rcMaterial> GetMaterial(T_UINT16 index = 0) const
  {
    return this->renderer_->GetMaterial(index);
  }
  GG_INLINE SharedRef<rcMaterial> GetMaterial(T_UINT16 index = 0)
  {
    return this->renderer_->GetMaterial(index);
  }
  GG_INLINE T_UINT16 GetMaterialCount()
  {
    return this->renderer_->GetMaterialCount();
  }

  // =================================================================
  // Data Member
  // =================================================================
protected:
  Transform* transform_;

private:
	bool enabled_;
  WeakRef<GameObject> parent_;
  std::vector<SharedRef<GameObject>> children_;

  Renderer* renderer_;

};
