#pragma once

#include "GameObject.h"

class Transform3D;

class GameObject3D : public GameObject
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  GameObject3D();
  virtual ~GameObject3D();

  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual void Init() override;

  // =================================================================
  // Methods
  // =================================================================
public:
  virtual void AddChild(GameObject3D* child);
  virtual void RemoveChild(GameObject3D* child);
  virtual void RemoveSelf();
  virtual void ClearChildren();

  // =================================================================
  // Events
  // =================================================================
public:
  virtual void ManagedDraw(GameObjectRenderState* state) override;

  virtual void ManagedPreUpdate() override;
  virtual void ManagedUpdate() override;
  virtual void ManagedPostUpdate() override;

  virtual void FireOnPositionChanged(GameObject* root) override;
  virtual void FireOnScaleChanged(GameObject* root) override;
  virtual void FireOnRotationChanged(GameObject* root) override;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE bool HasParent() const
  {
    return this->parent_;
  }
  GG_INLINE GameObject3D* GetParent() const
  {
    return this->parent_;
  }

  GG_INLINE Transform3D* GetTransform()
  {
    return (Transform3D*)this->transform_;
  }
  GG_INLINE const Transform3D* GetTransform() const
  {
    return (Transform3D*)this->transform_;
  }
  
  // =================================================================
  // Data Member
  // =================================================================
private:
  GameObject3D* parent_;
  std::vector<GameObject3D*> children_;
};
