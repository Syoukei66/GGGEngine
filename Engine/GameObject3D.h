#pragma once

#include <vector>
#include "GameObject.h"
#include "Color.h"
#include "Transform3D.h"

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

  virtual void ManagedPreUpdate() override;
  virtual void ManagedUpdate() override;
  virtual void ManagedPostUpdate() override;

  // =================================================================
  // Method
  // =================================================================
public:
  //子GameObjectを追加します。
  //追加された子GameObjectをdeleteする機能はありません
  virtual void AddChild(GameObject3D* child);
  //指定した子GameObjectを子リストから削除します。
  virtual void RemoveChild(GameObject3D* child);
  //自身を親GameObjectの子リストから削除します。
  virtual void RemoveSelf();
  //全ての子GameObjectを子リストから削除します。
  virtual void ClearChildren();

  virtual void Draw(GameObjectRenderState* state);

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

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline bool HasParent() const
  {
    return this->parent_;
  }
  inline GameObject3D* GetParent() const
  {
    return this->parent_;
  }

  inline Transform3D* GetTransform()
  {
    return (Transform3D*)this->transform_;
  }
  inline const Transform3D* GetTransform() const
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
