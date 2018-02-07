#pragma once

#include <vector>
#include "GameObject.h"
#include "Color.h"
#include "Transform2D.h"

class EntityModifierRoot;

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

  virtual void ManagedPreUpdate() override;
  virtual void ManagedUpdate() override;
  virtual void ManagedPostUpdate() override;

  // =================================================================
  // Method
  // =================================================================
public:
  void AddChild(GameObject2D* child);
  void RemoveChild(GameObject2D* child);
  void RemoveSelf();
  void ClearChildren();

  virtual void Draw(GameObjectRenderState* state);

private:
  void UpdateChildrenZIndex();

public:
  void RegisterEntityModifier(EntityModifierRoot* root);
  void UnregisterEntityModifier(EntityModifierRoot* root);
  void ClearEntityModifiers();

protected:
  virtual void PushMatrixStack(GameObjectRenderState* state);
  virtual void PopMatrixStack(GameObjectRenderState* state);

  // =================================================================
  // Events
  // =================================================================
public:
  virtual void FireOnPositionChanged(GameObject* root) override;
  virtual void FireOnScaleChanged(GameObject* root) override;
  virtual void FireOnRotationChanged(GameObject* root) override;

  virtual void OnChildrenZIndexChanged();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline bool HasParent() const
  {
    return this->parent_;
  }
  inline GameObject2D* GetParent() const
  {
    return this->parent_;
  }

  inline Transform2D* GetTransform()
  {
    return (Transform2D*)this->transform_;
  }
  inline const Transform2D* GetTransform() const
  {
    return (Transform2D*)this->transform_;
  }

  inline void SetZIndex(T_INT8 zindex)
  {
    this->zindex_ = zindex;
    if (this->parent_)
    {
      this->parent_->OnChildrenZIndexChanged();
    }
  }
  inline T_INT8 GetZIndex() const
  {
    return this->zindex_;
  }
  
private:
  GameObject2D* parent_;
  std::vector<GameObject2D*> children_;

  T_INT8 zindex_;
  bool children_zindex_dirty_;
};
