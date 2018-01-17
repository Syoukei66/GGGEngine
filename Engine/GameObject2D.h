#pragma once

#include <vector>
#include "GameObject.h"
#include "Color.h"
#include "Transform2D.h"

class EntityModifierRoot;
class GameObject2DRenderState;

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
  //子GameObjectを追加します。
  //追加された子GameObjectをdeleteする機能はありません
  void AddChild(GameObject2D* child);
  //指定した子GameObjectを子リストから削除します。
  void RemoveChild(GameObject2D* child);
  //自身を親GameObjectの子リストから削除します。
  void RemoveSelf();
  //全ての子GameObjectを子リストから削除します。
  void ClearChildren();

  virtual void Draw(GameObject2DRenderState* state);

  virtual void PreDraw(GameObject2DRenderState* state) {}
  void ManagedDraw(GameObject2DRenderState* state);
  //virtual void NativeDraw(GameObject2DRenderState* state) {}
  virtual void PostDraw(GameObject2DRenderState* state) {}

private:
  void UpdateChildrenZIndex();

public:
  void RegisterEntityModifier(EntityModifierRoot* root);
  void UnregisterEntityModifier(EntityModifierRoot* root);
  void ClearEntityModifiers();

protected:
  virtual void PushMatrixStack(GameObject2DRenderState* state);
  virtual void PopMatrixStack(GameObject2DRenderState* state);

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
    return this->transform_;
  }
  inline const Transform2D* GetTransform() const
  {
    return this->transform_;
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
  Transform2D* transform_;


  GameObject2D* parent_;
  std::vector<GameObject2D*> children_;

  T_INT8 zindex_;
  bool children_zindex_dirty_;
};
