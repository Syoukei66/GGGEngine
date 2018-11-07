#pragma once

#include "GameObject.h"

class EntityModifierRoot;
class Transform2D;

class GameObject2D : public GameObject
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  GameObject2D();
  virtual ~GameObject2D();
  
  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual void Init() override;

  // =================================================================
  // Methods
  // =================================================================
public:
  void AddChild(GameObject2D* child);
  void RemoveChild(GameObject2D* child);
  void RemoveSelf();
  void ClearChildren();

private:
  void UpdateChildrenZIndex();

public:
  void RegisterEntityModifier(EntityModifierRoot* root);
  void UnregisterEntityModifier(EntityModifierRoot* root);
  void ClearEntityModifiers();

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

  virtual void OnChildrenZIndexChanged();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE bool HasParent() const
  {
    return this->parent_;
  }
  GG_INLINE GameObject2D* GetParent() const
  {
    return this->parent_;
  }

  GG_INLINE Transform2D* GetTransform()
  {
    return (Transform2D*)this->transform_;
  }
  GG_INLINE const Transform2D* GetTransform() const
  {
    return (Transform2D*)this->transform_;
  }

  GG_INLINE void SetZIndex(T_INT8 zindex)
  {
    this->zindex_ = zindex;
    if (this->parent_)
    {
      this->parent_->OnChildrenZIndexChanged();
    }
  }
  GG_INLINE T_INT8 GetZIndex() const
  {
    return this->zindex_;
  }
  
private:
  GameObject2D* parent_;
  std::vector<GameObject2D*> children_;

  T_INT8 zindex_;
  bool children_zindex_dirty_;
};
