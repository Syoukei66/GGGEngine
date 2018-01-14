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
  virtual void Draw(GameObject2DRenderState* state);

  virtual void PreDraw(GameObject2DRenderState* state) {}
  virtual void NativeDraw(GameObject2DRenderState* state) {}
  virtual void PostDraw(GameObject2DRenderState* state) {}


private:
  void UpdateChildrenZIndex();

public:
  //自身が親となった際の座標をローカル座標としている事に注意
  //absoluteをtrueにすると、親にIsWorldフラグた立っていようとSceneの絶対座標を得れる
 
  //TODO:IsWorldを復活させる必要あるかも
  void ConvertPositionLocalToWorld(const TVec2f* local, TVec2f* dest, GameObject2D* root = nullptr) const;
  void ConvertPositionLocalToWorld(T_FLOAT local_x, T_FLOAT local_y, TVec2f* dest, GameObject2D* root = nullptr) const;
  T_FLOAT ConvertXLocalToWorld(T_FLOAT local_x, GameObject2D* root = nullptr) const;
  T_FLOAT ConvertYLocalToWorld(T_FLOAT local_y, GameObject2D* root = nullptr) const;

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
  inline Transform2D* GetTransform()
  {
    return this->transform_;
  }
  inline const Transform2D* GetTransform() const
  {
    return this->transform_;
  }
  inline void SetColor(const Color& color)
  {
    this->color_ = color;
  }
  inline void SetColor(T_UINT8 r, T_UINT8 g, T_UINT8 b)
  {
    this->color_.SetColor(r, g, b);
  }
  inline void SetColor(T_UINT8 r, T_UINT8 g, T_UINT8 b, T_UINT8 a)
  {
    this->color_.SetColor(r, g, b, a);
  }
  inline const Color& GetColor() const
  {
    return this->color_;
  }
  inline void SetRed(T_UINT8 r)
  {
    this->color_.SetRed(r);
  }
  inline T_UINT8 GetRed() const
  {
    return this->color_.GetRed();
  }
  inline void SetGreen(T_UINT8 g)
  {
    this->color_.SetGreen(g);
  }
  inline T_UINT8 GetGreen() const
  {
    return this->color_.GetGreen();
  }
  inline void SetBlue(T_UINT8 b)
  {
    this->color_.SetBlue(b);
  }
  inline T_UINT8 GetBlue() const
  {
    return this->color_.GetBlue();
  }
  inline void SetAlpha(T_UINT8 a)
  {
    this->color_.SetAlpha(a);
  }
  inline T_UINT8 GetAlpha() const
  {
    return this->color_.GetAlpha();
  }
  inline T_PACKED_COLOR_UINT32 GetPackedColor()
  {
    return this->color_.GetPackedColor();
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

  Color color_;

  GameObject2D* parent_;
  std::vector<GameObject2D*> children_;

  T_INT8 zindex_;
  bool children_zindex_dirty_;
};
