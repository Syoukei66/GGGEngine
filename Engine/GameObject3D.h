#pragma once

#include <vector>
#include "GameObject.h"
#include "Color.h"
#include "Transform3D.h"

class GameObject3DRenderState;

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
  void AddChild(GameObject3D* child);
  //指定した子GameObjectを子リストから削除します。
  void RemoveChild(GameObject3D* child);
  //自身を親GameObjectの子リストから削除します。
  void RemoveSelf();
  //全ての子GameObjectを子リストから削除します。
  void ClearChildren();

  //描画メソッドです。自身と自身の子の描画処理を行います。
  //これらのメソッドはエンジンが描画サイクルの中で呼び出す為、
  //ユーザーが直接呼び出す機会はありません。
  //描画を行いたい場合はGameObjectを現在のSceneをrootとした
  //GameObjectの子GameObjectに追加してください。
  //Drawメソッド内では以下の順番で処理が行われます。
  //  0.VBO更新処理
  //  1.PreDraw()
  //  2.ZIndexが0未満の子GameObjectのDraw()
  //  4.NativeDraw() //自身の描画処理
  //  5.ZIndexが0以上の子GameObjectのDraw()
  //  6.PostDraw()
  virtual void Draw(GameObject3DRenderState* state);

  virtual void PreDraw(GameObject3DRenderState* state) {}
  virtual void NativeDraw(GameObject3DRenderState* state) {}
  virtual void PostDraw(GameObject3DRenderState* state) {}

protected:
  virtual void PushMatrixStack(GameObject3DRenderState* state);
  virtual void PopMatrixStack(GameObject3DRenderState* state);

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
    return this->transform_;
  }

  inline const Transform3D* GetTransform() const
  {
    return this->transform_;
  }

  inline void SetZTestFlag(bool z_test)
  {
    this->z_test_ = z_test;
  }

  inline bool GetZTestFlag() const
  {
    return this->z_test_;
  }

  inline void SetBillboardingFlag(bool billboarding)
  {
    this->billbording_ = billboarding;
  }

  inline bool IsBillboard() const
  {
    return this->billbording_;
  }

private:
  Transform3D* transform_;
  GameObject3D* parent_;
  std::vector<GameObject3D*> children_;

  bool z_test_;
  bool billbording_;
};
